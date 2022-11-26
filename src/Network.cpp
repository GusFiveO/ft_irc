/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Network.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:25:42 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 22:33:15 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"
#include "Network.hpp"

Network::Network() :
	_users(),
	_servName("ircaa"),
	_hostname("localhost"),
	_port("8080"), /*Dont forget to remove the default init*/
	_maxCh(5),
	_passwrd("111"),
	_operPass("admin")

{
}

Network::~Network()
{
}

void
Network::setOperPassword(std::string operPass)
{
	_operPass = operPass;
}

std::string
Network::getOperPassword() const
{
	return _operPass;
}

void
Network::setPassword(std::string passwrd)
{
	_passwrd = passwrd;
}

std::string
Network::getPassword() const
{
	return _passwrd;
}

void
Network::addUser(User& user)
{
	_users.insert(std::make_pair<std::string, User*>(user.getNickname(), &user));
}

void
Network::addOperator(User& user)
{
	user.becomeOperator();
	_operators.push_back(&user);
}

User*
Network::addOperator(std::string nickname)
{
	User* newOp;
	newOp = getUser(nickname);
	if (newOp == NULL)
		return NULL;
	addOperator(*newOp);
	return newOp;
}

void
Network::removeOperator(User* user)
{
	std::string nickname = user->getNickname();

	for (OperVector::iterator it = _operators.begin(); it != _operators.end(); it++)
	{
		if ((*it)->getNickname() == nickname)
			_operators.erase(it);
	}
}

void
Network::removeUser(size_t idx)
{
	User* user = _usersHint[idx];
	close(user->getPollFd()->fd);

	if (!user->getNickname().empty())
		_users.erase(user->getNickname());
	_usersHint.erase(_usersHint.begin() + idx);
	delete user;
}

void
Network::removeUser(std::string nickname)
{
	UserMap::iterator userIt = _users.find(nickname);

	if (userIt != _users.end())
	{
		_users.erase(_users.find(nickname));
	}
}

void
Network::addConnexion(t_pollfd* newConnection, char* addr)
{
	//TODO recup l'address du client
	User* newUser = new User(*newConnection, addr);
	_usersHint.push_back(newUser);
}

User*
Network::getUser(size_t idx)
{
	if (idx > _usersHint.size())
		throw(std::out_of_range("Network::getUser()"));
	return _usersHint[idx];
}

std::string
Network::getServName() const
{
	return _servName;
}

std::string
Network::getPort() const
{
	return _port;
}

User*
Network::getUser(std::string nickname)
{
	UserMap::iterator it = _users.find(nickname);
	if (it == _users.end())
		return NULL;
	return it->second;;
}

bool
Network::isUserConnected(size_t idx)
{
	if (idx > _usersHint.size())
		throw(std::out_of_range("Network::isUserConnected()"));
	return _usersHint[idx]->isConnected();
}

bool
Network::maxChannelsReached(User* usr) const
{
	return usr->getChannels().size() >= (size_t)_maxCh ? true : false;
}

size_t
Network::HintSize()
{
	return _usersHint.size();
}

size_t
Network::MapSize()
{
	return _users.size();
}


Channel*
Network::addChannel(std::string x)
{
	Channel* ch = new Channel(x, 5);

	_channelVec.push_back(ch);
	return ch;
}

void
Network::removeChannel(std::string chanName)
{
	ChannelVector::iterator it;

	for (it = _channelVec.begin(); it != _channelVec.end(); it++)
	{
		if ((*it)->getTitle() == chanName)
		{
			_channelVec.erase(it);
			break;
		}
	}
}

Channel*
Network::getChannel(std::string x) const
{
	Channel* ch = NULL;
	for (ChannelVector::const_iterator it = _channelVec.begin(); it != _channelVec.end(); ++it)
	{
		if (x == (*it)->getTitle())
		{
			ch = *it;
		}
	}
	return (ch);
}

void
Network::channelAddUser(std::string x, User* user)
{
	Channel* ch = getChannel(x);
	ch->addUser(user);
}

void
Network::channelRemoveUser(std::string x, User* user)
{
	Channel* ch = getChannel(x);
	ch->removeUser(user);
}

/* TEMP */

void
Network::printMap()
{
	UserMap::iterator it = _users.begin();
	
	while (it != _users.end())
	{
		std::cout << "( " << (it->second->isOperator() == true ? "oper, " : "") << it->second->getNickname() << "--"<< it->second->getUsername() << "--" << it->second->getRealname() << " )"<< ", ";
		it++;
	}
	std::cout << std::endl;
	
}

void
Network::printChanUser(std::string chanName)
{
	ChannelVector::iterator it;

	for (it = _channelVec.begin(); it != _channelVec.end(); it++)
	{
		if ((*it)->getTitle() == chanName)
		{
			(*it)->printUsers();
		}
	}
}

Network::ChannelVector
Network::getChannelVec() const
{
	return _channelVec;
}

void
Network::removeUserFromChannels(User* user)
{
	std::vector<Channel*> channels = user->getChannels();

	std::vector<Channel*>::iterator it;

	for (it = channels.begin(); it != channels.end(); it++)
	{
		std::string mess;

		mess.append(":");
		/* Test */
		mess.append(user->getNickname());
		mess.append("!");
		mess.append(user->getUsername());
		mess.append(std::string("@") += user->getAddr() += " ");
		mess.append(" ");
		mess.append("PART ");
		mess.append((*it)->getTitle());
		mess.append(" ");
		mess.append(":");
		mess.append("user quitted the server");
		mess.append("\r\n");
		(*it)->broadCasting(mess, user);
		(*it)->removeUser(user);
		if ((*it)->empty())
			removeChannel((*it)->getTitle());
	}
}

void
Network::setPort(std::string x)
{
	_port = x;
}

std::string
Network::getCurrentTime() const
{
	std::time_t x = std::time(NULL);
	return std::asctime(std::localtime(&x));
}

void
Network::clear()
{
	UserVector::iterator it;

	for (it = _usersHint.begin(); it != _usersHint.end(); it++)
	{
		delete *it;
	}

 	ChannelVector::iterator it2;
	for (it2 = _channelVec.begin(); it2 != _channelVec.end(); it2++)
	{
		delete *it2;
	}
}

void
Network::setHostname(std::string hostname)
{
	_hostname = hostname;
}

std::string
Network::getHostname() const
{
	return _hostname;
}

char*
Network::getsockaddr(int fd)
{
	struct sockaddr sa;
	unsigned int namelen = sizeof(&sa);

	bzero(&sa, sizeof(sa));

	if (getsockname(fd, &sa, &namelen))
		return NULL;

	struct in_addr addr = (reinterpret_cast<struct sockaddr_in*>(&sa))->sin_addr;

	return inet_ntoa(addr);
}

void
Network::broadcast(std::string mess)
{
	UserVector::iterator it;

	for (it = _usersHint.begin(); it != _usersHint.end(); it++)
	{
		if (send((*it)->getPollFd()->fd, mess.data(), mess.size(), 0) == -1)
		{
			(*it)->disconnect();
		}
	}
}

void
Network::printChannels()
{
	ChannelVector::iterator it;

	for (it = _channelVec.begin(); it != _channelVec.end(); it++)
	{
		std::cout << (*it)->getTitle() << std::endl;
	}
}
