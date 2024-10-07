/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:15:57 by eviala            #+#    #+#             */
/*   Updated: 2024/10/05 15:46:40 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->mutex_dead);
	int (is_dead) = philo->data->one_dead;
	if (is_dead != 1)
		printf("%lld %d %s\n", (get_time()) - (philo->data->start_time),
			philo->index_tab + 1, status);
	pthread_mutex_unlock(&philo->data->mutex_dead);
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	ft_usleep(long long time, t_data *data)
{
	pthread_mutex_lock(&data->mutex_dead);
	int (is_dead) = data->one_dead;
	pthread_mutex_unlock(&data->mutex_dead);
	long long (start) = get_time();
	while (!is_dead)
	{
		if (time_diff(start, get_time()) >= time)
			break ;
		usleep(50);
	}
}

int	is_satieted(t_data *data)
{
	int (i) = -1;
	int (current_eat) = 0;
	pthread_mutex_lock(&data->meal_check);
	int (max_eat) = data->nb_max_eat;
	pthread_mutex_unlock(&data->meal_check);
	if (max_eat > 0)
	{
		while (++i < data->nb_philos)
		{
			pthread_mutex_lock(&data->meal_check);
			current_eat = data->philos[i].current_eat;
			pthread_mutex_unlock(&data->meal_check);
			if (current_eat < max_eat)
				return (0);
		}
		pthread_mutex_lock(&data->meal_check);
		data->satiated = 1;
		pthread_mutex_unlock(&data->meal_check);
		return (1);
	}
	return (0);
}
