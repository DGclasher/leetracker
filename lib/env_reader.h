#ifndef ENV_READER_H
#define ENV_READER_H
#include <string>
#include <unordered_map>

class EnvReader {
    public:
    EnvReader(const std::string &file_name);
    std::string GetVariableName(const std::string &name);

    private:
    std::unordered_map<std::string, std::string> env_vars;
};

#endif