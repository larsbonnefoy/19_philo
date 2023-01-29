/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:09:24 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/29 12:49:30 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char **argv);

int	init_data(int argc, char **argv, t_data *data)
{
	if (check_input(argc, argv) == -1)
		return (-1);
	data->active_phil = ft_atoi_positive(argv[1]);
	data->time_to_die = ft_atoi_positive(argv[2]);
	data->time_to_eat = ft_atoi_positive(argv[3]);
	data->time_to_sleep = ft_atoi_positive(argv[4]);
	data->start_t = get_time(); 
	data->philo_alive = 1;	
	data->mutex = malloc(sizeof(pthread_mutex_t) * data->active_phil);
	data->mutex_alive = malloc(sizeof(pthread_mutex_t) * 1);
	data->mutex_active_philo = malloc(sizeof(pthread_mutex_t));
	data->mutex_log = malloc(sizeof(pthread_mutex_t));
	if (data->mutex == NULL)
		return (0);
	if (pthread_mutex_init(data->mutex_alive, NULL) != 0)
		return (0); 
	if (pthread_mutex_init(data->mutex_log, NULL) != 0)
	{
		pthread_mutex_destroy(data->mutex_alive);
		return (0); 
	}
	if (pthread_mutex_init(data->mutex_active_philo, NULL) != 0)
	{
		pthread_mutex_destroy(data->mutex_alive);
		pthread_mutex_destroy(data->mutex_log);
		return (0); 
	}
	if (argc == 6)
		data->amount_to_eat = ft_atoi_positive(argv[5]);
	else
		data->amount_to_eat = -1; 
	return (1);
}

int	check_input(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Error\n");
		return (-1);
	}
	i = 1;
	while (i < argc) 
	{
		if (check_digit(argv[i]) < 0 || ft_atoi_positive(argv[i]) <= 0)
		{
			printf("Error\n");
			return (-1); 
		}
		i++;	
	}
	return (0);
}
