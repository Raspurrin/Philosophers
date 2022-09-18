/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:20:04 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/19 00:11:08 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	unlock(t_philo *philo, t_data *data)
{
	pthread_mutex_unlock(&data->forks[philo->index]);
	if (philo->index == data->philo_nbr)
		pthread_mutex_unlock(&data->forks[0]);
	else
		pthread_mutex_unlock(&data->forks[philo->index + 1]);
}

static void	lock(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->index]);
	if (philo->index == data->philo_nbr)
		pthread_mutex_lock(&data->forks[0]);
	else
		pthread_mutex_lock(&data->forks[philo->index + 1]);
}

static void	eat(t_philo *philo, t_data *data)
{
	int64_t	cur_time;

	cur_time = get_time(philo->start_time);
	philo->meal_time = cur_time;
	lock(philo, data);
	printf("%lld\t ms | philosopher %d is eating\n", cur_time, philo->index + 1);
	usleep(philo->data->nomoclock);
	unlock(philo, data);
	philo->meal_count++;
}

bool	death_check(t_philo *philo, t_data *data)
{
	int64_t	cur_time;

	pthread_mutex_lock(&philo->data->end_mutex);
	if (philo->data->end_state == true)
		return (true);
	pthread_mutex_unlock(&data->end_mutex);
	cur_time = get_time(philo->start_time);
	if (cur_time - philo->meal_time == data->ripoclock)
	{
		printf("%lld\t ms | philosopher %d died\n", cur_time, \
												philo->index + 1);
		pthread_mutex_lock(&data->end_mutex);
		data->end_state = true;
		pthread_mutex_unlock(&data->end_mutex);
		return (true);
	}
	return (false);
}

void	*routine(void *v_philo)
{
	t_philo *const	philo = v_philo;

	philo->start_time = start_time();
	if (philo->index % 2 == 1)
		usleep(10);
	if (death_check(philo, philo->data))
		return (NULL);
	while (philo->meal_count < philo->data->nomoclock)
	{
		eat(philo, philo->data);
		printf("%lld\t ms | philosopher %d is sleeping\n", \
							get_time(philo->start_time), philo->index + 1);
		usleep(philo->data->nomoclock);
	}
	return (NULL);
}
