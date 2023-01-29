/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:08:30 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/27 19:29:35 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	eating(t_philo *philo);
int	use_forks(t_philo *philo, int take_forks);
int sleeping(t_philo *philo);

void *eat_sleep_think(void *arg)
{
	t_philo *philo;
	int	eat_lft;
	int	eat_max;

	philo = (t_philo *)arg;	
	eat_lft = 0;
	eat_max = philo->data->amount_to_eat;
	if (philo->id_philo % 2 == 0 )
		smart_sleep(philo->data->time_to_eat / 2, philo);
	while ((eat_lft < eat_max || eat_max == -1) && (philo->data->philo_alive))
	{
		print_actions(philo, THINK);
		if (!eating(philo))
			return (arg);			
		eat_lft++;
		if (!sleeping(philo))
			return (arg);
	}
	//ici data race??? idk why
	pthread_mutex_lock(philo->data->mutex_active);
	philo->data->active_phil--;
	pthread_mutex_unlock(philo->data->mutex_active);
	return (arg); 
}

int	eating(t_philo *philo)
{
	if (!use_forks(philo, 1))
		return (0);
	philo->last_meal = get_time() - philo->data->start_t;
	print_actions(philo, EAT);
	if (!smart_sleep(philo->data->time_to_eat, philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}	
	use_forks(philo, 0);	
	return (1);
}

int	use_forks(t_philo *philo, int take_forks)
{
	if (take_forks == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_actions(philo, FORK);
		if (philo->right_fork == philo->left_fork)
		{	
			smart_sleep(philo->data->time_to_die, philo);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		pthread_mutex_lock(philo->left_fork);
		print_actions(philo, FORK);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	return (1); 
}

int sleeping(t_philo *philo)
{
	print_actions(philo, SLEEP);
	if (!smart_sleep(philo->data->time_to_sleep, philo))
		return (0);
	return (1);
}
