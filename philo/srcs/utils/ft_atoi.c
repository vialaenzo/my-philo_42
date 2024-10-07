/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviala <eviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:48:48 by eviala            #+#    #+#             */
/*   Updated: 2024/10/05 15:46:15 by eviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int (i) = 0;
	int (sign) = 1;
	unsigned long long (result) = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (unsigned long long)(LONG_MAX / 10)
			|| (result == (unsigned long long)(LONG_MAX / 10) && (str[i]
					- '0') > (LONG_MAX % 10)))
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * (int)result);
}
