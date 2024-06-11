#include "graphhandler.h"
#include "qcustomplot.h"

#include <QSizePolicy>

GraphHandler::GraphHandler(QCustomPlot *plot, QObject *parent)
    : QObject(parent), m_plot(plot)
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

void GraphHandler::updateGraph(double value, double timestamp)
{
    if (m_plot->graphCount() == 0) {
        m_plot->addGraph();
    }

    m_plot->graph(0)->addData(timestamp, value);

    double currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
    double minX = currentTime - m_displayDuration;
    double maxX = currentTime;
    m_plot->xAxis->setRange(minX, maxX);

    double maxValue = m_plot->yAxis->range().upper;
    if (value > maxValue) {
        maxValue = value;
    }
    m_plot->yAxis->setRange(0, maxValue);

    m_plot->replot();
}

void GraphHandler::handleDataReceived(const QByteArray &data)
{
    QString strData = QString::fromLatin1(data).trimmed();

    // Check whether the data is invalid
    if (strData == "0.00") {
        qDebug() << "Invalid data received: " << strData;
        return;
    }

    // Find the location of the first non-zero character
    int startIndex = strData.indexOf(QRegularExpression("[^0]"));
    qDebug() << ">> startIndex:" + QString::number(startIndex);
    if (startIndex != -1) {
        strData = strData.mid(startIndex);
        if (strData == "0") {
            return;
        }
    } else {
        return;
    }

    qDebug() << ">> data:" + strData;
    bool ok;
    double value = strData.toDouble(&ok);

    // Check if a string can be converted to a valid floating point number
    if (!ok) {
        qDebug() << "Failed to parse data: " << strData;
        return;
    }

    // Get the current timestamp
    double timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;

    updateGraph(value, timestamp);
}
