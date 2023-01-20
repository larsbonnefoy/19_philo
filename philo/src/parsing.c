/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:09:24 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/20 13:42:29 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char **argv);

int	init_data(int argc, char **argv, t_data *data)
{
	t_timeval tv;

	if (check_input(argc, argv) == -1)
	{
		printf("Error\n");
		return (-1);
	}
	data->nbr_philo = ft_atoi_positive(argv[1]);
	data->time_to_die = ft_atoi_positive(argv[2]);
	data->time_to_eat = ft_atoi_positive(argv[3]);
	data->time_to_sleep = ft_atoi_positive(argv[4]);
	data->mutex = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	if (data->mutex == NULL)
		return (-1);
	gettimeofday(&tv, NULL);
	data->start_t = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (argc == 6)
		data->amount_to_eat = ft_atoi_positive(argv[5]);
	else
		data->amount_to_eat = -1; 
	return (0);
}

int	check_input(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc < 5)
		return (-1);
	if (argc > 6)
		return (-1);	
	i = 1;
	while (i < argc) 
	{
		if (check_digit(argv[i]) < 0)
			return (-1); 
		if (ft_atoi_positive(argv[i]) <  0)
			return (-1);
		i++;	
	}
	return (0);
}
