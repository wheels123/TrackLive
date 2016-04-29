#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

#include "qmainplot.h"
#include "qtrackclient.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    inline void initToolBar(void);
    inline void initCentralWidget(void);
    inline void initStatusBar(void);
    inline void initTrackClient(void);

private:
    // Toolbar items
    QLineEdit    *lineEditHost;
    QLineEdit    *lineEditPort;
    QPushButton  *pushButtonConnect;
    // Status Bar items
    QLabel       *labelStatus;
    // Plot widget
    QMainPlot    *mainPlotLive;
    // TCP socket
    QTrackClient *trackClient;

private:
    // Button events
    inline void onButtonConnectClicked();
    inline void onButtonDisconnectClicked();
    void onPushButtonConnectClicked();
    // Socket error event
    void onTcpSocketError(QAbstractSocket::SocketError error);
};

#endif // MAINWINDOW_H