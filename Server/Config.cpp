#include "Config.hpp"

#include <iostream>
#include <fstream>

#include "JsonTool.hpp"

using namespace std;

Config* Config::m_singleInstance = nullptr;

Config::Config()
{
    initConfig();
}

Config::~Config()
{

}

Config& Config::getInstance()
{
    if(m_singleInstance == nullptr){
        m_singleInstance = new Config();
    }

    return *m_singleInstance;
}

void Config::initConfig()
{
    m_defaultConfig["tcpPort"] = 13337;
    m_defaultConfig["maxClients"] = 10;

    readConfigFile();
}

bool Config::readConfigFile()
{
    JsonTool& jsonTool = JsonTool::getInstance();
    Json::Value configRoot = jsonTool.jsonFileToValue("server.conf");

    for(const string& propertyName : m_defaultConfig.getMemberNames()){
        if(configRoot.isMember(propertyName)){
            m_config[propertyName] = configRoot[propertyName].asUInt();
        }
    }
}



Json::Value Config::field(const string& fieldName) const
{
    Json::Value field;

    if(m_defaultConfig.isMember(fieldName) && m_config.isMember(fieldName)){
        field = m_config[fieldName];
    }
    else if(m_defaultConfig.isMember(fieldName)){
        field = m_defaultConfig[fieldName];
    }

    return field;
}
