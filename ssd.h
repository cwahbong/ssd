#include <map>
#include <functional>

namespace ssd {

class Command: private std::function<int(int, char **)> {
public:
    using function::function;

    Command(const std::map<std::string, Command> & mapping): function([mapping](int argc, char ** argv){
        if (argc < 1) {
            return -1;
        }
        const auto it = mapping.find(argv[0]);
        if (it == mapping.end()) {
            return -1;
        }
        return it->second(argc - 1, argv + 1);
    }) {}

    Command(std::initializer_list<std::pair<const std::string, Command>> list): Command(std::map<std::string, Command>(list)) {}

    using function::operator();
};

class MainCommand: private Command {
public:
    MainCommand(const Command & command): Command(command) {}
    MainCommand(Command && command): Command(std::move(command)) {}
    MainCommand(std::initializer_list<std::pair<const std::string, Command>> list): Command(list) {}

    int operator()(int argc, char ** argv) const {
        return Command::operator()(argc - 1, argv + 1);
    }
};

} // namespace ssd
