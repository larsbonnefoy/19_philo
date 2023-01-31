/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:59:22 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/31 15:34:09 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	t_timeval	current_t;
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

void	print_actions(t_philo *philo, char *message)
{
	int	action_time;

	if (!check_run_simu(philo))
		return ;
	action_time = get_time() - philo->data->start_t;
	pthread_mutex_lock(&philo->data->mutex_log);
	printf("%d %d %s\n", action_time, philo->id_philo, message);
	pthread_mutex_unlock(&philo->data->mutex_log);
}

t_philo	**free_and_destroy_philo(t_philo **ph_arr, int philo_to_free, int code)
{
	int	i;

	i = 0;
	if (code != 0)
		ft_error("memory issue");
	while (i < philo_to_free)
	{
		if (code == 0)
		{
			pthread_mutex_destroy(&ph_arr[i]->mutex_last_meal);
			code++;
		}
		if (code == 1)
		{
			pthread_mutex_destroy(ph_arr[i]->left_fork);
			code++;
		}
		if (code == 2)
			free(ph_arr[i]);
		i++;
	}
	free(ph_arr);
	return (NULL);
}

int	free_and_destroy_data(t_data *data, int action_code)
{
	if (action_code != 0)
		ft_error("memory issue");
	if (action_code == 0)
	{
		pthread_mutex_destroy(&data->mutex_log);
		action_code++;
	}
	if (action_code == 1)
	{
		pthread_mutex_destroy(&data->mutex_run_sim);
		action_code++;
	}
	if (action_code == 2)
		free(data->mutex);
	return (0);
}
