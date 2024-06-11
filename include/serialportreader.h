#ifndef SERIALPORTREADER_H
#define SERIALPORTREADER_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QJsonObject>

class SerialPortReader : public QObject
{
    Q_OBJECT

public:
    explicit SerialPortReader(QObject *parent = nullptr);
    ~SerialPortReader();

    bool openSerialPort();
    void closeSerialPort();

    bool readConfigFromFile(const QString &filePath);

    bool sendStartSignal();

    bool isSerialPortOpen() const;

signals:
    void dataReceived(const QByteArray &data);

private slots:
    void handleReadyRead();

private:
    QSerialPort *m_serialPort;
    QString m_portName;
    qint32 m_baudRate;
    QSerialPort::DataBits m_dataBits;
    QSerialPort::StopBits m_stopBits;
    QSerialPort::Parity m_parity;
    QSerialPort::FlowControl m_flowControl;
};

#endif // SERIALPORTREADER_H
