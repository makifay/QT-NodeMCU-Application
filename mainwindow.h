#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

class QUdpSocket;

#define _TXT_START_SERVER_ "Start"
#define _TXT_STOP_SERVER_ "Stop"


#define _LINE_TEMP_ 0
#define _LINE_HUMI_ 1

#define _DOT_TEMP_ 2
#define _DOT_HUMI_ 3

typedef union {
    float f1;
    uint8_t fdata[4];
}st_float;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void readPendingDatagrams();
    void on_bt_start_server_clicked();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int SOCKET_STATE;
    QUdpSocket *udpSocket;



    void createSocket(int port );
    QString plotData(QList<QByteArray> data);
    void writeData(QByteArray data);

    void graph_data_update(QCustomPlot *customPlot,float temp);
    void setupRealtimeDataDemo(QCustomPlot *customPlot);
};

#endif // MAINWINDOW_H
