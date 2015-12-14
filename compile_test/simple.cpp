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

ssd::MainCommand
simple_nomatch()
{
    return {
        {ssd::nomatch, std::function<int(int, char **)>()},
    };
}
