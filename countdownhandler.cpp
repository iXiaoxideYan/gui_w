#include "countdownhandler.h"


#include <QLabel>
#include <QTimer>

CountdownHandler::CountdownHandler(QLabel *countdownLabel,
                                   QObject *parent)
    : QObject(parent)
    , m_countdownLabel(countdownLabel)
{
    m_countdownTimer = new QTimer(this);
    connect(m_countdownTimer, &QTimer::timeout, this, &CountdownHandler::updateCountdown);

    // Set the horizontal alignment of the text to right justified
    m_countdownLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    // create a new font object and set the font size
    QFont font = m_countdownLabel->font();
    font.setPointSize(24);
    m_countdownLabel->setFont(font);
}

void CountdownHandler::startCountdown(int seconds)
{
    m_countdownValue = seconds;
    m_countdownLabel->setText("The remaining time: " + QString::number(m_countdownValue));
    m_countdownTimer->start(1000); // Update every second
}

void CountdownHandler::updateCountdown()
{
    m_countdownValue--;
    m_countdownLabel->setText("The remaining time: " + QString::number(m_countdownValue));

    if (m_countdownValue <= 0) {
        m_countdownTimer->stop();
        // Perform any additional actions when the countdown reaches zero
        // QMessageBox::information(this, "Countdown Finished", "The countdown has finished.");
    }
}
