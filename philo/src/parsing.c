/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:09:24 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/31 14:16:52 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char **argv);

int	init_data(int argc, char **argv, t_data *data)
{
	if (!check_input(argc, argv))
		return (0);
	data->nbr_phil = ft_atoi_positive(argv[1]);
	data->time_to_die = ft_atoi_positive(argv[2]);
	data->time_to_eat = ft_atoi_positive(argv[3]);
	data->time_to_sleep = ft_atoi_positive(argv[4]);
	data->start_t = get_time();
	data->run_simu = 1;
	data->mutex = malloc(sizeof(pthread_mutex_t) * data->nbr_phil);
	if (!data->mutex)
		return (0);
	if (pthread_mutex_init(&data->mutex_run_sim, NULL) != 0)
		return (free_and_destroy_data(data, 2));
	if (pthread_mutex_init(&data->mutex_log, NULL) != 0)
		return (free_and_destroy_data(data, 1));
	if (argc == 6)
		data->meals = ft_atoi_positive(argv[5]);
	else
		data->meals = -1;
	return (1);
}

int	check_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (ft_error("wrong amount of arguments"));
	i = 1;
	while (i < argc)
	{
		if (check_digit(argv[i]) < 0 || ft_atoi_positive(argv[i]) <= 0)
			return (ft_error("unvalid argument"));
		i++;
	}
	return (1);
}

int ft_error(char *error_msg)
{
	printf("Error : %s\n", error_msg);
	return (0);
}
