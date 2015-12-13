#include <ssd.h>

ssd::MainCommand
simple_lambda()
{
    return {
        {"a", [](int, char **){ return 0; }},
        {"b", [](int, char **){ return 0; }},
        {"c", [](int, char **){ return 0; }},
    };
}
