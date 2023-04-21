#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QMqttClient;
class Client;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void on_pushButtonFile_clicked();

    void finished();
    void okTransmissionSlot(qulonglong indexp, qulonglong index);

private:
    Ui::Widget *ui;
    Client *client_;
    QThread thread_;
};
#endif // WIDGET_H
