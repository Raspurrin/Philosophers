/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:48:01 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/10 19:01:02 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * end_state signifies if a philosopher has died.
 * The calling thread will wait for other to finish with pthread_join.
 */
int32_t	main(int32_t argc, char **argv)
{
	t_data	data;
	int32_t	i;

	i = 0;
	if (!(error_check(argc, argv)))
		return (0);
	init_philos(&data, argc, argv);
	death_checker(&data);
	while (i < data.philo_nbr)
		pthread_join(data.philo[i++].sopher, NULL);
	if (data.end_state == false)
		printf("Everyone has eaten!\n");
	free_stuff(&data);
	return (0);
}
