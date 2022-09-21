/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:19:43 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/21 22:56:19 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	init_args(t_data *data, int32_t argc, char **argv)
{
	data->end_state = false;
	data->philo_nbr = ft_atoi(argv[1]);
	data->ripoclock = ft_atoi(argv[2]);
	data->nomoclock = ft_atoi(argv[3]);
	data->zzzoclock = ft_atoi(argv[4]);
	if (argc == 6)
		data->min_meals = ft_atoi(argv[5]);
	else
		data->min_meals = -1;
}

void	init_data(t_data *data, int32_t argc, char **argv)
{
	int32_t	i;
	int64_t	start_time;

	i = 0;
	init_args(data, argc, argv);
	data->philo = malloc(data->philo_nbr * sizeof(t_philo));
	data->forks = malloc (data->philo_nbr * sizeof(pthread_mutex_t));
	pthread_mutex_init(&data->end_mutex, NULL);
	start_time = get_time(0);
	while (i < data->philo_nbr)
	{
		data->philo[i].index = i;
		data->philo[i].data = data;
		data->philo[i].start_time = start_time;
		data->philo[i].meal_time = start_time;
		data->philo[i].meal_count = 0;
		data->philo[i].can_eat = true;
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_create(&data->philo[i].sopher, NULL, routine, \
										(void *)&data->philo[i]);
		i++;
	}
}
