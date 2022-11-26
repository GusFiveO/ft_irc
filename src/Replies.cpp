/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:19:41 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 21:47:27 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replies.hpp"

/*********************************************************************/
/******************************Replies********************************/
/*********************************************************************/

Replies::Replies(User* user, std::vector<std::string>& args) :
	_user(user),
	_args(args),
	_ver("beta"),
    _provider(std::string(":") + g_network.getsockaddr(user->getPollFd()->fd))
{
}

//Replies::Replies(User* user, std::vector<std::string> args) :
//    _host_prefix(":localhost")
//{
//	(void)user;
//	(void)args;
//}
//
//Replies::Replies(User* user, std::vector<std::string> args) :
//    _host_prefix(":localhost")
//{
//	(void)user;
//	(void)args;
//}

Replies::~Replies()
{
}

void
Replies::sendReplies(enum RPL code)
{
	std::string reply;

	reply = buildReplies(code);
	if (send(_user->getPollFd()->fd, reply.data(), reply.size(), 0) == -1)
	{
		_user->disconnect();
	}
}

void
Replies::sendError(enum ERR code)
{
	std::string err;
	err = buildError(code);
	if (send(_user->getPollFd()->fd, err.data(), err.size(), 0) == -1)
	{
		_user->disconnect();
	}
}

std::string
Replies::buildReplies(enum RPL code/*, std::vector<std::string> vec*/)
{
	std::string rtvl;
	std::ostringstream convert;

    /* :localhost 101 nickname */

	convert << code;
	rtvl += _provider;
	rtvl += std::string(" ");
	if (code < 10)
	{
		rtvl += "00";
	}
	rtvl += convert.str();
	if (!_user->getNickname().empty())
		rtvl += std::string(" ");
	rtvl += _user->getNickname();
	rtvl += std::string(" ");

	switch (code)
	{
	    case E_RPL_WELCOME:
            rtvl += RPL_WELCOME();
            break;
        case E_RPL_YOURHOST:
            rtvl += RPL_YOURHOST();
            break;
        case E_RPL_CREATED:
            rtvl += RPL_CREATED();
            break;
        case E_RPL_MYINFO:
            rtvl += RPL_MYINFO();
            break;
        case E_RPL_BOUNCE:
            rtvl += RPL_BOUNCE();
            break;
        case E_RPL_AWAY:
            rtvl += RPL_AWAY();
            break;
        case E_RPL_WHOISUSER:
            rtvl += RPL_WHOISUSER();
            break;
        case E_RPL_WHOISSERVER:
            rtvl += RPL_WHOISSERVER();
            break;
        case E_RPL_WHOISOPERATOR:
            rtvl += RPL_WHOISOPERATOR();
            break;
        case E_RPL_WHOISCHANNELS:
            rtvl += RPL_WHOISCHANNELS();
            break;
        case E_RPL_WHOISIDLE:
            rtvl += RPL_WHOISIDLE();
            break;
        case E_RPL_ENDOFWHOIS:
            rtvl += RPL_ENDOFWHOIS();
            break;
        case E_RPL_LIST:
            rtvl += RPL_LIST();
            break;
        case E_RPL_LISTEND:
            rtvl += RPL_LISTEND();
            break;
        case E_RPL_NOTOPIC:
            rtvl += RPL_NOTOPIC();
            break;
        case E_RPL_TOPIC:
            rtvl += RPL_TOPIC();
            break;
        case E_RPL_NAMREPLY:
            rtvl += RPL_NAMREPLY();
            break;
        case E_RPL_ENDOFNAMES:
            rtvl += RPL_ENDOFNAMES();
            break;
        case E_RPL_YOUREOPER:
            rtvl += RPL_YOUREOPER();
            break;
		case E_RPL_INVITING:
			rtvl += RPL_INVITING();
			break;
	default:
		break;
	}
    return rtvl += std::string("\r\n");
}


