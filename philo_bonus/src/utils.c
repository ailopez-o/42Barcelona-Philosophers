/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:36:34 by ailopez-          #+#    #+#             */
/*   Updated: 2022/11/28 09:36:37 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/defines.h"
#include <sys/time.h>

long long	timestamp(void)
{
	struct timeval	time;
	unsigned long	l;
	unsigned long	s;
	unsigned long	u;

	gettimeofday(&time, NULL);
	s = (time.tv_sec * 1000);
	u = (time.tv_usec / 1000);
	l = s + u;
	return (l);
}

unsigned int	real_time(long long time)
{
	long long	now;

	now = timestamp();
	return ((unsigned int)(now - time));
}

void	philo_sleep(long long time)
{
	long long	init_time;

	init_time = timestamp();
	while (1)
	{
		if ((timestamp() - init_time) >= time)
			break ;
		usleep(50);
	}
}

void	ft_error(int error, t_table *table)
{
	if (error == INVALID_ARGS)
	{
		printf("Invalid arguments\n");
		exit (INVALID_ARGS);
	}
	if (error == ENOMEM)
	{
		printf("Out of memory\n");
		exit (ENOMEM);
	}
	free(table->philos);
	free(table->forks);
}

void	status_print(t_philo *philo, char *str, char *color)
{
	if (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->data->print_mtx);
		//printf("%u ", real_time(first_timestamp));
		//printf("%d ", philo_id);
		//printf("%s\n",str);
		printf("%s%u ms ▶ %s", KBLU, real_time(philo->data->start_time), \
			DEF_COLOR);
		printf("👤 Philo [%03d] ", philo->num_philo);
		printf("%s%s%s\n\n", color, str, DEF_COLOR);
		pthread_mutex_unlock(&philo->data->print_mtx);
	}
}
