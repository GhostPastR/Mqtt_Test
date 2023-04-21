#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtMqtt/QtMqtt>

struct ParameterClient{
    QString host;
    quint32 port{};
    QString user;
    QString pass;
    QString topic;
    QString file;
};

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject *parent = nullptr);
    Client(const ParameterClient &parametr, QObject *parent = nullptr);

    void setParameter(const ParameterClient &parameter);

    void run();

signals:
    void finished();
    void errorMessage(QString message);
    void okTransmission(qulonglong indexp, qulonglong index);

private slots:
    void updateLogStateChange();
    void error(const QMqttClient::ClientError &error);

private:
    ParameterClient parameter_;
    QMqttClient *client_{};

    void dataTransmission(QString filePath, QString topic);
};

#endif // CLIENT_H
