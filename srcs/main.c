/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:15:11 by eviala            #+#    #+#             */
/*   Updated: 2024/10/07 12:39:58 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	satiated_and_dead(t_data *data, int which_one, int index)
{
	(void)index;
	if (which_one == 1)
	{
		pthread_mutex_lock(&data->mutex_dead);
		data->one_dead = 1;
		printf("%lld %d" RED_B " died" RESET "\n", (get_time())
			- (data->start_time), index + 1);
		pthread_mutex_unlock(&data->mutex_dead);
	}
}

void	*monitor_routine(void *arg)
{
	int (i);
	t_data *(data) = (t_data *)arg;
	while (1)
	{
		i = -1;
		if (is_satieted(data))
			return (NULL);
		while (++i < data->nb_philos)
		{
			pthread_mutex_lock(&data->meal_check);
			if ((time_diff(data->philos[i].last_eat,
						get_time())) >= data->time_td)
			{
				pthread_mutex_unlock(&data->meal_check);
				return (satiated_and_dead(data, 1, i), NULL);
			}
			pthread_mutex_unlock(&data->meal_check);
		}
		pthread_mutex_lock(&data->mutex_dead);
		if (data->one_dead)
			return (pthread_mutex_unlock(&data->mutex_dead), NULL);
		pthread_mutex_unlock(&data->mutex_dead);
		usleep(10);
	}
	return (NULL);
}

void	alone_philo(t_data *data)
{
	pthread_mutex_lock(&data->philos[0].fork_left);
	print_status(&data->philos[0], "has taken a fork");
	pthread_mutex_unlock(&data->philos[0].fork_left);
	print_status(&data->philos[0], "No second fork available");
	ft_usleep(data->time_te, data);
	print_status(&data->philos[0], "is sleeping");
	ft_usleep(data->time_tslp, data);
	print_status(&data->philos[0], "is thinking");
	print_status(&data->philos[0], RED_B "died" RESET);
}

static int	parsing(char **argv, int argc)
{
	int	value;

	int (limit) = INT_MAX;
	int (args_to_check) = 0;
	if (argc == 5)
		args_to_check = 4;
	else if (argc == 6)
		args_to_check = 5;
	int (i) = 0;
	while (++i <= args_to_check)
	{
		value = ft_atoi(argv[i]);
		if (value <= 0 || value > limit)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_error(ARGS));
	if (!parsing(argv, argc))
		return (ft_error(ARGS2));
	if (!data_init(&data, argv, argc))
		return (ft_error(MALLOC));
	philo_tab(&data);
	if (data.nb_philos == 1)
		return (alone_philo(&data), 0);
	if (pthread_create(&data.monitor_thread, NULL, monitor_routine, &data) != 0)
		return (ft_error(THREAD));
	if (thread_init(&data) != 0)
		return (ft_error(THREAD));
	ft_free_all(&data);
	return (0);
}
