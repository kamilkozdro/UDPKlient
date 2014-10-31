#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "udpclient.h"
#include "adminwindow.h"
#include <string.h>

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = 0);
    mainWindow(char argv[]);
    ~mainWindow();

    UDPClient *udpClient;
    adminWindow* adminWin;

private slots:

    void clickedConnectButton();
    void clickedDisconnectButton();
    void clickedXAxisButton();
    void clickedYAxisButton();
    void clickedZAxisButton();
    void clickedLightButton();
    void clickedGrabFrameButton();

    void enableDisconnectButton();
    void enableConnectButton();

private:
    Ui::mainWindow *ui;

};

#endif // MAINWINDOW_H

