#ifndef REPLIES_HPP
# define REPLIES_HPP

# include <string>
# include <iostream>
# include <sstream>
# include "ft_irc.hpp"
# include "Network.hpp"

class User;

enum RPL
{
    E_RPL_WELCOME = 1,
    E_RPL_YOURHOST,
    E_RPL_CREATED,
    E_RPL_MYINFO,
    E_RPL_BOUNCE,
    E_RPL_USERHOST = 302,
    E_RPL_ISON = 303,
    E_RPL_AWAY = 301,
    E_RPL_UNAWAY = 305,
    E_RPL_NOAWAY = 306,
    E_RPL_WHOISUSER = 311,
    E_RPL_WHOISSERVER = 312,
    E_RPL_WHOISOPERATOR = 313,
    E_RPL_WHOISIDLE = 317,
    E_RPL_ENDOFWHOIS = 318,
    E_RPL_WHOISCHANNELS = 319,
    E_RPL_WHOWASUSER = 314,
    E_RPL_LISTSTART = 321,
    E_RPL_LIST = 322,
    E_RPL_LISTEND = 323,
    E_RPL_UNIQOPIS = 325,
    E_RPL_CHANNELMODEIS = 324,
    E_RPL_NOTOPIC = 331,
    E_RPL_TOPIC = 332,
    E_RPL_INVITING = 341,
    E_RPL_SUMMONING = 342,
    E_RPL_INVITELIST = 346,
	E_RPL_ENDOFINVITELIST = 347,
    E_RPL_EXCEPTLIST = 348,
    E_RPL_ENDOFEXCEPTLIST = 349,
    E_RPL_VERSION = 351,
    E_RPL_WHOREPLY = 352,
    E_RPL_ENDOFWHO = 315,
    E_RPL_NAMREPLY = 353,
    E_RPL_ENDOFNAMES = 366,
    E_RPL_LINKS = 364,
    E_RPL_ENDOFLINKS = 365,
    E_RPL_BANLIST = 367,
    E_RPL_ENDOFBANLIST = 368,
    E_RPL_INFO = 371,
    E_RPL_ENDOFINFO = 374,
    E_RPL_MOTDSTART = 375,
    E_RPL_MOTD = 372,
    E_RPL_ENDOFMOTD = 376,
    E_RPL_YOUREOPER = 381,
    E_RPL_REHASHING = 382,
    E_RPL_YOURESERVICE = 383,
    E_RPL_TIME = 391,
    E_RPL_USERSSTART = 392,
    E_RPL_USERS = 393,
    E_RPL_ENDOFUSERS = 394,
    E_RPL_NOUSERS = 395,
    E_RPL_TRACELINK = 200,
    E_RPL_TRACECONNECTING,
    E_RPL_TRACEHANDSHAKE,
    E_RPL_TRACEUNKNOWN,
    E_RPL_TRACEOPERATOR,
    E_RPL_TRACEUSER,
    E_RPL_TRACESERVER,
    E_RPL_TRACESERVICE,
    E_RPL_TRACENEWTYPE,
    E_RPL_TRACECLASS,
    E_RPL_TRACERECONNECT,
    E_RPL_TRACELOG = 261,
    E_RPL_TRACEEND,
    E_RPL_STATSLINKINFO = 211,
    E_RPL_STATSCOMMANDS,
    E_RPL_ENDOFSTATS = 219,
    E_RPL_STATSUPTIME = 242,
    E_RPL_STATSOLINE,
    E_RPL_UMODEIS = 221,
    E_RPL_SERVLIST = 234,
    E_RPL_SERVLISTEND,
    E_RPL_LUSERCLIENT = 251,
    E_RPL_LUSEROP,
    E_RPL_LUSERUNKNOWN,
    E_RPL_LUSERCHANNELS,
    E_RPL_LUSERME,
    E_RPL_ADMINME,
    E_RPL_ADMINLOC1,
    E_RPL_ADMINLOC2,
    E_RPL_ADMINEMAIL,
    E_RPL_TRYAGAIN = 263
};

