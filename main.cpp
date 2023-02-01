
#include "shell/shell.hpp"

int main(int argc, char *argv[]) {
    std::vector<std::string> args;
    for (int i = 1; i < argc; i++) {
        args.push_back(std::string(argv[i]));
    }

    karl::shell::run(args);
    return 0;
}