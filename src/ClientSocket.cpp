/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:19:41 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 21:28:58 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"

ClientSocket::ClientSocket()
{
}

ClientSocket::ClientSocket(struct addrinfo* info, t_pollfd& clientFd) :
	Socket(info),
	_clientFd(&clientFd)
{
}

ClientSocket::~ClientSocket()
{
}

std::string
ClientSocket::parseFdProvider(std::string x)
{
	if (x.find("PRIVMSG") == (std::string::size_type)-1)
	{
		std::string();
	}
	std::string provider;
	for (std::string::iterator it = x.begin() + 1; *it != '!'; ++it)
	{
		provider += *it;
	}
	return provider ;
}

int
ClientSocket::receive()
{
	int ret;
	char buffer[4096];

	std::memset(&buffer, '\0', sizeof(buffer));

	ret = recv(_clientFd->fd, &buffer, 4096, MSG_DONTWAIT);
	if (ret <= 0)
	{
		if (ret == 0 || errno != EWOULDBLOCK)
		{
			std::cout << "client disconnected" << std::endl;
			return DECO_CODE;
		}
		return 1;
	}

	buffer[ret] = '\0';
	_buffer += std::string(buffer);
	return 0;
}

/* Clear the buffer by outputting everything. */

void
ClientSocket::flush()
{
	_buffer.clear();
}

std::string
ClientSocket::getBuffer()
{
	return _buffer;
}

void
ClientSocket::setAwayMsg(std::string x)
{
	_awayMsg = x;
}
