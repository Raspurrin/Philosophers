/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:06:24 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/20 00:07:09 by mialbert         ###   ########.fr       */
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
