/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WHOIS.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschiffe <aschiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:00:00 by aschiffe          #+#    #+#             */
/*   Updated: 2022/11/24 19:55:40 by aschiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Replies.hpp"

// #define DAY_T 86400

// std::string
// getElapsedTime(clock_t regTime)
// {
// 	std::string rtvl;
// 	clock_t t1;

// 	t1 = clock();

// 	int d = 0;
// 	int h = 0;
// 	int m = 0;
// 	int s = 0;

// 	float diff = ((float)regTime - (float)t1);
// 	float convert_sec = diff / 1000;

	
// 	// Check afterwards if it can pose a problem beyond a day
// 	s = fmod(convert_sec, 60);
	
// 	if (convert_sec < DAY_T)
// 	{
// 		float minutes = convert_sec / 60;
// 		m = fmod(minutes, 60);
// 		float hours = minutes / 60;
// 		h = hours;
// 		d = 0;
// 	}
// 	else
// 	{
// 		float days = convert_sec / (DAY_T);
// 		d = (int)(days);
// 		float minutes = convert_sec / 60;
// 		m = fmod(minutes, 60);
// 		float hours = minutes / 60;
// 		h = fmod (hours, 24);
// 	}

// 	std::ostringstream c1,c2,c3,c4;
// 	c1 << d;
// 	rtvl += c1.str() += " days";
// 	c2 << h;
// 	rtvl += c2.str() += " hours";
// 	c3 << m;
// 	rtvl += c3.str() += " minutes";
// 	c4 << s;
// 	rtvl += c4.str() += " seconds";
// 	return rtvl;
// }

void
WHOIS(Command* cmd)
{
	User*						user = cmd->getUser();
	std::vector<std::string>	args = cmd->getArgs();
	User*		 				dest = g_network.getUser(args[1]);
	std::vector<Channel*>		chVec;
	std::string 				tmp;
	Replies 					rply(user, args);

	if (user->isRegistered() == false)
	{
		rply.sendError(E_ERR_NOTREGISTERED);
	}
	else if (args.size() == 1)
	{
		rply.sendError(E_ERR_NONICKNAMEGIVEN);
	}
	else if (dest == NULL)
	{
		rply.sendError(E_ERR_NOSUCHNICK);
	}
	else
	{
		chVec = dest->getChannels();

		args.push_back(dest->getUsername());
		args.push_back("localhost");
		args.push_back(dest->getRealname());
		rply.sendReplies(E_RPL_WHOISUSER);

		args[2] = g_network.getServName();
		args[3] = "some server information"; // g_network.getServInformation();
		rply.sendReplies(E_RPL_WHOISSERVER);

		if (dest->isOperator())
		{
			rply.sendReplies(E_RPL_WHOISOPERATOR);
		}
		args[2].clear();

		if (chVec.size() > 0)
		{
			for (std::vector<Channel *>::iterator it = chVec.begin(); it != chVec.end(); ++it)
			{
				if ((*it)->isOperator(dest) == true)
				{
					tmp += "@";		
				}
				args[2] += tmp + (*it)->getTitle() + " ";
				tmp.clear();
			}
			rply.sendReplies(E_RPL_WHOISCHANNELS);
		}

		std::ostringstream c;
		c << ((float)std::clock() - (float)dest->getRegTime()) / 100;
		args[2] = c.str();
		rply.sendReplies(E_RPL_WHOISIDLE);
		rply.sendReplies(E_RPL_ENDOFWHOIS);
	}
}
