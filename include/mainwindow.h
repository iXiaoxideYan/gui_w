#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "countdownhandler.h"
#include "datasmoother.h"
#include "graphhandler.h"
#include "serialportreader.h"

// #include "graphhandler.h"
#include <QLabel>
#include <QMainWindow>

// Set to one to enable debugging information, set to 0 to disable debugging information
// #define DEBUG_MODE 1

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void setConfigFilePath(const QString &filePath);

    void setSerialPortReader(SerialPortReader *reader);

    void readSerialData();

private slots:

    void handleDataReceived(const QByteArray &data);

    void updateDurationInfo(const QString &info);

    void on_start_clicked();

    void on_show_clicked();

    void on_exit_clicked();

    void timeout();

private:
    Ui::MainWindow *ui;
    QString m_configFilePath;
    QByteArray m_partialData;
    QByteArray m_completeData;
    SerialPortReader *m_reader;
    QByteArray m_receivedData;
    QDateTime m_lastDataReceivedTime;
    qint64 m_timeout;
    QString m_savePath;
    QTimer *m_timer;
    qint64 m_expectedDataSize;
    QString m_unvalidData = "0.00\r\n";
    QDateTime m_validDataStartTime;
    double m_displayDuration = 20.0;
    DataSmoother dataSmoother;
    GraphHandler *graphHandler;
    CountdownHandler *countdownHandler;
    QTimer *m_countdownTimer;
    int m_countdownValue;

    void setupUI();
    // void configureGraph();
    void checkData(const QByteArray &data);
    void processData();
    bool isInvalidData();
    bool isTimeoutReached(const QByteArray &validData);
    void handleTimeout(const QByteArray &validData);
    QByteArray extractValidData();
    void updateLastDataReceivedTime() {
        m_lastDataReceivedTime = QDateTime::currentDateTime();
    }
    void setValidDataTimerStart();
    void showErrorMessage();
    bool isParticipantInfoEntered() const;
    bool isDataComplete() const;
    void restructureIncompleteData(const QByteArray &data);
    void clearPlot();
    QString getFilePath() const;
    bool isRealTimeMode(const QString &filePath) const;
    void handleRealTimeMode();
    void handleFileMode(const QString &filePath);
    void plotData(const QVector<double> &xData, const QVector<double> &yData);
};
#endif // MAINWINDOW_H
