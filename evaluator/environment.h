#ifndef KARL_ENVIRONMENT_H
#define KARL_ENVIRONMENT_H

#include "../object/object.h"
#include <map>
#include <string>

class Environment {
private:
    std::map<std::string, Object *> variables;

    void error(std::string identifier);

public:
    Object *get(std::string identifier);

    void set(std::string identifier, Object *value);
};


#endif // KARL_ENVIRONMENT_H
