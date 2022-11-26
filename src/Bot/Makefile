CLANG = clang++
NAME = ircaaBot

SRCS = 	main.cpp \
		IrcaaBot.cpp \
		BotServices.cpp

INC_PATH = includes/
OBJS = $(SRCS:.cpp=.o)
HEADERS = $(addprefix includes/, IrcaaBot.hpp)
FLAGS = -Werror -Wall -Wextra -std=c++98 -g -I$(INC_PATH)

%.o : %.cpp
		$(CLANG) $(FLAGS) -c $< -o $@

all: $(NAME) $(HEADERS)

$(NAME): $(OBJS)
	@echo "\033[0;33mLinking process..."
	$(CLANG) -o $(NAME) $(OBJS)
	@echo "\033[0;32m-----------------------------------"
	@echo "\033[0;32m|              DONE               |"
	@echo "\033[0;32m-----------------------------------"

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
