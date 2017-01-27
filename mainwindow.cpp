#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(new_tcp_connection()));
    if(!server->listen(QHostAddress::Any, default_port))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started!";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::new_tcp_connection()
{
    // need to grab the socket
    socket = server->nextPendingConnection();
    socket->setReadBufferSize(512);
    connect(socket, SIGNAL(readyRead()), SLOT(read_data_from_socket()));
}

void MainWindow::read_data_from_socket()
{
    QByteArray data;
    string str_data;

    if (socket->bytesAvailable())
    {
        data = socket->readAll();
        str_data = data.constData();
        qDebug() << "Incoming socket data: " << data;

        socket->write("Got it.");   // or write something back based on the received msg
        socket->flush();
        socket->waitForBytesWritten(50);
        socket->close();    // closing the socket manually to avoid memory leaks

        handle_tcp_command(str_data);   // pass the msg
    }
    else
    {
        socket->write("could not receive data");
        socket->flush();
        socket->waitForBytesWritten(50);
        socket->close();
    }
}

void MainWindow::handle_tcp_command(string cmd)
{
    // you can do anything you want in this function based on the given msg
}
