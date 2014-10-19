#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "udpclient.h"

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();

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
    UDPClient *udpClient;

};

#endif // MAINWINDOW_H

