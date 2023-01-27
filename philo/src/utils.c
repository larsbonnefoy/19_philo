/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:59:22 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/27 15:52:33 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_actions(t_philo *philo, int action);

int get_time()
{
	t_timeval 	current_t;
	int			mill_sec;

	gettimeofday(&current_t, NULL);	
	mill_sec = ((current_t.tv_sec * 1000) + (current_t.tv_usec / 1000));
	return (mill_sec);
}

int	smart_sleep(int duration, t_philo *philo)
{
	int	start_time; 

	start_time = get_time();
	while (get_time() - duration < start_time)
	{
		if (!check_philo_alive(philo))
			return (0);
		usleep(100);
	}
	return (1);
}

void print_actions(t_philo *philo, int action)
{
	int action_time;

	if (!check_philo_alive(philo))
		return ;
	action_time = get_time() - philo->data->start_t;
	pthread_mutex_lock(&philo->data->log);
	if (action == 0)
		printf("%d %d has taken a fork\n", action_time, philo->id_philo);
	else if (action == 1)
		printf("%d %d is eating\n", action_time, philo->id_philo);
	else if (action == 2)
		printf("%d %d is sleeping\n", action_time, philo->id_philo);
	else if (action == 3)
		printf("%d %d is thinking\n", action_time, philo->id_philo);
	pthread_mutex_unlock(&philo->data->log);
}

int		run_thread(t_philo **philo_array)
{
	t_data	*data;
	int 	time_of_check;
	int		i;
	t_philo *philo;

	i = 0;
	philo = NULL;
	data = philo_array[0]->data;
	while (i < data->active_phil)
	{
		philo = philo_array[i];
		time_of_check = get_time() - philo->data->start_t;
		if (philo->last_meal + data->time_to_die < time_of_check)//si il vient de mourir, changer la value et end	
		{
			pthread_mutex_lock(&data->mutex_alive);
			data->philo_alive = 0;
			printf("%d %d died\n", time_of_check, philo->id_philo);
			pthread_mutex_unlock(&data->mutex_alive);
			return (0);
		}
		i++;
	}
	return (1);
}

int check_philo_alive(t_philo *philo)
{
	t_data *data = philo->data;
	
	pthread_mutex_lock(&data->mutex_alive);
	if (!data->philo_alive)
	{
		pthread_mutex_unlock(&data->mutex_alive);
		return (0);	
	}
	pthread_mutex_unlock(&data->mutex_alive);
	return (1);
}

void free_all(t_philo **philo_array, t_data *data)
{
	int i;
	int active_philo;

	i = 0;
	active_philo = philo_array[0]->data->active_phil;
	while (i < active_philo)
	{
		free(philo_array[i]);	
		i++;
	}
	free(philo_array);
	free(data->mutex);
}

int	death_thread(t_data *data, int nbr_start_philo)
{
	pthread_mutex_lock(&data->mutex_active);
	if (data->active_phil != nbr_start_philo)
	{
		pthread_mutex_unlock(&data->mutex_active);
		return (0);
	}	
	pthread_mutex_unlock(&data->mutex_active);
	return (1);
}
