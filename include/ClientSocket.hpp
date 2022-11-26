/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschiffe <aschiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:59:57 by alorain           #+#    #+#             */
/*   Updated: 2022/11/21 17:49:28 by aschiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_SOCKET_HPP
# define CLIENT_SOCKET_HPP

# include "Socket.hpp"
# include "ft_irc.hpp"

class ClientSocket : public Socket
{
	typedef std::vector<struct pollfd>::size_type	size_type;

	public:
		ClientSocket();
		ClientSocket(struct addrinfo* info, t_pollfd& clientFd);
		virtual ~ClientSocket();

		int
		receive();

		void
		flush();

		int
		respond(size_t idx);

		void
		setAwayMsg(std::string);

		std::string
		getBuffer();

		std::string
		parseFdProvider(std::string x);

	private:

		t_pollfd*	_clientFd;
		std::string	_buffer;
		std::string _awayMsg;
		
};

#endif 
