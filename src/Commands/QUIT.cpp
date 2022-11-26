/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:00:00 by aschiffe          #+#    #+#             */
/*   Updated: 2022/11/25 21:43:10 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Replies.hpp"

void
QUIT(Command* cmd)
{
    User*                       user = cmd->getUser();
    std::vector<std::string>	args = cmd->getArgs();
    /*Error: */

    send(user->getPollFd()->fd, args[1].data(), args[1].size(), 0);
    user->disconnect();
 
    (void)cmd;
}
