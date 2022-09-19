/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:19:53 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/19 22:10:49 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	error_check(int32_t argc, char **argv)
{
	int32_t	i;
	int32_t	j;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("You have to give either 4 or 5 arguments\n");
		exit(0);
	}
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j++]))
			{
				printf("yo wtf\n");
				exit(0);
			}
		}
		i++;
	}
	return (true);
}
