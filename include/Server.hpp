/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:31:57 by alorain           #+#    #+#             */
/*   Updated: 2022/11/23 15:18:50 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "ServerSocket.hpp"
# include "User.hpp"

class User;

class Server
{
	typedef std::map<std::string, User*>	UserMap;
	typedef std::vector<struct pollfd>		PollFdVector;

	public:
	
		Server(int port, std::string addr);
		~Server();
		//Server(struct addrinfo);

		int
		initServerSocket();

		bool
		run();

		void
		servLoop();

		int
		pollConnec();

		void
		receive(size_t idx);

		size_t
		getNbOfCo() const;
		
		int
		getEvent(size_t idx) const;

		void
		getNewConnexions();
		
		void
		removeUser(size_t idx);

		void
		checkConnection(size_t idx);
		
		void
		respond(size_t idx);

		int
		executeCommand(size_t idx);

		void
		clear();

		class PasswordAuthenticationFailed 
		{
			public :
				virtual const char* what() const throw()
				{
					return ("Server::PasswordAuthenticationFailed : wrong pwd");
				}
		};

		class SocketFailed 
		{
			public :
				virtual const char* what() const throw()
				{
					return ("Server::SockedFailed : socket failed");
				}
		};

		class GetAddrInfoFailed
		{
			public :
				virtual const char* what() const throw()
				{
					return ("Server::GetAddrInfoFailed : getaddrinfo failed");
				}
		};

	private:
		//Network			_network;
		Server();
		PollFdVector	_pollFds;
		ServerSocket*	_servSock;
		struct addrinfo	_hints;
		int				_port;
		std::string 	_addr;
		bool			_end;

};

#endif
