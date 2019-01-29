#ifndef _IPGeoServantImp_H_
#define _IPGeoServantImp_H_

#include "servant/Application.h"
#include "IPGeoServant.h"

/**
 *
 *
 */
class IPGeoServantImp : public Common::IPGeoServant
{
public:
    /**
     *
     */
    virtual ~IPGeoServantImp() {}

    /**
     *
     */
    virtual void initialize();

    /**
     *
     */
    virtual void destroy();

    /**
     *
     */
    virtual int test(tars::TarsCurrentPtr current) { return 0;};
    virtual tars::Int32 getIPGeo(const Common::IPGeoReq & req,Common::IPGeoRsp &rsp,tars::TarsCurrentPtr current) override;

private:
    bool isAppIDVaild(const long lAppID);
    bool isTimestampVaild(const long lTimeStamp);
    
    const long MAX_TIME_INTERVAL = 30;
};
/////////////////////////////////////////////////////
#endif
