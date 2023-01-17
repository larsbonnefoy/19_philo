/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:40:32 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/16 17:17:29 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**init_philo(t_data *data);
int		launch_simu(t_philo **philo_array);
void	*eat_sleep_think(void *arg);

int init_and_launch_simu(t_data *data)
{
	int i;
	t_philo **philo_array;

	philo_array = init_philo(data);
	if (philo_array == NULL)
		return (-1);
	if (launch_simu(philo_array) == -1)
		return (-1);
	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_join(philo_array[i]->th, (void **) &philo_array))
			return -1;
		printf("Thread of philo %d end\n", philo_array[i]->id_philo);	
		pthread_mutex_destroy(&philo_array[i]->mutex);
		i++;
	}
	printf("main thread end\n");
	return (0);
}

t_philo **init_philo(t_data *data)
{
	t_philo **philo_array; 
	int i;

	philo_array = malloc(sizeof(t_philo *) * data->nbr_philo);
	if (philo_array == NULL)
		return (NULL);
	i = 0;
	while (i < data->nbr_philo)
	{
		philo_array[i] = malloc(sizeof(t_philo));
		if (philo_array[i] == NULL)
			return (NULL); //free d'abord tous les philos -> fcts a faire
		philo_array[i]->id_philo = i;
		philo_array[i]->data = data;	
		if (pthread_mutex_init(&philo_array[i]->mutex, NULL) != 0)
			return (NULL); //free d'abord tous les philos -> fcts a faire
		i++;
	}
	return (philo_array);
}

int launch_simu(t_philo **philo_array)
{
	int i;
	int nbr_philo;

	i = 0;
	nbr_philo = philo_array[0]->data->nbr_philo;
	while (i < nbr_philo)
	{
		if (pthread_create(&philo_array[i]->th, NULL, &eat_sleep_think, philo_array) != 0)
			return -1;
		i++;
	}
	return (0);
}
//le soucis mtn c'est que chaque thread a acces a tous les philos
void *eat_sleep_think(void *arg)
{
	int i;
	int nbr_philo;

	t_philo **philo_array;
	philo_array = (t_philo **)arg;
	nbr_philo = philo_array[0]->data->nbr_philo;
	i = 0;
	while (i < nbr_philo)
	{
		if (i == philo_array[i]->id_philo)
			printf("philo nbr %d\n", philo_array[i]->id_philo);
		i++;
	}
	return ((void *) arg); //free dans la fonction de call ou ici ?
}
