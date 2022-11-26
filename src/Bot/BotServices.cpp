# include "IrcaaBot.hpp"

std::string
IrcaaBot::timeService()
{
	time_t x;
	struct tm* y;

	std::time (&x);
	y = std::localtime(&x);
	return (std::string(" :Current Day, Date and Time is : ") + asctime(y));
}