/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:30:15 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/28 21:01:15 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_stuff(t_data *data)
{
	int32_t	i;

	i = 0;
	while (i < data->philo_nbr)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->end_mutex);
	free(&data->philo[0]);
	free(&data->forks[0]);
}

void	print_state(t_data *data, t_philo *philo, char *msg, char *colour)
{
	pthread_mutex_lock(&data->end_mutex);
	if (data->end_state == false && philo->can_eat == true)
		printf("%s%lld\tms | philosopher %d %s\033[0m\n", colour, \
			get_time(philo->start_time), philo->index + 1, msg);
	pthread_mutex_unlock(&data->end_mutex);
}

bool	ft_isdigit(int32_t c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	ft_isspace(int32_t c)
{
	if (c == ' ' || c == '\n' || c == '\t' || \
		c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
}

int32_t	ft_atoi(const char *str)
{
	size_t	i;
	int32_t	sign;
	int32_t	out;

	i = 0;
	sign = 1;
	out = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		out = (out * 10) + (str[i++] - '0');
	return (out * sign);
}
