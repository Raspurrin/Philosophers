/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:30:15 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/22 01:26:58 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	ft_isdigit(int32_t c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	ft_isspace(int32_t c)
{
	if (c == ' ' || c == '\n' || c == '\t' || \
		c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
}

int32_t	ft_atoi(const char *str)
{
	size_t	i;
	int32_t	sign;
	int32_t	out;

	i = 0;
	sign = 1;
	out = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		out = (out * 10) + (str[i++] - '0');
	return (out * sign);
}
