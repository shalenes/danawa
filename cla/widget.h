#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>


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
    QTcpSocket *tcpSocket;

private slots:
    void disconnected();
    void on_pushButton_clicked();
    void connectIP();
    void on_pushButton_2_clicked();
};
#endif // WIDGET_H
