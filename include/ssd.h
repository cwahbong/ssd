#include <functional>
#include <map>
#include <tuple>

namespace ssd {

struct NomatchType {};
constexpr NomatchType nomatch{};

class Match {
public:
    Match(const char * name);
    Match(const std::string & name);
    Match(std::string && name);
    Match(NomatchType nomatch);

    friend bool operator<(const Match &, const Match &);
    friend bool operator<=(const Match &, const Match &);
    friend bool operator>(const Match &, const Match &);
    friend bool operator>=(const Match &, const Match &);
    friend bool operator==(const Match &, const Match &);
    friend bool operator!=(const Match &, const Match &);

private:
    std::tuple<bool, std::string> m_match;
};

class Command {
public:
    template <class Function>
    Command(Function function):
        m_function(function),
        m_map()
    {/* Empty. */}

    Command(const std::function<int(int, char **)> & function);
    Command(std::function<int(int, char **)> && function);

    Command(const std::map<Match, Command> & map);
    Command(std::map<Match, Command> && map);
    Command(std::initializer_list<std::pair<const Match, Command>> list);

    int operator() (int argc, char ** argv) const;

private:
    std::function<int(int, char **)> m_function;
    std::map<Match, Command> m_map;
};

class MainCommand {
public:
    MainCommand(const Command & command);
    MainCommand(Command && command);
    MainCommand(std::initializer_list<std::pair<const Match, Command>> list);

    int operator() (int argc, char ** argv) const;

private:
    Command m_command;
};

} // namespace ssd
