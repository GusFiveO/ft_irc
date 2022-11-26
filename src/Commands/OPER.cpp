/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OPER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:03:17 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 21:31:54 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Replies.hpp"

void
OPER(Command* cmd)
{
	User* user = cmd->getUser();
	std::vector<std::string> args = cmd->getArgs();
	Replies rply(user, args);

  
	if (user->isRegistered() == false)
	{
		rply.sendError(E_ERR_NOTREGISTERED);
	}
	else if (args.size() < 3)
	{
		rply.sendError(E_ERR_NEEDMOREPARAMS);
	}
	if (args[2] == g_network.getOperPassword())
	{
		if (user->isOperator() == false)
			g_network.addOperator(*user);
		rply.sendReplies(E_RPL_YOUREOPER);
	}
	else
	{
		rply.sendError(E_ERR_PASSWDMISMATCH);
	}
}
