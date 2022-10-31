#include "VectorData.h"
#include <QDebug>

const QString VectorData::getValueByKey(const QString key)
{
    auto findByKey = [&key](ConfigData configData)
    {
        return configData.key == key;
    };
    auto result = std::find_if(this->begin(), this->end(), findByKey);
    if(result != this->end())
    {
        return result->value;
    }
    else
    {
        qWarning() << "key:" << key << "doen't exist";
        return QString();
    }
}

bool VectorData::setValueByKey(const QString &key, const QString &value)
{
    auto findByKey = [&key](ConfigData configData)
    {
        return configData.key == key;
    };
    auto result = std::find_if(this->begin(), this->end(), findByKey);
    if(result != this->end())
    {
        result->value = value;
        return true;
    }
    else
    {
        qWarning() << "key:" << key << "doen't exist";
        return false;
    }
}
