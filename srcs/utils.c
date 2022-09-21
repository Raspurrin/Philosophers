/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:30:15 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/21 20:44:30 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

char	*get_rand_food(void)
{
	const char	*food[] = {"soup", "potato", "Konstantin", "bugs", "spaghetti", \
		"broodje frikandel", "boerenkool", "stroopwafel", "gevulde speculaas", \
		"döner", "you", "currywurst", "zuurkool", "nasi goreng", "curry", \
		"patatje oorlog", "burritos", "sambal boontjes"};

	return ((char *)food[rand() % 17]);
}

char	*get_rand_colour(void)
{
	const char	*colour[] = {"\033[0;31m", "\033[0;30m", "\033[0;32m", \
		"\033[0;33m", "\033[0;34m", "\033[0;35m", "\033[0;36m"};

	return ((char *)colour[rand() % 7]);
}

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
