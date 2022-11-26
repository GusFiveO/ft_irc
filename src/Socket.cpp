/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:29:59 by alorain           #+#    #+#             */
/*   Updated: 2022/11/14 17:27:08 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include "ft_irc.hpp"

Socket::Socket()
{
}

Socket::Socket(struct addrinfo* info) :
	_info(info), _fd(-1)
{
}

Socket::~Socket()
{
	freeaddrinfo(_info);
	if (_fd > 0)
	{
		close(_fd);
	}
}

int
Socket::getFd() const
{
	return _fd;
}

int
Socket::setSockOpt(int opt)
{
	int enable = 1;

	int ret = setsockopt(_fd, SOL_SOCKET, opt, (char*)(&enable), sizeof(enable));
	if (ret)
	{
		perror("setopt");
		std::cerr << "[-] Set option REUSEADDR failed" << std::endl;
		return 1;
	}
	return 0;
}

int
Socket::setSockFlag(int flag)
{
	fcntl(_fd, F_SETFL, flag);
	return 0;
}

int
Socket::bindSocket(struct addrinfo *info)
{

	if (bind(_fd, info->ai_addr, info->ai_addrlen))
	{
		std::cerr << "[-] Socket binding failed" << std::endl;
		return 1;
	}
	std::cout << "[+] Socket binding succes" << std::endl;
	return 0;
}

int
Socket::init(int flag, int opt)
{
	struct addrinfo* tmp;

	for (tmp = _info; tmp != NULL; tmp = tmp->ai_next)
	{
		_fd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (_fd < 0)
			continue;

		if (setSockFlag(flag))
			return 1;

		if (setSockOpt(opt))
			return 1;

		if (bindSocket(tmp) == 0)
			break;
		close(_fd);
	}
	return (0);
}
