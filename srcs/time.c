/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:06:24 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/20 21:37:36 by mialbert         ###   ########.fr       */
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
	int64_t	sleep_start;
	int64_t	cur_time;

	sleep_start = get_time(start_time);
	cur_time = sleep_start;
	while (cur_time - sleep_start < sleep_time)
		cur_time = get_time(start_time);
}
