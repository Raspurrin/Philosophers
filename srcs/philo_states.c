/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:20:04 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/16 00:09:59 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *v_philo)
{
	t_philo	*philo;
	int64_t	cur_time;

	philo = (t_philo *)v_philo;
	while (true)
	{
		cur_time = get_time();
		if (cur_time - philo->meal_time == philo->data->ripoclock)
			return (printf("%lld ms | philosopher %d died\n", cur_time, philo->index), NULL);
		// check if everyone has eaten
		if (philo->index % 2 == 0)
		{
			philo->meal_time = get_time();
			// mutex thing
			printf("%lld ms | philosopher %d is eating\n", cur_time, philo->index);
			philo->meal_count++;
		}
		else
			printf("%lld ms | philosopher %d is sleeping\n", cur_time, philo->index);
		usleep(philo->data->nomoclock);
	}
	return (NULL);
}
