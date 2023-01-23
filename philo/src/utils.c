/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:59:22 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/23 14:50:50 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_alive(t_philo *philo, int mod_key);
void print_actions(t_philo *philo, int action);

int get_time()
{
	t_timeval 	current_t;
	int			mill_sec;

	gettimeofday(&current_t, NULL);	
	mill_sec = ((current_t.tv_sec * 1000) + (current_t.tv_usec / 1000));
	return (mill_sec);
}

int	smart_sleep(int duration,t_philo *philo)
{
	int	start_time; 

	start_time = get_time();
	while (get_time() - duration < start_time)
	{
		if (!run_thread(philo))
			return (0);
		usleep(100);
	}
	return (1);
}

void print_actions(t_philo *philo, int action)
{
	int action_time;

	action_time = get_time() - philo->data->start_t;
	if (action == 0)
		printf("%d %d has taken a fork\n", action_time, philo->id_philo);
	else if (action == 1)
		printf("%d %d is eating\n", action_time, philo->id_philo);
	else if (action == 2)
		printf("%d %d is sleeping\n", action_time, philo->id_philo);
	else if (action == 3)
		printf("%d %d is thinking\n", action_time, philo->id_philo);
	else if (action == 4)
		printf("%d %d died\n", action_time, philo->id_philo);
	else if (action == 5)
		printf("%d %d dropped forks\n", action_time, philo->id_philo);
	else
		printf("Wrong action\n");
}

int		run_thread(t_philo *philo)
{
	t_data	*data;
	int 	time_of_check;

	data = philo->data;
	time_of_check = get_time() - philo->data->start_t;
	if (check_philo_alive(philo, 0) == 0)
		return (0);
	else if (philo->last_meal + data->time_to_die < time_of_check)//si il vient de mourir, changer la value et end	
	{
		check_philo_alive(philo, 1);
		return (0);
	}
	return (1);
}

int	check_philo_alive(t_philo *philo, int mod_key)
{
	t_data *data;

	data = philo->data;
	pthread_mutex_lock(&data->mutex_alive);
	if (mod_key == 0)
	{
		if (!data->philo_alive)
		{
			pthread_mutex_unlock(&data->mutex_alive);
			return (0);
		}
		pthread_mutex_unlock(&data->mutex_alive);
		return (1);
	}
	else 
	{
		data->philo_alive = 0;
		print_actions(philo, 4);
		pthread_mutex_unlock(&data->mutex_alive);
		return (0);
	}
}

void free_all(t_philo **philo_array, t_data *data)
{
	int i;
	int nbr_philo;

	i = 0;
	nbr_philo = philo_array[0]->data->nbr_philo;
	while (i < nbr_philo)
	{
		free(philo_array[i]);	
		i++;
	}
	free(philo_array);
	free(data->mutex);
}
