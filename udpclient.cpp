#include "udpClient.h"

#define LISTEN_PORT 3032
#define COM_PORT 3031
#define SERVER_PORT 3030
#define LOCAL_ADDRESS "192.168.1.2"
#define SERVER_ADDRESS "192.168.1.2"

UDPClient::UDPClient(QObject *parent) :
    QObject(parent)
{
}

UDPClient::UDPClient(QTextBrowser *ptr, char arg[])
{
    inSocket = new QUdpSocket(this);
    outSocket = new QUdpSocket(this);
    textWindow = ptr;
    connectionStatus = false;

    if(arg = "default")
    {
        localAddress.setAddress(LOCAL_ADDRESS); // ZROB: wykryj adres w lokalnej sieci
        serverAddress.setAddress(SERVER_ADDRESS);
        listenPort = LISTEN_PORT;
        comPort = COM_PORT;
        serverPort = SERVER_PORT;
    }  
    connect(inSocket,SIGNAL(readyRead()),this,SLOT(readData()));
    listenServer();
}

UDPClient::~UDPClient()
{
    if(inSocket != NULL)
    {
        delete inSocket;
        inSocket = NULL;
    }
    if(outSocket != NULL)
    {
        delete outSocket;
        outSocket = NULL;
    }
}

void UDPClient::listenServer()
{
    if(!connectionStatus)   // jesli nie ma pozwolenia na polaczenie
    {
        inSocket->bind(localAddress,listenPort);
    }
    else                    // uzyskano pozwolenie na polaczenie
    {
        inSocket->close();
        inSocket->bind(localAddress,comPort);
    }
}

void UDPClient::writeData(char string[])
{
    QByteArray datagram = string;
    if(!connectionStatus)
    {
        //outSocket->bind(serverAddress,serverPort);
        outSocket->writeDatagram(datagram.data(),datagram.size(), serverAddress,serverPort);
    }
    else
    {
        //outSocket->bind(serverAddress,comPort);
        outSocket->writeDatagram(datagram.data(),datagram.size(),serverAddress,comPort);
    }
}

//SLOTS

void UDPClient::connectToServer()
{
    if(!connectionStatus)
    {
        writeData("query");
    }
}

void UDPClient::disconnect()
{
    if(connectionStatus)
    {
       writeData("logout");
       connectionStatus = false;
       inSocket->close();
       listenServer();
    }
}

void UDPClient::readData()
{
    QByteArray datagram;
    while (inSocket->hasPendingDatagrams())
    {
        datagram.resize(inSocket->pendingDatagramSize());
        inSocket->readDatagram(datagram.data(),datagram.size()); //,&serverAddress
        textWindow->append(datagram);
    }

    if(datagram == "Y")
    {
        connectionStatus = true;
        textWindow->append("Prosba przyjeta");
    }
    else if(datagram == "N")    textWindow->append("Prosba odrzucona");
}

void UDPClient::clickedXAxisButton()
{

}

void UDPClient::clickedYAxisButton()
{

}

void UDPClient::clickedZAxisButton()
{

}

void UDPClient::clickedLightButton()
{

}

void UDPClient::clickedGrabFrameButton()
{

}

