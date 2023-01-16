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

t_philo *init_philo(t_data *data, int philo_id);

int init_simu(t_data *data)
{
	//variable lenght array pas possible;
	pthread_t 		th[data->nbr_philo];
	pthread_mutex_t	mutex[data->nbr_philo];
	int i;
	t_philo *philo[];

	i = 0;
	while (i < data->nbr_philo)
	{
		philo = init_philo(data, i);
		if (philo == NULL)
			return -1;
		if (pthread_create(&th[i], NULL, &routine, philo) != 0)
			return -1;
		i++;
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_join(th[i], (void **) &philo))
			return -1;
		printf("Thread of philo %d end\n", philo->id_philo);	
		free(philo);
		i++;
	}
	pthread_mutex_destroy(mutex);
	printf("main thread end\n");
	return (0);
}

t_philo *init_philo(t_data *data, int philo_id)
{
	t_philo *philo;
	
	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->id_philo = philo_id;
	philo->data = data;
	return (philo);
}
