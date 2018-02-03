#include "JsonUtils.hpp"

#include <iostream>

using namespace std;
using namespace Json;

JsonUtils::JsonUtils(std::string indentation):
    m_writerBuilder(),
    m_streamWriter(nullptr),
    m_charBuilder(),
    m_charReader(nullptr)
{
    m_writerBuilder["indentation"] = indentation;

    m_streamWriter = m_writerBuilder.newStreamWriter();
    m_charReader = m_charBuilder.newCharReader();
}

JsonUtils::~JsonUtils()
{
    delete m_streamWriter;
    delete m_charReader;
}

string JsonUtils::valueToJsonString(const Value& value)
{
    std::ostringstream dataStream;
    m_streamWriter->write(value, &dataStream);

    return dataStream.str();
}

Value JsonUtils::jsonStringToValue(const string& jsonString)
{
    Json::Value value;
    string errors;

    if(!m_charReader->parse(jsonString.c_str(), jsonString.c_str() + jsonString.size(), &value, &errors)){
        cout << errors << endl;
    }

    return value;
}