std::string
Replies::buildError(enum ERR code)
{
	std::string rtvl;
	std::ostringstream convert;

	convert << code;
	rtvl.append(_provider);
	rtvl.append(std::string(" "));
	rtvl.append(convert.str());
	if (!_user->getNickname().empty())
		rtvl += std::string(" ");
	rtvl.append(_user->getNickname());
	rtvl.append(std::string(" "));
	switch (code)
	{
        case E_ERR_NOSUCHNICK:
            rtvl += ERR_NOSUCHNICK();
            break;
        case E_ERR_NOSUCHSERVER:
            rtvl += ERR_NOSUCHSERVER();
            break;
        case E_ERR_NOSUCHCHANNEL:
            rtvl += ERR_NOSUCHCHANNEL();
            break;
        case E_ERR_TOOMANYCHANNELS:
            rtvl += ERR_TOOMANYCHANNELS();
            break;
        case E_ERR_NORECIPIENT:
            rtvl += ERR_NORECIPIENT();
            break;
        case E_ERR_NOTEXTTOSEND:
            rtvl += ERR_NOTEXTTOSEND();
            break;
        case E_ERR_NICKNAMEINUSE:
            rtvl += ERR_NICKNAMEINUSE();
            break;
        case E_ERR_NOTONCHANNEL:
            rtvl += ERR_NOTONCHANNEL();
            break;
        case E_ERR_NEEDMOREPARAMS:
            rtvl += ERR_NEEDMOREPARAMS();
            break;
        case E_ERR_ALREADYREGISTRED:
            rtvl += ERR_ALREADYREGISTRED();
            break;
        case E_ERR_CHANNELISFULL:
            rtvl += ERR_CHANNELISFULL();
            break;
        case E_ERR_CHANOPRIVSNEEDED:
            rtvl += ERR_CHANOPRIVSNEEDED();
            break;
		case E_ERR_USERONCHANNEL:
			rtvl += ERR_USERONCHANNEL();
			break;
		case E_ERR_INVITEONLYCHAN:
			rtvl += ERR_INVITEONLYCHAN();
			break;
		case E_ERR_NOTREGISTERED:
			rtvl += ERR_NOTREGISTERED();
			break;
		case E_ERR_NOPRIVILEGES:
			rtvl += ERR_NOPRIVILEGES();
			break;
		case E_ERR_PASSWDMISMATCH:
			rtvl += ERR_PASSWDMISMATCH();
			break;
        case E_ERR_ERRONEUSNICKNAME:
            rtvl += ERR_ERRONEUSNICKNAME();
        default:
			break;
	}
    return rtvl += std::string("\r\n");
}

std::string
Replies::RPL_WELCOME()
{
    std::string rtvl;
	rtvl += std::string(":Welcome to the Internet Relay Network ");
	rtvl += _user->getNickname() += std::string("!") += _user->getUsername() += std::string("@") += _user->getAddr();
    return rtvl;
}

std::string
Replies::RPL_YOURHOST()
{
	std::string rtvl;
	rtvl += std::string(" :Your host is") += g_network.getServName() += std::string(" running version ") += _ver;
    return rtvl;
}

std::string
Replies::RPL_CREATED()
{
	std::string rtvl;
	
	rtvl += std::string("This server was created "); /* += g_network.getServCreationDate(); */
    return std::string(rtvl);
}

std::string
Replies::RPL_MYINFO()
{
	std::string rtvl;
	rtvl += std::string(" :") += g_network.getServName() += std::string(" ") += _ver += std::string(" ") += std::string("available user modes") += std::string("available channel modes");
    return rtvl;
}

std::string
Replies::RPL_BOUNCE()
{
	std::string rtvl;
	rtvl += std::string("Try server ") += g_network.getServName() += std::string(", port ") += g_network.getPort(); 
    return rtvl;
}

std::string
Replies::RPL_AWAY()
{
	std::string rtvl;
    rtvl += _user->getUsername() += " :";
    for (std::vector<std::string>::iterator it = _args.begin() + 2; it != _args.end(); ++it)
    {
        rtvl += *it;
    }
    return rtvl;
}

std::string
Replies::RPL_LIST()
{
    std::string             rtvl;
    Channel*                ch = g_network.getChannel(_args[1]);

    std::ostringstream convert;
    convert << ch->getChannelSize();
    
    rtvl += _args[1] + std::string(" ") += convert.str() += std::string(" ") += ch->getTopic();
    
    return rtvl;
}

std::string
Replies::RPL_LISTEND()
{
    std::string rtvl;

    rtvl += ":End of LIST";
    return rtvl;
}

std::string
Replies::RPL_NOTOPIC()
{
	std::string rtvl;
	rtvl += _args[1] + std::string(" :No topic is set");
    return rtvl;
}

std::string
Replies::RPL_TOPIC()
{
	std::string rtvl;
    rtvl += _args[1] + std::string(" :") += g_network.getChannel(_args[1])->getTopic();
	return rtvl;
}

std::string
Replies::RPL_NAMREPLY()
{
	std::string 			rtvl;
	Channel* 				ch = g_network.getChannel(_args[1]);
	std::vector<User *> 	members = ch->getMembers();

	rtvl += std::string("=") += std::string(" ") += _args[1] + std::string(" :");
	for (std::vector<User *>::iterator it = members.begin(); it != members.end(); ++it)
	{
		if (ch->isOperator(*it) == true)
			rtvl += std::string("@");
		rtvl += (*it)->getNickname();
        if (it + 1 != members.end())
		{
			rtvl += std::string(" ");
		}
	}
    return rtvl;
}

std::string
Replies::RPL_ENDOFNAMES()
{
	std::string rtvl;
	rtvl += _args[1] + std::string(" :End of NAMES list");
    return rtvl;
}

std::string
Replies::RPL_YOUREOPER()
{
    std::string rtvl;
    rtvl += std::string(":You are now an operator, A k a The G.o.a.t");
    return rtvl;
}

std::string
Replies::RPL_INVITING()
{
	std::string rtvl;

	rtvl += _args[1] += std::string(" ") += _args[2];
	return rtvl;
}

