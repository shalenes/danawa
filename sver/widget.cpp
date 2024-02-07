#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QSqlDatabase mydb = QSqlDatabase :: addDatabase("QSQLITE"); //생성자가 호출되있을 때 데이터 베이스 연결
    mydb.setDatabaseName("C:/Users/user/Desktop/QT/data_base");

    if(!mydb.open())
        ui->label->setText("fail datebase");
    else{
        ui->label->setText("connect");
    }


    initialize();

}
void Widget::initialize()
{
    QHostAddress hostAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses(); //현재 시스템의 ip주소를 가져온다
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            hostAddress = ipAddressesList.at(i);
            break;
        }
    }

    if (hostAddress.toString().isEmpty())
        hostAddress = QHostAddress(QHostAddress::LocalHost);

    tcpServer = new QTcpServer(this); //QTcpserver 객체를 생성
    if (!tcpServer->listen(hostAddress, 25000)) { //포트 번호가 25000가 아닐때
        QMessageBox::critical(this, tr("TCP Server"),
                              tr("서버를 시작할 수 없습니다. 에러메세지 : %1.")
                                  .arg(tcpServer->errorString()));
        close();
    }

    ui->labelStatus->setText(tr("서버 동작 중 \n\n" // \n은 엔터  //아이피 번호랑 포트번호 표시
                                "IP : %1\n"
                                "PORT : %2\n")
                                 .arg(hostAddress.toString())
                                 .arg(tcpServer->serverPort()));
    //여기까지 서버가 열리면 되는 것

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection())); //클라이언트가 더 연결되면?

}

void Widget::newConnection()
{
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection(); //QTcpSocket 생성하면서 새로운 클라이언트 연결 수락
    connect(clientConnection, SIGNAL(disconnected()), clientConnection, SLOT(deleteLater()));
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Widget::readyRead() {

    QTcpSocket *new_socket = static_cast<QTcpSocket*>(sender());
    QByteArray readData = new_socket -> readAll();
    QString message = QString::fromUtf8(readData);
    ui -> connMsgEdit -> append(message);

    clnt = message.split(",");

    if(clnt[0]=="1"){
        readyRead1();
    }
    else
        readyRead2();


}

void Widget::readyRead1() {

    // clnt = message.split(",");
    ui -> label_2 ->setText(clnt[1]);
    ui -> label_3 ->setText(clnt[2]);
    ui -> label_4 ->setText(clnt[3]);
    ui -> label_5 ->setText(clnt[4]);
    ui -> label_6 ->setText(clnt[5]);

    // QSqlQuery query;
    // query.prepare("INSERT INTO user_info (name, id, pw, phone, e_mail) VALUES (:name, :id, :pw, :phone, :e_mail)");
    // query.bindValue(":name", clnt[0]);
    // query.bindValue(":id", clnt[1]);
    // query.bindValue(":pw", clnt[2]);
    // query.bindValue(":phone", clnt[3]);
    // query.bindValue(":e_mail", clnt[4]);
    // query.exec();
}



void Widget::readyRead2( ) {

    // QTcpSocket *new_socket = static_cast<QTcpSocket*>(sender());
    // QByteArray readData = new_socket -> readAll();
    // message = QString::fromUtf8(readData);
    // ui -> connMsgEdit -> append(message);

    // clnt = message.split(",");
    ui -> label_7 ->setText(clnt[1]);
    ui -> label_8 ->setText(clnt[2]);
    ui -> label_9 ->setText(clnt[3]);
    ui -> label_10 ->setText(clnt[4]);
    ui -> label_11 ->setText(clnt[5]);
}
Widget::~Widget()
{
    delete ui;
}
