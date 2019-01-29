#ifndef YPINGCN_DBMANAGER_H
#define YPINGCN_DBMANAGER_H

#include <list>

#include "util/tc_mysql.h"   // tars::TC_DBConf tars::TC_Mysql
#include "util/tc_autoptr.h" //tars::TC_HandleBase
#include "util/tc_thread.h"  // tars::TC_ThreadLock

#include "LogManager.h"

class DBManager : public tars::TC_HandleBase, public tars::TC_ThreadLock
{
  public:
    DBManager(){};
    ~DBManager() {}

    void init(const tars::TC_DBConf &conf, const int size)
    {
        DEBUG << endl;
        _tDBConf = conf;
        _tPoolSize = size;
    }
    tars::TC_Mysql *get()
    {
        tars::TC_ThreadLock::Lock lock(*this);
        try
        {
            tars::TC_Mysql *pMysql = nullptr;
            if (_lMySQLConnectionPool.size() == 0)
            {
                pMysql = new tars::TC_Mysql(_tDBConf._host, _tDBConf._user, _tDBConf._password, _tDBConf._database, _tDBConf._charset, _tDBConf._port, 0);
                pMysql->connect();
            }
            else
            {
                pMysql = _lMySQLConnectionPool.front();
                _lMySQLConnectionPool.pop_front();
            }
            return pMysql;
        }
        catch (const std::exception &exp)
        {
            ERROR << exp.what() << endl;
        }
        catch (...)
        {
            ERROR << "unknown error" << endl;
        }
        return nullptr;
    }
    void push(tars::TC_Mysql *mysql)
    {
        tars::TC_ThreadLock::Lock lock(*this);
        try
        {
            _lMySQLConnectionPool.push_back(mysql);
        }
        catch (const std::exception &exp)
        {
            ERROR << exp.what() << endl;
        }
        catch (...)
        {
            ERROR << "unknown error" << endl;
        }
    }

  private:
    std::list<tars::TC_Mysql *> _lMySQLConnectionPool;
    tars::TC_DBConf _tDBConf;
    int _tPoolSize;
};

typedef tars::TC_AutoPtr<DBManager> DBManagerPtr;

#endif //YPINGCN_DBMANAGER_H
