#include "../inc/defines.h"
#include <sys/time.h>

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

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