/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 04:53:08 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/10 06:53:04 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	death_checker(t_data *data)
{
	int32_t	i;

	i = 0;
	while (true)
	{
		pthread_mutex_lock(&data->end_mutex);
		if (get_time(data->philo[i].start_time) - \
						data->philo[i].meal_time >= data->ripoclock)
		{
			if (data->end_state == false)
			{
				printf("\033[1;31m%lld\tms | philosopher %d died. Rip. Big sad\n", \
				get_time(data->philo[i].start_time), data->philo[i].index + 1);
				data->end_state = true;
				pthread_mutex_unlock(&data->end_mutex);
				break ;
			}
		}
		pthread_mutex_unlock(&data->end_mutex);
		if (i == data->philo_nbr - 1)
		{
			usleep(100);
			i = 0;
		}
		i++;
	}
}
