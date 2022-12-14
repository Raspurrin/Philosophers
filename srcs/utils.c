/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 01:30:15 by mialbert          #+#    #+#             */
/*   Updated: 2022/10/11 21:44:28 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_at_exit(t_data *data, int32_t mutex_nbr, int32_t thread_nbr, \
																char *msg)
{
	int32_t	i;

	i = 0;
	printf("%s", msg);
	while (i < mutex_nbr)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->end_mutex);
	i = 0;
	while (i < thread_nbr)
		pthread_detach(data->philo[i++].sopher);
	free(&data->philo[0]);
	free(&data->forks[0]);
	exit(2);
}

void	print_state(t_data *data, t_philo *philo, char *msg, char *colour)
{
	pthread_mutex_lock(&data->end_mutex);
	if (data->end_state == false && philo->can_eat == true)
	{
		printf("%s%lld\tms | philosopher %d %s\033[0m\n", colour, \
			get_time(philo->start_time), philo->index + 1, msg);
	}
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

int64_t	ft_atoll(const char *str)
{
	size_t	i;
	int32_t	sign;
	int64_t	out;

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
