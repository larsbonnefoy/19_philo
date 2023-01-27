/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:40:32 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/27 17:48:21 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**init_philo(t_data *data);
void	end_simu(t_philo **philo_array, int nbr_start_philo);
int		launch_simu(t_philo **philo_array, t_data *data);
int		run_simu(t_philo **philo_array, t_data *data);
void	*eat_sleep_think(void *arg);
int		use_forks(t_philo *philo, int take_forks);
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);

int init_and_launch_simu(t_data *data)
{
	t_philo **philo_array;

	philo_array = init_philo(data);
	if (philo_array == NULL)
		return (0);
	if (!launch_simu(philo_array, data))
		return (0);
	if (!run_simu(philo_array, data))
		return (0);
	free_all(philo_array, data);
	return (1);
}

t_philo **init_philo(t_data *data)
{
	t_philo **philo_array; 
	int i;

	philo_array = malloc(sizeof(t_philo *) * data->active_phil);
	if (philo_array == NULL)
		return (NULL);
	i = 0;
	while (i < data->active_phil)
	{	
		philo_array[i] = malloc(sizeof(t_philo));
		if (philo_array[i] == NULL)
			return (0); //free d'abord tous les philos -> fcts a faire
		philo_array[i]->id_philo = i + 1;
		philo_array[i]->last_meal = 0;
		philo_array[i]->data = data;	
		philo_array[i]->left_fork = &data->mutex[i];
		philo_array[i]->right_fork = &data->mutex[(i + 1) % (data->active_phil)];
		if (pthread_mutex_init(&philo_array[i]->data->mutex[i], NULL) != 0)
			return (0); //free d'abord tous les philos -> fcts a faire
		i++;
	}
	return (philo_array);
}

int launch_simu(t_philo **philo_array, t_data *data)
{
	int i;
	int nbr_start_phil;

	i = 0;
	nbr_start_phil = data->active_phil;
	while (i < nbr_start_phil)
	{
		if (pthread_create(&philo_array[i]->th, NULL, &eat_sleep_think, philo_array[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

void *eat_sleep_think(void *arg)
{
	t_philo *philo;
	int	eat_lft;
	int	eat_max;

	philo = (t_philo *)arg;	
	eat_lft = 0;
	eat_max = philo->data->amount_to_eat;
	if (philo->id_philo % 2 == 0 )
		smart_sleep(philo->data->time_to_die / 2, philo);
	while ((eat_lft < eat_max || eat_max == -1) && (philo->data->philo_alive))
	{
		print_actions(philo, 3);
		if (!eating(philo))
			return (arg);			
		if (!sleeping(philo))
			return (arg);
	}
	pthread_mutex_lock(&philo->data->mutex_active);
	philo->data->active_phil--;
	pthread_mutex_unlock(&philo->data->mutex_active);
	return (arg); //free dans la fonction de call 
}

int	use_forks(t_philo *philo, int take_forks)
{
	if (take_forks == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_actions(philo, 0);
		if (philo->right_fork == philo->left_fork)
		{	
			smart_sleep(philo->data->time_to_die, philo);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		pthread_mutex_lock(philo->left_fork);
		print_actions(philo, 0);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print_actions(philo, 5);
	}
	return (1); 
}

void end_simu(t_philo **philo_array, int nbr_start_philo)
{
	int i;
	i = 0;

	while (i < nbr_start_philo)
	{
		pthread_join(philo_array[i]->th, (void **) &philo_array[i]); //check la valeur de return !!
		i++;
	}
}

int	eating(t_philo *philo)
{
	if (!use_forks(philo, 1))
		return (0);
	philo->last_meal = get_time() - philo->data->start_t;
	print_actions(philo, 1);
	if (!smart_sleep(philo->data->time_to_eat, philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}	
	use_forks(philo, 0);	
	return (1);
}

int sleeping(t_philo *philo)
{
	print_actions(philo, 2);
	if (!smart_sleep(philo->data->time_to_sleep, philo))
		return (0);
	return (1);
}

int run_simu(t_philo **philo_array, t_data *data)
{
	int nbr_start_phil;

	nbr_start_phil = data->active_phil;
	while (1)
	{
		if (!(death_thread(data, nbr_start_phil)))
		{
			end_simu(philo_array, nbr_start_phil);
			break;
		}
		else if (!(run_thread(philo_array)))
		{
			end_simu(philo_array, nbr_start_phil);
			break;
		}		
	}
	return (1);
}
