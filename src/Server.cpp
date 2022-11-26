/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:08:20 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 22:08:26 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Network.hpp"
#include "Status.hpp"

e_status g_status;

Server::Server(int port, std::string pwd) :
	_port(port),
	_addr("127.0.0.1"),
	_end(false) 
{
	g_network.setPassword(pwd);
	_servSock = NULL;
}

Server::~Server()
{
}

int
Server::initServerSocket()
{
	struct addrinfo hints;
	struct addrinfo* info;
	struct sockaddr_in hints2;

	std::memset(&hints, 0, sizeof(struct addrinfo));
	std::memset(&hints2, 0, sizeof(struct sockaddr_in));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints2.sin_port = htons(_port);
	hints.ai_addr = reinterpret_cast<struct sockaddr*>(&hints2);

	if (getaddrinfo(_addr.data(), NULL, &hints, &info))
	{
		throw Server::GetAddrInfoFailed();
	}
	info->ai_addr = reinterpret_cast<struct sockaddr*>(&hints2);

	ServerSocket* listener = new ServerSocket(info, _pollFds);
	_servSock = listener;
	_servSock->init(O_NONBLOCK, SO_REUSEADDR);

	if (_servSock->listenSock(50) == -1)
	{
		throw Server::SocketFailed();
	}
	_pollFds.push_back(t_pollfd());
	_pollFds[0].fd = _servSock->getFd();
	_pollFds[0].events = POLLIN;
	return 0;
}

int
Server::pollConnec()
{
	size_t time_limit;

	time_limit = 3 * 60 * 1000; // 3min
	
	int rc;

	if ((rc = poll(&_pollFds[0], _pollFds.size(), time_limit)) == -1)
	{
		std::cerr << "[-] Poll failed" << std::endl;
		_end = true;
		return 1;
	}
	return 0;
}

bool
Server::run()
{
	t_pollfd*	newConnection;

	newConnection = NULL;
	if (_end)
	{
		return false;
	}
	if (_pollFds.size() != 0 && pollConnec() == -1)
	{
		return false;
	}
	_servSock->getNewConnexions();
	//newConnection = _servSock->getNewConnexions();
	//if (newConnection)
	//{
	//	g_network.addConnexion(newConnection);
	//}
	return true;
}

void
Server::servLoop()
{
	g_status = RUNNING;
	while (Server::run())
	{
		for (size_t i = 1; i < Server::getNbOfCo(); i++)
		{
			if (Server::getEvent(i) == 0)
			{
				continue;
			}
			else
			{
				User *user;
				try
				{
					user = g_network.getUser(i - 1);
					if (user->isConnected() != false)
						user->receive();
					if (user->isConnected() != false)
						user->executeCommand();
				}
				catch(...)
				{
					throw;
				}
				Server::checkConnection(i);
			}
		}
		if (g_status == STOP)
		{
			clear();
			break;
		}
	}
}

void
Server::clear()
{
	PollFdVector::iterator it;

	for (it = _pollFds.begin(); it != _pollFds.end(); it++)
	{
		close(it->fd);
	}
	g_network.clear();
	delete _servSock;
}

void
Server::getNewConnexions()
{
	_servSock->getNewConnexions();
}

//void
//Server::receive(size_t idx)
//{
//	User* user;
//	try
//	{
//		user =  g_network.getUser(idx -	1);
//	}
//	catch(...)
//	{
//		throw;
//	}
//	user->receive();
//}

size_t
Server::getNbOfCo() const
{
	return _pollFds.size();
}

int
Server::getEvent(size_t idx) const
{
	return _pollFds[idx].revents;
}

void
Server::removeUser(size_t idx)
{
	_pollFds.erase(_pollFds.begin() + idx);
	g_network.removeUser(idx - 1);
	return; 
}

void
Server::checkConnection(size_t idx)
{
	User* user = g_network.getUser(idx - 1);
	if (user->isConnected() == false)
	{	
		g_network.removeUserFromChannels(user);
		removeUser(idx);
		std::cout << "client disconnected" << std::endl;
	}
}
