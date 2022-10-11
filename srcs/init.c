/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:19:43 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/11 01:47:12 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * Initialising the data struct. Main arguments:
 * 	1 - Amount of philosophers (threads)
 * 	2 - A philo dies if ripoclock exceeds starting time of last meal/start sim
 *  3 - Nomoclock - time it takes to eat after picking up both "forks"
 *  4 - Zzzoclock - Time it takes to sleep after successfully eating
 *  5 - [optional] min_meals - Min amount of meals the philosophers need to eat
 * 		for the simulation to stop. If none given it goes ad infinitum
 * The same amount of forks (mutexes) are given as the amount of philosophers
 */
static void	init_data(t_data *data, int32_t argc, char **argv)
{
	data->end_state = false;
	data->philo_nbr = ft_atoll(argv[1]);
	if (data->philo_nbr == 0)
	{
		printf("There has to be at least one philosopher\n");
		exit(0);
	}
	data->ripoclock = ft_atoll(argv[2]);
	data->nomoclock = ft_atoll(argv[3]);
	data->zzzoclock = ft_atoll(argv[4]);
	if (argc == 6)
		data->min_meals = ft_atoll(argv[5]);
	else
		data->min_meals = -1;
	data->forks = malloc (data->philo_nbr * sizeof(pthread_mutex_t));
	data->philo = malloc(data->philo_nbr * sizeof(t_philo));
	pthread_mutex_init(&data->end_mutex, NULL);
	pthread_mutex_init(&data->start_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
}

/**
 * - Starting time is the start of the simulation, even though not 
 * all threads start at the same time. Meal_time is used to keep track of the 
 * start of their meals to track the death time. It is initialised with 
 * start_time because with no last meal, the start of the sim is counted.
 * - If a mutex or thread fails, philo_nbr is initialised with i + 1 because
 * then the right amount of threads can be joined and mutexes destroyed.
 * If a mutex fails, then I make sure another thread is created to ensure
 * the number is correct for both threads and mutexes.
 */
void	init_philos(t_data *data, int32_t argc, char **argv)
{
	int32_t	i;
	int64_t	start_time;

	i = 0;
	init_data(data, argc, argv);
	start_time = get_time(0);
	while (i < data->philo_nbr)
	{
		data->philo[i].index = i;
		data->philo[i].data = data;
		printf("start_time init: %lld\n\n", start_time);
		data->philo[i].start_time = start_time;
		data->philo[i].meal_time = 0;
		data->philo[i].meal_count = 0;
		data->philo[i].can_eat = true;
// 		if (!pthread_mutex_init(&data->forks[i], NULL) || \
// !(pthread_create(&data->philo[i].sopher, NULL, routine, (void *)&data->philo[i])))
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_create(&data->philo[i].sopher, NULL, routine, \
												(void *)&data->philo[i]);
		// {
		// 	data->philo_nbr = i + 1;
		// 	return ;
		// }
		i++;
	}
}
