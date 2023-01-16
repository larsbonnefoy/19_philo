#include "philo.h"

void print_struct(t_data *data)
{
	printf("nbr_philo	= %d\n", data->nbr_philo);
	printf("time_to_die	= %d\n", data->time_to_die);
	printf("time_to_eat	= %d\n", data->time_to_eat);
	printf("time_to_sleep	= %d\n", data->time_to_sleep);
	printf("amount_to_eat	= %d\n", data->amount_to_eat);
}

void *routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	sleep(2);
	return ((void *) arg); //free dans la fonction de call ou ici ?
}


