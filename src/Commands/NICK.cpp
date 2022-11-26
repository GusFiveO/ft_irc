/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschiffe <aschiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:18:19 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 19:10:13 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Replies.hpp"
// #include "Utils.hpp"

bool
checkBNFValidity(std::string x)
{
	std::string::iterator it;

	if (x.size() <= 9 && (isalpha(*x.begin()) || isBNFSpecial(*x.begin())))
	{
		it = x.begin();
		for (; it != x.end() && (	(isalpha(*it) ||
									isdigit(*it) ||
									isBNFSpecial(*it)) &&
									*it != '-')
		; ++it)
		{
		}
	}
	return it != x.end() ? false : true;
}

void
NICK(Command* cmd)
{
    std::vector<std::string> args = cmd->getArgs();
	User* user = cmd->getUser(); 
    Replies rply (user, args);
 
	if (user->isPassed() == false)
	{
		return;
	}
    else if (args.size() < 2)
    {
        rply.sendError(E_ERR_NONICKNAMEGIVEN);
    }
	else if (args[1] != user->getNickname()
		&& g_network.getUser(args[1]) /*&& !user->getNickname().empty()*/)
	{
		std::string prevNick = user->getNickname();
		user->setNickname(args[1]);
        rply.sendError(E_ERR_NICKNAMEINUSE);
		user->setNickname(prevNick);
	}
	else
	{
		if (checkBNFValidity(args[1]) == false)
		{
			rply.sendError(E_ERR_ERRONEUSNICKNAME);
			return ;
		}
		if (user->isRegistered())
		{
			std::string prevNick = user->getNickname();
			user->setNickname(args[1]);
			g_network.removeUser(prevNick);
			g_network.addUser(*user);
		}
		else
		{
			if (!user->getUsername().empty())
			{

				user->setNickname(args[1]);
				g_network.addUser(*user);
				rply.sendReplies(E_RPL_WELCOME);
				user->register_();
			}
			user->setNickname(args[1]);
		}
	}
}
