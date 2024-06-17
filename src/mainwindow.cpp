#include "mainwindow.h"
#include "file.h"
#include "dataprocessor.h"
#include "ui_mainwindow.h"
#include "jsonmanager.h"
#include <QIntValidator>
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_timeout(10)
    , dataSmoother(5)
    , graphHandler(nullptr)
    , dataProcessor()
    , countdownHandler(nullptr)
{
    ui->setupUi(this);
    setupUI();

    countdownHandler = new CountdownHandler(ui->m_countdownLabel, this);
    graphHandler = new GraphHandler(ui->backdrop, this);
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
    connect(m_reader, &SerialPortReader::portClosed, this, &MainWindow::handleSerialPortClosed);

    // this->m_reader->sendStartSignal();
}

void MainWindow::setSerialPortReader(SerialPortReader *reader)
{
    m_reader = reader;
}

QString MainWindow::generateFilePath(const QString &prefix, const QString &suffix) {
    auto placeholder = ui->line_code->text() + "_" + ui->line_trial->text();
    QString dirPath = m_savePath + "/" + placeholder;
#ifdef DEBUG_MODE //1
    qDebug() << "The file path: " + dirPath;
#endif
    // Ensure the directory exists
    checkDir(dirPath);

    return dirPath + "/" + prefix + "_" + placeholder + suffix;
}

void MainWindow::saveMaxValueToFile(QByteArray &rawData)
{
    double maxValue = dataProcessor->getMaxValueFromByteArray(rawData);

    QString csvFile = generateFilePath("max_value", ".csv");

    saveCSV(csvFile, QString::number(maxValue));
}

void MainWindow::saveRawDataToFile(QByteArray &rawData)
{
    QList<QByteArray> raw = dataProcessor->getRawData(rawData);

    QString csvFile = generateFilePath("raw_data", ".csv");
    saveListToCSV(raw, csvFile);
}

void MainWindow::saveData(QByteArray validData)
{
    QAbstractButton *button = ui->button_group->checkedButton();

    saveRawDataToFile(validData);

    saveMaxValueToFile(validData);
}

void MainWindow::resetLabels()
{
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
}

QString MainWindow::getDurationTime()
{
    QDateTime endTime = QDateTime::currentDateTime();
    qint64 duration = m_validDataStartTime.msecsTo(endTime);
    QString durationInfo = "Duration of the valid data processing: " + QString::number(duration) + " ms";

    return durationInfo;
}

bool MainWindow::isTimeoutReached() {

#ifdef DEBUG_MODE //1
    qDebug() << ">> Diff: " + QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch() - m_lastDataReceivedTime.toMSecsSinceEpoch());
#endif

    return (QDateTime::currentDateTime().toMSecsSinceEpoch() - m_lastDataReceivedTime.toMSecsSinceEpoch() >= m_timeout && m_completeData == m_unvalidData);
}

QByteArray MainWindow::extractValidData() {
    QByteArray validData;

#ifdef DEBUG_MODE //1
    qDebug() << ">> m_receivedData: " + m_receivedData;
    qDebug() << ">> m_receivedData.length(): " + QString::number(m_receivedData.length());
#endif

    if (m_receivedData.length() > m_expectedDataSize){
        validData = m_receivedData;
        updateLastDataReceivedTime();
    }
    return validData;
}

void MainWindow::setValidDataTimerStart()
{
    m_validDataStartTime = QDateTime::currentDateTime();
}

void MainWindow::saveAndResetData(QByteArray completeData)
{
    saveData(completeData);

    resetLabels();

    // Measure and log the time duration of the valid data processing
    QString durationInfo = getDurationTime();

#ifdef DEBUG_MODE //1
    qDebug() << durationInfo;
#endif

    updateDurationInfo(durationInfo);

    clearCache();
}

void MainWindow::handleTimeout(const QByteArray &validData) {
    QByteArray completeData = validData;

#ifdef DEBUG_MODE //1
    qDebug() << ">>**************************************** Finished!";
#endif

    saveAndResetData(completeData);
    m_lastDataReceivedTime = QDateTime::currentDateTime();
}

bool MainWindow::isInvalidData() {
    return m_completeData == m_unvalidData;
}

void MainWindow::processData()
{
    if(isInvalidData()){
        if (m_receivedData.length() < m_expectedDataSize){
            setValidDataTimerStart();
        }
        if(dataProcessor->areAllValuesZero(m_receivedData)){
            clearCompleteDataCache();
            return;
        }
        if (m_receivedData.length() > m_expectedDataSize && isTimeoutReached()){
            handleTimeout(m_receivedData);
        }
        return;
    }

    m_receivedData.append(m_completeData);
    QByteArray validData = extractValidData();

#ifdef DEBUG_MODE // 1
    qDebug() << "validData: " + validData;
#endif

    if (validData.isEmpty()) {
        return;
    }

    if (!countdownHandler->getCountdownTimer()->isActive()) {
        // Start the countdown only if it's not already running
        countdownHandler->startCountdown();
    }

    clearCompleteDataCache();
    m_receivedData.append(validData);

#ifdef DEBUG_MODE
    qDebug() << "m_receivedData: " + m_receivedData;
#endif
}

