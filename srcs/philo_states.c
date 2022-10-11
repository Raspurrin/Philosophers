/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:20:04 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/11 02:19:57 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	unlock(t_philo *philo, t_data *data)
{
	
	// printf("before unlock\n");
	pthread_mutex_unlock(&data->forks[philo->index]);
	print_state(philo->data, philo, "released a fork", "");
	// printf("after unlock\n");
	if (data->philo_nbr == 1)
		return ;
	// printf("before unlock\n");
	if (philo->index + 1 == data->philo_nbr)
		pthread_mutex_unlock(&data->forks[0]);
	else
		pthread_mutex_unlock(&data->forks[philo->index + 1]);
	print_state(philo->data, philo, "released another fork", "");
	// printf("after unlock\n");
}

static void	lock(t_philo *philo, t_data *data)
{
	// printf("before lock\n");
	pthread_mutex_lock(&data->forks[philo->index]);
	// printf("after lock\n");
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

bool	death_check(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	if (data->end_state == true)
		return (pthread_mutex_unlock(&data->end_mutex), true);
	return (pthread_mutex_unlock(&data->end_mutex), false);
}

static bool	eat(t_philo *philo, t_data *data)
{
	int64_t	cur_time;

	lock(philo, data);
	pthread_mutex_lock(&data->end_mutex);
	if (data->end_state == false && philo->can_eat == true)
	{
		philo->meal_count++;
		cur_time = get_time(philo->start_time);
		philo->meal_time = cur_time;
		printf("%s%lld\tms | philosopher %d is eating %s\033[0m\n", \
				get_rand_colour(), get_time(philo->start_time), philo->index + 1, get_rand_food());
		pthread_mutex_unlock(&data->end_mutex);
		if (!no_usleep(philo->data->nomoclock, philo))
			return (unlock(philo, data), pthread_mutex_unlock \
										(&data->end_mutex), false);
	}
	else
		pthread_mutex_unlock(&data->end_mutex);
	unlock(philo, data);
	return (true);
}

void	*routine(void *v_philo)
{
	t_philo *const	philo = v_philo;

	if (philo->index % 2 == 1)
		no_usleep(10, philo);
	while (philo->meal_count < philo->data->min_meals || \
								philo->data->min_meals == -1)
	{
		if (death_check(philo->data))
			return (NULL);
		if (!eat(philo, philo->data))
			return (NULL);
		print_state(philo->data, philo, "is sleeping", "");
		if (!(no_usleep(philo->data->zzzoclock, philo)))
			return (NULL);
		print_state(philo->data, philo, "is thinking", "");
	}
	return (NULL);
}
