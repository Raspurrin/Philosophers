/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:20:04 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/22 00:42:06 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	unlock(t_philo *philo, t_data *data)
{
	if (philo->data->end_state == false)
		printf("%lld\t  ms | philosopher %d released a fork\n", \
						get_time(philo->start_time), philo->index + 1);
	pthread_mutex_unlock(&data->forks[philo->index]);
	if (data->philo_nbr == 1)
		return ;
	if (philo->index + 1 == data->philo_nbr)
		pthread_mutex_unlock(&data->forks[0]);
	else
		pthread_mutex_unlock(&data->forks[philo->index + 1]);
	if (philo->data->end_state == false)
		printf("%lld\t  ms | philosopher %d released another fork\n", \
						get_time(philo->start_time), philo->index + 1);
}

static void	lock(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->index]);
	pthread_mutex_lock(&data->end_mutex);
	if (philo->data->end_state == false)
		printf("%lld\t  ms | philosopher %d took a fork\n", \
						get_time(philo->start_time), philo->index + 1);
	pthread_mutex_unlock(&data->end_mutex);
	if (data->philo_nbr == 1)
	{
		philo->can_eat = false;
		return ;
	}
	if (philo->index + 1 == data->philo_nbr)
		pthread_mutex_lock(&data->forks[0]);
	else
		pthread_mutex_lock(&data->forks[philo->index + 1]);
	if (philo->data->end_state == false)
		printf("%lld\t  ms | philosopher %d took another fork\n", \
						get_time(philo->start_time), philo->index + 1);
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
	pthread_mutex_lock(&data->end_mutex);
	if (data->end_state == false && philo->can_eat == true)
	{
		philo->meal_count++;
		cur_time = get_time(philo->start_time);
		philo->meal_time = cur_time;
		printf("%s%lld\tms | philosopher %d is eating %s\033[0m\n", \
				get_rand_colour(), cur_time, philo->index + 1, get_rand_food());
		pthread_mutex_unlock(&data->end_mutex);
		if (!ft_sleep(philo->data->nomoclock, philo))
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

	if (death_check(philo, philo->data))
		return (NULL);
	if (philo->index % 2 == 1)
		usleep(10);
	while (philo->meal_count < philo->data->min_meals || \
								philo->data->min_meals == -1)
	{
		if (!eat(philo, philo->data) || death_check(philo, philo->data))
			return (NULL);
		pthread_mutex_lock(&philo->data->end_mutex);
		if (philo->data->end_state == false && philo->can_eat == true)
			printf("%lld\t  ms | philosopher %d is sleeping\n", \
					get_time(philo->start_time), philo->index + 1);
		pthread_mutex_unlock(&philo->data->end_mutex);
		if (!(ft_sleep(philo->data->zzzoclock, philo)))
			return (NULL);
		pthread_mutex_lock(&philo->data->end_mutex);
		if (philo->data->end_state == false && philo->can_eat == true)
			printf("%lld\t  ms | philosopher %d is thinking\n", \
					get_time(philo->start_time), philo->index + 1);
		pthread_mutex_unlock(&philo->data->end_mutex);
	}
	return (NULL);
}
