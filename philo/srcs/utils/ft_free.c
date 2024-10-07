/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:06:43 by eviala            #+#    #+#             */
/*   Updated: 2024/10/07 14:53:08 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_free_all(t_data *data)
{
	int	i;

	if (!data)
		return (1);
	if (data->monitor_thread)
	{
		pthread_join(data->monitor_thread, NULL);
		data->monitor_thread = 0;
	}
	if (data->philos)
	{
		i = -1;
		while (++i < data->nb_philos)
			pthread_mutex_destroy(data->philos[i].fork_left);
		free(data->philos);
		data->philos = NULL;
	}
	pthread_mutex_destroy(&data->printf);
	pthread_mutex_destroy(&data->mutex_dead);
	pthread_mutex_destroy(&data->meal_check);
	return (0);
}
