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

static int	write_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (write(2, str, len));
}

int	ft_error(int error)
{
	if (error == EINVAL)
		write_error("Invalid arguments\n");
	if (error == ENOMEM)
		write_error("Out of memory\n");
	return (error);
}

/*
	//printf("%s%u ms ▶ %s", KBLU, real_time(philo->data->start_time), \
	//	DEF_COLOR);
	//printf("👤 Philo [%03d] ", philo->num_philo);
	//printf("%s%s%s\n\n", color, str, DEF_COLOR);
*/

int	status_print(t_philo *philo, char *str, char *color, int print_death)
{
	if (pthread_mutex_lock(&philo->data->print_mtx))
		return (EDEADLK);
	if (!philo->data->dead || print_death)
	{
		if (printf("%s%04u%s  %03d %s%s%s\n", YELLOW, \
			real_time(philo->data->start_time), DEF_COLOR, \
			philo->num_philo, color, str, DEF_COLOR) < 0)
			return (EIO);
	}
	if (pthread_mutex_unlock(&philo->data->print_mtx))
		return (EDEADLK);
	return (0);
}
