/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:57:01 by ailopez-          #+#    #+#             */
/*   Updated: 2022/12/08 14:57:03 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/defines.h"
#include "../inc/utils.h"

int	free_mutex(t_table *table)
{
	int	i;
	int	error;

	error = 0;
	i = -1;
	while (++i < table->num_philos)
		error += pthread_mutex_destroy(&(table->forks[i]));
	error += pthread_mutex_destroy(&(table->data.print_mtx));
	error += pthread_mutex_destroy(&(table->data.start_mtx));
	free(table->philos);
	free(table->forks);
	return (error);
}

int	threads_join(t_table *table)
{
	int		i;

	i = -1;
	while (++i < table->num_philos)
		pthread_join(table->philos[i].thread_id, NULL);
	pthread_join(table->monitor, NULL);
	return (0);
}

int	status_print(t_philo *philo, char *str, char *color, int print_death)
{
	if (pthread_mutex_lock(&philo->data->print_mtx))
		return (EDEADLK);
	if (!philo->data->dead || print_death)
	{
		if (printf("%s%04u ms ▶ %s 👤 Philo [%03d] %s%s%s\n", KBLU, \
			real_time(philo->data->start_time), DEF_COLOR, \
			philo->num_philo, color, str, DEF_COLOR) < 0)
			return (EIO);
	}
	if (pthread_mutex_unlock(&philo->data->print_mtx))
		return (EDEADLK);
	return (0);
}

void	philo_sleep(long long time, char *dead)
{
	long long	init_time;

	init_time = timestamp();
	while (!*dead)
	{
		if ((timestamp() - init_time) >= time)
			break ;
		usleep(300);
	}
}
