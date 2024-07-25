/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:16:44 by afavier           #+#    #+#             */
/*   Updated: 2024/07/16 14:53:01 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

int	check_is_dead(t_philosopher *philo);

int	start_thread(t_philo_table *phi_table)
{
	int		i;
	size_t	start_time;

	i = 0;
	pthread_mutex_lock(&phi_table->start);
	while (i < phi_table->philo->nb_philo)
	{
		if (pthread_create(&phi_table->philo[i].thread, NULL,
				thread, &phi_table->philo[i]) != 0)
		{
			phi_table->philo[0].nb_philo = i;
			return (pthread_mutex_unlock(&phi_table->start), -1);
		}
		i++;
	}
	i = 0;
	start_time = get_current_time();
	while (i < phi_table->philo->nb_philo)
	{
		phi_table->philo[i].time_to_start = start_time;
		phi_table->philo[i].last_eating = start_time;
		i++;
	}
	pthread_mutex_unlock(&phi_table->start);
	return (0);
}

int	join_t(t_philo_table *phi_table, int good)
{
	int	i;

	i = 0;
	if (good == 0 && pthread_join(phi_table->check_death, NULL ) != 0)
		return (-1);
	while (i < phi_table->philo->nb_philo)
	{
		if (pthread_join(phi_table->philo[i].thread, NULL ) != 0)
			return (-1);
		i++;
	}
	return (0);
}

void	*thread(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	pthread_mutex_lock(philo->start);
	pthread_mutex_unlock(philo->start);
	if (print_action(philo, "is thinking") == -1)
		return (NULL);
	if (philo->n % 2 == 0)
		ft_usleep(philo->time_to_eat, philo);
	while (check_is_dead(philo) == 0)
	{
		if (pickup_forks(philo) == -1)
			return (put_down_forks(philo), NULL);
		if (eat(philo) == -1)
			return (put_down_forks(philo), NULL);
		put_down_forks(philo);
		if (philo_sleep(philo) == -1)
			break ;
		if (philo_thinkings(philo) == -1)
			break ;
	}
	return (NULL);
}

int	check_is_dead(t_philosopher *philo)
{
	pthread_mutex_lock(philo->dead);
	if (*(philo)->is_dead == 1)
	{
		pthread_mutex_unlock(philo->dead);
		return (-1);
	}
	pthread_mutex_unlock(philo->dead);
	return (0);
}
