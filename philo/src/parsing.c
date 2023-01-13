/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:09:24 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/13 15:30:42 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char **argv);

int	init_struct(int argc, char **argv, t_data *data)
{
	if (check_input(argc, argv) == -1)
	{
		printf("Error\n");
		return (-1);
	}
	data->nbr_philo = ft_atoi_positive(argv[1]);
	data->time_to_die = ft_atoi_positive(argv[2]);
	data->time_to_eat = ft_atoi_positive(argv[3]);
	data->time_to_sleep = ft_atoi_positive(argv[4]);
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
		if (ft_atoi_positive(argv[i]) <  0)
			return (-1);
		i++;	
	}
	return (0);
}
