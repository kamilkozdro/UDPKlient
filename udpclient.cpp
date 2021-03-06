#include "udpClient.h"

UDPClient::UDPClient(QObject *parent) :
    QObject(parent)
{
}

UDPClient::UDPClient(QTextBrowser *ptr, quint16 ClientPort, quint16 ComPort, quint16 ServerPort)
    :clientPort(ClientPort),comPort(ComPort),serverPort(ServerPort)
{
    logFile.setFileName("A:/log.txt");
    logFile.open(QIODevice::Append);
    socket = new QUdpSocket(this);
    textWindow = ptr;
    connectionStatus = false;
    loadConfig();

    connect(socket,SIGNAL(readyRead()),this,SLOT(readData()));
}

UDPClient::~UDPClient()
{
    if(socket != NULL)
    {
        delete socket;
        socket = NULL;
    }
    logFile.close();
}

QHostAddress UDPClient::whatsMyIP()
{
    QNetworkInterface network;

    for(int i=0; i<network.allAddresses().count(); i++)
    {
        if(network.allAddresses().at(i).protocol() == QAbstractSocket::IPv4Protocol)
        {
            if(network.allAddresses().at(i).toString().contains("192.168.1"))
                return network.allAddresses().at(i);
        }
    }
    return QHostAddress::Null;
}

void UDPClient::loadConfig()
{
    /* ZAPIS KONFIGURACJI
        #Port na ktorym nasluchuje serwer
        3030
        #Port na ktorym wystepuje komunikacja serwer - zaakceptowany klient
        3031
        #Port na ktorym nasluchuje klient
        3032
        #Adres serwera
        192.168.1.2
    */
    // TYMCZASOWO DYSK A:
    QFile confFile("A:/config.txt");

    if(!confFile.open(QIODevice::ReadOnly | QIODevice::Text))  qDebug() << "Fail to read config file";
    else
    {
        QByteArray buffer;

        buffer = confFile.readLine();
        buffer = confFile.readLine();
        buffer.chop(1);
        serverPort = buffer.toUInt();
        //qDebug() << hex << serverPort;
        buffer = confFile.readLine();
        buffer = confFile.readLine();
        buffer.chop(1);
        comPort = buffer.toUInt();
        //qDebug() << hex << comPort;
        buffer = confFile.readLine();
        buffer = confFile.readLine();
        buffer.chop(1);
        clientPort = buffer.toUInt();
        //qDebug() << hex << clientPort;
        buffer = confFile.readLine();
        buffer = confFile.readLine();
        buffer.chop(1);
        if( buffer == "0")  localAddress = whatsMyIP();
        else    localAddress.setAddress(QString(buffer));
        //qDebug() << buffer;
        confFile.close();
    }
}

int UDPClient::listenServer()
{
    if(!connectionStatus)   // jesli nie ma pozwolenia na polaczenie / poczatkowe
    {
        socket->bind(localAddress,clientPort);
        if(socket->state() == socket->BoundState)
        {
            textWindow->append("Nasluchuje na LISTEN:"+QString::number(socket->localPort()));
            return 1;
        }
        else
        {
            textWindow->append("Nie nasluchuje");
            return 0;
        }
    }
    else                    // uzyskano pozwolenie na polaczenie
    {
        socket->close();
        socket->bind(localAddress,comPort);
        if(socket->state() == socket->BoundState)
        {
            textWindow->append("Nasluchuje na COM:"+QString::number(socket->localPort()));
            return 0;
        }
        else
        {
            textWindow->append("Nie nasluchuje na COM");
            return 2;
        }
    }
}

void UDPClient::writeData(char string[])
{
    QByteArray datagram = string;
    if(!connectionStatus)
    {
        socket->writeDatagram(datagram.data(),datagram.size(), serverAddress,serverPort);
        socket->waitForBytesWritten();
    }
    else
    {
        socket->writeDatagram(datagram.data(),datagram.size(),serverAddress,comPort);
        socket->waitForBytesWritten();
    }
}

void UDPClient::writeData(QString string)
{
    QByteArray datagram;
    datagram.append(string);
    if(!connectionStatus)
    {
        socket->writeDatagram(datagram.data(),datagram.size(), serverAddress,serverPort);
        socket->waitForBytesWritten();
    }
    else
    {
        socket->writeDatagram(datagram.data(),datagram.size(),serverAddress,comPort);
        socket->waitForBytesWritten();
    }
}

void UDPClient::broadcast(char string[])
{
    QByteArray datagram = string;
    socket->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,serverPort);
    socket->waitForBytesWritten();
}

// PROCEDURES - SLOTS

void UDPClient::connectToServer()
{
    listenServer();
    if(!connectionStatus)
    {
        if(serverAddress.isNull())
            broadcast("query");
        else
            writeData("query");
    }
}

void UDPClient::disconnect()
{
    if(connectionStatus)
    {
        writeData("logout");
        connectionStatus = false;
        emit disconnected();
        socket->close();
        listenServer();
    }
}
// sposob na zapis tylko obrazu do pliku?
void UDPClient::readData()
{
    QByteArray datagram;
    while (socket->hasPendingDatagrams())
    {
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(),datagram.size(),&serverAddress);
        //textWindow->append(datagram);
        //logFile.write(datagram);
    }

    if(datagram == "Y")
    {
        connectionStatus = true;
        emit connectionEstablished();
        textWindow->append("Prosba przyjeta");
        listenServer();
    }
    else if(datagram == "N")
        textWindow->append("Prosba odrzucona");
    else if( (datagram[0] == 'P') && (datagram[1] == '5'))
    {
        QFile image("image.pgm");
        textWindow->append("Odebrano obraz");
        if(!image.open(QIODevice::WriteOnly | QIODevice::Text))
            textWindow->append("Nie utworzono pliku obrazu");
        else
        {
            image.write(datagram);
            image.waitForBytesWritten(3000);    // potrzebne?
            image.close();
        }
    }
}

void UDPClient::movePlatform(QString value)
{
    if(connectionStatus)
    {
        writeData(value);
    }
}

void UDPClient::setLight(QString value)
{
    if(connectionStatus)
    {
        writeData(QString("setLight = ")+value);
    }
}

void UDPClient::grabFrame()
{
    if(connectionStatus)
    {
        writeData("grabFrame");
    }
}

