/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:00:00 by aschiffe          #+#    #+#             */
/*   Updated: 2022/11/25 21:44:12 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Replies.hpp"

void
JOIN(Command* cmd)
{
	User* 						user = cmd->getUser();
	std::vector<std::string>	args = cmd->getArgs();
	Replies 					rply(user, args);
	Channel* 					chan = NULL;
	Network::ChannelVector		chVec = g_network.getChannelVec();


	if (user->isRegistered() == false)
	{
		rply.sendError(E_ERR_NOTREGISTERED);
	}
	else if (args.size() == 1)
	{
		rply.sendError(E_ERR_NEEDMOREPARAMS);
	}
	else if (g_network.maxChannelsReached(user) == true)
	{
		rply.sendError(E_ERR_TOOMANYCHANNELS);
	}
	else if (args[1] == "0" && args.size() == 2)
	{
		for (Network::ChannelVector::iterator it = chVec.begin(); it != chVec.end(); ++it)
		{
			Channel* ch = *it;
			std::string tmp = user->getNickname();
			if (ch->isPartOf(tmp) == true)
			{
				ch->removeUser(tmp);
			}
		}
	}
	else if (args.size() >= 2)
	{
		std::string tok_args = args[1];
		char* tok = std::strtok(&tok_args[0], ",");
		while (tok != NULL)
		{
			std::string tokstr;
			tokstr = tok;
			args[1] = tokstr;
			chan = g_network.getChannel(tokstr);
			if (chan == NULL)
			{
				chan = g_network.addChannel(args[1]);
				chan->addUser(user);
				user->addChannel(chan);

				std::string mess(":");
				mess += user->getNickname();
				mess.append("!");
				mess.append(user->getUsername());
				mess.append(std::string("@") += user->getAddr() += " ");
				mess += std::string("JOIN :") += chan->getTitle() += std::string("\r\n");


				if (send(user->getPollFd()->fd, mess.data(), mess.size(), 0) == -1)
					user->disconnect();

				rply.sendReplies(E_RPL_TOPIC);
				rply.sendReplies(E_RPL_NAMREPLY);
				rply.sendReplies(E_RPL_ENDOFNAMES);
			}
			else if (chan->isInviteOnly() && user->isInvited(chan) == false)
			{
				rply.sendError(E_ERR_INVITEONLYCHAN);
			}
			else
			{
				if (chan->isChannelFull() == true)
				{
					rply.sendError(E_ERR_CHANNELISFULL);
				}
				else
				{
					chan->addUser(user);
					user->addChannel(chan);

					std::string mess(":");
					mess += user->getNickname();
					mess.append("!");
					mess.append(user->getUsername());
					mess.append(std::string("@") += user->getAddr() += " ");
					mess += std::string("JOIN :") += chan->getTitle() += std::string("\r\n");


					if (send(user->getPollFd()->fd, mess.data(), mess.size(), 0) == -1)
						user->disconnect();
				
					rply.sendReplies(E_RPL_TOPIC);
					rply.sendReplies(E_RPL_NAMREPLY);
					rply.sendReplies(E_RPL_ENDOFNAMES);
				}
			}
			tok = std::strtok(NULL, ",");
		}
	}
	return ;
}
