/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:17:17 by eviala            #+#    #+#             */
/*   Updated: 2024/10/07 15:07:42 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philo *philo)
{
	t_data *(data) = philo->data;
	if (philo->index_tab % 2)
	{
		pthread_mutex_lock(philo->fork_right);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_left);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
		print_status(philo, "has taken a fork");
	}
	print_status(philo, "is eating");
	pthread_mutex_lock(&data->meal_check);
	philo->last_eat = get_time();
	(philo->current_eat)++;
	pthread_mutex_unlock(&data->meal_check);
	ft_usleep(data->time_te, data);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

static int	is_dead(t_philo *philo)
{
	t_data *(data) = philo->data;
	pthread_mutex_lock(&data->mutex_dead);
	if (philo->data->one_dead)
		return (pthread_mutex_unlock(&data->mutex_dead), 1);
	pthread_mutex_unlock(&data->mutex_dead);
	return (0);
}

void	*td_routine(void *args)
{
	t_philo *(philo) = (t_philo *)args;
	t_data *(data) = philo->data;
	if (philo->index_tab % 2)
		ft_usleep(10, data);
	while (1)
	{
		if (is_dead(philo))
			return (NULL);
		philo_eats(philo);
		pthread_mutex_lock(&data->meal_check);
		if (data->satiated)
			return (pthread_mutex_unlock(&data->meal_check), NULL);
		pthread_mutex_unlock(&data->meal_check);
		print_status(philo, "is sleeping");
		ft_usleep(data->time_tslp, data);
		if (is_dead(philo))
			return (NULL);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

int	thread_init(t_data *data)
{
	int (i) = -1;
	while (++i < data->nb_philos)
	{
		if (pthread_create(&data->philos[i].tpid, NULL, &td_routine,
				&data->philos[i]) != 0)
			return (1);
	}
	i = -1;
	while (++i < data->nb_philos)
	{
		if (pthread_join(data->philos[i].tpid, NULL) != 0)
			return (2);
	}
	return (0);
}
