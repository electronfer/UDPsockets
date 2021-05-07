#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Node 2 Qt");

    this->setGeometry(578,50,278,272);

    udpsocket = new QUdpSocket(this);
    udpsocket->bind(LOCAL_ADDR,LOCAL_PORT);

    ui->plainTextEdit->setReadOnly(true);

    ui->plainTextEdit->setPlainText("Enter the IP address and port of the connection pair, separated by a comma, and click connect:");
    ui->plainTextEdit->appendPlainText("My address is: " + QHostAddress(LOCAL_ADDR).toString());
    ui->plainTextEdit->appendPlainText("My port is: " + QString("%1").arg(LOCAL_PORT));

    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(on_bSend_clicked()));
    connect(udpsocket,SIGNAL(readyRead()),this,SLOT(readInformationReceived()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readInformationReceived()
{
    while (udpsocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(static_cast<int>( udpsocket->pendingDatagramSize()));

        udpsocket->readDatagram(datagram.data(), datagram.size(),
                                &PairAddr, &PairPort);

        ui->plainTextEdit->appendPlainText(QString(datagram + " [" + PairAddr.toString() + ", %1]").arg(PairPort));
    }
}


void MainWindow::on_bConnect_clicked()
{
    PairAddr = QHostAddress( ui->lineEdit->text().section(',',0,0) );

    PairPort = static_cast<quint16>( ui->lineEdit->text().section(',',1,1).toInt() );

    ui->labAddr->setText( QHostAddress(LOCAL_ADDR).toString() );
    ui->labPort->setText( QString("%1").arg(LOCAL_PORT) );

    ui->lineEdit->clear();
    ui->plainTextEdit->clear();

    ui->plainTextEdit->setPlainText("Write text and clic Send\n");
}

void MainWindow::on_bSend_clicked()
{
    udpsocket->writeDatagram(ui->lineEdit->text().toLatin1(),PairAddr,PairPort);
    ui->lineEdit->clear();
}
