#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QFileDialog>
#include "client.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->lineEditHost->setText("test.mosquitto.org");
    ui->spinBoxPort->setValue(1883);
    ui->lineEditTopic->setText("piklema/test");
}

Widget::~Widget()
{
    if(client_){
        client_->deleteLater();
    }
    if(!thread_.wait(1000))
    {
        thread_.terminate();
        thread_.wait();
    }
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    client_ = new Client();
    connect(&thread_, &QThread::started, client_, &Client::run);
    connect(client_, &Client::finished, &thread_, &QThread::quit);

    connect(client_, &Client::finished, this, &Widget::finished);
    connect(client_, &Client::okTransmission, this, &Widget::okTransmissionSlot);
    client_->moveToThread(&thread_);

    client_->setParameter({ui->lineEditHost->text(),
                           static_cast<quint32>(ui->spinBoxPort->value()),
                           ui->lineEditUsername->text(),
                           ui->lineEditPassword->text(),
                           ui->lineEditTopic->text(),
                           ui->lineEditFilepath->text()
                          });

    thread_.start();
}

void Widget::on_pushButtonFile_clicked()
{
    ui->lineEditFilepath->setText(QFileDialog::getOpenFileName(this, tr("Файл")));
}

void Widget::finished()
{
    if(client_){
        client_->deleteLater();
    }
    thread_.quit();
    thread_.wait();
    ui->pushButton->setEnabled(true);
}

void Widget::okTransmissionSlot(qulonglong indexp, qulonglong index)
{
    QString str = tr("Статистика: ") + QString::number(indexp) + "/" + QString::number(index)
            + tr("(передано строк/общие количество)");
    QMessageBox::information(this, tr("Статистика"), str);
    if(client_){
        client_->deleteLater();
    }
    thread_.quit();
    thread_.wait();
    ui->pushButton->setEnabled(true);
}
