/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:59:28 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/01/31 10:24:25 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_create_out(int i, const char *str);

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi_positive(char *str)
{
	int	sign;
	int	base;
	int	i;

	i = 0;
	base = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{	
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (sign < 0)
		return (-1);
	if (ft_isdigit(str[i]) == 1)
	{	
		base = ft_create_out(i, str);
		return (base);
	}		
	else
		return (-1);
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]) == 1)
		i++;
	if (str[i] == '\0')
		return (0);
	else
		return (-1);
}

static int	ft_create_out(int i, const char *str)
{
	long int	out;

	out = 0;
	while (ft_isdigit(str[i]) == 1)
	{
		out = (out * 10) + (str[i] - 48);
		if (out > INT_MAX)
			return (-1);
		i++;
	}
	return ((int)out);
}
