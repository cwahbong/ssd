#include <functional>
#include <map>
#include <tuple>

namespace ssd {

struct NomatchType {};
constexpr NomatchType nomatch{};

class Match {
public:
    Match(const char * name):
        m_match(true, name)
    {/* empty */}

    Match(const std::string & name):
        m_match(true, name)
    {/* empty */}

    Match(std::string && name):
        m_match(true, std::move(name))
    {/* empty */}

    Match(NomatchType):
        m_match(false, std::string())
    {/* empty */}

    friend bool operator<(const Match & lhs, const Match & rhs)
    {
        return lhs.m_match < rhs.m_match;
    }

    friend bool operator<=(const Match & lhs, const Match & rhs)
    {
        return lhs.m_match <= rhs.m_match;
    }

    friend bool operator>(const Match & lhs, const Match & rhs)
    {
        return lhs.m_match > rhs.m_match;
    }

    friend bool operator>=(const Match & lhs, const Match & rhs)
    {
        return lhs.m_match >= rhs.m_match;
    }

    friend bool operator==(const Match & lhs, const Match & rhs)
    {
        return lhs.m_match == rhs.m_match;
    }

    friend bool operator!=(const Match & lhs, const Match & rhs)
    {
        return lhs.m_match != rhs.m_match;
    }

private:
    std::tuple<bool, std::string> m_match;
};

class Command {
public:
    template <class Function>
    Command(Function function):
        m_function(function),
        m_map()
    {/* empty */}

    Command(const std::function<int(int, char **)> & function):
        m_function(function),
        m_map()
    {/* empty */}

    Command(std::function<int(int, char **)> && function):
        m_function(std::move(function)),
        m_map()
    {/* empty */}

    Command(const std::map<Match, Command> & map):
        m_function(),
        m_map(map)
    {/* empty */}

    Command(std::map<Match, Command> && map):
        m_function(),
        m_map(std::move(map))
    {/* empty */}

    Command(std::initializer_list<std::pair<const Match, Command>> list):
        m_function(),
        m_map(list)
    {/* empty */}

    int operator() (int argc, char ** argv) const
    {
        if (m_function) {
            return m_function(argc, argv);
        }
        if (argc < 1) {
            return -1;
        }
        const auto it = m_map.find(argv[0]);
        if (it == m_map.end()) {
            return -1;
        }
        return it->second(argc - 1, argv + 1);
    }

private:
    std::function<int(int, char **)> m_function;
    std::map<Match, Command> m_map;
};

class MainCommand {
public:
    MainCommand(const Command & command):
        m_command(command)
    {/* empty */}

    MainCommand(Command && command):
        m_command(std::move(command))
    {/* empty */}

    MainCommand(std::initializer_list<std::pair<const Match, Command>> list):
        m_command(list)
    {/* empty */}

    int operator() (int argc, char ** argv) const
    {
        return m_command(argc - 1, argv + 1);
    }

private:
    Command m_command;
};

} // namespace ssd
