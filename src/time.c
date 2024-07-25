/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:16:49 by afavier           #+#    #+#             */
/*   Updated: 2024/07/16 14:52:46 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

size_t	get_current_time(void)
{
	struct timeval	time ;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday error\n", 19);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milli, t_philosopher *philo)
{
	size_t	time;

	time = get_current_time();
	while ((get_current_time() - time) < milli)
	{
		usleep(500);
		if (check_is_dead(philo) == -1)
			return (-1);
	}
	return (0);
}
