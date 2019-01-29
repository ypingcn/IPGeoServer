#include "servant/Communicator.h"

#include "IPGeoServant.h"

int main(int argc, char const *argv[])
{
    Communicator comm;
    try
    {
        Common::IPGeoServantPrx prx;
        comm.stringToProxy("Common.IPGeoServer.IPGeoServantObj@tcp -h 192.168.199.130 -p 10006", prx);
        try
        {
            Common::IPGeoReq req;
            req.lAppid = 100;
            req.lTimestamp = TC_TimeProvider::getInstance()->getNow();
            req.sQueryIP = "8.8.8.8";
            Common::IPGeoRsp rsp;
            
            int iRet = prx->getIPGeo(req,rsp);
            cout << "ret:" << iRet << endl;
            cout << "rsp: status - " << rsp.tStatus << endl;
            cout << "rsp: description - " << rsp.sDescription << endl;
            cout << "rsp: short name - " << rsp.sCountryShortName << endl;
            cout << "rsp: full name - " << rsp.sCountryFullName << endl;
        }
        catch(...)
        {
            cout << "exception -" << endl;
        }
    }
    catch(...)
    {
        cout << "exception" << endl;
    }
    
    return 0;
}
