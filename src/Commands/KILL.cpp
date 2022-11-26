/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KILL.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschiffe <aschiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:25:30 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 20:22:15 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Replies.hpp"

void
KILL(Command* cmd)
{
	User* user = cmd->getUser();
	User* target = NULL;
	std::vector<std::string> args = cmd->getArgs();
	Replies rply(user, args);
	
	if (user->isRegistered() == false)
	{
		rply.sendError(E_ERR_NOTREGISTERED);
	}
	else if (args.size() != 3)
	{
		rply.sendError(E_ERR_NEEDMOREPARAMS);
	}
	else if (user->isOperator() == false)
	{
		rply.sendError(E_ERR_NOPRIVILEGES);
	}
	else if ((target = g_network.getUser(args[1])) == NULL)
	{
		rply.sendError(E_ERR_NOSUCHNICK);
	}
	else
	{
		std::string msg;
		std::string comment(&args[2][1]);

		msg.append(":");
		msg.append(user->getNickname());
		msg.append("!");
		msg.append(user->getUsername());
		msg.append(std::string("@") += user->getAddr() += " ");
		msg.append("KILL");
		msg.append(" ");
		msg.append(target->getNickname());
		msg.append(" ");
		msg.append(":");
		msg.append(comment);
		msg.append("\r\n");
		
		if (send(target->getPollFd()->fd, msg.data(), msg.size(), 0) == -1)
		{
			target->disconnect();
		}

		msg.clear();
		msg.append(":");
		msg.append(target->getNickname());
		msg.append("!");
		msg.append(target->getUsername());
		msg.append(std::string("@") += user->getAddr() += " ");
		msg.append("QUIT");
		msg.append(" ");
		msg.append(":Killed by ");
		msg.append(user->getNickname());
		msg.append(" ");
		msg.append(comment);
		msg.append("\r\n");

		std::vector<Channel*> channels= target->getChannels();
		std::vector<Channel*>::iterator it;

		for (it = channels.begin(); it != channels.end(); it++)
		{
			(*it)->broadCasting(msg, NULL);
		}
		msg.clear();
		msg.append(":");
		msg.append(target->getNickname());
		msg.append("!");
		msg.append(target->getUsername());
		msg.append(std::string("@") += user->getAddr() += " ");
		msg.append("ERROR");
		msg.append(" ");
		msg.append(":Closing Link: ");
		msg.append(g_network.getServName());
		msg.append("\r\n");

		if (send(target->getPollFd()->fd, msg.data(), msg.size(), 0) == -1)
		{
			target->disconnect();
		}
		target->disconnect();
		close(target->getPollFd()->fd);

	}
		//TODO implement the KILL command
}
