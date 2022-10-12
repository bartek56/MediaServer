#ifndef VECTORDATA_H
#define VECTORDATA_H

#include <QString>
#include <vector>

struct ConfigData {
  QString key;
  QString value;

  ConfigData(QString k, QString v) : key(k), value(v) {}
};


class VectorData : public std::vector<ConfigData>
{
public:
    const QString getValueByKey(const QString key);
    bool setValueByKey(const QString& key, const QString& value);
};

#endif
