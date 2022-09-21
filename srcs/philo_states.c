/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:20:04 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/21 03:16:49 by mialbert         ###   ########.fr       */
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
	{
		if (pthread_mutex_unlock(&data->forks[philo->index + 1]))
			philo->can_eat = false;
	}
}

static void	lock(t_philo *philo, t_data *data)
{
	// printf("1.2.1\n");
	pthread_mutex_lock(&data->forks[philo->index]);
	// printf("1.2.2\n");
	if (data->philo_nbr == 1)
	{
		philo->can_eat = false;
		return ;
	}
	if (philo->index + 1 == data->philo_nbr)
	{
		// printf("1.2.3\n");
		if (pthread_mutex_lock(&data->forks[0]))
			philo->can_eat = false;
		// printf("1.2.4\n");
	}
	else
	{
		// printf("1.2.3\n");
		if (pthread_mutex_lock(&data->forks[philo->index + 1]))
			philo->can_eat = false;
		// printf("1.2.4\n");
	}
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

	// printf("1.1\n");
	if (death_check(philo, philo->data))
		return ;
	// printf("1.2\n");
	lock(philo, data);
	// printf("1.3\n");
	pthread_mutex_lock(&data->end_mutex);
	// printf("1.4\n");
	if (data->end_state == false && philo->can_eat == true)
	{
		// printf("1.5\n");
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
	// printf("1.6\n");
	// printf("1.7\n");
	// printf("1.8\n");
	unlock(philo, data);
	// printf("1.9\n");
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
		if (death_check(philo, philo->data))
			return (NULL);
		// printf("1\n");
		eat(philo, philo->data);
		// printf("2\n");
		if (death_check(philo, philo->data))
		{
			// printf("3\n");
			return (NULL);
			// printf("4\n");
		}
		pthread_mutex_lock(&philo->data->end_mutex);
		// printf("5\n");
		if (philo->data->end_state == false)
			printf("%lld\t ms | philosopher %d is sleeping\n", \
					get_time(philo->start_time), philo->index + 1);
		// printf("6\n");
		pthread_mutex_unlock(&philo->data->end_mutex);
		if (!(ft_sleep(philo->data->zzzoclock, philo)))
			return (NULL);
	}
	return (NULL);
}
