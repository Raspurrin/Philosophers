/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:48:01 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/19 23:36:47 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int32_t	main(int32_t argc, char **argv)
{
	t_data	data;
	int32_t	i;

	i = 0;
	if (!(error_check(argc, argv)))
		return (printf("hello"), 0);
	init_data(&data, argc, argv);
	while (i < data.philo_nbr)
		pthread_join(data.philo[i++].sopher, NULL);
	if (data.end_state == true)
		return (0);
	printf("Everyone has eaten!\n");
	return (0);
}
