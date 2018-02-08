#ifndef JSONTOOL_H
#define JSONTOOL_H

#include <string>
#include <sstream>

#include <json/writer.h>
#include <json/reader.h>
#include <json/value.h>

class JsonTool
{
public:
    JsonTool(std::string indentation = "");
    ~JsonTool();

    std::string valueToJsonString(const Json::Value& value) const;
    Json::Value jsonStringToValue(const std::string& jsonString) const;
    Json::Value jsonFileToValue(const std::string& filePath) const;

private:
    Json::StreamWriterBuilder m_writerBuilder;
    Json::StreamWriter* m_streamWriter;

    Json::CharReaderBuilder m_charBuilder;
    Json::CharReader* m_charReader;
};

#endif	// JSONTOOL_H

