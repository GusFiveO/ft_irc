#include "Channel.hpp"

Channel::Channel(std::string title, int maxSize) :
    _title(title),
    _topic("default topic - lorem ipsum"),
    _maxSize(maxSize),
	_flags()
{
}

Channel::Channel(std::string title, std::string topic, int maxSize) :
    _title(title),
    _topic(topic),
    _maxSize(maxSize),
	_flags()
{
}

Channel::~Channel()
{
}

void
Channel::addUser(User* user)
{
    std::string w_msg;

	if (_members.size() == 0)
		_operators.push_back(user);
    _members.push_back(user);
    /* Test */
    w_msg.append(":");
    /* Test */
    w_msg.append(user->getNickname());
    w_msg.append("!");
    w_msg.append(user->getUsername());
    w_msg.append(std::string("@") += user->getAddr() += " ");
    w_msg.append("JOIN ");
    w_msg.append(_title);
	w_msg.append("\r\n");

    Channel::broadCasting(w_msg, user);
}

void
Channel::removeUser(User* user)
{
    _members.erase(std::find(_members.begin(), _members.end(), user));
	if (empty())
		g_network.removeChannel(getTitle());
}

void
Channel::removeUser(std::string x)
{
    _members.erase(std::find(_members.begin(), _members.end(), g_network.getUser(x)));
	if (empty())
		g_network.removeChannel(getTitle());
}

std::string
Channel::getTitle() const
{
    return _title;
}

std::string
Channel::getTopic() const
{
    return _topic;
}

std::vector<User *>
Channel::getMembers() const
{
    return _members;
}

int
Channel::getMaxSize() const
{
    return _maxSize;
}

int
Channel::getChannelSize() const
{
    return _members.size();
}

void
Channel::setTopic(std::string x)
{
    _topic = x;
}

void
Channel::clearTopic()
{
    _topic.clear();
}

void
Channel::broadCasting(std::string msg, User* user)
{
	for (std::vector<User *>::iterator it = _members.begin(); it != _members.end(); it++)
	{
        if (*it != user)
        {
            if (send((*it)->getPollFd()->fd, msg.data(), msg.size(), 0) == -1)
            {
                (*it)->disconnect();
            }
        }
	}
}

bool
Channel::isPartOf(std::string nickname)
{
	std::vector<User*>::iterator it;

	for (it = _members.begin(); it != _members.end(); it++)
	{
		if ((*it)->getNickname() == nickname)
			return true;
	}
	return false;
}

bool
Channel::empty() const
{
	return _members.empty();
}

void
Channel::printUsers()
{
	std::vector<User*>::iterator it;

	for (it = _members.begin(); it != _members.end(); it++)
	{
		std::cout << "(" << (*it)->getNickname() << "), "; 
	}
	std::cout << std::endl;
}

bool
Channel::isChannelFull() const
{
    return (int)_members.size() >= _maxSize ? true : false;
}

void
Channel::addOperator(User* user)
{
	_operators.push_back(user);
}

void
Channel::removeOperator(std::string nickname)
{
    _operators.erase(std::find(_operators.begin(), _operators.end(), g_network.getUser(nickname)));
}

//bool
//Channel::isOperator(User* user)
//{
//	std::vector<User*>::iterator	it;
//	std::string						nickname = user->getNickname();
//
//	for (it = _operators.begin(); it != _operators.end(); it++)
//	{
//		if ((*it)->getNickname() == nickname)
//			return true;
//	}
//	return false;
//}
bool
Channel::isOperator(User* user)
{
	std::vector<User*>::iterator	it;

	for (it = _operators.begin(); it != _operators.end(); it++)
	{
		if ((*it) == user)
			return true;
	}
	return false;
}

void
Channel::addFlag(char flag)
{
	if (_flags.find(flag) == std::string::npos)	
	{
		_flags.push_back(flag);
	}
}

void
Channel::removeFlag(char flag)
{
	if (_flags.empty())
		return;
	_flags.erase(_flags.find(flag));
}

std::string
Channel::getFlags() const
{
	return _flags;
}

bool
Channel::isInviteOnly()
{
	if (_flags.find('i') != std::string::npos)
		return true;
	return false;
}

bool
Channel::isMembersOnly()
{
	if (_flags.find('n') != std::string::npos)
		return true;
	return false;
}

bool
Channel::isDictature()
{
	if (_flags.find('m') != std::string::npos)
		return true;
	return false;
}

bool
Channel::isPrivate()
{
	if (_flags.find('p') != std::string::npos)
		return true;
	return false;
}

bool
Channel::isTopicStrict()
{
	if (_flags.find('t') != std::string::npos)
		return true;
	return false;
}
