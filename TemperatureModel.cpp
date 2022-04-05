#include "TemperatureModel.h"

TemperatureModel::TemperatureModel(QObject *parent)
    : QObject{parent}
{

}

double TemperatureModel::cpuTemperature() const
{
    return m_cpuTemperature;
}

void TemperatureModel::setCpuTemperature(const double cpuTemperature)
{
    if( m_cpuTemperature != cpuTemperature )
    {
        m_cpuTemperature = cpuTemperature;

        emit cpuTemperatureChanged(m_cpuTemperature);
    }
}
