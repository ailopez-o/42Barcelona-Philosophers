#include "../inc/defines.h"
#include <sys/time.h>

unsigned long	timestamp(void)
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

unsigned long	real_time(t_philo *philo)
{
	return (timestamp() - philo->start_time);
}


/*
void	philo_sleep(long long time)
{
	long long i;

	i = timestamp();
	while(1)
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}
*/