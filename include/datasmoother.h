#ifndef DATASMOOTHER_H
#define DATASMOOTHER_H

#include <QVector>
#include <numeric>

class DataSmoother {
public:
    // Constructor, initialize the buffer size
    DataSmoother(int size) : bufferSize(size) {}

    // Smooth the function, add new data and calculate
    // the moving average
    double smooth(double newValue) {
        dataBuffer.append(newValue);
        if (dataBuffer.size() > bufferSize) {
            dataBuffer.removeFirst();
        }
        // Calculate the average value of the data in the buffer
        double smoothedValue = std::accumulate(dataBuffer.begin(), dataBuffer.end(), 0.0) / dataBuffer.size();
        return smoothedValue;
    }

private:
    int bufferSize; // Buffer size
    QVector<double> dataBuffer;
};

#endif // DATASMOOTHER_H
