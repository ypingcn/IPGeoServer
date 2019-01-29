#include "IPGeoServantImp.h"
#include "servant/Application.h"

#include "LogManager.h"

#include "DBHandler.h"

using namespace std;

//////////////////////////////////////////////////////
void IPGeoServantImp::initialize()
{
    //initialize servant here:
    //...
}

//////////////////////////////////////////////////////
void IPGeoServantImp::destroy()
{
    //destroy servant here:
    //...
}

tars::Int32 IPGeoServantImp::getIPGeo(const Common::IPGeoReq &req, Common::IPGeoRsp &rsp, tars::TarsCurrentPtr current)
{
    if (!isAppIDVaild(req.lAppid))
    {
        rsp.tStatus = Common::ReturnCode::eAppidError;
        rsp.sDescription = Common::etos(Common::ReturnCode::eAppidError) + ":Appid Error for getIPGeo";
        return -1;
    }
    if (!isTimestampVaild(req.lTimestamp))
    {
        rsp.tStatus = Common::ReturnCode::eTimestampError;
        rsp.sDescription = Common::etos(Common::ReturnCode::eTimestampError) + ":Timestamp invaild for getIPGeo";
        return -1;
    }

    string sClientIP;
    if (!req.sQueryIP.empty())
    {
        sClientIP = req.sQueryIP;
    }
    else
    {
        map<string, string>::const_iterator it = current->getContext().find("X-Forwarded-For");
        if (it == current->getContext().cend())
        {
            sClientIP = current->getIp();
        }
        else
        {
            sClientIP = TC_Common::sepstr<string>(",", it->second)[0];
        }
    }

    long lClientIP = 0;
    long lMulti = 1;
    vector<string> vClientIPDigits = TC_Common::sepstr<string>(sClientIP, ".");
    if (vClientIPDigits.size() != 4)
    {
        ERROR << "vClientIPDigits|" << vClientIPDigits.size() << endl;
        rsp.tStatus = Common::ReturnCode::eArgError;
        rsp.sDescription = Common::etos(Common::ReturnCode::eArgError) + ":IPv4 only,need x.x.x.x";
        return -1;
    }

    for (auto it = vClientIPDigits.rbegin(); it != vClientIPDigits.rend(); it++)
    {
        lClientIP = lClientIP + TC_Common::strto<long>(*it) * lMulti;
        lMulti = lMulti * 256;
    }

    DEBUG << "lClientIP|" << lClientIP << "|sClientIP|" << sClientIP << endl;

    return DBHandler::getInstance()->getCountry(lClientIP, rsp);
}

bool IPGeoServantImp::isAppIDVaild(const long lAppID)
{
    if (lAppID == 0)
        return false;
    return true;
}

bool IPGeoServantImp::isTimestampVaild(const long lTimeStamp)
{
    if (lTimeStamp == 0)
        return false;
    long lNow = (long)TC_TimeProvider::getInstance()->getNow();
    if (abs(lTimeStamp - lNow) > MAX_TIME_INTERVAL)
        return false;
    return true;
}
