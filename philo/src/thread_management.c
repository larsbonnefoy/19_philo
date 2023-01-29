/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:20:29 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/29 14:26:21 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		run_thread(t_philo **philo_array)
{
	t_data	*data;
	int 	time_of_check;
	int		i;
	t_philo *philo;
	int		last_meal;

	i = 0;
	philo = NULL;
	data = philo_array[0]->data;
	while (i < data->active_phil)
	{
		philo = philo_array[i];
		time_of_check = get_time() - philo->data->start_t;
		pthread_mutex_lock(&philo->mutex_last_meal);
		last_meal = philo->last_meal;
		pthread_mutex_unlock(&philo->mutex_last_meal);
		if (last_meal + data->time_to_die < time_of_check)//si il vient de mourir, changer la value et end	
		{
			pthread_mutex_lock(data->mutex_alive);
			data->philo_alive = 0;
			printf("%d %d died\n", time_of_check, philo->id_philo);
			pthread_mutex_unlock(data->mutex_alive);
			return (0);
		}
		i++;
	}
	return (1);
}

int check_philo_alive(t_philo *philo)
{
	t_data *data = philo->data;
	
	pthread_mutex_lock(data->mutex_alive);
	if (!data->philo_alive)
	{
		pthread_mutex_unlock(data->mutex_alive);
		return (0);	
	}
	pthread_mutex_unlock(data->mutex_alive);
	return (1);
}

int	finished_eating(t_data *data, int nbr_start_philo)
{
	pthread_mutex_lock(data->mutex_active);
	if (data->active_phil != nbr_start_philo)
	{
		pthread_mutex_unlock(data->mutex_active);
		return (1);
	}	
	pthread_mutex_unlock(data->mutex_active);
	return (0);
}
