#include "mainwindow.h"
#include <QToolBar>
#include <QIntValidator>
#include <QHBoxLayout>
#include <QStatusBar>


//
// Constructor and deconstructor
//
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initToolBar();

    initCentralWidget();

    initStatusBar();

    initTrackClient();
}

MainWindow::~MainWindow()
{

}

//
// Initialization functions
//
inline void MainWindow::initToolBar()
{
    QToolBar *toolBar = new QToolBar(this);

    QWidget *hBoxWidget = new QWidget(toolBar);

    //
    // Create a label and a edit for hostname
    //
    lineEditHost = new QLineEdit(hBoxWidget);

    QLabel *labelHost = new QLabel("&Host :", hBoxWidget);
    labelHost->setBuddy(lineEditHost);

    //
    // Create a label as a indent
    //
    QLabel *labelIndentA = new QLabel(hBoxWidget);

    //
    // Create a label and a edit for port
    //
    lineEditPort = new QLineEdit(hBoxWidget);
    lineEditPort->setValidator(new QIntValidator(1, 65535, lineEditPort));

    QLabel *labelPort = new QLabel("&Port :", hBoxWidget);
    labelPort->setBuddy(lineEditPort);

    //
    // Create a label as a indent
    //
    QLabel *labelIndentB = new QLabel(hBoxWidget);

    //
    // Create a connect button
    //
    pushButtonConnect = new QPushButton("&Connect", hBoxWidget);
    pushButtonConnect->setCheckable(true);

    connect(pushButtonConnect, &QPushButton::clicked,
            this, &MainWindow::onPushButtonConnectClicked);

    //
    // Add hBoxLayout for all items
    //
    QHBoxLayout *hBoxLayout = new QHBoxLayout(hBoxWidget);

    hBoxLayout->addWidget(labelHost);
    hBoxLayout->addWidget(lineEditHost);
    hBoxLayout->addWidget(labelIndentA);
    hBoxLayout->addWidget(labelPort);
    hBoxLayout->addWidget(lineEditPort);
    hBoxLayout->addWidget(labelIndentB);
    hBoxLayout->addWidget(pushButtonConnect);
    hBoxLayout->addStretch();

    //
    // Add all these things into toolbar
    //
    toolBar->addWidget(hBoxWidget);

    addToolBar(toolBar);
}

inline void MainWindow::initCentralWidget(void)
{
    mainPlotLive = new QMainPlot(this);

    setCentralWidget(mainPlotLive);
}

inline void MainWindow::initStatusBar()
{
    QStatusBar *statusBar = new QStatusBar(this);

    labelStatus = new QLabel(statusBar);
    labelStatus->setAlignment(Qt::AlignHCenter);

    labelStatus->setText("Status : Ready to plot");

    statusBar->addWidget(labelStatus);

    setStatusBar(statusBar);
}

inline void MainWindow::initTrackClient()
{
    trackClient = new QTrackClient(this);

    using SocketErrorFunc = void(QTcpSocket::*)(QAbstractSocket::SocketError);
    connect(trackClient,
            static_cast<SocketErrorFunc>(&QAbstractSocket::error),
            this,
            &onTcpSocketError);
}

//
// Button event
//
inline void MainWindow::onButtonConnectClicked()
{
    pushButtonConnect->setText("Dis&connect");

    trackClient->connectToHost(lineEditHost->text(),
                               lineEditPort->text().toInt());
}

inline void MainWindow::onButtonDisconnectClicked()
{
    trackClient->disconnectFromHost();

    pushButtonConnect->setText("&Connect");
}

void MainWindow::onPushButtonConnectClicked()
{
    if (pushButtonConnect->isChecked()) {
        onButtonConnectClicked();
    } else {
        onButtonDisconnectClicked();
    }
}

//
// Socket error event
//
void MainWindow::onTcpSocketError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error);

    labelStatus->setText("Status : " + trackClient->errorString());
}