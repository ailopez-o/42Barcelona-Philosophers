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

void	init_mutex(t_table *table)
{
	int		i;

	table->forks = malloc (sizeof(pthread_mutex_t) * table->num_philos);
	if (table->forks == NULL)
		ft_error (ENOMEM, table);
	pthread_mutex_init(&table->data.print_mtx, NULL);
	i = -1;
	while (++i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			ft_error (ENOMEM, table);
	}
}

void	init_threads(t_table *table)
{
	int		i;

	table->philos = malloc (sizeof(t_philo) * table->num_philos);
	if (table->philos == NULL)
		ft_error (ENOMEM, table);
	i = -1;
	while (++i < table->num_philos)
	{
		table->philos[i].num_philo = i + 1;
		table->philos[i].mutex_fork_left = &table->forks[i];
		if (i == 0)
			table->philos[i].mutex_fork_right = \
			&table->forks[table->num_philos - 1];
		else
			table->philos[i].mutex_fork_right = &table->forks[i - 1];
		table->data.dead = 0;
		table->philos[i].num_eats = 0;
		table->philos[i].data = &table->data;
	}
	threads_start(table);
	if (pthread_create(&table->monitor, NULL, monitor, table))
		ft_error (ENOMEM, table);
}

void	parsing_args(int argv, char **argc, t_table *table)
{
	if (argv < 5)
		ft_error(INVALID_ARGS, table);
	table->num_philos = ft_atoi(argc[1]);
	table->data.time_to_die = ft_atoi(argc[2]);
	table->data.time_to_eat = ft_atoi(argc[3]);
	table->data.time_to_sleep = ft_atoi(argc[4]);
	table->data.number_time_eats = 0;
	if (argv == 6)
		table->data.number_time_eats = ft_atoi(argc[5]);
	if (table->num_philos < 2)
		ft_error(INVALID_ARGS, table);
	if (table->data.time_to_die < 0 || table->data.time_to_eat < 0 || \
		table->data.time_to_sleep < 0)
		ft_error(INVALID_ARGS, table);
}

int	main(int argv, char **argc)
{
	t_table			table;
	unsigned long	time;

	parsing_args(argv, argc, &table);
	init_mutex(&table);
	init_threads(&table);
	threads_join (&table);
	free_mutex(&table);
	free(table.philos);
	free(table.forks);
	return (0);
}
