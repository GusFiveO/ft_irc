/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:22:50 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 21:43:08 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Replies.hpp"
#include "MODEutils.hpp"

// a - user is flagged as away;
// i - marks a users as invisible;
// w - user receives wallops;
// r - restricted user connection;
// o - operator flag;
// O - local operator flag;
// s - marks a user for receipt of server notices.

static bool
isChannelName(std::string name)
{
	char	prefix[] = "#&+!";
	size_t	i;

	for (i = 0; i < 4; i++)
		if (name[0] == prefix[i])
			break;
	if (prefix[i] == '\0')
		return false;
	else if (prefix[i] == '!')
	{
		for (size_t j = 1; j < 6; j++)
		{
			if (!std::isdigit(name[i]) || !std::isupper(name[i]))
				return false;
		}
	}
	return true;
}

static int
checkArgs(std::vector<std::string> args)
{
	if (args.size() < 2)
		return E_ERR_NEEDMOREPARAMS;
	if (isChannelName(args[1]) == false)
		return -1;
	if (args.size() == 2) //doit retourner les modes du channel 
		return -1;
	if (g_network.getChannel(args[1]) == NULL)
		return E_ERR_NOSUCHCHANNEL;

	return 0;
}

void
MODE(Command* cmd)
{
	User* user = cmd->getUser();
	std::vector<std::string> args = cmd->getArgs();
	Replies rply(user, args);

	int err_code = checkArgs(args);
	if (user->isRegistered() == false)
	{
		rply.sendError(E_ERR_NOTREGISTERED);
	}
	else if (err_code > 0)
	{
		rply.sendError(static_cast<enum ERR>(err_code));
	}
	else if (err_code == -1)
	{
		return;
	}
	else
	{
		Channel*			chan = g_network.getChannel(args[1]);
		std::string 		modeList = args[2];
		std::string 		flags("imonpt");
		int					userIdx;

		userIdx = 1;
		if (chan->isOperator(user) == false)
		{
			return rply.sendError(E_ERR_CHANOPRIVSNEEDED);
		}

		t_action action = NONE;
		for (size_t i = 0; i < modeList.size(); i++)
		{
			if (modeList[i] == '+' || modeList[i] == '-')
			{
				action = (modeList[i] == '+') ? ADD : REMOVE;
			}
			else if (flags.find(modeList[i]) == std::string::npos)
			{
				rply.sendError(E_ERR_UMODEUNKNOWNFLAG);
			}
			else if (modeList[i] != 'o')
			{
				addChannelFlag(user, chan, action, modeList[i]);
			}
			else if (modeList[i] == 'o')
			{
				User* target = g_network.getUser(args[2 + userIdx]);
				if (target)
				{	
					if (action == ADD)
						chan->addOperator(target);
					else
						chan->removeOperator(target->getNickname());
				}
				userIdx++;
			}
		}
	}
}
