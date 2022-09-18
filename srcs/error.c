/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:19:53 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/19 00:13:09 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	error_check(int32_t argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("You have to give either 4 or 5 arguments\n");
		exit(0);
	}
	return (true);
}
