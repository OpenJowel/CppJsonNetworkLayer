#ifndef JSONUTILS_H
#define JSONUTILS_H

#include <string>
#include <sstream>

#include <json/writer.h>
#include <json/reader.h>
#include <json/value.h>

class JsonUtils
{
public:
    JsonUtils(std::string indentation = "");
    ~JsonUtils();

    std::string valueToJsonString(const Json::Value& value);
    Json::Value jsonStringToValue(const std::string& jsonString);

private:
    Json::StreamWriterBuilder m_writerBuilder;
    Json::StreamWriter* m_streamWriter;

    Json::CharReaderBuilder m_charBuilder;
    Json::CharReader* m_charReader;
};

#endif	// JSONUTILS_H

