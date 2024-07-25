/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:15:53 by afavier           #+#    #+#             */
/*   Updated: 2024/07/16 14:13:50 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

int			philo_dead(t_philosopher *philo);
static void	philo_meal(t_philosopher *philo, int *meal);
static void	is_dead(t_philo_table *table, t_philosopher *philo);
static void	finish_meal(t_philo_table *table);

void	*check_dead(void *data)
{
	t_philo_table	*philo_table;
	int				i;
	int				meal;

	philo_table = (t_philo_table *)data;
	pthread_mutex_lock(&philo_table->start);
	while (!philo_table->go)
		;
	pthread_mutex_unlock(&philo_table->start);
	while (true)
	{
		i = 0;
		meal = 0;
		while (i < philo_table->philo[0].nb_philo)
		{
			philo_meal(&(philo_table->philo[i]), &meal);
			if (philo_dead(&(philo_table->philo[i])) == -1)
				return (is_dead(philo_table, &(philo_table->philo[i])), NULL);
			i++;
		}
		if (meal == philo_table->philo->nb_philo)
			return (finish_meal(philo_table), NULL);
	}
	return (NULL);
}

static void	philo_meal(t_philosopher *philo, int *meal)
{
	pthread_mutex_lock(philo->last_eat);
	if ((*philo).eating != -1)
	{
		if ((*philo).nb_meal >= (*philo).eating)
			(*meal) += 1;
		else
			(*meal) = 0;
	}
	pthread_mutex_unlock(philo->last_eat);
}

int	philo_dead(t_philosopher *philo)
{
	pthread_mutex_lock(philo->last_eat);
	if (((get_current_time() - philo->last_eating) >= philo->time_to_died))
	{
		pthread_mutex_unlock(philo->last_eat);
		return (-1);
	}
	pthread_mutex_unlock(philo->last_eat);
	return (0);
}

static void	is_dead(t_philo_table *table, t_philosopher *philo)
{
	pthread_mutex_lock(&table->dead);
	table->is_dead = 1;
	pthread_mutex_unlock(&table->dead);
	pthread_mutex_lock(&table->write_mutex);
	printf("%ld %d died\n", get_current_time()
		- philo->time_to_start, philo->n);
	pthread_mutex_unlock(&table->write_mutex);
}

static void	finish_meal(t_philo_table *table)
{
	pthread_mutex_lock(&table->dead);
	table->is_dead = 1;
	pthread_mutex_unlock(&table->dead);
}
