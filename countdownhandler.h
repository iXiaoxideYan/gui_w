#ifndef COUNTDOWNHANDLER_H
#define COUNTDOWNHANDLER_H

#include <QLabel>

class CountdownHandler : public QObject
{
    Q_OBJECT

public:
    explicit CountdownHandler(QLabel *countdownLabel, QObject *parent = nullptr);

    void startCountdown(int seconds);

private slots:
    void updateCountdown();

private:
    QLabel *m_countdownLabel;
    QTimer *m_countdownTimer;
    int m_countdownValue;
};

#endif // COUNTDOWNHANDLER_H
