#ifndef UDPClient_H
#define UDPClient_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QTextBrowser>
#include <QFile>

#define LISTEN_PORT 0xBD8 //3032
#define COM_PORT 0xBD7 //3031
#define SERVER_PORT 0xBD6 //3030
#define LOCAL_ADDRESS "192.168.1.3"
//#define SERVER_ADDRESS "192.168.1.2"

class UDPClient : public QObject
{
    Q_OBJECT
public:
    UDPClient(QObject *parent = 0);
    // lepszy sposob na wyslanie readData do comText?
    UDPClient(QTextBrowser *ptr, quint16 ListenPort=LISTEN_PORT, quint16 ComPort=COM_PORT, quint16 ServerPort=SERVER_PORT);
    ~UDPClient();

    QUdpSocket *socket;
    QHostAddress localAddress,serverAddress;
    quint16 listenPort, serverPort, comPort;
    QTextBrowser *textWindow;
    QFile logFile;
    bool connectionStatus;

    QHostAddress whatsMyIP();
    void loadConfig();
    void listenServer();
    void writeData(char string[]);
    void writeData(QString string);
    void broadcast(char string[]);

    void connectToServer();
    void disconnect();
    void setXAxis(QString value);
    void setYAxis(QString value);
    void setZAxis(QString value);
    void grabFrame();
    void setLight(QString value);

signals:

    void connectionEstablished();
    void disconnected();

public slots:

    void readData();

};

#endif // UDPClient_H

