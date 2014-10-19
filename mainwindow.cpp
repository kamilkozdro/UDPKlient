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
    connect(ui->xAxisButton,SIGNAL(clicked()),this,SLOT(clickedXAxisButton()));
    connect(ui->yAxisButton,SIGNAL(clicked()),this,SLOT(clickedYAxisButton()));
    connect(ui->zAxisButton,SIGNAL(clicked()),this,SLOT(clickedZAxisButton()));
    connect(ui->lightButton,SIGNAL(clicked()),this,SLOT(clickedLightButton()));
    connect(ui->grabFrameButton,SIGNAL(clicked()),this,SLOT(clickedGrabFrameButton()));
}

mainWindow::~mainWindow()
{
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

void mainWindow::clickedXAxisButton()
{
    udpClient->setXAxis(ui->xAxisLine->text());
}

void mainWindow::clickedYAxisButton()
{
    udpClient->setYAxis(ui->yAxisLine->text());
}

void mainWindow::clickedZAxisButton()
{
    udpClient->setZAxis(ui->zAxisLine->text());
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
