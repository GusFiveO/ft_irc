/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschiffe <aschiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:18:19 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 19:10:09 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Replies.hpp"

//check si le USER est registered (il a eu NICK + USER)
// check si il a deja eu USER

void
USER(Command* cmd)
{
	User* user = cmd->getUser();
	std::vector<std::string>	args = cmd->getArgs();
	Replies rply(user, args);

	if (user->isPassed() == false)
	{
		return;
	}
	if (user->isRegistered())
	{
		rply.sendError(E_ERR_ALREADYREGISTRED);
	}
	else if (args.size() < 5)
	{
		rply.sendError(E_ERR_NEEDMOREPARAMS);
	}
	else
	{
		user->setUsername(args[1]);
		user->setRealname(args[4]);
		if (!user->getNickname().empty())
		{
			rply.sendReplies(E_RPL_WELCOME);
			user->register_();
			g_network.addUser(*user);
		}

	}
}
