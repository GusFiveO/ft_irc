/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschiffe <aschiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:17:41 by alorain           #+#    #+#             */
/*   Updated: 2022/11/24 15:39:10 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "Parser.hpp"
# include "Network.hpp"
# include "ClientSocket.hpp"

class Parser;
class Channel;
class ClientSocket;

// a - user is flagged as away;
// i - marks a users as invisible;
// w - user receives wallops;
// r - restricted user connection;
// o - operator flag;
// O - local operator flag;
// s - marks a user for receipt of server notices.

struct UserInfo
{
	std::string	nickname;
	std::string username;
	std::string realname;
	UserInfo();
	UserInfo(std::string nickname, std::string username, std::string realname);
};

class User
{
	typedef enum UserStatus
	{
		PENDING,
		DISCONNECTED,
		PASS,
		REGISTERED,
		CONNECTED

	} e_UserStatus;

	typedef struct UserInfo t_UserInfo;

	public:

		User();
		User(t_pollfd& pollfd, char* addr);
		User(t_UserInfo info, t_pollfd& pollfd, char* addr);
		~User();
		

		void
		receive();

		void
		flushBuffer();

		int
		respond(size_t idx);

		std::string
		getBuffer();

		void
		executeCommand();

		std::string
		getNickname() const;

		std::string
		getUsername() const;

		std::string
		getRealname() const;

		t_pollfd*
		getPollFd() const;

		bool
		isConnected() const;

		bool
		isRegistered() const;

		void
		register_();

		void
		disconnect();

		void
		pass();
		
		bool
		isPassed() const;

		bool
		isOperator() const;

		void
		becomeOperator();

		void
		setNickname(std::string nick);

		void
		setUsername(std::string user);

		void
		setRealname(std::string real);

		std::vector<Channel*>
		getChannels();
		
		void
		addChannel(Channel *chan);

		void
		removeChannel(Channel *chan);

		void
		printStatus();

		void
		setAwayMsg(std::string);

		void
		addInvite(Channel* channel);
	
		bool
		isInvited(Channel* channel);
		clock_t
		getRegTime() const;

		std::string
		getAddr() const;

	private:

		t_pollfd*				_pollFd;
		t_UserInfo				_info;
		e_UserStatus			_status;
		ClientSocket			_socket;
		bool					_op;
		Parser					*_parser;
		std::vector<Channel*>	_channels;
		std::vector<Channel*>	_invited;
		std::clock_t			_registerTime;
		std::string				_addr;
};

#endif
