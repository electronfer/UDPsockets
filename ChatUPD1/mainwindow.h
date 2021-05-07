#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostAddress>
#include <QUdpSocket>
#include <QVector>

//MACROS
#define LOCAL_ADDR QHostAddress::LocalHost
#define LOCAL_PORT 1234

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void readInformationReceived();

private slots:
    void on_bConnect_clicked();

    void on_bSend_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *udpsocket;
    QHostAddress PairAddr;
    quint16 PairPort;
};
#endif // MAINWINDOW_H
