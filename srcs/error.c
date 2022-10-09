/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:19:53 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/10 01:09:32 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int32_t	check_error(char	*argv)
{
	size_t	i;
	int64_t	nbr;

	i = 0;
	while (*argv == '0')
		argv++;
	if (!*argv)
		return (0);
	if (argv[0] == '+' || argv[0] == '-')
		i++;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i++]))
			return (printf("input contains something "
					"different than digits"), false);
	}
	if (i <= 11)
	{
		nbr = ft_atoll(argv);
		if (nbr <= INT_MAX && nbr >= INT_MIN)
			return (true);
	}
	return (printf("Input is too high or low"), false);
}

bool	error_check(int32_t argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("You have to give either 4 or 5 arguments\n");
		exit(0);
	}
	argv++;
	while (*argv)
	{
		if (!check_error(*argv))
			exit(0);
		argv++;
	}
	return (true);
}
