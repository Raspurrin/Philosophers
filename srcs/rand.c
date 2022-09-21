/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:27:00 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/22 01:27:16 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static uint32_t	ft_rand(void)
{
	static uint32_t	seed = 69;

	return (seed *= 230043533);
}

char	*get_rand_food(void)
{
	const char	*food[] = {"soup", "potato", "Konstantin", "bugs", "spaghetti", \
		"broodje frikandel", "boerenkool", "stroopwafel", "gevulde speculaas", \
		"döner", "you", "currywurst", "zuurkool", "nasi goreng", "curry", \
		"patatje oorlog", "burritos", "sambal boontjes"};

	return ((char *)food[ft_rand() % 17]);
}

char	*get_rand_colour(void)
{
	const char	*colour[] = {"\033[0;31m", "\033[0;30m", "\033[0;32m", \
		"\033[0;33m", "\033[0;34m", "\033[0;35m", "\033[0;36m"};

	return ((char *)colour[ft_rand() % 7]);
}
