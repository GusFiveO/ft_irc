/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Network.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschiffe <aschiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:16:25 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 22:18:49 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_HPP
# define NETWORK_HPP

# include "User.hpp"
# include "Channel.hpp"

class User;
class Channel;

class Network
{
	public:

		typedef std::map<std::string, User*>	UserMap;
		typedef std::vector<User*>				UserVector;
		typedef std::vector<User*>				OperVector;
		typedef std::vector<Channel*>			ChannelVector;							

		Network();
		~Network();

		void
		setOperPassword(std::string operPass);

		std::string
		getOperPassword() const;

		void
		setPassword(std::string passwrd);

		std::string
		getPassword() const;

		void
		setHostname(std::string);

		std::string
		getHostname() const;

		void
		addUser(User& user);

		void
		removeUser(size_t idx);

		void
		removeUser(std::string nickname);

		void
		addOperator(User& user);

		User*
		addOperator(std::string nickname);
		
		void
		removeOperator(User* user);

		void
		addConnexion(t_pollfd* newConnection, char* addr);

		User*
		getUser(size_t idx);

		User*
		getUser(std::string nickname);

		std::string
		getServName() const;

		std::string
		getPort() const;

		void
		setPort(std::string x);

		size_t
		HintSize();

		size_t
		MapSize();

		void
		printMap();

		bool
		isUserConnected(size_t idx);

		bool
		maxChannelsReached(User* usr) const;

		Channel*
		addChannel(std::string x);

		Channel*
		getChannel(std::string x) const;

		ChannelVector
		getChannelVec() const;

		void
		removeChannel(std::string chanName);

		void
		channelAddUser(std::string x, User* user);

		void
		channelRemoveUser(std::string x, User* user);

		void
		printChanUser(std::string chanName);

		void
		removeUserFromChannels(User* user);

		std::string
		getCurrentTime() const;

		void
		clear();

		char*
		getsockaddr(int fd);

		void
		broadcast(std::string mess);

		void
		printChannels();

	private:

		UserMap			_users;
		ChannelVector	_channelVec;
		UserVector		_usersHint;
		OperVector		_operators;

		std::string		_servName;
		std::string		_hostname;
		std::string		_port;
		int				_maxCh;
		std::string		_passwrd;
		std::string		_operPass;
};

extern Network g_network;

#endif
