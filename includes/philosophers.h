/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:42:58 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/22 04:02:25 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct philo	t_philo;

typedef struct data
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int32_t			philo_nbr;
	int32_t			ripoclock;
	int32_t			nomoclock;
	int32_t			zzzoclock;
	int32_t			min_meals;
	bool			end_state;
	pthread_mutex_t	end_mutex;
}	t_data;

typedef struct philo
{
	bool			can_eat;
	pthread_mutex_t	meal_mutex;
	int64_t			start_time;
	pthread_t		sopher;
	int32_t			index;
	int64_t			meal_time;
	int32_t			meal_count;
	t_data			*data;
}	t_philo;

char	*get_rand_food(void);
char	*get_rand_colour(void);
int32_t	ft_atoi(const char *str);
bool	error_check(int32_t argc, char **argv);
void	init_data(t_data *data, int32_t argc, char **argv);
void	*routine(void *v_philo);
int64_t	get_time(int64_t start_time);
bool	no_usleep(int64_t sleep_time, t_philo *philo);
bool	ft_isalpha(int32_t c);
bool	ft_isdigit(int32_t c);
bool	death_check(t_philo *philo, t_data *data);
void	free_stuff(t_data *data);

#endif