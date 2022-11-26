/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:42:39 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 21:29:50 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
//#include "Status.hpp"

Parser::Parser()
{
    Parser::initCommandsMap();
}

Parser::Parser(std::string buffer)
	: _raw(buffer)
{
    Parser::initCommandsMap();
}

void
Parser::initCommandsMap()
{
    _CommandsMap["JOIN"] = &JOIN;
    _CommandsMap["LIST"] = &LIST;
    _CommandsMap["PART"] = &PART;
    _CommandsMap["QUIT"] = &QUIT;
    _CommandsMap["NICK"] = &NICK;
    _CommandsMap["USER"] = &USER;
    _CommandsMap["WHOIS"] = &WHOIS;
    _CommandsMap["INVITE"] = &INVITE;
    _CommandsMap["KICK"] = &KICK;
    _CommandsMap["TOPIC"] = &TOPIC;
    _CommandsMap["PRIVMSG"] = &PRIVMSG;
    _CommandsMap["PASS"] = &PASS;
    _CommandsMap["OPER"] = &OPER;
    _CommandsMap["PING"] = &PING;
    _CommandsMap["NOTICE"] = &NOTICE;
    _CommandsMap["MODE"] = &MODE;
    //_CommandsMap["SQUIT"] = &SQUIT;
    _CommandsMap["squit"] = &SQUIT;
    _CommandsMap["kill"] = &KILL;
}

Parser::~Parser()
{}

Command*
Parser::parseCommand(User* user)
{
    std::vector<std::string> vec;
    Command* command;

    char *tok = std::strtok(&_raw[0], " ");
    while (tok != NULL)
    {
		vec.push_back(tok);
		vec.back().erase(std::remove(vec.back().begin(), vec.back().end(), '\r'),
				vec.back().end());
        tok = std::strtok(NULL, " ");
		if (tok && vec[0] == "USER" && std::strchr(tok, ':'))
		{
			std::string tmp(&tok[1]);
			tok = std::strtok(NULL, " ");
			if (tok != NULL)
			{
				tmp += std::string(" ") + tok;
			}
			vec.push_back(tmp);
		}

		vec.back().erase(std::remove(vec.back().begin(), vec.back().end(), '\r'),
				vec.back().end());
    }
	if (vec.empty())
		return NULL;
    std::map<std::string, Commands>::iterator it = _CommandsMap.find(vec[0]);

    if (it == _CommandsMap.end())
        return NULL;

    command = new Command(it->second, user, vec);
	return command;
}
