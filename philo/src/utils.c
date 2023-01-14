
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
	sleep(2);
	printf("Thread %d beg\n", *(int *)arg);	
	return ((void *) arg);
}

int init_simu(t_data *data)
{
	pthread_t th[data->nbr_philo];
	pthread_mutex_t mutex[data->nbr_philo];
	int i;
	int *a;

	pthread_mutex_init(mutex, NULL);

	i = 0;
	while (i < data->nbr_philo)
	{
		a = malloc(sizeof(int));
		if (a == NULL)
			return -1;
		*a = i;	
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			return -1;
		if (data->amount_to_eat == -1)
		{
			if (pthread_detach(th[i]) != 0)
				return -1;
		}
		i++;
	}
	//si amount_to_eat == -1, detach les threads et continuer la simu a l'infini
	//sinon, il faut que chaque thread fasse  amount_to_eat pour join ensuite e finir la simu
	if (data->amount_to_eat != -1)
	{
		i = 0;
		while (i < data->nbr_philo)
		{
			if (pthread_join(th[i], NULL))
				return -1;
			printf("Thread %d end\n", i);	
			i++;
		}
	}
	free(a);
	pthread_mutex_destroy(mutex);
	printf("main thread end\n");
	pthread_exit(0);
	return (0);
}
