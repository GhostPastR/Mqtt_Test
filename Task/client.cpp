#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{

}

Client::Client(const ParameterClient &parameter, QObject *parent)
    : QObject(parent), parameter_(parameter)
{

}

void Client::setParameter(const ParameterClient &parameter)
{
    parameter_ = parameter;
}

void Client::run()
{
    if(!client_){
        client_ = new QMqttClient(this);

        connect(client_, &QMqttClient::stateChanged, this, &Client::updateLogStateChange);
        connect(client_, &QMqttClient::errorChanged, this, &Client::error);
    }
    client_->setHostname(parameter_.host);
    client_->setPort(parameter_.port);
    client_->setUsername(parameter_.user);
    client_->setPassword(parameter_.pass);
    client_->connectToHost();
}

void Client::updateLogStateChange()
{
    if(!client_) {
        return;
    }
    if(client_->state() == QMqttClient::ClientState::Connected){
        qDebug() << tr("Связь установлена!");
        dataTransmission(parameter_.file, parameter_.topic);
    }
}

void Client::error(const QMqttClient::ClientError &error)
{
    qDebug() << error;
    client_->disconnectFromHost();
    emit finished(); 
}

void Client::dataTransmission(QString filePath, QString topic)
{
    QFile inputFile(filePath);
    if (inputFile.open(QIODevice::ReadOnly)){
        QTextStream in(&inputFile);
        qulonglong index = 0;
        qulonglong indexp = 0;
        qDebug() << tr("Начало передачи данных!");
        while (!in.atEnd()){
            auto &&data = in.readLine();
            if (client_->publish(topic, data.toUtf8()) != -1){
                ++indexp;
            }
            ++index;
        }
        qDebug() << tr("Передача данных закончена!");
        client_->disconnectFromHost();
        emit okTransmission(indexp, index);
    }
    else{
        qDebug() << tr("Не удалось открыть файл!");
        client_->disconnectFromHost();
        emit finished();
    } 
}
