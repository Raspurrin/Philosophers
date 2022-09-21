/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:06:24 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/22 00:45:47 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief Get the amount of miliseconds elapsed since the Epoch.
 * time.tv_sec uses seconds and time.tv_usec uses microseconds,
 * so these units need to be converted as the time stamp uses
 * miliseconds. 
 * Microseconds: one thousands of a second
 * Milliseconds: one millionth of a second
 * @return int64_t 
 */
int64_t	get_time(int64_t start_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - start_time);
}

bool	no_usleep(int64_t sleep_time, t_philo *philo)
{
	int64_t	sleep_start;
	int64_t	cur_time;

	sleep_start = get_time(philo->start_time);
	cur_time = sleep_start;
	while (cur_time - sleep_start < sleep_time)
	{
		if (death_check(philo, philo->data))
			return (false);
		usleep(100);
		cur_time = get_time(philo->start_time);
	}
	return (true);
}
