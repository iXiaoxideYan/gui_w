#include "serialportreader.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include "jsonmanager.h"

SerialPortReader::SerialPortReader(QObject *parent)
    : QObject(parent), m_serialPort(nullptr)
{
    m_serialPort = new QSerialPort(this);
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortReader::handleReadyRead);
}

SerialPortReader::~SerialPortReader()
{
    delete m_serialPort;
}

bool SerialPortReader::openSerialPort()
{
    m_serialPort->setPortName(m_portName);
    m_serialPort->setBaudRate(m_baudRate);
    m_serialPort->setDataBits(m_dataBits);
    m_serialPort->setStopBits(m_stopBits);
    m_serialPort->setParity(m_parity);
    m_serialPort->setFlowControl(m_flowControl);

    if (!m_serialPort->open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open serial port:" << m_serialPort->portName() << m_serialPort->errorString();
        return false;
    }
    return true;
}

bool SerialPortReader::isSerialPortOpen() const {
    return m_serialPort->isOpen();
}

void SerialPortReader::closeSerialPort()
{
    if(this->isSerialPortOpen())
        m_serialPort->close();
}

bool SerialPortReader::readConfigFromFile(const QString &filePath)
{
    JsonManager jsonManager(filePath);
    if (!jsonManager.readJsonFile()) {
        qWarning() << "Failed to read JSON file:" << filePath;
        return false;
    }

    QVariantMap config = jsonManager.jsonObject().toVariantMap();
    if (!jsonManager.isJsonFileEmpty(config)) {
        return false;
    }

    m_portName = config.value("portName").toString();
    m_baudRate = config.value("baudeRate").toInt();
    m_dataBits = static_cast<QSerialPort::DataBits>(config.value("dataBits").toInt());
    m_stopBits = static_cast<QSerialPort::StopBits>(config.value("stopBits").toInt());
    m_parity = static_cast<QSerialPort::Parity>(config.value("parity").toInt());
    // m_flowControl = static_cast<QSerialPort::FlowControl>(config.value("flowControl").toInt());

    return true;
}

void SerialPortReader::handleReadyRead()
{
    QByteArray data = m_serialPort->readAll();
    emit dataReceived(data);
}

bool SerialPortReader::sendStartSignal()
{
    if (!m_serialPort || !m_serialPort->isOpen()) {
        qDebug() << "Serial port is not open.";
        return false;
    }

    // Send the start flag bit of a byte
    char startSignal = 0x01;
    qint64 bytesWritten = m_serialPort->write(&startSignal, 1);
    if (bytesWritten == -1) {
        qDebug() << "Failed to write start signal to serial port:" << m_serialPort->errorString();
        return false;
    }

    qDebug() << "Start signal sent successfully!";
    return true;
}
