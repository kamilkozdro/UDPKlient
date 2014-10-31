#include "adminwindow.h"
#include "ui_adminwindow.h"

adminWindow::adminWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminWindow)
{
    ui->setupUi(this);
}

adminWindow::adminWindow(UDPClient* udp):
    ui(new Ui::adminWindow)
{
    udpClient = udp;
    ui->setupUi(this);
}

adminWindow::~adminWindow()
{
    udpClient = NULL;
    delete ui;
}
