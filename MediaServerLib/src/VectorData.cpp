#include "VectorData.h"

const QString VectorData::getValueByKey(const QString key)
{
    auto findByKey = [&key](ConfigData configData){
        return configData.key == key;
    };
    auto result =  std::find_if(this->begin(),this->end(), findByKey);
    if (result != this->end())
    {
        return result->value;
    }
    else
        return QString();
}

bool VectorData::setValueByKey(const QString &key, const QString &value)
{
    auto findByKey = [&key](ConfigData configData){
        return configData.key == key;
    };
    auto result =  std::find_if(this->begin(),this->end(), findByKey);
    if (result != this->end())
    {
        result->value = value;
        return true;
    }

    return false;
}
