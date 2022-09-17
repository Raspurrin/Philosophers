/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:20:04 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/18 00:59:29 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// static bool	meal_check(t_data *data)
// {
// 	int32_t	i;

// 	i = 0;
// 	while (i < data->min_meals)
// 	{
// 		if (data->philo[i].meal_count != data->min_meals)
// 			return (false);
// 	}
// 	return (true);
// }

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

	cur_time = get_time();
	philo->meal_time = get_time();
	lock(philo, data);
	printf("%lld ms | philosopher %d is eating\n", cur_time, philo->index + 1);
	usleep(philo->data->nomoclock);
	unlock(philo, data);
	philo->meal_count++;
}

void	*routine(void *v_philo)
{
	int64_t	cur_time;
	t_philo	*const philo = v_philo;

	cur_time = get_time();
	if (philo->index % 2 == 1)
		usleep(10);
	while (true)
	{		
		// if (cur_time - philo->meal_time == philo->data->ripoclock)
		// 	return (printf("%lld ms | philosopher %d died\n", cur_time, philo->index), NULL);
		// if (meal_check(philo->data))
		// 	return (printf("Everyone has eaten!\n"), NULL);
		eat(philo, philo->data);
		printf("%lld ms | philosopher %d is sleeping\n", cur_time, philo->index + 1);
		usleep(philo->data->nomoclock);
	}
	return (NULL);
}