/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:56:43 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/16 16:30:13 by lbonnefo         ###   ########.fr       */
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
	t_timeval		time;
}				t_data;

typedef struct	s_philo
{
	int				id_philo;	
	pthread_t		th;
	pthread_mutex_t	mutex;
	t_data			*data;
}				t_philo;

int	ft_atoi_positive(char *str);
int	init_struct(int argc, char **argv, t_data *data);
int	check_digit(char *str);
int init_and_launch_simu(t_data *data);
void *routine(void *arg);

void print_struct(t_data *data);
#endif
