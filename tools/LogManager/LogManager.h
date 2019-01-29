#ifndef YPINGCN_LOGMANAGER_H
#define YPINGCN_LOGMANAGER_H

#include "servant/TarsLogger.h"

#define INFO tars::TarsRollLogger::getInstance()->logger()->info() << __FILE__ << "|" << __FUNCTION__ << "|" << __LINE__ << "|"
#define DEBUG tars::TarsRollLogger::getInstance()->logger()->debug() << __FILE__ << "|" << __FUNCTION__ << "|" << __LINE__ << "|"
#define ERROR tars::TarsRollLogger::getInstance()->logger()->error() << __FILE__ << "|" << __FUNCTION__ << "|" << __LINE__ << "|"
#define WARN tars::TarsRollLogger::getInstance()->logger()->warn() << __FILE__ << "|" << __FUNCTION__ << "|" << __LINE__ << "|"
#define ANY tars::TarsRollLogger::getInstance()->logger()->any() << __FILE__ << "|" << __FUNCTION__ << "|" << __LINE__ << "|"

#endif //YPINGCN_LOGMANAGER_H