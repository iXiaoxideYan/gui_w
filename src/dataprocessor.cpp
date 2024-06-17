#include <algorithm>
#include "dataprocessor.h"

double DataProcessor::toDouble(const QByteArray &valueStr) const {
    bool ok;
    double value = valueStr.trimmed().toDouble(&ok);
    return ok ? value : std::numeric_limits<double>::min();
}

double DataProcessor::getMaxValue(const QVector<double> &data) const {
    if (data.isEmpty()) {
        return 0.0;
    }

    return *std::max_element(data.constBegin(), data.constEnd());
}

double DataProcessor::getMaxValueFromList(const QList<QByteArray> &dataList) const {
    double maxValue = std::numeric_limits<double>::min();

    for (const QByteArray &valueStr : dataList) {
        double value = toDouble(valueStr);
        if (value > maxValue) {
            maxValue = value;
        }
    }

    return maxValue;
}

double DataProcessor::getMaxValueFromByteArray(const QByteArray &data) const {
    // const char *separator = "\r\n";
    // QList<QByteArray> values = data.split(*separator);
    QList<QByteArray> values = getRawData(data);
    return getMaxValueFromList(values);
}

QList<QByteArray> DataProcessor::getRawData(const QByteArray &data) const
{
    QList<QByteArray> values = data.split('\n');
    return values;
}

QVector<double> DataProcessor::parseData(const QByteArray &data) const {
    QList<QByteArray> values = getRawData(data);
    QVector<double> parsedData;

    for (const QByteArray &valueStr : values) {
        double value = toDouble(valueStr);
        if (value != std::numeric_limits<double>::min()) { // Filter out invalid values
            parsedData.append(value);
        }
    }

    return parsedData;
}

bool DataProcessor::areAllValuesZero(const QString &inputString)
{
    QRegularExpression re("\\b\\d+(\\.\\d+)?\\b");
    QRegularExpressionMatch match = re.match(inputString);

    while (match.hasMatch()) {
        QString number = match.captured(0);
        if (number.toDouble() != 0.00) {
            return false;
        }
        match = re.match(inputString, match.capturedEnd());
    }
    return true;
}
