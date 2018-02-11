/*
  Singletone class providing a simple usage layer to the JsonCpp library
*/

#ifndef JSONTOOL_H
#define JSONTOOL_H

#include <string>
#include <unordered_map>

#include <json/writer.h>
#include <json/reader.h>
#include <json/value.h>

class JsonTool
{
public:
    // Available indentation flags
    enum Indentation {Spaces, Tab, None};

    // Destructor
    ~JsonTool();

    // Singletone getter
    static JsonTool& getInstance();

    // Returns the value parsed as a json string
    std::string valueToJsonString(const Json::Value& value, Indentation indent = None) const;

    // Returns a Value node from a json string
    Json::Value jsonStringToValue(const std::string& jsonString) const;

    // Returns the contain of a file as a Json Value object
    Json::Value jsonFileToValue(const std::string& filePath) const;

private:
    // Constructor
    JsonTool();

    // Attributes
    static JsonTool* m_singleInstance;

    std::unordered_map<Indentation, Json::StreamWriter*> m_writers;
    Json::CharReader* m_charReader;
};

#endif	// JSONTOOL_H

