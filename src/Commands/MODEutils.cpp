/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODEutils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:12:47 by alorain           #+#    #+#             */
/*   Updated: 2022/11/24 20:55:47 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MODEutils.hpp"

int
addChannelFlag(User* user, Channel* chan, t_action action, char flag)
{
	if (!chan->isOperator(user))
		return E_ERR_CHANOPRIVSNEEDED;
	else
	{
		if (action == ADD)
			chan->addFlag(flag);
		else if (action == REMOVE)
			chan->removeFlag(flag);
	}
	return 0;
}

