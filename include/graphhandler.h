#ifndef GRAPHHANDLER_H
#define GRAPHHANDLER_H

#include <QObject>
#include <QVector>

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

private:
    QCustomPlot *m_plot;
    double m_displayDuration = 20.0;
};

#endif // GRAPHHANDLER_H