std::string
Replies::RPL_WHOISUSER()
{
    std::string rtvl;
    rtvl += _args[1] + std::string(" ") + _args[2] + std::string(" ") + _args[3] + std::string(" * :") += _args[4];
    return rtvl;
}

std::string
Replies::RPL_WHOISSERVER()
{
    std::string rtvl;
    rtvl += _args[1] + std::string(" ") + _args[2] + std::string(" :") += _args[3];
    return rtvl;
}

std::string
Replies::RPL_WHOISOPERATOR()
{
    std::string rtvl;
    rtvl += _args[1] + std::string(" :is an IRC operator");
    return rtvl;
}

std::string
Replies::RPL_WHOISCHANNELS()
{
    std::string rtvl;
    rtvl += _args[1] + std::string(" :") += _args[2];
    return rtvl;
}

std::string
Replies::RPL_WHOISIDLE()
{
    std::string rtvl;
    rtvl += _args[1] + std::string(" ") +  _args[2] + std::string(" :seconds idle");
    return rtvl;
}

std::string
Replies::RPL_ENDOFWHOIS()
{
    std::string rtvl;
    rtvl += _args[1] + std::string(" :End of /WHOIS list");
    return rtvl;
}

/*********************************************************************/
/******************************ERR-Replies****************************/
/*********************************************************************/

std::string
Replies::ERR_NOSUCHNICK()
{
    std::string rtvl;
    rtvl += _args[1] + std::string(" :No such nick/channel");
    return rtvl;
}

std::string
Replies::ERR_NOSUCHSERVER()
{
    std::string rtvl;
    rtvl += _args[1] + std::string(" :No such server");    
    return rtvl;
}

std::string
Replies::ERR_NOSUCHCHANNEL()
{
	std::string rtvl;
	rtvl += _args[0] + " :No such channel";
	return rtvl;
}

std::string
Replies::ERR_TOOMANYCHANNELS()
{
	std::string rtvl;
	rtvl += _args[1] + " :You have joined too many channels";
	return rtvl;
}

std::string
Replies::ERR_NORECIPIENT()
{
    std::string rtvl;

    rtvl += std::string(":No recipient given ") += std::string("(") += _args[0] + std::string(")");
    return rtvl;
}

std::string
Replies::ERR_NOTEXTTOSEND()
{
    std::string rtvl;

    rtvl += ":No text to send";
    return rtvl;
}

std::string
Replies::ERR_NOTOPLEVEL()
{
    return std::string();
}

std::string
Replies::ERR_NICKNAMEINUSE()
{
	std::string rtvl;
    rtvl += _user->getNickname() + std::string(" :Nickname is already in use");
    return rtvl;
}

std::string
Replies::ERR_NOTONCHANNEL()
{
	std::string rtvl;
	rtvl += _args[0] + std::string(" :You're not on that channel"); 
    return rtvl;
}

std::string
Replies::ERR_NEEDMOREPARAMS()
{
	std::string rtvl(_args[0]);
	rtvl.append(" :Not enough parameters");
    return rtvl;
}

std::string
Replies::ERR_ALREADYREGISTRED()
{
	std::string rtvl;
	rtvl.append(":Unauthorized command (already registered)");
    return rtvl;
}

std::string
Replies::ERR_PASSWDMISMATCH()
{
	std::string rtvl(_user->getNickname());
	rtvl += std::string(" :Password incorrect");
    return rtvl;
}

std::string
Replies::ERR_CHANOPRIVSNEEDED()
{
    std::string rtvl;
	if (_args[0] == "INVITE")
    	rtvl += _args[2] + " :You're not channel operator";
	else if (_args[0] == "TOPIC" || _args[0] == "MODE" || _args[0] == "KICK")
    	rtvl += _args[1] + " :You're not channel operator";
    return rtvl;
}

std::string
Replies::ERR_USERONCHANNEL()
{
	std::string rtvl;
	rtvl += _args[1] + std::string(" ") + _args[2] + std::string(" :is already on channel");
	return rtvl;
}

std::string
Replies::ERR_INVITEONLYCHAN()
{
	std::string rtvl;
	rtvl += _args[1] += std::string(" :Cannot join channel (+i)");
	return rtvl;
}

std::string
Replies::ERR_CHANNELISFULL()
{
    std::string rtvl;
    rtvl += _args[1] + " :Cannot join channel (+1)";
    return rtvl;
}

std::string
Replies::ERR_NOTREGISTERED()
{
	std::string rtvl;
	rtvl += std::string(":You have not registered");
	return rtvl;
}

std::string
Replies::ERR_NOPRIVILEGES()
{
	std::string rtvl;
	rtvl += std::string(":Permission Denied- You're not an IRC operator");
	return rtvl;
}

std::string
Replies::ERR_ERRONEUSNICKNAME()
{
    std::string rtvl;
    rtvl += _args[1] += " :Erroneous nickname";
    return rtvl;
}
