/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:15:35 by afavier           #+#    #+#             */
/*   Updated: 2024/07/16 14:10:19 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

static int	number_eat(char **argv);

int	initialize_table(t_philo_table *phi_table, t_philosopher *philo)
{
	if (pthread_mutex_init(&phi_table->write_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&phi_table->dead, NULL) != 0)
	{
		pthread_mutex_destroy(&phi_table->write_mutex);
		return (-1);
	}
	if (pthread_mutex_init(&phi_table->last_eat, NULL) != 0)
	{
		pthread_mutex_destroy(&phi_table->write_mutex);
		pthread_mutex_destroy(&phi_table->dead);
		return (-1);
	}
	if (pthread_mutex_init(&phi_table->start, NULL) != 0)
	{
		pthread_mutex_destroy(&phi_table->write_mutex);
		pthread_mutex_destroy(&phi_table->dead);
		pthread_mutex_destroy(&phi_table->last_eat);
		return (-1);
	}
	phi_table->philo = philo;
	phi_table->is_dead = 0;
	phi_table->go = false;
	return (0);
}

void	initialize_philo(char **argv, t_forks *forks, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < ft_atol(argv[1]))
	{
		philo[i].n = i + 1;
		philo[i].nb_philo = ft_atol(argv[1]);
		philo[i].eating = number_eat(argv);
		philo[i].time_to_start = get_current_time();
		philo[i].time_to_died = ft_atol(argv[2]);
		philo[i].time_to_eat = ft_atol(argv[3]);
		philo[i].time_to_sleep = ft_atol(argv[4]);
		philo[i].last_eating = get_current_time();
		philo[i].nb_meal = 0;
		philo[i].r_fork = &forks[i];
		if (i == 0)
			philo[i].l_fork = &forks[ft_atol(argv[1]) - 1];
		else
			philo[i].l_fork = &forks[i - 1];
		philo[i].has_l_fork = 0;
		philo[i].has_r_fork = 0;
		i++;
	}
}

void	init_philo_mutex(char **argv, t_philosopher *philo,
						t_philo_table *phi_table)
{
	int	i;

	i = 0;
	while (i < ft_atol(argv[1]))
	{
		philo[i].dead = &phi_table->dead;
		philo[i].write_mutex = &phi_table->write_mutex;
		philo[i].last_eat = &phi_table->last_eat;
		philo[i].is_dead = &phi_table->is_dead;
		philo[i].go = &phi_table->go;
		philo[i].start = &phi_table->start;
		i++;
	}
}

int	initialize_forks(t_forks *forks, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_mutex_init(&forks[i].fork, NULL) != 0)
		{
			while (i > 0)
			{
				pthread_mutex_destroy(&forks[i].fork);
				i--;
			}
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	number_eat(char **argv)
{
	if (argv[5])
		return (ft_atol(argv[5]));
	else
		return (-1);
}
