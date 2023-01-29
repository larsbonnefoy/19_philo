/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_run_simu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:03:39 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/29 14:25:09 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_philo	**init_philo(t_data *data);
int		launch_simu(t_philo **philo_array, t_data *data);
int		run_simu(t_philo **philo_array, t_data *data);
void	end_simu(t_philo **philo_array, int nbr_start_philo);

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
		if (pthread_mutex_init(&philo_array[i]->mutex_last_meal, NULL) != 0)
			return (0); 
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

int run_simu(t_philo **philo_array, t_data *data)
{
	int nbr_start_phil;

	nbr_start_phil = data->active_phil;
	while (1)
	{
		if (finished_eating(data, nbr_start_phil))
		{
			end_simu(philo_array, nbr_start_phil);
			break;
		}
		if (!(run_thread(philo_array)))
		{
			end_simu(philo_array, nbr_start_phil);
			break;
		}		
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
