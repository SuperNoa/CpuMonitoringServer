#ifndef TEMPERATUREMODEL_H
#define TEMPERATUREMODEL_H

#include <QObject>

class TemperatureModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double cpuTemperature READ cpuTemperature NOTIFY cpuTemperatureChanged)

public:
    explicit TemperatureModel(QObject *parent = nullptr);

    double cpuTemperature() const;
    void setCpuTemperature(const double cpuTemperature);

signals:
    void cpuTemperatureChanged(double);

private:
    double m_cpuTemperature { 0 };

};

#endif // TEMPERATUREMODEL_H
