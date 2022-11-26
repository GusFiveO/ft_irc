/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SQUIT.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:06:10 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 21:43:09 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Replies.hpp"
#include "Status.hpp"

#include "ft_irc.hpp"

std::string
getComment(std::vector<std::string>::iterator first, std::vector<std::string>::iterator last)
{
	std::vector<std::string>::iterator it = first;
	std::string ret;

	while (it != last)
	{
		ret.append(*it);
		if (++it != last)
			ret.append(" ");
	}
	return ret;
}

void
SQUIT(Command* cmd)
{
	User* user = cmd->getUser();
	std::vector<std::string> args = cmd->getArgs();
	Replies rply(user, args);


	if (user->isRegistered() == false)
	{
		rply.sendError(E_ERR_NOTREGISTERED);
	}
	else if (args.size() < 2)
	{
		rply.sendError(E_ERR_NEEDMOREPARAMS);
	}
	else if (user->isOperator() == false)
	{
		rply.sendError(E_ERR_NOPRIVILEGES);
	}
	else
	{
		if (args[1] == g_network.getsockaddr(user->getPollFd()->fd)
				|| (args[1] == "localhost" && std::string(g_network.getsockaddr(user->getPollFd()->fd)) == "127.0.0.1"))
		{
			if (args.size() >= 3 && args[2][0] == ':')
			{
				std::string mess;
				std::string comment;
				
				comment = getComment(args.begin() + 2, args.end());
				mess.append("ERROR");
				mess.append(" ");
				mess.append("server shutdown");
				mess.append(" ");
				mess.append(comment);
				mess.append("\r\n");

				g_network.broadcast(mess);
			}
			g_status = STOP;
		}
		else
			rply.sendError(E_ERR_NOSUCHSERVER);
	}
}
