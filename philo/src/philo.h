/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:56:43 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/13 15:54:38 by lbonnefo         ###   ########.fr       */
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

typedef struct	s_data {
	
	int nbr_philo;
	int time_to_die;
	int time_to_eat;
	int	time_to_sleep;
	int	amount_to_eat;

}				t_data;

int	ft_atoi_positive(char *str);
int	init_struct(int argc, char **argv, t_data *data);
int	check_digit(char *str);

#endif
