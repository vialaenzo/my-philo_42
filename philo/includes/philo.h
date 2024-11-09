/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:44:38 by eviala            #+#    #+#             */
/*   Updated: 2024/10/09 09:39:12 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MAGENTA "\033[0;35m"
# define YELLOW_B "\033[1;93m"
# define RED_B "\033[1;31m"
# define RESET "\033[0m"

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t			tpid;
	long long			last_eat;
	int					current_eat;
	pthread_mutex_t		*fork_left;
	pthread_mutex_t		*fork_right;
	t_data				*data;
	int					index_tab;
}						t_philo;

typedef struct s_data
{
	int					nb_philos;
	int					time_td;
	int					time_tslp;
	int					time_te;
	int					nb_max_eat;
	t_philo				*philos;
	pthread_mutex_t		printf;
	pthread_mutex_t		mutex_dead;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		dining_room_mutex;
	int					one_dead;
	int					philosophers_eating;
	int					satiated;
	int					all_eat;
	long long			start_time;
	pthread_t			monitor_thread;
}						t_data;

typedef enum e_error
{
	MALLOC = 1,
	MUTEX,
	ARGS,
	THREAD,
	ARGS2,
}						t_error;

int						ft_atoi(const char *str);
int						ft_error(t_error the_error);
int						ft_free_all(t_data *data);
int						thread_init(t_data *data);
long long				get_time(void);
void					print_status(t_philo *philo, char *status);
void					ft_usleep(long long time, t_data *data);
long long				time_diff(long long past, long long pres);
int						is_satieted(t_data *data);
int						data_init(t_data *data, char **argv, int argc);
int						philo_tab(t_data *data);

#endif
