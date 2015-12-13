#include <map>
#include <functional>

namespace ssd {

class Command {
public:
    template <class Function>
    Command(Function function):
        m_function(function),
        m_map()
    {/* Empty. */}

    Command(const std::function<int(int, char **)> & function);
    Command(std::function<int(int, char **)> && function);

    Command(const std::map<std::string, Command> & map);
    Command(std::map<std::string, Command> && map);
    Command(std::initializer_list<std::pair<const std::string, Command>> list);

    int operator() (int argc, char ** argv) const;

private:
    std::function<int(int, char **)> m_function;
    std::map<std::string, Command> m_map;
};

class MainCommand {
public:
    MainCommand(const Command & command);
    MainCommand(Command && command);
    MainCommand(std::initializer_list<std::pair<const std::string, Command>> list);

    int operator() (int argc, char ** argv) const;

private:
    Command m_command;
};

} // namespace ssd
