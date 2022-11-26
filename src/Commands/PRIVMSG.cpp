/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:00:00 by aschiffe          #+#    #+#             */
/*   Updated: 2022/11/25 21:44:18 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Replies.hpp"

/* Check with many bytes */

void
PRIVMSG(Command* cmd)
{
	User*						user = cmd->getUser();
	std::vector<std::string>	args = cmd->getArgs();
	std::string 				msg;
	Replies 					rply(user, args);
	User*						recep = NULL;
	Channel*					ch = NULL;

	/* If the first character is a hashtag, it indicates that it is a channel,
	otherwise it is a message to another user */

	if (user->isRegistered() == false)
	{
		rply.sendError(E_ERR_NOTREGISTERED);
	}
	else if (args[1][0] == '#')
	{
		if ((ch = g_network.getChannel(args[1])) == NULL)
		{
			rply.sendError(E_ERR_NOSUCHNICK);
			return;
		}
		else if ((ch->isMembersOnly() && ch->isPartOf(user->getNickname()) == false))
		{
			std::vector<std::string> errArg;
			errArg.push_back(args[1]);
			Replies	err(user, errArg);
			err.sendError(E_ERR_NOTONCHANNEL);
			return;
		}
		else if (!ch->isOperator(user) && ch->isDictature())
			return;
	}
	else
	{
		if ((recep = g_network.getUser(args[1])) == NULL || recep->isConnected() == false)
		{
			rply.sendError(E_ERR_NOSUCHNICK);
			return;
		}
	}
	if (args.size() == 1)
	{
		rply.sendError(E_ERR_NORECIPIENT);
	}
	else if (args.size() < 3)
	{
		rply.sendError(E_ERR_NOTEXTTOSEND);
	}
	else 
	{
		msg.append(std::string(":"));
		msg.append(user->getNickname());
		msg.append(std::string("!"));
		msg.append(user->getUsername());
		msg.append(std::string("@") += user->getAddr() += " ");
		msg.append(args[0]);
		msg.append(std::string(" "));

		std::string dest;

		/* Here i check if the recipient is a channel or a user, depending on that,
		i will concatenate the correct recipient */

		ch != NULL ? dest += ch->getTitle() : dest += recep->getNickname();		
		msg += dest += std::string(" :");

		/* We advance the iterator 2 steps since the first two elements of our vector are composed of the CMD and the recipient.
		Our goal here is to copy the message */

		for (std::vector<std::string>::iterator it = args.begin() + 2; it != args.end(); ++it)
		{
			if (it != args.begin() + 2)
				it->insert(0, " ");
			else
				it->erase(it->begin());
			msg += *it;
		}
		msg += std::string("\r\n");

		/* At this stage, we must check if we should broadcast a channel or send a sequence to a specific user */
		

		if (recep == NULL)
		{
			ch->broadCasting(msg, user);
		}
		else
		{
			if (send(recep->getPollFd()->fd, msg.data(), msg.size(), 0) == -1)
				recep->disconnect();
		}
	}
}
