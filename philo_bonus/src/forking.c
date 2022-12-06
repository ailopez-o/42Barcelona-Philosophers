/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:36:18 by ailopez-          #+#    #+#             */
/*   Updated: 2022/11/28 09:36:22 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/defines.h"
#include "../inc/utils.h"
int	philo_routine(t_philo *philo)
{
		//Tenedores

		//Comer

		//Dormir

		//Pensar


}

int	run_processes(t_table *table)
{
	int	i;

	table->pid = malloc(sizeof(pid_t) * table->num_philos);
	if (table->pid == NULL)
		return (ENOMEM);
	i = -1;	
	while (++i < table->num_philos)
	{
		table->pid[i] = fork();
		if (!table->pid[i])
		{
			// Estamos en el hijo, iniciamos la rutina del philo
			philo_routine(&table->philos[i]);
		}
		else
		{
			// Estamos en el padre
		}
	}
	return (0);
}


int	free_resources(t_table *table)
{
	free(table->philos);
	free(table->pid);	
	return (0);
}
