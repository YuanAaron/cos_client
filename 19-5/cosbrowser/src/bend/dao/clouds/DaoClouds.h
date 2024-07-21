#ifndef DAOCLOUDS_H
#define DAOCLOUDS_H

#include <src/middle/models/mybucket.h>

class DaoClouds
{
public:
    virtual QList<MyBucket> buckets() = 0;
};

#endif // DAOCLOUDS_H
