#include "ssd.h"

#include <iostream>

int main(int argc, char ** argv) {
    const ssd::MainCommand mainCommand {
        {"abc", [](int, char **){ std::cout << "PID" << std::endl; return 0; }},
        {"def", [](int, char **){ return 0; }},
        {"nested", {
            {"ghi", [](int, char **){ return 1; }},
            {"jkl", [](int, char **){ return 2; }},
            }
        },
        {"help", [](int, char **){ std::cout << "help abc" << std::endl; return 0; }}
    };
    return mainCommand(argc, argv);
}
