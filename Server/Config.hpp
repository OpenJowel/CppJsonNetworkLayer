#ifndef CONFIG_H
#define CONFIG_H

#include <set>

#include <json/reader.h>
#include <json/value.h>

class Config
{
public:
	Config();
	~Config();

    static Config& getInstance();
    bool readConfigFile();
    Json::Value field(const std::string& fieldName) const;

private:
    void initConfig();

    static Config* m_singleInstance;
    Json::Value m_config;
    Json::Value m_defaultConfig;
};

#endif	// CONFIG_H