bool MainWindow::isDataComplete() const {
    return m_partialData.endsWith("\r\n");
}

void MainWindow::restructureIncompleteData(const QByteArray &data) {
    if (!m_partialData.isEmpty()) {
        m_partialData.append(data);
    } else {
        m_partialData = data;
    }
}

void MainWindow::showErrorMessage()
{
    QMessageBox::critical(this, "Warning of errors", tr("Participant code and trial number are mandatory"));
}

bool MainWindow::isParticipantInfoEntered() const {
    return !ui->line_code->text().isEmpty() && !ui->line_trial->text().isEmpty();
}

void MainWindow::checkData(const QByteArray &data) {
    // Check if participant code and trial number are entered
    if(!isParticipantInfoEntered()){
        showErrorMessage();
        return;
    }

    // If there is incomplete data in the partial data buffer, append the new data to it
    restructureIncompleteData(data);

    // If the concatenated data ends with "\r\n", process the complete data
    if (isDataComplete()) {

#ifdef DEBUG_MODE //1
        qDebug() << ">> Complete data: " + m_partialData;
#endif

        m_completeData = m_partialData;
        processData();
        clearPartialDataCache();
    }
}

void MainWindow::handleDataReceived(const QByteArray &data){
    checkData(data);
}

void MainWindow::plotData(const QVector<double> &xData, const QVector<double> &yData) {

    ui->backdrop->addGraph();
    ui->backdrop->graph(0)->setData(xData, yData);

    ui->backdrop->xAxis->setRange(xData.first(), xData.last());
    ui->backdrop->yAxis->setRange(*std::min_element(yData.constBegin(), yData.constEnd()), *std::max_element(yData.constBegin(), yData.constEnd()));

    ui->backdrop->replot();
}

void MainWindow::handleFileMode(const QString &filePath) {
    if (!fileExists(filePath)) {
        QMessageBox::critical(this, "Tips", tr("Cannot find the file you enter"));
        ui->backdrop->replot();
        return;
    }

    QVector<double> yData = readFileData(filePath);

    if (yData.empty()) {
        qWarning() << "Cannot find the data file.";
        return;
    }

    qDebug() << yData.length();
    QVector<double> xData;
    for (int i = 0; i < yData.size(); ++i) {
        xData.push_back(i);
    }

    plotData(xData, yData);
}


void MainWindow::handleRealTimeMode() {
    if (!m_reader->isSerialPortOpen()) {
        if (!m_reader->openSerialPort()) {
            qWarning() << "Failed to open serial port, Please check the config file.";
            return;
        }
    }

    connect(m_reader, &SerialPortReader::dataReceived, graphHandler, &GraphHandler::handleDataReceived);
}


bool MainWindow::isRealTimeMode(const QString &filePath) const {
    return filePath.isEmpty();
}

QString MainWindow::getFilePath() const {
    return ui->filepath->text();
}

void MainWindow::clearPlot() {
    ui->backdrop->clearPlottables();
}

void MainWindow::on_show_clicked()
{
    clearPlot();

    // Get the file path entered by the user
    QString filePath = getFilePath();

    // If the user does not enter the file path, show data in real time
    if (isRealTimeMode(filePath)) {
        handleRealTimeMode();
    }else{
        handleFileMode(filePath);
    }
}

void MainWindow::updateDurationInfo(const QString &info) {
    ui->label_duration->setText(info);
}

void MainWindow::on_exit_clicked()
{
    disconnect(m_reader, &SerialPortReader::dataReceived, graphHandler, &GraphHandler::handleDataReceived);

    ui->backdrop->clearPlottables();
    ui->backdrop->replot();
}

void MainWindow::clearCompleteDataCache()
{
    m_receivedData.clear();
}

void MainWindow::clearPartialDataCache(){
    m_partialData.clear();
}

void MainWindow::clearCache(){
    clearCompleteDataCache();

    clearPartialDataCache();
}

void MainWindow::handleSerialPortClosed() {
    qWarning() << "Serial port closed. Saving current valid data.";

    QByteArray validData = extractValidData();
    if (!validData.isEmpty()) {
        // saveData(validData);
        // clearCache();
        // resetLabels();
        saveAndResetData(validData);
    }
}