enum ERR
{
    E_ERR_NOSUCHNICK = 401,
    E_ERR_NOSUCHSERVER,
    E_ERR_NOSUCHCHANNEL,
    E_ERR_CANNOTSENDTOCHAN,
    E_ERR_TOOMANYCHANNELS,
    E_ERR_WASNOSUCHNICK,
    E_ERR_TOOMANYTARGETS,
    E_ERR_NOSUCHSERVICE,
    E_ERR_NOORIGIN,
    E_ERR_NORECIPIENT = 411,
    E_ERR_NOTEXTTOSEND,
    E_ERR_NOTOPLEVEL,
    E_ERR_WILDTOPLEVEL,
    E_ERR_BADMASK,
    E_ERR_UNKNOWNCOMMAND = 421,
    E_ERR_NOMOTD,
    E_ERR_NOADMININFO,
    E_ERR_FILEERROR,
    E_ERR_NONICKNAMEGIVEN = 431,
    E_ERR_ERRONEUSNICKNAME,
    E_ERR_NICKNAMEINUSE,
    E_ERR_NICKCOLLISION = 436,
    E_ERR_UNAVAILRESOURCE,
    E_ERR_USERNOTINCHANNEL = 441,
    E_ERR_NOTONCHANNEL,
    E_ERR_USERONCHANNEL,
    E_ERR_NOLOGIN,
    E_ERR_SUMMONDISABLED,
    E_ERR_USERSDISABLED,
    E_ERR_NOTREGISTERED = 451,
    E_ERR_NEEDMOREPARAMS = 461,
    E_ERR_ALREADYREGISTRED,
    E_ERR_NOPERMFORHOST,
    E_ERR_PASSWDMISMATCH,
    E_ERR_YOUREBANNEDCREEP,
    E_ERR_YOUWILLBEBANNED,
    E_ERR_KEYSET,
    E_ERR_CHANNELISFULL = 471,
    E_ERR_UNKNOWNMODE,
    E_ERR_INVITEONLYCHAN,
    E_ERR_BANNEDFROMCHAN,
    E_ERR_BADCHANNELKEY,
    E_ERR_BADCHANMASK,
    E_ERR_NOCHANMODES,
    E_ERR_BANLISTFULL,
    E_ERR_NOPRIVILEGES = 481,
    E_ERR_CHANOPRIVSNEEDED,
    E_ERR_CANTKILLSERVER,
    E_ERR_RESTRICTED,
    E_ERR_UNIQOPPRIVSNEEDED,
    E_ERR_NOOPERHOST = 491,
    E_ERR_UMODEUNKNOWNFLAG = 501,
    E_ERR_USERSDONTMATCH = 502
};

class Replies
{
    private :

        std::string					_host;
        User*						_user;
        std::vector<std::string>&	_args;
		std::string					_ver;
        std::string                 _provider;

    public :

        Replies(User* user, std::vector<std::string>& args);
		~Replies();

		void
		sendReplies(enum RPL code);

        std::string
        buildReplies(enum RPL code/*, std::vector<std::string> vec*/);

		void
		sendError(enum ERR code);

        std::string
        buildError(enum ERR code);

        std::string
        RPL_WELCOME();

        std::string
        RPL_YOURHOST();

        std::string
        RPL_CREATED();

        std::string
        RPL_MYINFO();

        std::string
        RPL_BOUNCE();

        std::string
        RPL_USERHOST();

        std::string
        RPL_ISON();

        std::string
        RPL_AWAY();

        std::string
        RPL_UNAWAY();

        std::string
        RPL_NOAWAY();

        std::string
        RPL_WHOISUSER();

        std::string
        RPL_WHOISSERVER();

        std::string
        RPL_WHOISOPERATOR();

        std::string
        RPL_WHOISIDLE();

        std::string
        RPL_ENDOFWHOIS();

        std::string
        RPL_WHOISCHANNELS();

        std::string
        RPL_WHOWASUSER();

        std::string
        RPL_LISTSTART();

        std::string
        RPL_LIST();

        std::string
        RPL_LISTEND();

        std::string
        RPL_UNIQOPIS();

        std::string
        RPL_CHANNELMODEIS();

        std::string
        RPL_NOTOPIC();

        std::string
        RPL_TOPIC();

        std::string
        RPL_INVITING();

        std::string
        RPL_SUMMONING();

        std::string
        RPL_INVITELIST();

        std::string
        RPL_EXCEPTLIST();

        std::string
        RPL_ENDOFEXCEPTLIST();

        std::string
        RPL_VERSION();

        std::string
        RPL_WHOREPLY();

        std::string
        RPL_ENDOFWHO();

        std::string
        RPL_NAMREPLY();

        std::string
        RPL_ENDOFNAMES();

        std::string
        RPL_LINKS();

        std::string
        RPL_ENDOFLINKS();

        std::string
        RPL_BANLIST();

        std::string
        RPL_ENDOFBANLIST();

        std::string
        RPL_INFO();

        std::string
        RPL_ENDOFINFO();

        std::string
        RPL_MOTDSTART();

        std::string
        RPL_MOTD();

        std::string
        RPL_ENDOFMOTD();

        std::string
        RPL_YOUREOPER();

        std::string
        RPL_REHASHING();

        std::string
        RPL_YOURESERVICE();

        std::string
        RPL_TIME();

        std::string
        RPL_USERSSTART();

        std::string
        RPL_USERS();

