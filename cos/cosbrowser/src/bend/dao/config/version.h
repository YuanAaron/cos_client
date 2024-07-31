#ifndef VERSION_H
#define VERSION_H

#include <QString>

//完整版本号示例
//custom.beta.1.8.5 个人.公测.1.8.5版
//business.alpha.2.6.3 商用.内测.2.6.3版

class Version
{
public:
    Version();
    virtual void setVersion() = 0;

    QString version();
    QString versionNum();

    QString major() const;

protected:
    QString m_major; //business-商用版 custom-个人版
    QString m_env; //dev alpha(内测） beta（公测） prod

    int m_v1;
    int m_v2;
    int m_v3;
};

#endif // VERSION_H
