#ifndef GRAPHHANDLER_H
#define GRAPHHANDLER_H

#include "datasmoother.h"

#include <QObject>
#include <QVector>

#define DEBUG_MODE 1

class QCustomPlot;

class GraphHandler : public QObject
{
    Q_OBJECT

public:
    explicit GraphHandler(QCustomPlot *plot, QObject *parent = nullptr);
    ~GraphHandler();

    void configureGraph();
    void updateGraph(double value, double timestamp);
    void handleDataReceived(const QByteArray &data);

protected:
    void addDataToGraph(double value, double timestamp);

private:
    QCustomPlot *m_plot;
    double m_displayDuration = 20.0;
    QByteArray m_partialData;
    QByteArray m_completeData;
    QString m_terminator = "\r\n";
    QString m_unvalidData = "0.00\r\n";
    DataSmoother dataSmoother;

    void ensureGraphExists();
    void updateXAxisRange();
    void updateYAxisRange(double value);
    double getCurrentTimeInSeconds();
    void ajustCoordinate(double value);
    void preprocessData(const QByteArray &data);
    bool isDataComplete() const;
    void restructureData(const QByteArray &data);
    bool isValidData();
    double byteArrayToDouble(const QByteArray &data);
    void processReceivedData();
    double smoothData(double value);
};

#endif // GRAPHHANDLER_H
