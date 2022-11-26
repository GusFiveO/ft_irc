/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschiffe <aschiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:19:41 by alorain           #+#    #+#             */
/*   Updated: 2022/11/24 15:42:14 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerSocket.hpp"

ServerSocket::ServerSocket()
{
}

ServerSocket::ServerSocket(struct addrinfo* info, PollFdVector& clientsFd) :
	Socket(info),
	_clientsFd(&clientsFd)
{
}

ServerSocket::~ServerSocket()
{
}

int
ServerSocket::listenSock(size_type max_co)
{
	_maxConnec = max_co;
	if (listen(_fd, _maxConnec) == -1)
	{
		std::cout << "[-] Listen failed" << std::endl;
		return -1;
	}
	std::cout << "Listening..." << std::endl;
	return 0;
}

char*
getaddr(struct sockaddr sa)
{
	struct in_addr addr = (reinterpret_cast<struct sockaddr_in*>(&sa))->sin_addr;

	return inet_ntoa(addr);
}

t_pollfd*
ServerSocket::getNewConnexions()
{
	t_pollfd* client_sock;
	t_sockaddrin client_addr;
	struct sockaddr remote_sockaddr;
	unsigned int len = sizeof(remote_sockaddr);
	socklen_t addr_len;

	client_sock = new t_pollfd;
	std::memset(client_sock, 0, sizeof(*client_sock));
	std::memset(&remote_sockaddr, 0, sizeof(remote_sockaddr));
	while (client_sock->fd != -1)
	{
		addr_len = sizeof(&client_addr);
		std::memset(&client_addr, 0, addr_len);

		client_sock->fd = accept(_fd, &remote_sockaddr, &len);
		if (client_sock->fd < 0)
		{
			if (errno != EWOULDBLOCK)
				perror("accept");
			break;
		}
		client_sock->events = POLLIN;
		_clientsFd->push_back(*client_sock);
		g_network.addConnexion(client_sock, getaddr(remote_sockaddr));
		return client_sock;
	}
	delete client_sock;
	return NULL;
}
