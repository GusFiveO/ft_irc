/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschiffe <aschiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:00:00 by aschiffe          #+#    #+#             */
/*   Updated: 2022/11/24 20:01:19 by aschiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Replies.hpp"

void
INVITE(Command* cmd)
{
	(void)cmd;
	User*		user = cmd->getUser();
	User*		target = NULL;
	Channel*	chan = NULL;
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
	else if ((chan = g_network.getChannel(args[2])) == NULL)
	{
		rply.sendError(E_ERR_NOSUCHCHANNEL);
	}
	else if (chan->isPartOf(user->getNickname()) == false)
	{
		rply.sendError(E_ERR_NOTONCHANNEL);
	}
	else if (chan->isPartOf(args[1]) == true)
	{
		rply.sendError(E_ERR_USERONCHANNEL);
	}
	else if ((target = g_network.getUser(args[1])) == false)
	{
		rply.sendError(E_ERR_NOSUCHNICK);
	}
	else
	{
		if (chan->isInviteOnly() && chan->isOperator(user) == false)
		{
			rply.sendError(E_ERR_CHANOPRIVSNEEDED);
		}
		else
		{
			std::string msg;

			msg.append(std::string(":"));
			msg.append(user->getNickname());
			msg.append(std::string("!"));
			msg.append(user->getUsername());
			msg.append(std::string("@") += user->getAddr() += " ");
			msg.append(args[0]);
			msg.append(std::string(" "));
			msg.append(std::string(target->getNickname()));
			msg.append(std::string(" "));
			msg.append(std::string(chan->getTitle()));
			msg.append(std::string("\r\n"));

			if (send(target->getPollFd()->fd, msg.data(), msg.size(), 0) == -1)
				return target->disconnect();
			target->addInvite(chan);
			
			rply.sendReplies(E_RPL_INVITING);
		}
	}
}
