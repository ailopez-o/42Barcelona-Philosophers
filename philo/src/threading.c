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

void	philo_dead(t_philo *philo)
{		
	if (philo->data->dead)
		return ;
	philo->data->dead = 1;
	status_print(philo, "died 💀", KRED, 1);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_fork_left);
	status_print(philo, "has taken a fork", KMAG, 0);
	if (philo->mutex_fork_right)
		pthread_mutex_lock(philo->mutex_fork_right);
	else
		return (1);
	status_print(philo, "has taken a fork", KMAG, 0);
	status_print(philo, "is eating 🍕", KGRN, 0);
	philo->num_eats++;
	philo->last_meal = timestamp();
	philo_sleep (philo->data->time_to_eat, &philo->data->dead);
	pthread_mutex_unlock(philo->mutex_fork_left);
	pthread_mutex_unlock(philo->mutex_fork_right);
	return (0);
}

void	*philo_thread(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (!(philo->num_philo % 2))
		usleep(15000);
	pthread_mutex_lock(&philo->data->start_mtx);
	pthread_mutex_unlock(&philo->data->start_mtx);
	if (philo->data->time_to_die == 0)
	{
		philo_dead(philo);
		return (NULL);
	}	
	while (!philo->data->dead)
	{
		if (philo_eat(philo))
			return (NULL);
		status_print(philo, "is sleeping 💤", KCYN, 0);
		philo_sleep (philo->data->time_to_sleep, &philo->data->dead);
		status_print(philo, "is thinking 🗯", KWHT, 0);
		if (philo->data->number_time_eats >= 0 && \
		philo->num_eats >= philo->data->number_time_eats)
			philo->data->dead = 1;
	}
	return (NULL);
}

void	*monitor(void *table_info)
{
	int				i;
	int				time;
	t_table			*table;

	table = (t_table *)table_info;
	while (1 && !table->data.dead)
	{
		i = -1;
		while (++i < table->num_philos)
		{
			time = real_time(table->philos[i].last_meal);
			if (time > table->philos[i].data->time_to_die)
			{
				philo_dead(&table->philos[i]);
				return (NULL);
			}
		}
		usleep(100);
	}
	return (NULL);
}

int	threads_start(t_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&table->data.start_mtx);
	while (++i < table->num_philos)
	{
		if (pthread_create(&table->philos[i].thread_id, \
			NULL, philo_thread, &table->philos[i]))
			return (ECANCELED);
		table->philos[i].last_meal = timestamp();
	}
	table->data.start_time = timestamp();
	pthread_mutex_unlock(&table->data.start_mtx);
	return (0);
}
