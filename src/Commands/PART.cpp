/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:00:00 by aschiffe          #+#    #+#             */
/*   Updated: 2022/11/25 22:43:42 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Replies.hpp"

void
quitChannel(std::string chanName, User* user, std::vector<std::string> args)
{
	Channel*	chan = g_network.getChannel(chanName);
	std::vector<std::string> errArg;
	errArg.push_back(chanName);
	Replies	err(user, errArg);
	Replies	rply(user, args);

	if (user->isRegistered() == false)
	{
		rply.sendError(E_ERR_NOTREGISTERED);
	}
	else if (chan == NULL)
	{
		err.sendError(E_ERR_NOSUCHCHANNEL);
	}
	else if (chan->isPartOf(user->getNickname()) == false)
	{
		err.sendError(E_ERR_NOTONCHANNEL);
	}
	else
	{
		std::string msg = args[args.size() - 1];
		if (msg[0] != ':')
			msg = std::string("leave the channel");
		else
			msg.erase(0, 1);
		
		/*
		je construit le PART message a envoyer a tous les user du channel
		*/

		std::string w_msg;

		w_msg.append(":");
		w_msg.append(user->getNickname());
		w_msg.append("!");
		w_msg.append(user->getUsername());
		w_msg.append(std::string("@") += user->getAddr() += " ");
		w_msg.append("PART");
		w_msg.append(" ");
		w_msg.append(chanName);
		w_msg.append(" ");
		w_msg.append(":");
		w_msg.append(msg);
		w_msg.append("\r\n");

		chan->broadCasting(w_msg, user);

		/*
		Askip sur chicago ils disent que je dois remove le chan quand il est vide pas sur
		*/

		if (chan->empty())
			g_network.removeChannel(chan->getTitle());

		if (send(user->getPollFd()->fd, w_msg.data(), w_msg.size(), 0) == -1)
		{
			user->disconnect();
		}
		user->removeChannel(chan);
		chan->removeUser(user);
		if (chan->empty())
			delete chan;
		err.sendError(E_ERR_NOTONCHANNEL); //je fais ca pour fermer la window de irssi mais pas obligatoire
	} 

}

void
PART(Command* cmd)
{
	User* user = cmd->getUser();
	std::vector<std::string> args = cmd->getArgs();
	Replies	rply(user, args);

	if (args.size() < 2)
	{
		rply.sendError(E_ERR_NEEDMOREPARAMS);
	}
	else
	{
		char	*tok;
		std::string channelList = args[1];

		tok = std::strtok(&channelList[0], ",");
		while (tok)
		{
			quitChannel(std::string(tok), user, args);
			tok = std::strtok(NULL, ",");
		}
	}
}
