#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QString>
#include "udpclient.h"

namespace Ui {
class adminWindow;
}

class adminWindow : public QWidget
{
    Q_OBJECT

public:
    explicit adminWindow(QWidget *parent = 0);
    adminWindow(UDPClient* udp);
    ~adminWindow();

    UDPClient* udpClient;
 /*   QString getServerConfig();
    void setServerListenPort(char port[]);
    void setComPort(char port[]);
    void setClientListenPort(char port[]);
    void setServerAddress(char address[]);
*/
private:
    Ui::adminWindow *ui;
};

#endif // ADMINWINDOW_H
