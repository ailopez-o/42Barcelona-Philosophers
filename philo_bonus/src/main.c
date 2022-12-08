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
#include <fcntl.h>
#include "../inc/defines.h"
#include "../inc/utils.h"
#include "../inc/forking.h"

int	init_semaphores(t_table *table)
{
	sem_unlink("sem_print");
	sem_unlink("sem_fork");
	table->data.sem_print = sem_open("sem_print", O_CREAT | O_EXCL, 0644, 1);
	if (table->data.sem_print == NULL)
		return (ECANCELED);
	table->data.sem_fork = sem_open("sem_fork", \
		O_CREAT | O_EXCL, 0644, table->num_philos);
	if (table->data.sem_fork == NULL)
		return (ECANCELED);
	return (0);
}

int	init_philos(t_table *table)
{
	int		i;

	table->philos = malloc (sizeof(t_philo) * table->num_philos);
	if (table->philos == NULL)
		return (ENOMEM);
	i = -1;
	while (++i < table->num_philos)
	{
		table->philos[i].num_philo = i + 1;
		table->data.dead = 0;
		table->philos[i].num_eats = 0;
		table->philos[i].data = &table->data;
	}
	return (0);
}

int	free_resources(t_table *table)
{
	sem_close(table->data.sem_fork);
	sem_close(table->data.sem_print);
	free(table->philos);
	return (0);
}

int	init_resources(t_table *table)
{
	int	error;

	error = init_semaphores(table);
	if (error)
		return (error);
	error = init_philos(table);
	if (error)
		return (error);
	return (0);
}

int	main(int argv, char **argc)
{
	t_table	table;
	int		error;

	if (parsing_args(argv, argc, &table))
		return (ft_error (EINVAL));
	error = init_resources (&table);
	if (error)
		return (ft_error (error));
	error = start_routines(&table);
	if (error)
		return (ft_error (error));
	return (free_resources(&table));
}
