#include "graphhandler.h"
#include "qcustomplot.h"

#include <QSizePolicy>

GraphHandler::GraphHandler(QCustomPlot *plot, QObject *parent)
    : QObject(parent)
    , m_plot(plot)
    , dataSmoother(5)
{
    configureGraph();
}

GraphHandler::~GraphHandler()
{
}

void GraphHandler::configureGraph()
{
    m_plot->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_plot->xAxis->setLabel("Time");
    m_plot->yAxis->setLabel("Value");
}

void GraphHandler::updateYAxisRange(double value)
{
    double maxValue = m_plot->yAxis->range().upper;
    if (value > maxValue) {
        maxValue = value;
    }
    m_plot->yAxis->setRange(0, maxValue);
}

double GraphHandler::getCurrentTimeInSeconds()
{
    return QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
}

void GraphHandler::updateXAxisRange()
{
    double currentTime = getCurrentTimeInSeconds();
    double minX = currentTime - m_displayDuration;
    double maxX = currentTime;
    m_plot->xAxis->setRange(minX, maxX);
}

void GraphHandler::ajustCoordinate(double value)
{
    updateXAxisRange();

    updateYAxisRange(value);
}

void GraphHandler::addDataToGraph(double value, double timestamp)
{
    m_plot->graph(0)->addData(timestamp, value);
}

void GraphHandler::ensureGraphExists()
{
    if (m_plot->graphCount() == 0) {
        m_plot->addGraph();
    }
}

void GraphHandler::updateGraph(double value, double timestamp)
{
    ensureGraphExists();

    addDataToGraph(value, timestamp);

    ajustCoordinate(value);

    m_plot->replot();
}

bool GraphHandler::isValidData() {
    return m_partialData == m_unvalidData;
}

bool GraphHandler::isDataComplete() const {
    return m_partialData.endsWith("\r\n");
}

void GraphHandler::restructureData(const QByteArray &data)
{
    m_partialData.append(data);
}

double GraphHandler::smoothData(double value) {
    return dataSmoother.smooth(value);
}

void GraphHandler::processReceivedData() {

    m_completeData = m_partialData;
    m_partialData.clear();

    if (isValidData()) {
        return;
    }

#ifdef DEBUG_MODE //1
    qDebug() << ">> the complete data: " + m_completeData;
#endif

    double value = byteArrayToDouble(m_completeData);

#ifdef DEBUG_MODE //1
    qDebug() << ">> the value: " + QString::number(value);
#endif

    double timestamp = getCurrentTimeInSeconds();
    double smoothedValue = smoothData(value);
    updateGraph(smoothedValue, timestamp);
}

double GraphHandler::byteArrayToDouble(const QByteArray &data) {
    bool ok;
    double value = QString(data.trimmed()).toDouble(&ok);
    if (!ok) {
        // Handle conversion error
        qWarning() << "Conversion to double failed for data:" << data;
        return 0.0; // Or another appropriate error value or handling mechanism
    }
    return value;
}

void GraphHandler::preprocessData(const QByteArray &data){
    restructureData(data);
}

void GraphHandler::handleDataReceived(const QByteArray &data)
{
    preprocessData(data);

#ifdef DEBUG_MODE //1
    qDebug() << ">> the raw data:" + data;
    qDebug() << ">> the processed data:" + m_partialData;
#endif

    if(!isDataComplete()){
        return;
    }

    processReceivedData();
}
