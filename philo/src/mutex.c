/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:25:10 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/12 14:54:19 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int mails = 0;

void *routine()
{
	int i;
	int *rtn;
	
	while (i < 10000000)
	{	
		i++;
		mails++;
	}
	return ((void *) rtn);
}

int main()
{
	pthread_t p1;
	pthread_t p2;
	if (pthread_create(&p1, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&p1, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_join(p1, NULL) != 0)
		return 1;
	if (pthread_join(p2, NULL) != 0)
		return 1;
	printf("%d\n", mails);
}
