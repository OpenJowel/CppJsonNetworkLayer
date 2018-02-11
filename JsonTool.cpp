#include "JsonTool.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace Json;

JsonTool* JsonTool::m_singleInstance = nullptr;

JsonTool::JsonTool()
{
    StreamWriterBuilder writerBuilder;

    writerBuilder["indentation"] = "    ";
    m_writers[Spaces] = writerBuilder.newStreamWriter();

    writerBuilder["indentation"] = "\t";
    m_writers[Tab] = writerBuilder.newStreamWriter();

    writerBuilder["indentation"] = "";
    m_writers[None] = writerBuilder.newStreamWriter();

    CharReaderBuilder charBuilder;
    m_charReader = charBuilder.newCharReader();
}

JsonTool::~JsonTool()
{
    delete m_writers[Spaces];
    delete m_writers[Tab];
    delete m_writers[None];
    delete m_charReader;
}

JsonTool& JsonTool::getInstance()
{
    if(!m_singleInstance){
        m_singleInstance = new JsonTool();
    }

    return *m_singleInstance;
}

string JsonTool::valueToJsonString(const Value& value, Indentation indentation) const
{
    std::ostringstream dataStream;

    // JsonCpp doesn't offer success return value yet
    m_writers.at(indentation)->write(value, &dataStream);

    return dataStream.str();
}

Value JsonTool::jsonStringToValue(const string& jsonString) const
{
    Json::Value value;
    string errors;

    if(!m_charReader->parse(jsonString.c_str(), jsonString.c_str() + jsonString.size(), &value, &errors)){
        cout << errors << endl;
    }

    return value;
}

Value JsonTool::jsonFileToValue(const std::string& filePath) const
{
    Json::Value value;
    string errors;

    ifstream file(filePath);

    if(file.fail()){
        return value;
    }

    string jsonString;
    jsonString = string(istreambuf_iterator<char>(file), istreambuf_iterator<char>());

    value = jsonStringToValue(jsonString);

    return value;
}
