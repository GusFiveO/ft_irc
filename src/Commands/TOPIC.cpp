/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:00:00 by aschiffe          #+#    #+#             */
/*   Updated: 2022/11/25 21:43:09 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Replies.hpp"

//TODO toutes les modifs doivent envoyer un mesage au client pour le tenir au courant

void
TOPIC(Command* cmd)
{
	User*						user = cmd->getUser();
    std::vector<std::string>	args = cmd->getArgs();
	Channel*					ch = g_network.getChannel(args[1]);
	Replies 					rply(user, args);

	if (user->isRegistered() == false)
	{
		rply.sendError(E_ERR_NOTREGISTERED);
	}
	else if (args.size() == 1)
	{
		rply.sendError(E_ERR_NEEDMOREPARAMS);
		return ;
	}
	else if (ch == NULL)
	{
		rply.sendReplies(E_RPL_NOTOPIC);
	}
	else
	{
		if (args.size() == 2)
		{
			if (ch->getTopic().size() == 0 && user->isOperator() == false)
			{
				rply.sendReplies(E_RPL_NOTOPIC);
			}
			else
			{
				rply.sendReplies(E_RPL_TOPIC);
			}
		}
		if (args.size() >= 3)
		{
			if (ch->isPartOf(user->getNickname()) == false)
			{
				rply.sendError(E_ERR_NOTONCHANNEL);
			}
			else if (ch->isTopicStrict() && ch->isOperator(user) == false)
			{
				rply.sendError(E_ERR_CHANOPRIVSNEEDED);
				// rply.sendError(E_ERR_NOCHANMODES)
			}
			else // Depends on mode implementation
			{
				if (args[2] == ":" && args[2].size() == 1)
				{
					ch->clearTopic();
					
					std::string mess(":");
					mess += user->getNickname();
					mess.append("!");
					mess.append(user->getUsername());
					mess.append(std::string("@") += user->getAddr() += " ");
					mess += std::string(" TOPIC ")  += ch->getTitle() + std::string(" :") += std::string("\r\n");
					ch->broadCasting(mess, NULL);
				}
				else if (args[2][0] == ':')
				{
					std::string x = args[2];
					x.erase(x.begin());
					ch->setTopic(x);
					std::string mess(":");
					mess += user->getNickname();
					mess.append("!");
					mess.append(user->getUsername());
					mess.append(std::string("@") += user->getAddr() += " ");
					mess += std::string(" TOPIC ") += ch->getTitle() += std::string(" :");

					mess += x;
					for (size_t i = 3; i < args.size(); i++)
					{
						mess += std::string(" ");
						mess += args[i];
					}

					mess += std::string("\r\n");
					ch->broadCasting(mess, NULL);
				}
			}
		}
	}
}
