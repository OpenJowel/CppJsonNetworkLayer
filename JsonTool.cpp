#include "JsonTool.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using namespace Json;

JsonTool::JsonTool(std::string indentation):
    m_writerBuilder(),
    m_streamWriter(nullptr),
    m_charBuilder(),
    m_charReader(nullptr)
{
    m_writerBuilder["indentation"] = indentation;

    m_streamWriter = m_writerBuilder.newStreamWriter();
    m_charReader = m_charBuilder.newCharReader();
}

JsonTool::~JsonTool()
{
    delete m_streamWriter;
    delete m_charReader;
}

string JsonTool::valueToJsonString(const Value& value) const
{
    std::ostringstream dataStream;
    m_streamWriter->write(value, &dataStream);

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
