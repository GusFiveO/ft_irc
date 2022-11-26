/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:31:12 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 22:51:24 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

UserInfo::UserInfo() :
	nickname(), username(), realname()
{
}

UserInfo::UserInfo(std::string nick, std::string user, std::string real) :
	nickname(nick),
	username(user),
	realname(real)
{
}

User::User() :
	_pollFd(NULL),
	_info(),
	_status(PENDING),
	_socket(),
	_channels(),
	_registerTime(std::clock()),
	_addr("localhost")
{
}

User::User(struct pollfd& pollfd, char* addr) :
	_pollFd(&pollfd),
	_info(),
	_status(PENDING),
	_socket(NULL, pollfd),
	_op(false),
	_channels(),
	_registerTime(std::clock()),
	_addr(addr)
{
}

User::User(t_UserInfo info, struct pollfd& pollfd, char* addr) :
	_pollFd(&pollfd),
	_info(info),
	_status(PENDING),
	_socket(NULL, pollfd),
	_op(false),
	_channels(),
	_registerTime(std::clock()),
	_addr(addr)
{
}

User::~User()
{
	delete _pollFd;
	std::vector<Channel*>::iterator it;
	
	for (it = _channels.begin(); it != _channels.end(); it++)
	{
		if (!g_network.getChannel((*it)->getTitle()))
			delete *it;
	}
}
				/* FONCTIONS LIEES AU SOCKET */

void
User::receive()
{
	if (_socket.receive() == DECO_CODE)
		disconnect();
}

void
User::flushBuffer()
{
	_socket.flush();
}

void
User::executeCommand()
{
	std::string line;
	std::stringstream ss;

	if (_socket.getBuffer().find("\n") == std::string::npos)
	{
		return ;
	}
	ss << _socket.getBuffer();
	while (isConnected() && std::getline(ss, line))
	{
		Command* command;
		_parser = new Parser(line);
		command = _parser->parseCommand(this);
		if (command)
		{
			command->execute();
		}
		delete command;
		delete _parser;
	}
	if (isConnected())
		flushBuffer();
	return ;
}


std::string
User::getBuffer()
{
	return _socket.getBuffer();
}

std::string
User::getNickname() const
{
	return _info.nickname;
}
	
std::string
User::getUsername() const
{
	return _info.username;
}

std::string
User::getRealname() const
{
	return _info.realname;
}

t_pollfd*
User::getPollFd() const
{
	return _pollFd;
}

bool
User::isConnected() const
{
	return (_status != DISCONNECTED) ? true : false ;
}

void
User::pass()
{
	_status = PASS;
}

bool
User::isPassed() const
{
	return (_status >= PASS) ? true : false ;
}

void
User::register_()
{
	_status = REGISTERED;
}

bool
User::isRegistered() const
{
	return (_status >= REGISTERED) ? true : false;
}

bool
User::isOperator() const
{
	return _op;
}

void
User::becomeOperator()
{
	_op = true;
}

void
User::disconnect()
{
	_status = DISCONNECTED;
}

void
User::printStatus()
{
	switch (_status)
	{
		case 0:
			std::cout << "PENDING" << std::endl;
			break;
		case 1:
			std::cout << "DISCONNECTED" << std::endl;
			break;
		case 2:
			std::cout << "PASS" << std::endl;
			break;
		case 3:
			std::cout << "REGISTERED" << std::endl;
			break;
		case 4:
			std::cout << "CONNECTED" << std::endl;
			break;
	}
}

void
User::setNickname(std::string nick)
{
	_info.nickname = nick;
}

void
User::setUsername(std::string user)
{
	_info.username = user;
}

void
User::setRealname(std::string real)
{
	_info.realname = real;
}

std::vector<Channel*>
User::getChannels()
{
	return _channels;
}

void
User::addChannel(Channel* chan)
{
	_channels.push_back(chan);
}

void
User::removeChannel(Channel* chan)
{
	_channels.erase(std::find(_channels.begin(), _channels.end(), chan));
}

void
User::setAwayMsg(std::string x)
{
	_socket.setAwayMsg(x);
}

clock_t
User::getRegTime() const
{
	return _registerTime;
}

void
User::addInvite(Channel* chan)
{
	_invited.push_back(chan);	
}

bool
User::isInvited(Channel* chan)
{
	std::vector<Channel*>::iterator it;

	for (it = _invited.begin(); it != _invited.end(); it++)
	{
		if (*it == chan)
			return true;
	}
	return false;
}

std::string
User::getAddr() const
{
	return _addr;
}
