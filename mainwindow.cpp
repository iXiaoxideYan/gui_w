#include "mainwindow.h"
#include "file.h"
#include "dataprocess.h"
#include "ui_mainwindow.h"
#include "jsonmanager.h"
#include <QIntValidator>
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dataSmoother(5)
{
    ui->setupUi(this);
    setupUI();
    configureGraph();

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::timeout);

    m_countdownTimer = new QTimer(this);
    connect(m_countdownTimer, &QTimer::timeout, this, &MainWindow::updateCountdown);

    m_unvalidData = "0.00\r\n";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    ui->auto_complete->setChecked(true);
    ui->line_trial->setValidator(new QIntValidator(0, 9999, this));
    ui->Page->setTabPosition(QTabWidget::West);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(ui->show);
    layout->addWidget(ui->backdrop);
    layout->setAlignment(ui->show, Qt::AlignHCenter | Qt::AlignVCenter);
    layout->setAlignment(ui->backdrop, Qt::AlignHCenter | Qt::AlignVCenter);

    ui->m_countdownLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    // Create a new font object and set the font size
    QFont font = ui->m_countdownLabel->font();
    font.setPointSize(24);
    ui->m_countdownLabel->setFont(font);
}

void MainWindow::configureGraph()
{
    ui->backdrop->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->backdrop->xAxis->setLabel("Time");
    ui->backdrop->yAxis->setLabel("Value");
}

void MainWindow::setConfigFilePath(const QString &filePath)
{
    this->m_configFilePath = filePath;
    JsonManager jsonManager(this->m_configFilePath);
    if (!jsonManager.readJsonFile()) {
        qWarning() << "Failed to read JSON file:" << filePath;
        return;
    }

    QVariantMap config = jsonManager.jsonObject().toVariantMap();
    if (!jsonManager.isJsonFileEmpty(config)) {
        return;
    }

    m_timeout = config.value("timeOut").toInt();
    m_expectedDataSize = config.value("expectedDataSize").toInt();;
    m_savePath = config.value("savePath").toString();
}

void MainWindow::on_start_clicked()
{
    if(!this->m_reader->isSerialPortOpen()){
        if(this->m_reader->openSerialPort()){
            qWarning() << "Failed to open serial port, Please check the config file.";
            return;
        }
    }

    connect(m_reader, &SerialPortReader::dataReceived, this, &MainWindow::handleDataReceived);

    // this->m_reader->sendStartSignal();
}

void MainWindow::setSerialPortReader(SerialPortReader *reader)
{
    m_reader = reader;
}

void MainWindow::startCountdown(int seconds)
{
    m_countdownValue = seconds;
    ui->m_countdownLabel->setText("The remaining time: " + QString::number(m_countdownValue));
    m_countdownTimer->start(1000); // Update every second
}

void MainWindow::updateCountdown()
{
    m_countdownValue--;
    ui->m_countdownLabel->setText("The remaining time: " + QString::number(m_countdownValue));

    if (m_countdownValue <= 0) {
        m_countdownTimer->stop();
        // Perform any additional actions when the countdown reaches zero
        // QMessageBox::information(this, "Countdown Finished", "The countdown has finished.");
        ui->m_countdownLabel->setText("Countdown Finished.");
    }
}

void MainWindow::handleDataReceived(const QByteArray &data){
    // Check if participant code is entered
    if(ui->line_code->text().isEmpty()){
        QMessageBox::critical(this, "Warning of errors", tr("Participant code is mandatory"));
        return;
    }

    // Check if trial number is entered
    if(ui->line_trial->text().isEmpty()){
        QMessageBox::critical(this, "Warning of errors", tr("trial is mandatory"));
        return;
    }

    m_receivedData.append(data);
    qDebug() << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> The new round: ";
    qDebug() << m_receivedData;
    qDebug() << ">> Data size: " + QString::number(data.size());
    qDebug() << m_receivedData.size();

    int startIndex = m_receivedData.lastIndexOf("0.00\r\n");
    qDebug() << "startIndex: " + QString::number(startIndex);

    if (startIndex != -1) {
        // Check if it's a single occurrence at the beginning or near the end
        if (startIndex == 0) {
            // Update last data received time and continue waiting
            m_lastDataReceivedTime = QDateTime::currentDateTime();
        }
    }else {
        return;
    }

    if (!m_countdownTimer->isActive()) {
        // Start the countdown only if it's not already running
        startCountdown(30); // Start the countdown for 10 seconds, for example
    }

    QByteArray validData;
    if (startIndex > 12){
        validData = m_receivedData;
    }else{
        validData = m_receivedData.mid(startIndex);
    }

    qDebug() << "Valid data: " << validData;
    qDebug() << "The size of validData: " + QString::number(validData.size());

    if (startIndex == 6) {
        // Update last data received time and continue waiting
        m_validDataStartTime = QDateTime::currentDateTime();
    }

    m_receivedData.clear();
    m_receivedData.append(validData);


    if (startIndex != 0 && m_receivedData.size() >= m_expectedDataSize &&
        QDateTime::currentDateTime().toMSecsSinceEpoch() - m_lastDataReceivedTime.toMSecsSinceEpoch() >= m_timeout) {

        QByteArray completeData = validData.left(6);

        qDebug() << ">>**************************************** Finished!";

        double maxValue = getMaxValueFromByteArray(completeData);

        QString csvFile = this->m_savePath + "/max_" + ui->line_code->text() + "_" + ui->line_trial->text() + ".csv";
        saveCSV(csvFile, QString::number(maxValue));

        QAbstractButton *button = ui->button_group->checkedButton();
        if(button->text() == ui->auto_complete->text()){
            int trial_num = ui->line_trial->text().toInt();
            qDebug() << QString::number(trial_num).toLatin1();
            ui->line_trial->setText(QString::number(trial_num + 1));
        } else {
            // reset all the input
            ui->line_trial->clear();
            ui->line_code->clear();
        }

        // Measure and log the time duration of the valid data processing
        QDateTime endTime = QDateTime::currentDateTime();
        qint64 duration = m_validDataStartTime.msecsTo(endTime);
        QString durationInfo = "Duration of the valid data processing: " + QString::number(duration) + " ms";
        qDebug() << durationInfo;
        updateDurationInfo(durationInfo);

        m_receivedData.clear();
        m_lastDataReceivedTime = QDateTime::currentDateTime();
    }
}

