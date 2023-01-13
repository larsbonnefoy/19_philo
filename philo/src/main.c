/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:58:58 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/13 15:38:54 by lbonnefo         ###   ########.fr       */
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
}

void print_struct(t_data *data)
{
	printf("nbr_philo	= %d\n", data->nbr_philo);
	printf("time_to_die	= %d\n", data->time_to_die);
	printf("time_to_eat	= %d\n", data->time_to_eat);
	printf("time_to_sleep	= %d\n", data->time_to_sleep);
	printf("amount_to_eat	= %d\n", data->amount_to_eat);
}
/*
void *roll_dice()
{
	long int *value;
	long int i;
	value = malloc(sizeof(int));
	i = 0;
	*value = 0;
	while (i < 100000000000)
	{
		*value += 1;
		i++;
	}
	*value = (rand() % 6) + 1;
	return ((void *) value);
}
//comment ils attendent la fin exactement?
int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	pthread_t th[4];
	long int *res;
	int i;

	srand(time(NULL));	
	i = 0;
	while (i < 5)
	{
		if (pthread_create(&th[i], NULL, &roll_dice, NULL) != 0)
			return 1;
		printf("Thread %d beg\n", i);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		if (pthread_join(th[i], (void **) &res) != 0)
			return 1;
		printf("Roll of dice = %lu\n", *res);
		printf("Thread %d end\n", i);
		i++;
	}
	return (0);
}
*/
