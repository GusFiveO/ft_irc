/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:51:08 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 21:35:49 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Command.hpp"
#include "Replies.hpp"

void
PASS(Command* cmd)
{
	User* user = cmd->getUser();
	std::vector<std::string> args = cmd->getArgs();
	Replies rply(user, args);

	if (args.size() < 2)
	{
		rply.sendError(E_ERR_NEEDMOREPARAMS);
	}
	else if (args[1] != g_network.getPassword())
	{
		rply.sendError(E_ERR_PASSWDMISMATCH);
	}
	else
	{
		user->pass();
	}
	
}
