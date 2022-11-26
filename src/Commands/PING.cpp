
#include "Command.hpp"
#include "Replies.hpp"

void
PING(Command* cmd)
{
	User* user = cmd->getUser();
	std::vector<std::string> args = cmd->getArgs();
	Replies rply(user, args);

	if (args.size() < 2)
	{
		rply.sendError(E_ERR_NEEDMOREPARAMS);
	}
	else
	{
		std::string pong;

		pong.append("PONG :");
		pong.append(args[1]);
		pong.append("\r\n");

		
		send(user->getPollFd()->fd, pong.data(), pong.size(), 0);

	}
}
