#ifndef UDPClient_H
#define UDPClient_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QTextBrowser>

class UDPClient : public QObject
{
    Q_OBJECT
public:
    UDPClient(QObject *parent = 0);
    UDPClient(QTextBrowser *ptr,char arg[]);    // lepszy sposob na wyslanie readData do comText?
    ~UDPClient();

    QUdpSocket *inSocket, *outSocket;
    QHostAddress localAddress,serverAddress;
    quint16 listenPort, serverPort, comPort;
    QTextBrowser *textWindow;
    bool connectionStatus;

    void listenServer();
    void writeData(char string[]);

signals:

public slots:

    void connectToServer();
    void disconnect();
    void readData();
    void clickedXAxisButton();
    void clickedYAxisButton();
    void clickedZAxisButton();
    void clickedLightButton();
    void clickedGrabFrameButton();
};

#endif // UDPClient_H

