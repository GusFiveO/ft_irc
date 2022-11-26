/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Status.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:01:06 by alorain           #+#    #+#             */
/*   Updated: 2022/11/23 15:05:35 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_HPP
# define STATUS_HPP

typedef enum e_status
{
	RUNNING,
	STOP
} t_status;

extern e_status g_status;

#endif
