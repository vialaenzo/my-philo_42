/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:31:19 by eviala            #+#    #+#             */
/*   Updated: 2024/10/05 15:39:05 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(t_error the_error)
{
	char *(ERROR)[] = {"NULL", "Alloc failed", "Mutex failed",
		"nb_philo time_td time_te time_tslp [nb_of_eat]", "Thread",
		"Arguments are invaid (must be > 0 and <= 2147483647"};
	printf(RED_B "ERROR" RESET " : %s : " RED_B "ERROR" RESET "\n",
		ERROR[the_error]);
	return (the_error);
}
