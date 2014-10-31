#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "udpclient.h"

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    udpClient = new UDPClient(ui->comText);

    connect(ui->connectButton,SIGNAL(clicked()),this,SLOT(clickedConnectButton()));
    connect(ui->disconnectButton,SIGNAL(clicked()),this,SLOT(clickedDisconnectButton()));
    connect(udpClient,SIGNAL(connectionEstablished()),this,SLOT(enableDisconnectButton()));
    connect(udpClient,SIGNAL(disconnected()),this,SLOT(enableConnectButton()));
    connect(ui->movePlatformButton,SIGNAL(clicked()),this,SLOT(clickedMovePlatformButton()));
    connect(ui->lightButton,SIGNAL(clicked()),this,SLOT(clickedLightButton()));
    connect(ui->grabFrameButton,SIGNAL(clicked()),this,SLOT(clickedGrabFrameButton()));
}

mainWindow::mainWindow(char argv[]):
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    udpClient = new UDPClient(ui->comText);
    if(!strcmp(argv,"-admin"))
        adminWin = new adminWindow(udpClient);

    connect(ui->connectButton,SIGNAL(clicked()),this,SLOT(clickedConnectButton()));
    connect(ui->disconnectButton,SIGNAL(clicked()),this,SLOT(clickedDisconnectButton()));
    connect(udpClient,SIGNAL(connectionEstablished()),this,SLOT(enableDisconnectButton()));
    connect(udpClient,SIGNAL(disconnected()),this,SLOT(enableConnectButton()));
    connect(ui->movePlatformButton,SIGNAL(clicked()),this,SLOT(clickedMovePlatformButton()));
    connect(ui->lightButton,SIGNAL(clicked()),this,SLOT(clickedLightButton()));
    connect(ui->grabFrameButton,SIGNAL(clicked()),this,SLOT(clickedGrabFrameButton()));

    adminWin->show();
}

mainWindow::~mainWindow()
{
    if(adminWin != NULL)
    {
        delete adminWin;
        adminWin = NULL;
    }
    delete udpClient;
    udpClient = NULL;
    delete ui;
}

    // SLOTS

void mainWindow::clickedConnectButton()
{
    udpClient->connectToServer();
}

void mainWindow::clickedDisconnectButton()
{
    udpClient->disconnect();
}

void mainWindow::clickedMovePlatformButton()
{
    udpClient->movePlatform(ui->xAxisLine->text()+ui->yAxisLine->text()+ui->zAxisLine->text());
}

void mainWindow::clickedLightButton()
{
    udpClient->setLight(ui->lightLine->text());
}

void mainWindow::clickedGrabFrameButton()
{
    udpClient->grabFrame();
}

void mainWindow::enableDisconnectButton()
{
    ui->connectButton->setDisabled(true);
    ui->disconnectButton->setDisabled(false);
}

void mainWindow::enableConnectButton()
{
    ui->connectButton->setDisabled(false);
    ui->disconnectButton->setDisabled(true);
}
