#ifndef VERSIONJSON_H
#define VERSIONJSON_H

#include <src/bend/dao/config/version.h>

class VersionJson : public Version
{
public:
    VersionJson(const QString& path);

    virtual void setVersion() override;

private:
    QString m_path;
};

#endif // VERSIONJSON_H
