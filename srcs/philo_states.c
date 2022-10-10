/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:20:04 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/10 19:03:56 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	unlock(t_philo *philo, t_data *data)
{
	
	// printf("before unlock\n");
	// printf("philo: %d cur_time: %lld\n", philo->index + 1, get_time(philo->start_time));
	pthread_mutex_unlock(&data->forks[philo->index]);
	print_state(philo->data, philo, "released a fork", "");
	// printf("after unlock\n");
	// printf("philo: %d cur_time: %lld\n", philo->index + 1, get_time(philo->start_time));
	if (data->philo_nbr == 1)
		return ;
	// printf("before unlock\n");
	// printf("philo: %d cur_time: %lld\n", philo->index + 1, get_time(philo->start_time));
	if (philo->index + 1 == data->philo_nbr)
		pthread_mutex_unlock(&data->forks[0]);
	else
		pthread_mutex_unlock(&data->forks[philo->index + 1]);
	print_state(philo->data, philo, "released another fork", "");
	// printf("after unlock\n");
	// printf("philo: %d cur_time: %lld\n", philo->index + 1, get_time(philo->start_time));
}

static void	lock(t_philo *philo, t_data *data)
{
	// printf("before lock\n");
	// printf("philo: %d cur_time: %lld\n", philo->index + 1, get_time(philo->start_time));
	pthread_mutex_lock(&data->forks[philo->index]);
	// printf("after lock\n");
	// printf("philo: %d cur_time: %lld\n", philo->index + 1, get_time(philo->start_time));
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
	// printf("hi %d, time: \n", data->ripoclock);
	// printf("CHUJ %lld \n", philo->meal_time);
	// if (philo->index == 0)
	// 	printf("meal_time: %lld, substracted: %lld\n", philo->meal_time, cur_time - philo->meal_time);
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

	death_check(philo, philo->data);
	lock(philo, data);
	// printf("philo: %d cur_time: %lld\n", philo->index + 1, get_time(philo->start_time));
	// printf("before dying possibly\n");
	// printf("philo: %d cur_time: %lld\n", philo->index + 1, get_time(philo->start_time));
	death_check(philo, philo->data);
	// printf("philo: %d cur_time: %lld\n", philo->index + 1, get_time(philo->start_time));
	pthread_mutex_lock(&data->end_mutex);
	// printf("philo: %d cur_time: %lld\n", philo->index + 1, get_time(philo->start_time));
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
		// printf("philo: %d cur_time: %lld\n", philo->index + 1, get_time(philo->start_time));
		if (!eat(philo, philo->data))
			return (NULL);
		// printf("philo: %d cur_time: %lld\n", philo->index + 1, get_time(philo->start_time));
		print_state(philo->data, philo, "is sleeping", "");
		if (!(no_usleep(philo->data->zzzoclock, philo)))
			return (NULL);
		print_state(philo->data, philo, "is thinking", "");
		// if (!(no_usleep((philo->data->zzzoclock - (get_time(philo->start_time) \
		// 			- philo->meal_time) - philo->data->ripoclock) / 2, philo)))
		// 	return (NULL);
	}
	return (NULL);
}
