/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:20:04 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/21 03:29:29 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	unlock(t_philo *philo, t_data *data)
{
	pthread_mutex_unlock(&data->forks[philo->index]);
	if (data->philo_nbr == 1)
		return ;
	if (philo->index + 1 == data->philo_nbr)
		pthread_mutex_unlock(&data->forks[0]);
	else
		pthread_mutex_unlock(&data->forks[philo->index + 1]);
}

static void	lock(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->index]);
	if (data->philo_nbr == 1)
	{
		philo->can_eat = false;
		return ;
	}
	if (philo->index + 1 == data->philo_nbr)
		pthread_mutex_lock(&data->forks[0]);
	else
		pthread_mutex_lock(&data->forks[philo->index + 1]);
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
			printf("%lld\t ms | philosopher %d died\n", cur_time, \
												philo->index + 1);
		data->end_state = true;
		return (pthread_mutex_unlock(&data->end_mutex), true);
	}
	return (pthread_mutex_unlock(&data->end_mutex), false);
}

static void	eat(t_philo *philo, t_data *data)
{
	int64_t	cur_time;

	if (death_check(philo, philo->data))
		return ;
	lock(philo, data);
	pthread_mutex_lock(&data->end_mutex);
	if (data->end_state == false && philo->can_eat == true)
	{
		philo->meal_count++;
		cur_time = get_time(philo->start_time);
		philo->meal_time = cur_time;
		printf("%lld\t ms | philosopher %d is eating\n", cur_time, \
													philo->index + 1);
		pthread_mutex_unlock(&data->end_mutex);
		ft_sleep(philo->data->nomoclock, philo);
	}
	else
		pthread_mutex_unlock(&data->end_mutex);
	unlock(philo, data);
}

void	*routine(void *v_philo)
{
	t_philo *const	philo = v_philo;

	if (philo->index % 2 == 1)
		usleep(10);
	while (philo->meal_count < philo->data->min_meals || \
								philo->data->min_meals == -1)
	{
		pthread_mutex_lock(&philo->data->end_mutex);
		if (philo->data->end_state == false)
			printf("%lld\t ms | philosopher %d is thinking\n", \
					get_time(philo->start_time), philo->index + 1);
		pthread_mutex_unlock(&philo->data->end_mutex);
		eat(philo, philo->data);
		if (death_check(philo, philo->data))
			return (NULL);
		pthread_mutex_lock(&philo->data->end_mutex);
		if (philo->data->end_state == false)
			printf("%lld\t ms | philosopher %d is sleeping\n", \
					get_time(philo->start_time), philo->index + 1);
		pthread_mutex_unlock(&philo->data->end_mutex);
		if (!(ft_sleep(philo->data->zzzoclock, philo)))
			return (NULL);
	}
	return (NULL);
}
