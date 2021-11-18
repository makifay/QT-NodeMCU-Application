#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

#include <QUdpSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graph->xAxis->setRange(0, 100);
    ui->graph->yAxis->setRange(0, 1000);
    ui->txt_output->setTextColor(Qt::blue);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createSocket(int port )
 {
     udpSocket = new QUdpSocket(this);
     udpSocket->bind(QHostAddress::Any, port);

     connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
 }

 void MainWindow::readPendingDatagrams()
 {
     QString ret_txt = "";
     while (udpSocket->hasPendingDatagrams())
     {
         QByteArray inputData;
         inputData.resize(udpSocket->pendingDatagramSize());
         QHostAddress sender;
         quint16 senderPort;

         udpSocket->readDatagram(inputData.data(), inputData.size(),&sender, &senderPort);

         QList<QByteArray> dataArray = inputData.split(',');

         ui->txt_conn->clear();
         ui->txt_conn->setTextColor(Qt::darkGreen);
         ui->txt_conn->append(sender.toString()+ " is connected to Server");

         qDebug() << "gelen data: " ;
         qDebug() << dataArray.size();
         qDebug() << dataArray ;


         writeData(inputData);
         ret_txt = plotData(dataArray);
     }
 }

 void MainWindow::writeData(QByteArray data)
 {
     ui->txt_output->clear();
     ui->txt_output->append(data);

 }

QString MainWindow::plotData(QList<QByteArray> data)
{
    st_float temp;

    uint8_t i = 0;

    QVector<double> x(101), y(101); // data vectors
    for (int i=0; i<101; ++i)
    {
      y[i] = data[i].toDouble(); // input datas
      qDebug() << y ;
      x[i] = i; // x apsis
    }
    /// create graph and assign data to it:

    ui->graph->addGraph();
    ui->graph->graph(0)->setPen(QPen(Qt::red));
    ui->graph->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->graph->xAxis->setLabel("x");
    ui->graph->yAxis->setLabel("y");
    ui->graph->replot();

    return "";
}

void MainWindow::on_bt_start_server_clicked()
{

    if(SOCKET_STATE == 0)   //connect
    {
        int port = ui->txt_port->text().toInt();
        //QString ip =  ui->txt_ip->text();
        if(port > 0 && port < 65535)
        {
            createSocket(port );
            ui->bt_start_server->setText(_TXT_STOP_SERVER_);
            SOCKET_STATE = 1;
        }
        else
        {

        }
    }
    else
    {
        this->udpSocket->close();
        ui->bt_start_server->setText(_TXT_START_SERVER_);
        SOCKET_STATE = 0;
    }
}


