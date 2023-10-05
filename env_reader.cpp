#include "env_reader.h"
#include <fstream>
#include <sstream>
#include <iostream>

EnvReader::EnvReader(const std::string &file_name)
{
    std::ifstream file(file_name);
    if (!file.is_open())
    {
        std::cerr << "Unable to open .env file, make sure it exists in current path" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value))
        {
            env_vars[key] = value;
        }
    }
}

std::string EnvReader::GetVariableName(const std::string &name)
{
    auto it = env_vars.find(name);
    if (it != env_vars.end())
    {
        return it->second;
    }
    else
    {
        return "";
    }
}