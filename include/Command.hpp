/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschiffe <aschiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:16:37 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 16:19:49 by aschiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "ft_irc.hpp" 
//# include "Replies.hpp"
# include "User.hpp"
# include "Utils.hpp"


class User;
class Channel;

class Command
{
	public :

		typedef void(*Commands)(Command*);

		Command(Commands, User*, std::vector<std::string>);
		~Command();

		void
		display_vec();

		void
		execute();

		std::vector<std::string>
		getArgs();

		User*
		getUser() const;

	private :

		Commands						_funcPtr;
		User*							_user;
		std::vector<std::string>		_arguments;

};

void	NOTICE(Command* cmd);

void	PING(Command* cmd);

void	MODE(Command* cmd);

void	OPER(Command* cmd);

void	PASS(Command* cmd);

void	JOIN(Command* cmd);

void	HELP(Command* cmd);

void	LIST(Command* cmd);

void	PART(Command* cmd);

void	QUIT(Command* cmd);

void	NICK(Command* cmd);

void	USER(Command* cmd);

void	WHOIS(Command* cmd);

void	INVITE(Command* cmd);

void	KICK(Command* cmd);

void	TOPIC(Command* cmd);

void	PRIVMSG(Command* cmd);

void	DCC(Command* cmd);

void SQUIT(Command* cmd);

void KILL(Command* cmd);

#endif
