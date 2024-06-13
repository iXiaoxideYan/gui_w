#ifndef COUNTDOWNHANDLER_H
#define COUNTDOWNHANDLER_H

#include <QLabel>

class CountdownHandler : public QObject
{
    Q_OBJECT

public:
    explicit CountdownHandler(QLabel *countdownLabel, QObject *parent = nullptr);

    void startCountdown(int seconds = 30);

    QTimer *getCountdownTimer();

private slots:
    void updateCountdownTime();

private:
    QLabel *m_countdownLabel;
    QTimer *m_countdownTimer;
    int m_countdownValue;
    void ajustLabelSize();
};

#endif // COUNTDOWNHANDLER_H
