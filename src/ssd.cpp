#include "ssd.h"

namespace ssd {

Match::Match(const char * name):
    m_match(true, name)
{/* Empty. */}

Match::Match(const std::string & name):
    m_match(true, name)
{/* Empty. */}

Match::Match(std::string && name):
    m_match(true, std::move(name))
{/* Empty. */}

Match::Match(NomatchType):
    m_match(false, std::string())
{/* Empty. */}

bool
operator<(const Match & lhs, const Match & rhs)
{
    return lhs.m_match < rhs.m_match;
}

bool
operator<=(const Match & lhs, const Match & rhs)
{
    return lhs.m_match <= rhs.m_match;
}

bool
operator>(const Match & lhs, const Match & rhs)
{
    return lhs.m_match > rhs.m_match;
}

bool
operator>=(const Match & lhs, const Match & rhs)
{
    return lhs.m_match >= rhs.m_match;
}

bool
operator==(const Match & lhs, const Match & rhs)
{
    return lhs.m_match == rhs.m_match;
}

bool
operator!=(const Match & lhs, const Match & rhs)
{
    return lhs.m_match != rhs.m_match;
}

Command::Command(const std::function<int(int, char **)> & function):
    m_function(function),
    m_map()
{/* Empty. */}

Command::Command(std::function<int(int, char **)> && function):
    m_function(std::move(function)),
    m_map()
{/* Empty. */}

Command::Command(const std::map<Match, Command> & map):
    m_function(),
    m_map(map)
{/* Empty. */}

Command::Command(std::map<Match, Command> && map):
    m_function(),
    m_map(std::move(map))
{/* Empty. */}

Command::Command(std::initializer_list<std::pair<const Match, Command>> list):
    m_function(),
    m_map(list)
{/* Empty. */}

int
Command::operator() (int argc, char ** argv) const
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

MainCommand::MainCommand(const Command & command): m_command(command)
{/* Empty. */}

MainCommand::MainCommand(Command && command): m_command(std::move(command))
{/* Empty. */}

MainCommand::MainCommand(std::initializer_list<std::pair<const Match, Command>> list):
    m_command(list)
{/* Empty. */}

int
MainCommand::operator() (int argc, char ** argv) const
{
    return m_command(argc - 1, argv + 1);
}

} // namespace ssd
