#include <algorithm>
#include "dataprocess.h"
#include "QtCore/qdebug.h"

double getMaxValue(const QVector<double> &data) {
    if (data.isEmpty()) {
        return 0.0;
    }

    return *std::max_element(data.constBegin(), data.constEnd());
}


double getMaxValueFromByteArray(const QByteArray &data) {
    const char *separator = "\r\n";
    QList<QByteArray> values = data.split(*separator);
    double maxValue = std::numeric_limits<double>::min();

    foreach (const QByteArray &valueStr, values) {
        bool ok;
        double value = valueStr.toDouble(&ok);
        if (ok && value > maxValue) {
            maxValue = value;
        }
    }

    return maxValue;
}
