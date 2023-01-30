/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_run_simu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:09:10 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/30 17:09:12 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_philo	**init_philo(t_data *data);
int		launch_simu(t_philo **philo_array, t_data *data);
int		run_simu(t_philo **philo_array, t_data *data);
void	end_simu(t_philo **philo_array, int nbr_start_philo);

int	init_and_launch_simu(t_data *data)
{
	t_philo	**philo_array;

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

t_philo	**init_philo(t_data *data)
{
	t_philo	**philo_array;
	int		i;

	philo_array = malloc(sizeof(t_philo *) * data->nbr_phil);
	if (philo_array == NULL)
		return (NULL);
	i = 0;
	while (i < data->nbr_phil)
	{	
		philo_array[i] = malloc(sizeof(t_philo));
		if (philo_array[i] == NULL)
			return (0);
		philo_array[i]->id_philo = i + 1;
		philo_array[i]->last_meal = 0;
		philo_array[i]->times_eaten = 0;
		philo_array[i]->data = data;
		philo_array[i]->left_fork = &data->mutex[i];
		philo_array[i]->right_fork = &data->mutex[(i + 1) % (data->nbr_phil)];
		if (pthread_mutex_init(&philo_array[i]->data->mutex[i], NULL) != 0)
			return (0);
		if (pthread_mutex_init(&philo_array[i]->mutex_last_meal, NULL) != 0)
			return (0);
		i++;
	}
	return (philo_array);
}

int	launch_simu(t_philo **p_arr, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_phil)
	{
		if (pthread_create(&p_arr[i]->th, NULL, &routine, p_arr[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	run_simu(t_philo **philo_array, t_data *data)
{
	while (1)
	{
		if (!(run_thread(philo_array, data)))
		{
			end_simu(philo_array, data->nbr_phil);
			break ;
		}		
	}
	return (1);
}

void	end_simu(t_philo **philo_array, int nbr_start_philo)
{
	int	i;

	i = 0;
	while (i < nbr_start_philo)
	{
		pthread_join(philo_array[i]->th, (void **) &philo_array[i]);
		i++;
	}
}
