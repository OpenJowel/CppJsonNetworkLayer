/*
  Config allows to use an external configuration file using Json syntax
  Handles default parameters and discards useless ones.
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <json/value.h>

class Config
{
public:
	~Config();

    // Singletone getter
    static Config& getInstance();
    Json::Value field(const std::string& fieldName) const;

private:
    // Constructor
	Config();

    // Get configuration from external file
    bool readConfigFile();
    
    // Initializes configuration
    void initConfig();

    static Config* m_singleInstance;
    Json::Value m_config;
    Json::Value m_defaultConfig;
};

#endif	// CONFIG_H

