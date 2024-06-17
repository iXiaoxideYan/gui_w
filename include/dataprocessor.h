#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QByteArray>
#include <QVector>
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

class DataProcessor {
public:
    double getMaxValue(const QVector<double> &data) const;
    double getMaxValueFromByteArray(const QByteArray &data) const;
    double getMaxValueFromList(const QList<QByteArray> &dataList) const;
    QVector<double> parseData(const QByteArray &data) const;
    bool saveDataToCSV(const QVector<double> &data, const QString &filePath) const;
    bool saveListToCSV(const QList<QByteArray> &dataList, const QString &filePath) const;
    bool areAllValuesZero(const QString &inputString);

    QList<QByteArray> getRawData(const QByteArray &data) const;

private:
    double toDouble(const QByteArray &valueStr) const;
    bool m_saveRawData = false;
};

#endif // DATAPROCESSOR_H
