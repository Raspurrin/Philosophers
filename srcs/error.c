/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:19:53 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/10 02:36:59 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int32_t	check_error(char	*argv)
{
	size_t	i;
	int64_t	nbr;

	i = 0;
	nbr = 0;
	while (*argv == '0')
		argv++;
	if (!*argv)
		return (true);
	if (argv[0] == '+' || argv[0] == '-')
		i++;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i++]))
			return (printf("input can only contain digits"), false);
	}
	if (i > 0 && i <= 11)
	{
		nbr = ft_atoll(argv);
		if (nbr <= INT_MAX && nbr >= INT_MIN && nbr >= 0)
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
