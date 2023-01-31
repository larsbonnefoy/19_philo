/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:58:58 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/31 14:22:11 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!init_data(argc, argv, &data))
		return (-1);
	if (!init_and_launch_simu(&data))
		return (-1);
	free_and_destroy_data(&data, 0);
	return (0);
}
