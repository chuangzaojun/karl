#include "environment.h"

Object *Environment::get(std::string identifier) {
    if (variables.count(identifier)) {
        return variables[identifier];
    }
    error(identifier);
    return NULL;
}

void Environment::set(std::string identifier, Object *value) {
    if (variables.count(identifier)) {
        delete variables[identifier];
    }
    variables[identifier] = value;
}

void Environment::error(std::string identifier) {
    printf("undefined variable: %s\n", identifier.data());
    exit(0);
}