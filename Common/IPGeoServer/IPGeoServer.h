#ifndef _IPGeoServer_H_
#define _IPGeoServer_H_

#include <iostream>
#include "servant/Application.h"

using namespace tars;

/**
 *
 **/
class IPGeoServer : public Application
{
public:
    /**
     *
     **/
    virtual ~IPGeoServer() {};

    /**
     *
     **/
    virtual void initialize();

    /**
     *
     **/
    virtual void destroyApp();
};

extern IPGeoServer g_app;

////////////////////////////////////////////
#endif
