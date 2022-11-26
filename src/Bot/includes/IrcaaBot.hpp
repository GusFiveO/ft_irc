/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcaaBot.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 20:08:35 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 20:36:05 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCAA_BOT_HPP
# define IRCAA_BOT_HPP

# include <iostream>
# include <vector>

# include <poll.h>
# include <netdb.h>
# include <unistd.h>
# include <stdlib.h>
# include <memory>
# include <cstring>
# include <ctime>
# include <map>
# include <errno.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/socket.h>

enum E_FORMAT
{
	E_PRIVMSG_RPL,
	E_CHANNEL_RPL
};

class IrcaaBot
{
	public :

		IrcaaBot(int port, std::string pass);
		~IrcaaBot();

		int
		initIrcaaBot();
		
		void
		initStrings();
		
		void
		initChannel();

		int
		connectIrcaaServ();
		
		int
		registerIrcaaServ();
		
		void
		clientLoop();
		
		void
		ircaaRecv();
		
		void
		parseCmdline(std::string x, E_FORMAT flag);

		// Bot services

		std::string
		timeService();

		// typedef std::string(IrcaaBot::*Services)();

		// https://stackoverflow.com/questions/45386009/assign-function-pointer-inside-class

	private :

		int							_sock;
		int							_port;

		bool						_end;

		struct sockaddr_in  		_addr_in;
		struct protoent*			_proto;

		struct pollfd				_bot_poll;

		// char 						_buff[4096];

		std::string					_pass;
		std::string					_l_host;

		std::string					_nick;
    	std::string					_user;
		std::string					_oper;
		std::string					_pong;
		std::string					_quit;
		std::string					_j_channel;

		std::map<std::string, std::string(IrcaaBot::*)()> _ServicesMap;
};

#endif
