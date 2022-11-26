/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschiffe <aschiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:05:02 by alorain           #+#    #+#             */
/*   Updated: 2022/11/24 15:43:55 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Parser.hpp"
# include "Server.hpp"
# include "Network.hpp"

Network g_network;

void
usage()
{
	std::cerr << "usage : ./ircserv <port> <password>" << std::endl;
	exit(EXIT_FAILURE);
}

int
main(int argc, const char* argv[])
{
	g_network.addChannel("#TEST");
	g_network.addChannel("#TEST1");
	g_network.addChannel("#TEST2");

	if (argc != 3)
	{
		usage();
	}
	try
	{
		Server serv(std::atoi(argv[1]), argv[2]);
		g_network.setPort(argv[1]);
		serv.initServerSocket();
		serv.servLoop();
	}
	catch(Server::PasswordAuthenticationFailed& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch(Server::SocketFailed& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch(Server::GetAddrInfoFailed& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
