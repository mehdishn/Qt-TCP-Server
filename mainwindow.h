#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QTcpServer>
#include <QTcpSocket>

using namespace std;

//default port used for TCP communication
const int default_port = 9999;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QTcpServer *server;
    QTcpSocket *socket;

private slots: // related to the TCP server
void new_tcp_connection();
void read_data_from_socket();
void handle_tcp_command(string cmd);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
