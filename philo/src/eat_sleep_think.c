/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:08:30 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/31 13:59:53 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		eating(t_philo *philo);
int		use_forks(t_philo *philo, int take_forks);
void	sleeping(t_philo *philo);

void	*routine(void *arg)
{
	t_philo	*philo;
	int		run_simu;

	philo = (t_philo *)arg;
	if (philo->id_philo % 2 == 0)
		p_sleep(philo->data->time_to_eat / 2);
	pthread_mutex_lock(&philo->data->mutex_run_sim);
	run_simu = philo->data->run_simu;
	pthread_mutex_unlock(&philo->data->mutex_run_sim);
	while (run_simu)
	{
		print_actions(philo, THINK);
		eating(philo);
		sleeping(philo);
		pthread_mutex_lock(&philo->data->mutex_run_sim);
		run_simu = philo->data->run_simu;
		pthread_mutex_unlock(&philo->data->mutex_run_sim);
	}
	return (arg);
}

int	eating(t_philo *philo)
{
	if (!use_forks(philo, 1))
		return (0);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal = get_time() - philo->data->start_t;
	pthread_mutex_unlock(&philo->mutex_last_meal);
	print_actions(philo, EAT);
	p_sleep(philo->data->time_to_eat);
	if (philo->data->meals != -1)
	{
		pthread_mutex_lock(&philo->mutex_last_meal);
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->mutex_last_meal);
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
			p_sleep(philo->data->time_to_die);
			pthread_mutex_unlock(philo->right_fork);
			print_actions(philo, DIED);
			return (set_end_simu(philo->data));
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

void	sleeping(t_philo *philo)
{
	print_actions(philo, SLEEP);
	p_sleep(philo->data->time_to_sleep);
}
