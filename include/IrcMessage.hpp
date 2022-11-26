/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcMessage.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:16:37 by alorain           #+#    #+#             */
/*   Updated: 2022/11/02 15:29:51 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCMESSAGE_HPP
# define IRCMESSAGE_HPP

# include "ft_irc.hpp"

class IrcMessage
{
	public:
		IrcMessage();
		IrcMessage(std::string raw);
		~IrcMessage();

	private:

		std::string _raw;
		Prefix*		_prefix;
		Command*	_command;
		std::string _args;
};


#endif
