/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODEutils.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:12:35 by alorain           #+#    #+#             */
/*   Updated: 2022/11/24 20:56:13 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEUTIILS_HPP
# define MODEUTIILS_HPP

# include "User.hpp"
# include "Channel.hpp"
# include "Replies.hpp"


typedef enum e_action
{
	NONE,
	ADD,
	REMOVE
} t_action;

class User;
class Channel;

int
addChannelFlag(User* user, Channel* chan, t_action action, char flag);

//Channel::t_flag
//getFlag(char arg);

#endif
