#ifndef YPINGCN_IPGEO_DBHANDLER_H
#define YPINGCN_IPGEO_DBHANDLER_H

#include "servant/Application.h"
#include "util/tc_singleton.h"

#include "DBManager.h"
#include "LogManager.h"
#include "IPGeoServant.h"

class DBConfig : public tars::TC_Singleton<DBConfig>
{
public:
    string _host;
    string _user;
    string _password;
    string _database;
    string _charset;
    int _port;
    inline void load(tars::Application *app)
    {
        tars::TC_Config conf;
        string sConfFileName = "IPGeoServer.conf";
        app->addConfig(sConfFileName);
        conf.parseFile(tars::ServerConfig::BasePath + sConfFileName);

        _host = conf.get("/main/ipgeo/db/<host>");
        _user = conf.get("/main/ipgeo/db/<user>");
        _password = conf.get("/main/ipgeo/db/<password>");
        _database = conf.get("/main/ipgeo/db/<database>");
        _charset = conf.get("/main/ipgeo/db/<charset>");
        _port = std::stoi( conf.get("/main/ipgeo/db/<port>") );

        DEBUG << "load|db host " << _host << endl;
        DEBUG << "load|db user " << _user << endl;
        DEBUG << "load|db password " << _password << endl;
        DEBUG << "load|db database " << _database << endl;
        DEBUG << "load|db charset " << _charset << endl;
        DEBUG << "load|db port " << _port << endl;
    }
};

class DBHandler : public tars::TC_Singleton<DBHandler> // TODO
{
public:
    void init();
    int getCountry(long lClientIP,Common::IPGeoRsp& result);
private:
    DBManager * _DB;
};

#endif //YPINGCN_IPGEO_DBHANDLER_H
