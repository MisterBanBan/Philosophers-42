/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:15:13 by afavier           #+#    #+#             */
/*   Updated: 2024/07/16 14:13:40 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

int	print_action(t_philosopher *philo, char *sentence)
{
	pthread_mutex_lock(philo->write_mutex);
	if (check_is_dead(philo) == -1)
	{
		pthread_mutex_unlock(philo->write_mutex);
		return (-1);
	}
	printf("%ld %d %s\n", get_current_time()
		- philo->time_to_start, philo->n, sentence);
	pthread_mutex_unlock(philo->write_mutex);
	return (0);
}

int	eat(t_philosopher *philo)
{
	if (print_action(philo, "is eating") == -1)
		return (-1);
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_lock(philo->last_eat);
	(*philo).last_eating = get_current_time();
	(*philo).nb_meal += 1;
	pthread_mutex_unlock(philo->last_eat);

	return (0);
}

int	philo_sleep(t_philosopher *philo)
{
	if (print_action(philo, "is sleeping") == -1)
		return (-1);
	ft_usleep(philo->time_to_sleep, philo);
	return (0);
}

int	philo_thinkings(t_philosopher *philo)
{
	if (print_action(philo, "is thinking") == -1)
		return (-1);
	return (0);
}
