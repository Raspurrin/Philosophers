/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:19:43 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/18 21:56:56 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_data(t_data *data, int32_t argc, char **argv)
{
	int32_t	i;

	i = 0;
	data->end_state = false;
	data->philo_nbr = ft_atoi(argv[1]);
	data->ripoclock = ft_atoi(argv[2]);
	data->nomoclock = ft_atoi(argv[3]);
	data->zzzoclock = ft_atoi(argv[4]);
	if (argc == 6)
		data->min_meals = ft_atoi(argv[5]);
	data->philo = malloc(data->philo_nbr * sizeof(t_philo));
	data->forks = malloc (data->philo_nbr * sizeof(pthread_mutex_t));
	while (i < data->philo_nbr)
	{
		data->philo[i].index = i;
		data->philo[i].data = data;
		pthread_mutex_init(&data->forks[i++], NULL);
	}
	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_create(&data->philo[i].sopher, NULL, routine, \
										(void *)&data->philo[i]);
		i++;
	}
}
