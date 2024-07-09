#ifndef DAOBUCKET_H
#define DAOBUCKET_H

#include "src/bend/models/mybucket.h";
#include <QList>

class DaoBucket
{
public:
    DaoBucket();

    QList<MyBucket> bucketsFromMock(const QString& path);
};

#endif // DAOBUCKET_H
