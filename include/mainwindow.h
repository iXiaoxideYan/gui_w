#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "countdownhandler.h"
#include "dataprocessor.h"
#include "datasmoother.h"
#include "graphhandler.h"
#include "serialportreader.h"

// #include "graphhandler.h"
#include <QLabel>
#include <QMainWindow>

// Set to one to enable debugging information, set to 0 to disable debugging information
#define DEBUG_MODE 1

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

signals:
    void serialPortClosed();

private slots:

    void handleDataReceived(const QByteArray &data);

    void updateDurationInfo(const QString &info);

    void on_start_clicked();

    void on_show_clicked();

    void on_exit_clicked();

    // void timeout();

private:
    Ui::MainWindow *ui;
    QTimer *m_countdownTimer;

    QString m_savePath;
    QString m_configFilePath;
    QString m_unvalidData = "0.00\r\n";

    QByteArray m_partialData;
    QByteArray m_completeData;
    QByteArray m_receivedData;
    QDateTime m_lastDataReceivedTime;
    QDateTime m_validDataStartTime;

    qint64 m_timeout;
    qint64 m_expectedDataSize;
    int m_countdownValue;
    double m_displayDuration = 20.0;

    DataSmoother dataSmoother;
    GraphHandler *graphHandler;
    DataProcessor *dataProcessor;
    SerialPortReader *m_reader;
    CountdownHandler *countdownHandler;

    void setupUI();
    void checkData(const QByteArray &data);
    void processData();
    bool isInvalidData();
    bool isTimeoutReached();
    bool isParticipantInfoEntered() const;
    bool isDataComplete() const;
    bool isRealTimeMode(const QString &filePath) const;

    void handleTimeout(const QByteArray &validData);
    void updateLastDataReceivedTime() {
        m_lastDataReceivedTime = QDateTime::currentDateTime();
    }
    void setValidDataTimerStart();
    void showErrorMessage();
    void restructureIncompleteData(const QByteArray &data);
    void handleRealTimeMode();
    void handleFileMode(const QString &filePath);
    void handleSerialPortClosed();

    void plotData(const QVector<double> &xData, const QVector<double> &yData);
    void saveMaxValueToFile(QByteArray &rawData);
    void saveRawDataToFile(QByteArray &rawData);
    void saveData(QByteArray completeData);

    void clearCompleteDataCache();
    void clearPartialDataCache();
    void clearCache();
    void resetLabels();
    void clearPlot();

    QString generateFilePath(const QString &prefix, const QString &suffix);
    QString getFilePath() const;
    QString getDurationTime();

    QByteArray extractValidData();
    void saveAndResetData(QByteArray completeData);
};
#endif // MAINWINDOW_H
