/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschiffe <aschiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:59:57 by alorain           #+#    #+#             */
/*   Updated: 2022/11/14 18:45:25 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_SOCKET_HPP
# define SERVER_SOCKET_HPP

# include "Socket.hpp"
# include "Replies.hpp"

class ServerSocket : public Socket
{
	typedef std::vector<struct pollfd>				PollFdVector;
	typedef std::vector<bool>						ConnectionVector;
	typedef std::vector<struct pollfd>::size_type	size_type;

	public:
		ServerSocket();
		ServerSocket(struct addrinfo* info, PollFdVector& clientsFd);
		~ServerSocket();

		int
		listenSock(size_type max_co);

		t_pollfd*
		getNewConnexions();

	private:

		PollFdVector*	_clientsFd;
		size_type		_maxConnec;
		
};

#endif 
