/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:58:58 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/16 14:43:36 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void print_struct(t_data *data);

int main(int argc, char **argv)
{
	t_data data;
	if (init_struct(argc, argv, &data) == -1)
		return (-1);
	print_struct(&data);
	init_and_launch_simu(&data);
	return (0);
}
