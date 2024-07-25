/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:15:45 by afavier           #+#    #+#             */
/*   Updated: 2024/07/16 14:43:24 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"
#include <limits.h>

static int	arguments_parse(int argc, char **argv);
static int	is_num(char *input_user);
void		clear_f(t_forks *forks, int nb, t_philo_table *phi_table);
static int	check_philo(t_philo_table	*phi_table);

int	main(int argc, char **argv)
{
	t_philo_table	phi_table;
	t_philosopher	*philo;
	t_forks			*forks;
	int				nb;

	if (arguments_parse(argc, argv) == -1)
		return (-1);
	nb = ft_atol(argv[1]);
	forks = ft_calloc(nb, sizeof(t_forks));
	if (!forks)
		return (-1);
	if (initialize_forks(forks, nb))
		return (free(forks), -1);
	philo = ft_calloc(nb, sizeof(t_philosopher));
	if (!philo)
		return (-1);
	initialize_table(&phi_table, philo);
	initialize_philo(argv, forks, philo);
	init_philo_mutex(argv, philo, &phi_table);
	if (start_thread(&phi_table) == -1)
		return (join_t(&phi_table, 1), clear_f(forks, nb, &phi_table), -1);
	if (check_philo(&phi_table) == -1)
		return (join_t(&phi_table, 1), clear_f(forks, nb, &phi_table), -1);
	join_t(&phi_table, 0);
	return (clear_f(forks, nb, &phi_table), 0);
}

static int	check_philo(t_philo_table	*phi_table)
{
	pthread_mutex_lock(&phi_table->start);
	if (pthread_create(&phi_table->check_death, NULL, check_dead,
			phi_table) != 0)
		return (pthread_mutex_unlock(&phi_table->start), -1);
	phi_table->go = true;
	pthread_mutex_unlock(&phi_table->start);
	return (0);
}

static int	arguments_parse(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("To many args or not enough args"), -1);
	if ((is_num(argv[1]) == -1) || (is_num(argv[2]) == -1)
		|| (is_num(argv[3]) == -1) || (is_num(argv[4]) == -1))
		return (printf("Wrong args"), -1);
	if (argv[5] != NULL && (is_num(argv[5]) == -1))
		return (printf("Wrong args"), -1);
	if (ft_atol(argv[1]) == 0 || (ft_atol(argv[1]) == LONG_MAX)
		|| (ft_atol(argv[2]) == LONG_MAX) || (ft_atol(argv[3]) == LONG_MAX)
		|| (ft_atol(argv[4]) == LONG_MAX))
		return (printf("Numbers to long"), -1);
	if (ft_atol(argv[2]) == 0 || ft_atol(argv[3]) == 0 || ft_atol(argv[4]) == 0)
		return (printf("Wrong args"), -1);
	if (argv[5] != NULL && (ft_atol(argv[5]) == LONG_MAX
			|| ft_atol(argv[5]) == 0))
		return (printf("Wrong args"), -1);
	return (0);
}

static int	is_num(char *input_user)
{
	int	i;

	i = 0;
	while (input_user[i])
	{
		if (!ft_isdigit(input_user[i]))
			return (-1);
		i++;
	}
	return (0);
}

void	clear_f(t_forks *forks, int nb, t_philo_table *phi_table)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_destroy(&(forks)[i].fork);
		i++;
	}
	free(forks);
	pthread_mutex_destroy(&(phi_table)->dead);
	pthread_mutex_destroy(&(phi_table)->write_mutex);
	pthread_mutex_destroy(&(phi_table)->last_eat);
	pthread_mutex_destroy(&(phi_table)->start);
	free(phi_table->philo);
}
