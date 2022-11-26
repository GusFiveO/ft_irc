/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschiffe <aschiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:38:07 by alorain           #+#    #+#             */
/*   Updated: 2022/11/22 16:51:56 by aschiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include "ft_irc.hpp"
//# include "Network.hpp"
# include "Command.hpp"
// # include "Commands.hpp"

class User;
class Command;

class Parser
{

	public:

		Parser();
		Parser(std::string buffer);
		~Parser();

		Command* 	parseCommand(User* user);
		void		initCommandsMap();

		typedef void(*Commands)(Command*);

	private:
		//Network*	_network;
		//IrcMessage	_message;
		std::map<std::string, Commands> _CommandsMap;
		std::string 					_raw;

};

#endif
