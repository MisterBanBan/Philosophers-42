/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavier <afavier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:17:12 by afavier           #+#    #+#             */
/*   Updated: 2024/07/16 14:13:03 by afavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_forks
{
	int				available_fork;
	pthread_mutex_t	fork;
}	t_forks;

typedef struct s_philosopher
{
	pthread_t		thread;

	int				n;
	int				nb_philo;
	int				eating;
	int				nb_meal;
	size_t			time_to_start;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_died;
	t_forks			*l_fork;
	t_forks			*r_fork;
	int				has_l_fork;
	int				has_r_fork;
	int				*is_dead;
	size_t			last_eating;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*last_eat;
	pthread_mutex_t	*start;
	bool			*go;
}	t_philosopher;

typedef struct s_philo_table
{
	pthread_t		check_death;
	t_philosopher	*philo;
	int				is_dead;
	bool			go;
	pthread_mutex_t	dead;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	last_eat;
	pthread_mutex_t	start;
}	t_philo_table;

int		main(int argc, char **argv);
long	ft_atol(const char *str);
size_t	get_current_time(void);
void	initialize_philo(char **argv, t_forks *forks, t_philosopher *philo);
int		initialize_table(t_philo_table *phi_table, t_philosopher *philo);
int		ft_usleep(size_t milli, t_philosopher *philo);
int		start_thread(t_philo_table *phi_table);
void	*thread(void *data);
int		initialize_forks(t_forks *forks, int nb_philo);
void	*check_dead(void *data);
int		pickup_forks(t_philosopher *philo);
void	put_down_forks(t_philosopher *philo);
int		eat(t_philosopher *philo);
int		philo_sleep(t_philosopher *philo);
int		join_t(t_philo_table *phi_table, int good);
int		philo_thinkings(t_philosopher *philo);
int		check_is_dead(t_philosopher *philo);
int		print_action(t_philosopher *philo, char *sentence);
int		ft_isdigit(int c);
void	*ft_calloc(size_t nmemb, size_t size);
void	init_philo_mutex(char **argv, t_philosopher *philo,
			t_philo_table *phi_table);

#endif