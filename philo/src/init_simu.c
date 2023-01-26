/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:40:32 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/25 18:59:04 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**init_philo(t_data *data);
int		launch_simu(t_philo **philo_array);
void	*eat_sleep_think(void *arg);
int		use_forks(t_philo *philo, int take_forks);

int init_and_launch_simu(t_data *data)
{
	t_philo **philo_array;

	philo_array = init_philo(data);
	if (philo_array == NULL)
		return (0);
	if (launch_simu(philo_array) == 0)
		return (0);
	free_all(philo_array, data);
	printf("main thread end\n");
	return (1);
}

t_philo **init_philo(t_data *data)
{
	t_philo **philo_array; 
	int i;

	philo_array = malloc(sizeof(t_philo *) * data->nbr_philo);
	if (philo_array == NULL)
		return (NULL);
	i = 0;
	while (i < data->nbr_philo)
	{	
		philo_array[i] = malloc(sizeof(t_philo));
		if (philo_array[i] == NULL)
			return (0); //free d'abord tous les philos -> fcts a faire
		philo_array[i]->id_philo = i + 1;
		philo_array[i]->last_meal = 0;
		philo_array[i]->data = data;	
		philo_array[i]->left_fork = &data->mutex[i];
		philo_array[i]->right_fork = &data->mutex[(i + 1) % (data->nbr_philo)];
		if (pthread_mutex_init(&philo_array[i]->data->mutex[i], NULL) != 0)
			return (0); //free d'abord tous les philos -> fcts a faire
		i++;
	}
	return (philo_array);
}

int launch_simu(t_philo **philo_array)
{
	int i;
	int nbr_philo;

	i = 0;
	nbr_philo = philo_array[0]->data->nbr_philo;
	while (i < nbr_philo)
	{
		if (pthread_create(&philo_array[i]->th, NULL, &eat_sleep_think, philo_array[i]) != 0)
			return (0);
		i++;
	}
	while (1)
	{
		if (!(run_thread(philo_array)))
		{
			i = 0;
			while (i < nbr_philo)
			{
				printf("FAUT QUITTER SVP\n");
				pthread_join(philo_array[i]->th, (void **) &philo_array[i]); //check la valeur de return !!
				printf("Thread of philo %d end\n", philo_array[i]->id_philo);	
				pthread_mutex_destroy(&philo_array[i]->data->mutex[i]);
				i++;
			}
			break;
		}		
	}
	return (1);
}

void *eat_sleep_think(void *arg)
{
	t_philo *philo;
	int	amount_eat;

	philo = (t_philo *)arg;	
	amount_eat = philo->data->amount_to_eat;
	if (philo->id_philo % 2 == 0 )
		smart_sleep(philo->data->time_to_die / 2, philo);
	while (amount_eat != 0 && philo->data->philo_alive)	
	{
		print_actions(philo, 3);
		use_forks(philo, 1);
		amount_eat -=1;
		philo->last_meal = get_time() - philo->data->start_t;
		print_actions(philo, 1);
		if (!smart_sleep(philo->data->time_to_eat, philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			return (arg);
		}	
		use_forks(philo, 0);			
		print_actions(philo, 2);
		if (!smart_sleep(philo->data->time_to_sleep, philo))
			return (arg);
	}
	return (arg); //free dans la fonction de call ou ici ?
}

//check return value des mutex !!!
int	use_forks(t_philo *philo, int take_forks)
{
	if (take_forks == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_actions(philo, 0);
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
