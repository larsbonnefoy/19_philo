/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:20:29 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/31 11:50:07 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_end_simu(t_data *data);

int	run_thread(t_philo **philo_array, t_data *data)
{
	int		time_of_check;
	int		i;
	t_philo	*philo;
	int		last_meal;

	i = -1;
	philo = NULL;
	if (finished_eating(philo_array, data))
		return (set_end_simu(data));
	while (++i < data->nbr_phil)
	{
		philo = philo_array[i];
		time_of_check = get_time() - philo->data->start_t;
		pthread_mutex_lock(&philo->mutex_last_meal);
		last_meal = philo->last_meal;
		pthread_mutex_unlock(&philo->mutex_last_meal);
		if (last_meal + data->time_to_die < time_of_check)
		{
			print_actions(philo, DIED);
			return (set_end_simu(data));
		}
	}
	return (1);
}

int	check_run_simu(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->mutex_run_sim);
	if (!data->run_simu)
	{
		pthread_mutex_unlock(&data->mutex_run_sim);
		return (0);
	}
	pthread_mutex_unlock(&data->mutex_run_sim);
	return (1);
}

int	finished_eating(t_philo **philo_array, t_data *data)
{
	int		i;
	int		philo_done_eating;
	t_philo	*philo;

	philo_done_eating = 0;
	i = 0;
	while (i < data->nbr_phil)
	{
		philo = philo_array[i];
		pthread_mutex_lock(&philo->mutex_last_meal);
		if (philo->times_eaten >= data->meals && data->meals != -1)
			philo_done_eating++;
		pthread_mutex_unlock(&philo->mutex_last_meal);
		i++;
	}
	if (philo_done_eating == data->nbr_phil)
		return (1);
	else
		return (0);
}

int	set_end_simu(t_data *data)
{
	pthread_mutex_lock(&data->mutex_run_sim);
	data->run_simu = 0;
	pthread_mutex_unlock(&data->mutex_run_sim);
	return (0);
}
