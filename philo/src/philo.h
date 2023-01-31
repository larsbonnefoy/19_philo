/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:56:43 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/31 14:57:29 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

typedef struct timeval	t_timeval;

typedef struct s_data
{
	int				nbr_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	pthread_mutex_t	*mutex;
	int				start_t;
	int				run_simu;
	pthread_mutex_t	mutex_run_sim;
	pthread_mutex_t	mutex_log;
}				t_data;

typedef struct s_phil
{
	int				id_philo;
	int				last_meal;
	int				times_eaten;
	pthread_t		th;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	mutex_last_meal;
	t_data			*data;
}				t_philo;

//parsing
int		ft_atoi_positive(char *str);
int		init_data(int argc, char **argv, t_data *data);
int		check_digit(char *str);
int		ft_error(char *error_msg);

//init_run_simu.c
int		init_and_launch_simu(t_data *data);

//manage thread
int		run_thread(t_philo **philo_array, t_data *data);
int		check_run_simu(t_philo *philo);
int		finished_eating(t_philo **philo, t_data *data);
int		set_end_simu(t_data *data);

//routine
void	*routine(void *arg);
int		use_forks(t_philo *philo, int take_forks);

//utils
int		get_time(void);
int		p_sleep(int duration);
void	print_actions(t_philo *philo, char *message);
t_philo	**free_and_destroy_philo(t_philo **ph_arr, int philo_to_free, int code);
int		free_and_destroy_data(t_data *data, int i);

#endif
