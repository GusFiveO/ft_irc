// #include "ft_irc.hpp"
#include "Command.hpp"
#include "MODEutils.hpp"

Command::Command(Commands funcPtr, User* user, std::vector<std::string> vec) :
    _funcPtr(funcPtr),
    _user(user),
    _arguments(vec)
{
}

Command::~Command()
{
}

void
Command::display_vec()
{
    for (std::vector<std::string>::iterator it = _arguments.begin(); it != _arguments.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
}

void
Command::execute()
{
    (*_funcPtr)(this);
}

std::vector<std::string>
Command::getArgs()
{
    return _arguments;
}

User*
Command::getUser() const
{
	return _user;
}
