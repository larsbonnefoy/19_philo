/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:56:43 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/27 17:45:20 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

typedef struct	timeval t_timeval;

typedef struct	s_data {
	
	int 			active_phil;
	int 			time_to_die;
	int 			time_to_eat;
	int				time_to_sleep;
	int				amount_to_eat;
	pthread_mutex_t	*mutex; 
	int				start_t;
	int				philo_alive;
	pthread_mutex_t	mutex_alive;
	pthread_mutex_t	mutex_active;
	pthread_mutex_t	log;
}				t_data;

typedef struct	s_philo
{
	int				id_philo;
	int				last_meal;
	pthread_t		th;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_data			*data;
}				t_philo;

//parsing
int		ft_atoi_positive(char *str);
int		init_data(int argc, char **argv, t_data *data);
int		check_digit(char *str);

int		init_and_launch_simu(t_data *data);
//utils
int		get_time();
int		smart_sleep(int duration, t_philo *philo);
void	print_actions(t_philo *philo, int action);
int		run_thread(t_philo **philo_array);
void	free_all(t_philo **philo_array,t_data *data);
int		check_philo_alive(t_philo *philo);
int		death_thread(t_data *data, int nbr_start_philo);

#endif
