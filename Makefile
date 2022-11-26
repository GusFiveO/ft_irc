OBJ_DIR = bin/
INC_DIR = include/
SRC_DIR = src/
CMDS_DIR = Commands/

CMDS_SRCS =	USER.cpp \
			NICK.cpp \
			INVITE.cpp \
			JOIN.cpp \
			KICK.cpp \
			LIST.cpp \
			PART.cpp \
			QUIT.cpp \
			TOPIC.cpp \
			WHOIS.cpp \
			PRIVMSG.cpp \
			PASS.cpp \
			OPER.cpp \
			PING.cpp \
			NOTICE.cpp \
			MODEutils.cpp \
			MODE.cpp \
			SQUIT.cpp \
			KILL.cpp

CMDS = $(addprefix $(CMDS_DIR), $(CMDS_SRCS))


SRCS = 	main.cpp \
		Server.cpp \
		Socket.cpp \
		Channel.cpp \
		ServerSocket.cpp \
		Network.cpp \
		User.cpp \
		Parser.cpp \
		Command.cpp \
		Replies.cpp \
		ClientSocket.cpp \
		Utils.cpp \
		$(CMDS)

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.cpp=.o))

DEPENDS = $(OBJS:.o=.d)

NAME = ircserv

SANITIZE = -g3 -fsanitize=address
CPPFLAGS = -Wall -Werror -Wextra -std=c++98 -ggdb
INCPATH = -I$(INC_DIR)

CC = c++

all: $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)

-include $(DEPENDS)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	$(CC) $(CPPFLAGS) $(INCPATH) -MMD -MP -c $< -o $@

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/Commands

clean :
	rm -rf $(OBJ_DIR)

fclean : clean 
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
