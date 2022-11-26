/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschiffe <aschiffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:14:02 by alorain           #+#    #+#             */
/*   Updated: 2022/11/25 16:17:31 by aschiffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

# define DECO_CODE 2

# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <cstring>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <unistd.h>
# include <poll.h>
# include <vector>
# include <map>
# include <algorithm>
# include <fcntl.h>
# include <cerrno>
# include <sstream>
# include <string>
# include <cstdlib>
# include <ctime>
# include <time.h>
# include <math.h>

typedef struct pollfd       t_pollfd;
typedef struct sockaddr_in  t_sockaddrin;

# define PASSWORD "111"

#endif
