#include "IPGeoServer.h"
#include "IPGeoServantImp.h"

#include "DBHandler.h"

using namespace std;

IPGeoServer g_app;

/////////////////////////////////////////////////////////////////
void IPGeoServer::initialize()
{
    //initialize application here:
    //...
    DBConfig::getInstance()->load(this);
    DBHandler::getInstance()->init();
    addServant<IPGeoServantImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".IPGeoServantObj");
}
/////////////////////////////////////////////////////////////////
void IPGeoServer::destroyApp()
{
    //destroy application here:
    //...
}
/////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    try
    {
        g_app.main(argc, argv);
        g_app.waitForShutdown();
    }
    catch (std::exception &e)
    {
        cerr << "std::exception:" << e.what() << std::endl;
    }
    catch (...)
    {
        cerr << "unknown exception." << std::endl;
    }
    return -1;
}
/////////////////////////////////////////////////////////////////
