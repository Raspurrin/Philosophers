/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:30:15 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/18 18:43:20 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief Get the amount of miliseconds elapsed since the Epoch.
 * time.tv_sec uses seconds and time.tv_usec uses microseconds,
 * so these units need to be converted. 
 * @return int64_t 
 */
int64_t	get_time(int64_t start_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - start_time);
}

int64_t	start_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(int64_t sleep_time, int64_t start_time)
{
	int64_t	old_time; 

	old_time = get_time(start_time);
	while (true)
	{
		if (get_time(start_time) - old_time == sleep_time)
			return ;
	}
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

