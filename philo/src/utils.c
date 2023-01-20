/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:59:22 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/20 15:07:37 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_struct(t_data *data)
{
	printf("nbr_philo	= %d\n", data->nbr_philo);
	printf("time_to_die	= %d\n", data->time_to_die);
	printf("time_to_eat	= %d\n", data->time_to_eat);
	printf("time_to_sleep	= %d\n", data->time_to_sleep);
	printf("amount_to_eat	= %d\n", data->amount_to_eat);
}

int get_time()
{
	t_timeval 	current_t;
	int			mill_sec;

	gettimeofday(&current_t, NULL);	
	mill_sec = ((current_t.tv_sec * 1000) + (current_t.tv_usec / 1000));
	return (mill_sec);
}

void	smart_sleep(int duration)
{
	int	start_time; 

	start_time = get_time();
	while (get_time() - duration < start_time)
		usleep(100);
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
	else
		printf("Wrong action\n");
}

void set_mutexes(t_philo *philo)
{
	int id_philo;
	int amount_philo;

	amount_philo = philo->data->nbr_philo;
	id_philo = philo->id_philo;
	philo->left_fork = philo->data->mutex[id_philo];
	philo->right_fork = philo->data->mutex[(id_philo + 1) % amount_philo];
}
