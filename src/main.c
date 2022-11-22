/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:00:29 by ailopez-          #+#    #+#             */
/*   Updated: 2022/11/22 18:01:05 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/defines.h"
#include "../lib/ft_printf/inc/ft_printf.h"

void ft_error(int error)
{
	if (error == INVALID_ARGS)
	{
		ft_putstr_fd("Invalid arguments\n", 0);
		exit (INVALID_ARGS);
	}
}


int main (int argv, char **argc)
{
	t_philo	philo;

	if (argv < 5)
		ft_error(INVALID_ARGS);
	philo.num_philos = ft_atoi(argc[1]);
	philo.time_to_die = ft_atoi(argc[2]);
	philo.time_to_eat = ft_atoi(argc[3]);
	philo.time_to_sleep = ft_atoi(argc[4]);
	if (argv == 6)
		philo.number_time_eats = ft_atoi(argc[5]);


	ft_printf("NumPhilos [%d]\n", philo.num_philos);
	ft_printf("TimeToDie [%d]\n", philo.time_to_die);
	ft_printf("TimeToEat [%d]\n", philo.num_philos);
	ft_printf("TimeToSleep [%d]\n", philo.time_to_sleep);	
	if (argv == 6)
		ft_printf("NumTimeEats [%d]\n", philo.number_time_eats);
	return(0);
}
