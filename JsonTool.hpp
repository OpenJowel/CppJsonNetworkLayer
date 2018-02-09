#ifndef JSONTOOL_H
#define JSONTOOL_H

#include <string>
#include <sstream>

#include <unordered_map>

#include <json/writer.h>
#include <json/reader.h>
#include <json/value.h>

class JsonTool
{
public:
    enum Indentation {Spaces, Tab, None};
    ~JsonTool();

    static JsonTool& getInstance();

    std::string valueToJsonString(const Json::Value& value, Indentation indent = None) const;
    Json::Value jsonStringToValue(const std::string& jsonString) const;
    Json::Value jsonFileToValue(const std::string& filePath) const;

private:
    JsonTool();
    static JsonTool* m_singleInstance;

    std::unordered_map<Indentation, Json::StreamWriter*> m_writers;

    Json::CharReaderBuilder m_charBuilder;
    Json::CharReader* m_charReader;
};

#endif	// JSONTOOL_H

