/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschiffe <aschiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:00:00 by aschiffe          #+#    #+#             */
/*   Updated: 2022/11/24 19:59:15 by aschiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Replies.hpp"

void
LIST(Command* cmd)
{
	std::vector<std::string>	args = cmd->getArgs();
	User*						user = cmd->getUser();
	Replies 					rply(user, args);
	Network::ChannelVector		chVec = g_network.getChannelVec();
	Channel*					ch = NULL;

	if (user->isRegistered() == false)
	{
		rply.sendError(E_ERR_NOTREGISTERED);
	}
	else if (args.size() == 1 || (args.size() == 2 && args[1].size() == 0))
	{
		/* This is for irssi client */
		if (args.size() == 2 && args[1].size() == 0)
		{
			args.erase(args.begin() + 1);
		}
		while (chVec.size() != 0)
		{
			args.insert(args.end(), (*chVec.begin())->getTitle());
			rply.sendReplies(E_RPL_LIST);
			chVec.erase(chVec.begin());
			args.erase(args.begin() + 1);
		}
	}
	else if (args.size() == 2)
	{
		ch = g_network.getChannel(args[1]);
		if (ch == NULL)
		{
			rply.sendError(E_ERR_NOSUCHSERVER);
			return;
		}
		rply.sendReplies(E_RPL_LIST);
	}
	else if (args.size() > 2)
	{
		Channel* ch;
		while (args.size() != 1)
		{
			ch = g_network.getChannel(args[1]);
			if (ch == NULL)
			{
				rply.sendError(E_ERR_NOSUCHSERVER);
			}
			else
			{
				rply.sendReplies(E_RPL_LIST);
			}
			args.erase(args.begin() + 1);
		}
	}
	rply.sendReplies(E_RPL_LISTEND);
	// ERR_TOOMANYMATCHES
}
