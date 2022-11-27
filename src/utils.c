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
	//printf("TimeStamp [%lu] seg - [%d]useg\n", s, time.tv_usec);
	return (l);
}

unsigned int real_time(long long time)
{
	long long	now;

	now = timestamp();
	return ((unsigned int)(now - time));
}

void	philo_sleep(long long time)
{
	long long init_time;

	init_time = timestamp();
	while(1)
	{
		if ((timestamp() - init_time) >= time)
			break ;
		usleep(50);
	}
}
