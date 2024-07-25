/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taken_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:16:35 by afavier           #+#    #+#             */
/*   Updated: 2024/07/16 14:53:23 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

static int	right_put_fork(t_philosopher *philo);
static int	left_put_fork(t_philosopher *philo);

int	pickup_forks(t_philosopher *philo)
{
	while ((*philo).has_l_fork == 0 || (*philo).has_r_fork == 0)
	{
		if (right_put_fork(philo) == -1)
			return (-1);
		if (left_put_fork(philo) == -1)
			return (-1);
		usleep(200);
	}
	return (0);
}

static int	right_put_fork(t_philosopher *philo)
{
	if (check_is_dead(philo) == -1)
		return (-1);
	pthread_mutex_lock(&philo->r_fork->fork);
	if ((*philo).r_fork->available_fork == 0)
	{
		(*philo).r_fork->available_fork = 1;
		(*philo).has_r_fork = 1;
		pthread_mutex_unlock(&philo->r_fork->fork);
		if (print_action(philo, "has taken a fork") == -1)
			return (-1);
	}
	else
		pthread_mutex_unlock(&philo->r_fork->fork);
	return (0);
}

static int	left_put_fork(t_philosopher *philo)
{
	if (check_is_dead(philo) == -1)
		return (-1);
	pthread_mutex_lock(&philo->l_fork->fork);
	if ((*philo).l_fork->available_fork == 0)
	{
		(*philo).l_fork->available_fork = 1;
		(*philo).has_l_fork = 1;
		pthread_mutex_unlock(&philo->l_fork->fork);
		if (print_action(philo, "has taken a fork") == -1)
			return (-1);
	}
	else
		pthread_mutex_unlock(&philo->l_fork->fork);
	return (0);
}

void	put_down_forks(t_philosopher *philo)
{
	if ((*philo).has_l_fork == 1 && (*philo).has_r_fork == 1)
	{
		pthread_mutex_lock(&philo->l_fork->fork);
		(*philo).has_l_fork = 0;
		(*philo).l_fork->available_fork = 0;
		pthread_mutex_unlock(&philo->l_fork->fork);
		pthread_mutex_lock(&philo->r_fork->fork);
		(*philo).has_r_fork = 0;
		(*philo).r_fork->available_fork = 0;
		pthread_mutex_unlock(&philo->r_fork->fork);
	}
}
