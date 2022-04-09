#include "TemperatureModel.h"

TemperatureModel::TemperatureModel(QObject *parent)
    : QObject{parent}
{

}

int TemperatureModel::cpuTemperature() const
{
    return m_cpuTemperature;
}

void TemperatureModel::setCpuTemperature(const int cpuTemperature)
{
    if( m_cpuTemperature != cpuTemperature )
    {
        m_cpuTemperature = cpuTemperature;

        emit cpuTemperatureChanged(m_cpuTemperature);
    }
}
