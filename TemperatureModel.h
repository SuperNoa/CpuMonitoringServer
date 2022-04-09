#ifndef TEMPERATUREMODEL_H
#define TEMPERATUREMODEL_H

#include <QObject>

class TemperatureModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int cpuTemperature READ cpuTemperature NOTIFY cpuTemperatureChanged)

public:
    explicit TemperatureModel(QObject *parent = nullptr);

    int cpuTemperature() const;
    void setCpuTemperature(const int cpuTemperature);

signals:
    void cpuTemperatureChanged(int newCpuTemperatureChanged);

private:
    int m_cpuTemperature { 0 };

};

#endif // TEMPERATUREMODEL_H
