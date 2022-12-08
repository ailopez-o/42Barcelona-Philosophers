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
#include "../inc/utils.h"
#include "../inc/threading.h"

int	init_mutex(t_table *table)
{
	int	i;

	table->forks = malloc (sizeof(pthread_mutex_t) * table->num_philos);
	if (table->forks == NULL)
		return (ENOMEM);
	if (pthread_mutex_init(&table->data.print_mtx, NULL))
		return (ECANCELED);
	if (pthread_mutex_init(&table->data.start_mtx, NULL))
		return (ECANCELED);
	i = -1;
	while (++i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (ECANCELED);
	}
	return (0);
}

void	fork_asignament(t_philo *philo, pthread_mutex_t *forks, int num_philos)
{
	philo->mutex_fork_left = &forks[philo->num_philo - 1];
	if (philo->num_philo == 1)
		philo->mutex_fork_right = &forks[num_philos - 1];
	else
		philo->mutex_fork_right = &forks[philo->num_philo - 2];
	if (num_philos == 1)
		philo->mutex_fork_right = NULL;
}

int	init_threads(t_table *table)
{
	int	i;

	table->philos = malloc (sizeof(t_philo) * table->num_philos);
	if (table->philos == NULL)
		return (ENOMEM);
	i = -1;
	while (++i < table->num_philos)
	{
		table->philos[i].num_philo = i + 1;
		fork_asignament (&table->philos[i], table->forks, table->num_philos);
		table->data.dead = 0;
		table->philos[i].num_eats = 0;
		table->philos[i].data = &table->data;
	}
	if (threads_start(table))
		return (ECANCELED);
	if (pthread_create(&table->monitor, NULL, monitor, table))
		return (ECANCELED);
	return (0);
}

int	init_resources(t_table *table)
{
	int	error;

	error = init_mutex(table);
	if (error)
		return (error);
	error = init_threads(table);
	if (error)
		return (error);
	return (0);
}

int	main(int argv, char **argc)
{
	t_table			table;
	int				error;

	if (parsing_args(argv, argc, &table))
		return (ft_error (EINVAL));
	error = init_resources (&table);
	if (error)
		return (ft_error (error));
	threads_join (&table);
	return (free_mutex(&table));
}
