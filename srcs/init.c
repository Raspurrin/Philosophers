/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:19:43 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/13 23:46:01 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_data(t_data *data, int32_t argc, char **argv) // argc
{
	size_t	i;

	i = 0;
	data->philo_nbr = ft_atoi(argv[1]);
	data->ripoclock = ft_atoi(argv[2]);
	data->nomoclock = ft_atoi(argv[3]);
	data->zzzoclock = ft_atoi(argv[4]);
	data->min_meals = ft_atoi(argv[5]);
	data->philo = malloc(data->philo_nbr * sizeof(t_philo));
	while (i < data->philo_nbr)
	{
		data->philo[i].index = i + 1;
		pthread_create(&data->philo[i].sopher, NULL, routine, \
										(void *)&data->philo[i]);
		pthread_mutex_init(&data->philo[i].right_fork, NULL);
		if (i > 0)
			data->philo[i].left_fork = data->philo[i - 1].right_fork;
		i++;
	}
}
