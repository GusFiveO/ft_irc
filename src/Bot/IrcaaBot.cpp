/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcaaBot.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 20:08:19 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 21:30:27 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IrcaaBot.hpp"

IrcaaBot::IrcaaBot(int port, std::string pass) :
	_port(port),
	_end(false),
	_bot_poll(pollfd()),
	_pass(pass)
{
	_ServicesMap[":TIME\r\n"] = &IrcaaBot::timeService;
	IrcaaBot::initStrings();
	IrcaaBot::initIrcaaBot();
}

IrcaaBot::~IrcaaBot()
{
	close(_sock);
}

int
IrcaaBot::initIrcaaBot()
{
	_proto = getprotobyname("tcp");
	if (!_proto)
	{
		std::cerr << "getprotobyname() failed" << std::endl;
		return -1;
	}
	_sock = socket(AF_INET, SOCK_STREAM, _proto->p_proto);
	if (!_sock)
	{
		std::cerr << "socket() failed" << std::endl;
		return -2;
	}
	_addr_in.sin_family = AF_INET;
	_addr_in.sin_port = htons(_port);
	_addr_in.sin_addr.s_addr = inet_addr("127.0.0.1");

	std::memset(&_bot_poll, 0, sizeof(_bot_poll));
	_bot_poll.fd = _sock;
	_bot_poll.events = POLLIN;

	IrcaaBot::connectIrcaaServ();
	IrcaaBot::registerIrcaaServ();
	IrcaaBot::initChannel();
	IrcaaBot::clientLoop();
	return 0;
}

int
IrcaaBot::connectIrcaaServ()
{
	if (connect(_sock, (struct sockaddr *)&_addr_in, sizeof(_addr_in)) == -1)
	{
		std::cerr << "connect() failed" << std::endl;
		this->~IrcaaBot();
		exit(EXIT_FAILURE);
	}
	std::cout << "Connecting to IrcaaServ" << std::endl;
	return 0;
}

int
IrcaaBot::registerIrcaaServ()
{
	if (send(_sock, _pass.data(), _pass.size(), 0) == -1 ||
		send(_sock, _nick.data(), _nick.size(), 0) == -1 ||
		send(_sock, _user.data(), _user.size(), 0) == -1 /* || */
		/* send(_sock, _oper.data(), _oper.size(), 0) == -1 */)
	{
		std::cerr << "send() failed" << std::endl;
		this->~IrcaaBot();
		exit(EXIT_FAILURE);
	}
	return 0;
}

void
IrcaaBot::parseCmdline(std::string x, E_FORMAT flag)
{
	std::string tmp;
	std::vector<std::string> args;
	char* tok = std::strtok(&x[0], "!@ ");

	while (tok != NULL)
	{
		args.push_back(tok);
		tok = std::strtok(NULL, "!@ ");
	}

	if (args[0][0] != ':' || args.size() < 6)
	{
		return ;
	}
	args[0].erase(0, 1);

	tmp.append("PRIVMSG ");
	
	flag == E_PRIVMSG_RPL ? tmp.append(args[0]) : tmp.append("#WESTWORLD");

	std::map<std::string, std::string(IrcaaBot::*)()>::iterator it = _ServicesMap.find(args[5]);

	if (it != _ServicesMap.end())
	{
		std::string(IrcaaBot::*funcPtr)() = it->second;
		tmp.append((this->*funcPtr)());
		if (send(_sock, tmp.data(), tmp.size(), 0) == -1)
		{
			this->~IrcaaBot();
			exit(EXIT_FAILURE);
		}
	}
}

void
IrcaaBot::ircaaRecv()
{
	int		ret;
	char    recv_buff[4096];

	ret = poll(&_bot_poll, 1, (3 * 60 * 1000));
	
	if (ret < 0)
	{
		_end = true ;
		std::cerr << "poll() failed" << std::endl;
	}
	if (_bot_poll.revents & POLLIN)
	{
		std::memset(&recv_buff, '\0', sizeof(recv_buff));
		ret = recv(_sock, &recv_buff, sizeof(recv_buff), 4096);
		if (ret <= 0)
		{
			if (ret == 0 || errno != EWOULDBLOCK)
			{
				this->~IrcaaBot();
				exit(EXIT_FAILURE);
			}
			return ;
		}
		std::string recv_str(recv_buff);
		if (recv_str.find("PRIVMSG") != std::string::npos)
		{
			recv_str.find("#WESTWORLD") != std::string::npos ?
			IrcaaBot::parseCmdline(recv_buff, E_CHANNEL_RPL) :
			IrcaaBot::parseCmdline(recv_buff, E_PRIVMSG_RPL);
		}
		else if (recv_str.find("ERROR") != std::string::npos)
		{
			_end = true;
		}
	}
}

void
IrcaaBot::clientLoop()
{
	//send(_sock, _pong.data(), _pong.size(), 0);
	while (_end == false)
	{
		IrcaaBot::ircaaRecv();
	}
}

void
IrcaaBot::initStrings()
{
	_l_host = "localhost";
	_pass = "PASS " + _pass + "\r\n";
	_nick = "NICK ircaabot\r\n";
	_user = "USER ircaabot ircaabot localhost :IRCAA bot\r\n";
	/* _oper = "OPER ircaabot admin\r\n"; */
	_pong = "PING localhost\r\n";
	_j_channel = "JOIN #WESTWORLD\r\n";
}

void
IrcaaBot::initChannel()
{
	if (send(_sock, _j_channel.data(), _j_channel.size(), 0) == -1)
	{
		std::cerr << "send() failed" << std::endl;
		this->~IrcaaBot();
		exit(EXIT_FAILURE);
	}
}
