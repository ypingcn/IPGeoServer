#include "DBHandler.h"

#include "SQLBuilder.h"

void DBHandler::init()
{
    tars::TC_DBConf conf;
    conf._host = DBConfig::getInstance()->_host;
    conf._user = DBConfig::getInstance()->_user;
    conf._password = DBConfig::getInstance()->_password;
    conf._database = DBConfig::getInstance()->_database;
    conf._charset = DBConfig::getInstance()->_charset;
    conf._port = DBConfig::getInstance()->_port;
    _DB = new DBManager();
    _DB->init(conf, 4);
}

int DBHandler::getCountry(long lClientIP, Common::IPGeoRsp &tResult)
{
    sqlbuilder::SelectModel tSelect;
    string condition = "ip_from <= " + to_string(lClientIP) + " and " + " ip_to >= " + to_string(lClientIP);
    tSelect.select("*").from("ip2location_db1").where(condition);

    try
    {
        tars::TC_Mysql *mysql = _DB->get();
        if (!mysql)
        {
            tResult.tStatus = Common::ReturnCode::eDbError;
            tResult.sDescription = Common::etos(Common::ReturnCode::eDbError) + ":Get DB handler error";
            ERROR << "mysql * error" << endl;
            return -1;
        }

        DEBUG << "sql|" << tSelect.str() << endl;
        tars::TC_Mysql::MysqlData sqlData = mysql->queryRecord(tSelect.str());
        if (sqlData.size() > 0)
        {
            tResult.tStatus = Common::ReturnCode::eOk;
            tResult.sCountryShortName = sqlData[0]["country_code"];
            tResult.sCountryFullName = sqlData[0]["country_name"];
            DEBUG << "result|" << sqlData[0]["ip_from"] << "|" << sqlData[0]["ip_to"] << "|"
                  << sqlData[0]["country_code"] << "|" << sqlData[0]["country_name"] << endl;
        }

        _DB->push(mysql);
    }
    catch (const std::exception &exp)
    {
        ERROR << exp.what() << endl;
        tResult.tStatus = Common::ReturnCode::eOtherError;
        tResult.sDescription = Common::etos(Common::ReturnCode::eOtherError) + ":" + exp.what();
        return -1;
    }
    catch (...)
    {
        tResult.tStatus = Common::ReturnCode::eUnknownError;
        tResult.sDescription = Common::etos(Common::ReturnCode::eUnknownError);
        return -1;
    }
    return 0;
}