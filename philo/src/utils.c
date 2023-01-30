/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:59:22 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/30 15:55:44 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_time()
{
	t_timeval 	current_t;
	int			mill_sec;

	gettimeofday(&current_t, NULL);	
	mill_sec = ((current_t.tv_sec * 1000) + (current_t.tv_usec / 1000));
	return (mill_sec);
}

int	p_sleep(int duration)
{
	int	start_time; 

	start_time = get_time();
	while (get_time() - duration < start_time)
		usleep(100);
	return (1);
}

void print_actions(t_philo *philo, int action)
{
	int action_time;

	if (!check_philo_alive(philo))
		return ;
	action_time = get_time() - philo->data->start_t;
	pthread_mutex_lock(&philo->data->mutex_log);
	if (action == 0)
		printf("%d %d has taken a fork\n", action_time, philo->id_philo);
	else if (action == 1)
		printf("%d %d is eating\n", action_time, philo->id_philo);
	else if (action == 2)
		printf("%d %d is sleeping\n", action_time, philo->id_philo);
	else if (action == 3)
		printf("%d %d is thinking\n", action_time, philo->id_philo);
	pthread_mutex_unlock(&philo->data->mutex_log);
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
