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
		usleep(600);
	}
}

int	status_print(t_philo *philo, char *str, char *color, int lock)
{
	if (sem_wait(philo->data->sem_print))
		return (ECANCELED);
	if (printf("%s%04u ms ▶ %s 👤 Philo [%03d] %s%s%s\n", KBLU, \
			real_time(philo->data->start_time), DEF_COLOR, \
			philo->num_philo, color, str, DEF_COLOR) < 0)
		return (EIO);
	if (lock == 1)
		return (0);
	if (sem_post(philo->data->sem_print))
		return (ECANCELED);
	return (0);
}
