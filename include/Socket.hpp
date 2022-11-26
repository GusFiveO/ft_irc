/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschiffe <aschiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:36:50 by alorain           #+#    #+#             */
/*   Updated: 2022/11/21 03:03:45 by aschiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

//# include "ft_irc.hpp"
# include <vector>
# include <poll.h>
# include <string>

typedef struct pollfd t_pollfd;

class Socket
{
	public:
		Socket();
		Socket(struct addrinfo* info);
		~Socket();


		int getFd() const;
		int init(int flag, int opt);

	protected:
		int setSockOpt(int opt);
		int setSockFlag(int flag);
		int bindSocket(struct addrinfo *info);

	protected:
		struct addrinfo*	_info;
		int					_fd;
};

#endif
