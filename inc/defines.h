#ifndef DEFINES_H
# define DEFINES_H

# include <stdbool.h>

#define	INVALID_ARGS	22

typedef struct s_philo {
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_time_eats;
}	t_philo;


#endif