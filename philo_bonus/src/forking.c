/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:36:18 by ailopez-          #+#    #+#             */
/*   Updated: 2022/12/08 03:08:26 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/defines.h"
#include "../inc/utils.h"

void	*philo_death_supervisor(void *params)
{
	t_philo		*philo;
	long long	time;

	philo = (t_philo *)params;
	while (!philo->data->dead)
	{
		time = real_time(philo->last_meal);
		if (time > philo->data->time_to_die)
		{
			philo->data->dead = 1;
			status_print(philo, "died 💀", KRED, 1);
			exit (1);
		}
		usleep(500);
	}
	exit(0);
}

void	philo_eats(t_philo *philo)
{
	sem_wait(philo->data->sem_fork);
	status_print(philo, "has taken a fork", KMAG, 0);
	sem_wait(philo->data->sem_fork);
	status_print(philo, "has taken a fork", KMAG, 0);
	status_print(philo, "is eating 🍕", KGRN, 0);
	philo->last_meal = timestamp();
	philo_sleep(philo->data->time_to_eat);
	philo->num_eats++;
	sem_post(philo->data->sem_fork);
	sem_post(philo->data->sem_fork);
}

int	philo_routine(t_philo *philo)
{
	pthread_t	id_supervisor;

	pthread_create(&id_supervisor, NULL, philo_death_supervisor, philo);
	philo->last_meal = timestamp();
	while (!philo->data->dead)
	{
		philo_eats(philo);
		if (philo->data->number_time_eats >= 0 && \
			philo->num_eats >= philo->data->number_time_eats)
			exit (0);
		status_print(philo, "is sleeping 💤", KCYN, 0);
		philo_sleep(philo->data->time_to_sleep);
		status_print(philo, "is thinking 🗯", KWHT, 0);
	}
	pthread_join(id_supervisor, NULL);
	exit (0);
}

int	stop_routines(t_table *table)
{
	int	status;
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < table->num_philos)
				kill(table->philos[i].pid, SIGKILL);
			return (0);
		}
	}
	return (0);
}

int	start_routines(t_table *table)
{
	int	i;

	i = -1;
	table->data.start_time = timestamp();
	while (++i < table->num_philos)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid == 0)
			philo_routine(&table->philos[i]);
		else if (table->philos[i].pid < 0)
			return (1);
		usleep(100);
	}
	stop_routines (table);
	return (0);
}
