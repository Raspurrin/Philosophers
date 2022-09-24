/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:20:04 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/24 17:14:45 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	unlock(t_philo *philo, t_data *data)
{
	print_state(philo->data, philo, "released a fork", "");
	pthread_mutex_unlock(&data->forks[philo->index]);
	if (data->philo_nbr == 1)
		return ;
	if (philo->index + 1 == data->philo_nbr)
		pthread_mutex_unlock(&data->forks[0]);
	else
		pthread_mutex_unlock(&data->forks[philo->index + 1]);
	print_state(philo->data, philo, "released another fork", "");
}

static void	lock(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->index]);
	print_state(philo->data, philo, "took a fork", "");
	if (data->philo_nbr == 1)
	{
		philo->can_eat = false;
		return ;
	}
	if (philo->index + 1 == data->philo_nbr)
		pthread_mutex_lock(&data->forks[0]);
	else
		pthread_mutex_lock(&data->forks[philo->index + 1]);
	print_state(philo->data, philo, "took another fork", "");
}

bool	death_check(t_philo *philo, t_data *data)
{
	int64_t	cur_time;

	pthread_mutex_lock(&data->end_mutex);
	if (data->end_state == true)
		return (pthread_mutex_unlock(&data->end_mutex), true);
	cur_time = get_time(philo->start_time);
	if (cur_time - philo->meal_time >= data->ripoclock)
	{
		if (data->end_state == false)
			printf("\033[1;31m%lld\tms | philosopher %d died. Rip. Big sad\n", \
													cur_time, philo->index + 1);
		data->end_state = true;
		return (pthread_mutex_unlock(&data->end_mutex), true);
	}
	return (pthread_mutex_unlock(&data->end_mutex), false);
}

static bool	eat(t_philo *philo, t_data *data)
{
	int64_t	cur_time;

	if (death_check(philo, philo->data))
		return (false);
	lock(philo, data);
	death_check(philo, philo->data);
	if (philo->can_eat == true)
	{
		philo->meal_count++;
		cur_time = get_time(philo->start_time);
		philo->meal_time = cur_time;
		// printf("%s%lld\tms | philosopher %d is eating %s\033[0m\n", \
		// 		get_rand_colour(), cur_time, philo->index + 1, get_rand_food());
		print_state(data, philo, "is eating", get_rand_colour());
		pthread_mutex_unlock(&data->end_mutex);
		if (!no_usleep(philo->data->nomoclock, philo))
			return (unlock(philo, data), pthread_mutex_unlock \
										(&data->end_mutex), false);
	}
	else
		pthread_mutex_unlock(&data->end_mutex);
	unlock(philo, data);
	if (death_check(philo, philo->data))
		return (false);
	return (true);
}

void	*routine(void *v_philo)
{
	t_philo *const	philo = v_philo;

	if (death_check(philo, philo->data))
		return (NULL);
	if (philo->index % 2 == 1)
		usleep(10);
	while (philo->meal_count < philo->data->min_meals || \
								philo->data->min_meals == -1)
	{
		if (!eat(philo, philo->data))
			return (NULL);
		print_state(philo->data, philo, "is sleeping", "");
		if (!(no_usleep(philo->data->zzzoclock, philo)))
			return (NULL);
		print_state(philo->data, philo, "is thinking", "");
	}
	return (NULL);
}
