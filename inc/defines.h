#ifndef DEFINES_H
# define DEFINES_H

# include <stdbool.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#define	INVALID_ARGS	22
#define	ENOMEM			12

#define DEF_COLOR	"\033[0;39m"
#define GRAY		"\033[0;90m"
#define RED			"\033[0;91m"
#define GREEN		"\033[0;92m"
#define YELLOW		"\033[0;93m"
#define BLUE		"\033[0;94m"
#define MAGENTA		"\033[0;95m"
#define CYAN 		"\033[0;96m"
#define WHITE		"\033[0;97m"
#define KNRM		"\x1B[0m"
#define KRED		"\x1B[31m"
#define KGRN		"\x1B[32m"
#define KYEL		"\x1B[33m"
#define KBLU		"\x1B[34m"
#define KMAG		"\x1B[35m"
#define KCYN		"\x1B[36m"
#define KWHT		"\x1B[37m"


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