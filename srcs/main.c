/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:48:01 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/17 23:22:12 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int32_t	main(int32_t argc, char **argv)
{
	t_data	data;

	error_check(argc);
	init_data(&data, argc, argv);
	return (0);
}