void MainWindow::on_show_clicked()
{
    ui->backdrop->clearPlottables();

    // Get the file path entered by the user
    QString filePath = ui->filepath->text();

    // If the user does not enter the file path, use the default path
    if (filePath.isEmpty()) {
        // filePath = "./data.txt";

        if(!this->m_reader->isSerialPortOpen()){
            if(this->m_reader->openSerialPort()){
                qWarning() << "Failed to open serial port, Please check the config file.";
                return;
            }
        }

        connect(m_reader, &SerialPortReader::dataReceived, this, &MainWindow::handleDisplayRealTimeData);

        return;
    }

    if (!checkFile(filePath)) {
        QMessageBox::critical(this, "Tips", tr("Cannot find the file you enter"));
        ui->backdrop->replot();
        return;
    }

    QVector<double> yData = readFileData(filePath);

    if(yData.empty()){
        qWarning() << "Cannot find the data file. ";
        return;
    }

    qDebug() << yData.length();
    QVector<double> xData;
    for (int i = 0; i < yData.size(); ++i)
        xData.push_back(i);

    ui->backdrop->addGraph();
    ui->backdrop->graph(0)->setData(xData, yData);

    ui->backdrop->xAxis->setRange(xData.first(), xData.last());
    ui->backdrop->yAxis->setRange(*std::min_element(yData.constBegin(), yData.constEnd()), *std::max_element(yData.constBegin(), yData.constEnd()));

    ui->backdrop->replot();
}

void MainWindow::timeout()
{
    if (QDateTime::currentDateTime().toMSecsSinceEpoch() - m_lastDataReceivedTime.toMSecsSinceEpoch() >= m_timeout &&
        m_receivedData.size() >= m_expectedDataSize) {
        qDebug() << ">> timeout!";
        m_receivedData.clear();
    }
}

void MainWindow::updateDurationInfo(const QString &info) {
    ui->label_duration->setText(info);
}

void MainWindow::updateGraph(double &value, double &timestamp) {
    // If there is no graphic object in the chart, add a
    if (ui->backdrop->graphCount() == 0) {
        ui->backdrop->addGraph();
    }
    // Add new data points to the chart
    ui->backdrop->graph(0)->addData(timestamp, value);

    // Get the current time
    double currentTime =
        QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;

    // Set the X-axis range
    double minX = currentTime - m_displayDuration;
    double maxX = currentTime;
    ui->backdrop->xAxis->setRange(minX, maxX);

    // Get the maximum value of the Y-axis
    double maxValue = ui->backdrop->yAxis->range().upper;

    // Update the Y-axis range to adapt to the new data
    if (value > maxValue) {
        maxValue = value;
    }
    ui->backdrop->yAxis->setRange(0, maxValue);

    // Redraw the chart
    ui->backdrop->replot();
}

void MainWindow::handleDisplayRealTimeData(const QByteArray &data) {
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

    // Check whether the string can be converted to a valid floating-point number
    if (!ok) {
        qDebug() << "Failed to parse data: " << strData;
        return;
    }

    // Smooth the data
    double smoothedValue = dataSmoother.smooth(value);

    // Get the current timestamp
    double timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;

    updateGraph(smoothedValue, timestamp);

    // graphHandler.handleDataReceived(data);
    // QByteArray trimmedData = data.trimmed();

    // qDebug() << trimmedData;

    // bool ok;
    // double value = trimmedData.toDouble(&ok);

    // if (ok) {
    //     double timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch() /
    //     1000.0;

    //     if (ui->backdrop->graphCount() == 0) {
    //         ui->backdrop->addGraph();
    //     }

    //     ui->backdrop->graph(0)->addData(timestamp, value);

    //     double currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch() /
    //     1000.0;

    //     double minX = currentTime - m_displayDuration;
    //     double maxX = currentTime;
    //     ui->backdrop->xAxis->setRange(minX, maxX);
    //     ui->backdrop->yAxis->rescale(true);
    //     ui->backdrop->replot();
    // } else {
    //     qDebug() << "Failed to parse data: " << trimmedData;
    // }
}

void MainWindow::on_exit_clicked()
{
    disconnect(m_reader, &SerialPortReader::dataReceived, this, &MainWindow::handleDisplayRealTimeData);

    ui->backdrop->clearPlottables();
    ui->backdrop->replot();
}
