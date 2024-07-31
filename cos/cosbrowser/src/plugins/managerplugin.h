#ifndef MANAGERPLUGIN_H
#define MANAGERPLUGIN_H

#include <QObject>

#include <src/bend/dao/clouds/DaoClouds.h>

#include <src/bend/dao/config/version.h>

class ManagerPlugin : public QObject
{
    Q_OBJECT
public:
    explicit ManagerPlugin(QObject *parent = nullptr);
    ~ManagerPlugin();

    DaoClouds* clouds() const;

signals:

public:
    void installPlugins(int argc, char* argv[]);

private:
    DaoClouds* m_clouds;
    Version* m_version;

};

#endif // MANAGERPLUGIN_H
