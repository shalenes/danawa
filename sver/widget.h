#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    void initialize();
    QTcpServer *tcpServer;
    QVector<QString> clnt;



private slots:
    void newConnection();
    void readyRead();
    void readyRead1( );
    void readyRead2( );

};
#endif // WIDGET_H
