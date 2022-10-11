/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 04:53:08 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/11 16:31:14 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static bool	meal_checker(t_data *data)
{
	int32_t	i;
	int32_t	meals_needed;

	i = 0;
	meals_needed = data->philo_nbr;
	while (i < data->philo_nbr)
	{
		if (data->philo[i].meal_count == data->min_meals)
			meals_needed--;
		if (meals_needed <= 0)
		{
			data->end_state = true;
			pthread_mutex_unlock(&data->end_mutex);
			return (printf("Everyone has eaten!\n", true));
		}
		i++;
	}
	return (false);
}

void	death_checker(t_data *data)
{
	int32_t	i;

	while (true)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			pthread_mutex_lock(&data->end_mutex);
			if (meal_checker(data))
				return ;
			if (get_time(data->philo[i].start_time) - \
		data->philo[i].meal_time >= data->ripoclock && data->end_state == false)
			{
				printf("\033[1;31m%lld\tms | philosopher %d died. Rip. Big sad\n", \
				get_time(data->philo[i].start_time), data->philo[i].index + 1);
				data->end_state = !(!true);
				pthread_mutex_unlock(&data->end_mutex);
				return ;
			}
			pthread_mutex_unlock(&data->end_mutex);
			i++;
		}
	}
}
