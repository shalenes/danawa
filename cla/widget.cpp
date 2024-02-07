#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    initialize();
}

void Widget::initialize()
{
    tcpSocket = new QTcpSocket(this); //

    connect(tcpSocket, SIGNAL(readyRead()),this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(disconnected()),this,SLOT(disconnected()));
}


void Widget::connectIP()
{
    QString serverIP = "10.10.20.107";
    QString serverPort = "25000";

    QHostAddress serverAddress(serverIP);

    tcpSocket->connectToHost(serverAddress, serverPort.toUShort());
}


void Widget::on_pushButton_clicked()
{
    connectIP();
    QString a = ui->lineEdit_1->text();
    QString b = ui->lineEdit_2->text();
    QString c = ui->lineEdit_3->text();
    QString d = ui->lineEdit_4->text();
    QString e = ui->lineEdit_5->text();
    QString message = a + "," + b+ "," + c+ "," + d+ "," + e ;

    tcpSocket->write(message.toUtf8()); // 문자열을 UTF-8 형식으로 변환하여 전송
}


void Widget::disconnected()
{
    qDebug() << Q_FUNC_INFO << "서버 접속 종료.";
}







Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_2_clicked()
{
    connectIP();
    QString a = ui->lineEdit_1->text();
    QString b = ui->lineEdit_2->text();
    QString c = ui->lineEdit_3->text();
    QString d = ui->lineEdit_4->text();
    QString e = ui->lineEdit_5->text();
    QString f = ui->lineEdit_6->text();
    QString message = a + "," + b+ "," + c+ "," + d+ "," + e+ "," + f ;

    tcpSocket->write(message.toUtf8()); // 문자열을 UTF-8 형식으로 변환하여 전송

}

