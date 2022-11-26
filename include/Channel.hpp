#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "User.hpp"
# include "Network.hpp"

class User;

class Channel
{
	public:

	typedef enum e_flag
	{
		INVITE_ONLY,
		MEMBERS_ONLY,
		DICTATURE,
		PRIVATE,
		SILENT,
		TOPIC
	} t_flag;


		Channel(std::string title, int maxSize);
		Channel(std::string title, std::string topic, int maxSize);
		~Channel();

		void
		addUser(User* user);

		void
		removeUser(User* user);

		void
		removeUser(std::string x);

		void
		broadCasting(std::string w_msg, User* user);

		std::string
		getTitle() const;

		std::string
		getTopic() const;

		void
		setTopic(std::string x);

		void
		clearTopic();

		std::vector<User *>
		getMembers() const;
		
		int
		getChannelSize() const;

		int
		getMaxSize() const;

		bool
		isPartOf(std::string nickname);

		bool
		empty() const;

		void
		printUsers();

		bool
		isChannelFull() const;

		void
		addOperator(User* user);

		void
		removeOperator(std::string nickname);

		bool
		isOperator(User* user);

		void
		addFlag(char flag);

		void
		removeFlag(char flag);
	
		std::string
		getFlags() const;

		bool
		isInviteOnly();

		bool
		isMembersOnly();

		bool
		isDictature();

		bool
		isTopicStrict();

		bool
		isPrivate();

		/* Dont forget to implement max users replies */

	private:

		std::string         _title;
		std::string         _topic;
		int                 _maxSize;
		std::vector<User*>	_members;
		std::vector<User*>	_operators;
		std::string			_flags;
};

#endif
