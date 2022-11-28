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

void * philo_thread(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (!(philo->num_philo % 2))
		usleep(15000);
	while (!philo->data->dead)
	{
		// Cogemos los tenedores
		pthread_mutex_lock(philo->mutex_fork_left);
		status_print(philo, "has taken left fork", KMAG);
		pthread_mutex_lock(philo->mutex_fork_right);
		status_print(philo, "has taken right fork", KMAG);
		// Comemos 
		status_print(philo, "is eating", KGRN);
		// Guardamos el tiempo de la última comida
		philo->last_meal = timestamp();
		//printf ("LastMeal [%lli]\n", philo->last_meal);
		philo_sleep (philo->data->time_to_eat);
		// Soltamos los tenedores
		pthread_mutex_unlock(philo->mutex_fork_left);
		//status_print(philo->num_philo, &philo->data->print_mtx, "has release left fork", philo->data->start_time, KYEL);
		pthread_mutex_unlock(philo->mutex_fork_right);
		//status_print(philo->num_philo, &philo->data->print_mtx, "has release right fork", philo->data->start_time, KYEL);
		// Dormimos
		status_print(philo, "is sleeping", KCYN);
		philo_sleep (philo->data->time_to_sleep);
		// Despertamos y pensamos hasta encontrar tenedor
		status_print(philo, "is thinking", KWHT);
	}
	return NULL;
}

void * monitor (void *table_info)
{
	int i;
	unsigned int time;
	unsigned int diff;
	t_table	*table;

	table = (t_table *)table_info;
	// Checkea si hay algún philo que ha pasado el tiempo máximo desde la última comida
	while (1 && !table->data.dead)
	{
		i = -1;
		while (++i < table->num_philos)
		{
			time = real_time(table->philos[i].last_meal);
			if (time > table->philos[i].data->time_to_die)
			{
				status_print(&table->philos[i], "die", KRED);
				table->philos[i].data->dead = 1;
			}
		}
		usleep(100);
	}
	return NULL;
}

void	threads_join(t_table *table)
{
	int		i;
	
	i = -1; 
	while (++i < table->num_philos)
		pthread_join(table->philos[i].thread_id, NULL);
	pthread_join(table->monitor, NULL);
}

void	threads_start(t_table *table)
{
	int		i;

	table->data.start_time = timestamp();
	i = -1;
	while (++i < table->num_philos)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, philo_thread, &table->philos[i]))
			ft_error (ENOMEM, table);
		table->philos[i].last_meal = timestamp();
	}
}

void free_mutex(t_table *table)
{
	int i;

	i = -1;
	while (++i < table->num_philos)
	pthread_join(table->philos[i].thread_id, NULL);
	i = -1;
	while (++i < table->num_philos)
		pthread_mutex_destroy(&(table->forks[i]));
	pthread_mutex_destroy(&(table->data.print_mtx));
}
