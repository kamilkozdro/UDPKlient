#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "udpclient.h"

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    udpClient = new UDPClient(ui->comText,"default");

    connect(ui->connectButton,SIGNAL(clicked()),udpClient,SLOT(connectToServer()));
}

mainWindow::~mainWindow()
{
    delete udpClient;
    udpClient = NULL;
    delete ui;
}
