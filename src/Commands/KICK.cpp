/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:00:00 by aschiffe          #+#    #+#             */
/*   Updated: 2022/11/25 21:43:59 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Replies.hpp"

void
KICK(Command* cmd)
{
	User* user = cmd->getUser();
	std::vector<std::string> args = cmd->getArgs();
	Replies	rply(user, args);
	Channel* chan;

	if (user->isRegistered() == false)
	{
		rply.sendError(E_ERR_NOTREGISTERED);
	}
	else if (args.size() < 3)
	{
		rply.sendError(E_ERR_NEEDMOREPARAMS);
	}
	else if ((chan = g_network.getChannel(args[1])) == NULL)
	{
		std::vector<std::string> errArg;
		errArg.push_back(args[1]);
		Replies	err(user, errArg);

		err.sendError(E_ERR_NOSUCHCHANNEL);
	}
	else if (chan->isOperator(user) == false)
	{
		rply.sendError(E_ERR_CHANOPRIVSNEEDED);
	}
	else if (chan->isPartOf(user->getNickname()) == false)
	{
		std::vector<std::string> errArg;
		errArg.push_back(args[1]);
		Replies	err(user, errArg);

		err.sendError(E_ERR_NOTONCHANNEL);
	}
	else
	{
		std::vector<std::string> errArg;
		errArg.push_back(args[1]);
		User* target = g_network.getUser(args[2]);
		if (target == NULL)
		{
			Replies	err(user, errArg);
			err.sendError(E_ERR_USERNOTINCHANNEL);
			return;
		}
			
		//Replies	err(target, errArg);
		Replies	err(user, errArg);
			
		std::string msg = args[args.size() - 1];
		if (msg.size() == 1)
			msg = std::string(":leave the channel");
		
		/*
		je construit le PART message a envoyer a tous les user du channel
		*/

		std::string w_msg;

		w_msg.append(":");
		w_msg.append(user->getNickname());
		w_msg.append("!");
		w_msg.append(user->getUsername());
		w_msg.append(std::string("@") += user->getAddr() += " ");
		w_msg.append("KICK");
		w_msg.append(" ");
		w_msg.append(chan->getTitle());
		w_msg.append(" ");
		w_msg.append(target->getNickname());
		w_msg.append(" ");
		w_msg.append(msg);
		w_msg.append("\r\n");

		chan->broadCasting(w_msg, user);
		chan->removeUser(target);
		target->removeChannel(chan);

		if (send(user->getPollFd()->fd, w_msg.data(), w_msg.size(), 0) == -1)
		{
			user->disconnect();
		}
	}
		
}