        std::string
        RPL_ENDOFUSERS();

        std::string
        RPL_NOUSERS();

        std::string
        RPL_TRACELINK();

        std::string
        RPL_TRACECONNECTING();

        std::string
        RPL_TRACEHANDSHAKE();

        std::string
        RPL_TRACEUNKNOWN();

        std::string
        RPL_TRACEOPERATOR();

        std::string
        RPL_TRACEUSER();

        std::string
        RPL_TRACESERVER();

        std::string
        RPL_TRACESERVICE();

        std::string
        RPL_TRACENEWTYPE();

        std::string
        RPL_TRACECLASS();

        std::string
        RPL_TRACERECONNECT();

        std::string
        RPL_TRACELOG();

        std::string
        RPL_TRACEEND();

        std::string
        RPL_STATSLINKINFO();

        std::string
        RPL_STATSCOMMANDS();

        std::string
        RPL_ENDOFSTATS();

        std::string
        RPL_STATSUPTIME();

        std::string
        RPL_STATSOLINE();

        std::string
        RPL_UMODEIS();

        std::string
        RPL_SERVLIST();

        std::string
        RPL_SERVLISTEND();

        std::string
        RPL_LUSERCLIENT();

        std::string
        RPL_LUSEROP();

        std::string
        RPL_LUSERUNKNOWN();

        std::string
        RPL_LUSERCHANNELS();

        std::string
        RPL_LUSERME();

        std::string
        RPL_ADMINME();

        std::string
        RPL_ADMINLOC1();

        std::string
        RPL_ADMINLOC2();

        std::string
        RPL_ADMINEMAIL();

        std::string
        RPL_TRYAGAIN();

        /*********************************************************************/
        /******************************ERR-Replies****************************/
        /*********************************************************************/

        std::string
        ERR_NOSUCHNICK();

        std::string
        ERR_NOSUCHSERVER();

        std::string
        ERR_NOSUCHCHANNEL();

        std::string
        ERR_CANNOTSENDTOCHAN();

        std::string
        ERR_TOOMANYCHANNELS();

        std::string
        ERR_WASNOSUCHNICK();

        std::string
        ERR_TOOMANYTARGETS();

        std::string
        ERR_NOSUCHSERVICE();

        std::string
        ERR_NOORIGIN();

        std::string
        ERR_NORECIPIENT();

        std::string
        ERR_NOTEXTTOSEND();

        std::string
        ERR_NOTOPLEVEL();

        std::string
        ERR_WILDTOPLEVEL();

        std::string
        ERR_BADMASK();

        std::string
        ERR_UNKNOWNCOMMAND();

        std::string
        ERR_NOMOTD();

        std::string
        ERR_NOADMININFO();

        std::string
        ERR_FILEERROR();

        std::string
        ERR_NONICKNAMEGIVEN();

        std::string
        ERR_ERRONEUSNICKNAME();

        std::string
        ERR_NICKNAMEINUSE();

        std::string
        ERR_NICKCOLLISION();

        std::string
        ERR_UNAVAILRESOURCE();

        std::string
        ERR_USERNOTINCHANNEL();

        std::string
        ERR_NOTONCHANNEL();

        std::string
        ERR_USERONCHANNEL();

        std::string
        ERR_NOLOGIN();

        std::string
        ERR_SUMMONDISABLED();

        std::string
        ERR_USERSDISABLED();

        std::string
        ERR_NOTREGISTERED();

        std::string
        ERR_NEEDMOREPARAMS();

        std::string
        ERR_ALREADYREGISTRED();

        std::string
        ERR_NOPERMFORHOST();

        std::string
        ERR_PASSWDMISMATCH();

        std::string
        ERR_YOUREBANNEDCREEP();

        std::string
        ERR_YOUWILLBEBANNED();

        std::string
        ERR_KEYSET();

        std::string
        ERR_CHANNELISFULL();

        std::string
        ERR_UNKNOWNMODE();

        std::string
        ERR_INVITEONLYCHAN();

        std::string
        ERR_BANNEDFROMCHAN();

        std::string
        ERR_BADCHANNELKEY();

        std::string
        ERR_BADCHANMASK();

        std::string
        ERR_NOCHANMODES();

        std::string
        ERR_BANLISTFULL();

        std::string
        ERR_NOPRIVILEGES();

        std::string
        ERR_CHANOPRIVSNEEDED();

        std::string
        ERR_CANTKILLSERVER();

        std::string
        ERR_RESTRICTED();

        std::string
        ERR_UNIQOPPRIVSNEEDED();

        std::string
        ERR_NOOPERHOST();

        std::string
        ERR_UMODEUNKNOWNFLAG();

        std::string
        ERR_USERSDONTMATCH();

};

#endif
