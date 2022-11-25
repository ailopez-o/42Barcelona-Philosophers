/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:00:29 by ailopez-          #+#    #+#             */
/*   Updated: 2022/11/22 18:01:05 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/defines.h"
#include "../inc/utils.h"
#include "../lib/ft_printf/inc/ft_printf.h"

void ft_error(int error, t_table *table)
{
	if (error == INVALID_ARGS)
	{
		ft_putstr_fd("Invalid arguments\n", 0);
		exit (INVALID_ARGS);
	}
	if (error == ENOMEM)
	{
		ft_putstr_fd("Out of memory\n", 0);
		exit (ENOMEM);
	}
	free(table->philos);
	free(table->forks);
}

void	status_print(int	philo_id, pthread_mutex_t *print_mutex, char *str, long long first_timestamp)
{
	pthread_mutex_lock(print_mutex);
	printf("Time => [%lli] ", timestamp() - first_timestamp);
	printf("Philo [%i]:", philo_id + 1);
	printf("%s\n", str);
	pthread_mutex_unlock(print_mutex);
}

void * philo_thread(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	pthread_mutex_lock(philo->mutex_print);
	//ft_printf("PhiloNum [%d] created - Left Fork Id [%d] - Right Fork id [%d]\n", philo->num_philo + 1, philo->left_fork->num, philo->right_fork->num);
	pthread_mutex_unlock(philo->mutex_print);	
	sleep(1);
	// Cogemos el tenedor
	pthread_mutex_lock(&philo->left_fork->mutex);
	status_print(philo->num_philo, philo->mutex_print, "has taken left fork", timestamp());	
	pthread_mutex_lock(&philo->right_fork->mutex);
	status_print(philo->num_philo, philo->mutex_print, "has taken right fork", timestamp());	
	usleep(300);
	status_print(philo->num_philo, philo->mutex_print, "is eating", timestamp());	
	pthread_mutex_unlock(&philo->left_fork->mutex);
	status_print(philo->num_philo, philo->mutex_print, "has release left fork", timestamp());		
	pthread_mutex_unlock(&philo->right_fork->mutex);
	status_print(philo->num_philo, philo->mutex_print, "has release right fork", timestamp());	
	pthread_mutex_lock(philo->mutex_print);	
	ft_printf("PhiloNum [%d] finished\n", philo->num_philo + 1);
	pthread_mutex_unlock(philo->mutex_print);		
    return NULL;
}

void	init_threads_and_mutex(t_table *table)
{
	int		i;

	//	Alocamos memoria para los id de los threads
	if (!(table->philos = malloc (sizeof(t_philo) * table->num_philos)))
		ft_error (ENOMEM, table);
	//	Alocamos memoria para los forks
	if (!(table->forks = malloc (sizeof(t_fork)* table->num_philos)))
		ft_error (ENOMEM, table);
	// Inicializamos el mutex del printf
	pthread_mutex_init(&table->print_mtx, NULL);
	// Creamos los mutex de los forks
	i = 0;
	while (i < table->num_philos)
	{
		table->forks[i].num = i;
		if (pthread_mutex_init(&table->forks[i].mutex, NULL))
			ft_error (ENOMEM, table);
		i++;
	}
	/*
	i = 0;	
	while (i < table->num_philos)
	{
		ft_printf("Fork Id [%d]\n", table->forks[i].num);
		i++;
	}
	*/	
	// Creamos todos los hilos "pilosophers"
	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].num_philo = i;\
		table->philos[i].left_fork = &table->forks[i];
		if (table->philos[i].num_philo == 0)
			table->philos[i].right_fork = &table->forks[table->num_philos - 1];
		else
			table->philos[i].right_fork = &table->forks[i - 1];
		table->philos[i].mutex_print = &table->print_mtx;
		table->philos[i].start_time = table->start_time;
		if (pthread_create(&table->philos[i].thread_id, NULL, &philo_thread, &table->philos[i]))
			ft_error (ENOMEM, table);
		table->philos[i].last_meal = timestamp();
		i++;
	}
}

void	parsing_args(int argv, char **argc, t_table *table)
{
	if (argv < 5)
		ft_error(INVALID_ARGS, table);
	table->num_philos = ft_atoi(argc[1]);
	table->data.time_to_die = ft_atoi(argc[2]);
	table->data.time_to_eat = ft_atoi(argc[3]);
	table->data.time_to_sleep = ft_atoi(argc[4]);
	if (argv == 6)
		table->data.number_time_eats = ft_atoi(argc[5]);
	ft_printf("NumPhilos [%d]\n", table->num_philos);
	ft_printf("TimeToDie [%d]\n", table->data.time_to_die);
	ft_printf("TimeToEat [%d]\n", table->data.time_to_eat);
	ft_printf("TimeToSleep [%d]\n", table->data.time_to_sleep);	
	if (argv == 6)
		ft_printf("NumTimeEats [%d]\n", table->data.number_time_eats);
}

int main (int argv, char **argc)
{
	t_table	table;
	int		i;

	// Inicializamos el clock
	table.start_time = timestamp();
	// Parseamos
	parsing_args(argv, argc, &table);
	// Inicializamos thrrads and mutex
	init_threads_and_mutex(&table);
	// Esperamos a que terminen todos los hilos
	i = 0; 
	while (i < table.num_philos)
	{
		pthread_join(table.philos[i].thread_id, NULL);
		i++;
	}
	// Liberamos los mallocs
	free(table.philos);
	free(table.forks);		
	return(0);
}