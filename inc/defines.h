#ifndef DEFINES_H
# define DEFINES_H

# include <stdbool.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#define	INVALID_ARGS	22
#define	ENOMEM			12

typedef struct s_data{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_time_eats;
}	t_data;

typedef struct s_fork{
	int				num;
	pthread_mutex_t mutex;
}	t_fork;

typedef struct s_philo {
	int					num_philo;
	unsigned long		start_time;
	t_data				*data;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_mutex_t		*mutex_print;
	pthread_t			thread_id;
	long long			last_meal;
}	t_philo;

typedef struct s_table {
	unsigned long	start_time;
	t_data			data;
	pthread_mutex_t	print_mtx;
	int				num_philos;
	t_fork			*forks;
	t_philo			*philos;
}	t_table;






#endif