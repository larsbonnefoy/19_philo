/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:56:43 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/20 15:07:40 by lbonnefo         ###   ########.fr       */
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
	
	int 			nbr_philo;
	int 			time_to_die;
	int 			time_to_eat;
	int				time_to_sleep;
	int				amount_to_eat;
	pthread_mutex_t	*mutex; //avoir ici l'array de mutex pour pouvoir acceder a n'importe quel mutex
	int				start_t;
}				t_data;

typedef struct	s_philo
{
	int				id_philo;
	int				last_meal;
	pthread_t		th;
	pthread_mutex_t left_fork;
	pthread_mutex_t right_fork;
	t_data			*data;
}				t_philo;

int		ft_atoi_positive(char *str);
int		init_data(int argc, char **argv, t_data *data);
int		check_digit(char *str);
int		init_and_launch_simu(t_data *data);
void	*routine(void *arg);
int		get_time();
void	smart_sleep(int duration);
void	print_actions(t_philo *philo, int action);
void set_mutexes(t_philo *philo);

void	print_struct(t_data *data);

#endif
