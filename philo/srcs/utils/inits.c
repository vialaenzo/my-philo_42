/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:45:36 by eviala            #+#    #+#             */
/*   Updated: 2024/10/09 09:41:12 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_init(t_data *data, char **argv, int argc)
{
	data->nb_max_eat = -1;
	if (argc == 6)
		data->nb_max_eat = ft_atoi(argv[5]);
	data->nb_philos = ft_atoi(argv[1]);
	data->time_td = ft_atoi(argv[2]);
	data->time_te = ft_atoi(argv[3]);
	data->time_tslp = ft_atoi(argv[4]);
	data->one_dead = 0;
	data->all_eat = 0;
	data->satiated = 0;
	data->philosophers_eating = 0;
	pthread_mutex_init(&data->dining_room_mutex, NULL);
	pthread_mutex_init(&data->mutex_dead, NULL);
	pthread_mutex_init(&data->printf, NULL);
	pthread_mutex_init(&data->meal_check, NULL);
	data->start_time = get_time();
	if (data->nb_philos <= 0 || data->time_td <= 0 || data->time_te <= 0
		|| data->time_tslp <= 0)
		return (0);
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
		return (0);
	return (1);
}

int	philo_tab(t_data *data)
{
	t_philo	*philo;

	int (i) = -1;
	while (++i < data->nb_philos)
	{
		philo = &data->philos[i];
		philo->last_eat = get_time();
		philo->current_eat = 0;
		philo->index_tab = i;
		philo->data = data;
		philo->fork_left = malloc(sizeof(pthread_mutex_t));
		if (!philo->fork_left)
			return (0);
		pthread_mutex_init(philo->fork_left, NULL);
	}
	i = -1;
	while (++i < data->nb_philos - 1)
	{
		data->philos[i].fork_right = data->philos[i + 1].fork_left;
	}
	data->philos[i].fork_right = data->philos[0].fork_left;
	return (1);
}
