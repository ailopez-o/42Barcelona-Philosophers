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

void	threads_join(t_table *table)
{
	int		i;
	
	i = 0; 
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(table->monitor, NULL);
}

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

void	status_print(int	philo_id, pthread_mutex_t *print_mutex, char *str, long long first_timestamp, char *color)
{
	pthread_mutex_lock(print_mutex);
	printf("%s%u ms ▶ %s", KBLU, real_time(first_timestamp), DEF_COLOR);
	printf("👤 Philo [%03d] ", philo_id);
	printf("%s%s%s\n\n", color, str, DEF_COLOR);
	pthread_mutex_unlock(print_mutex);
}

void * philo_thread(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (!(philo->num_philo % 2))
		usleep(15000);
	while (!philo->data->dead)
	{
		// Cogemos los tenedores
		pthread_mutex_lock(philo->mutex_fork_left);
		status_print(philo->num_philo, &philo->data->print_mtx, "has taken left fork", philo->data->start_time, KMAG);
		pthread_mutex_lock(philo->mutex_fork_right);
		status_print(philo->num_philo, &philo->data->print_mtx, "has taken right fork", philo->data->start_time, KMAG);
		// Comemos 
		status_print(philo->num_philo, &philo->data->print_mtx, "is eating",philo->data->start_time, KGRN);
		// Guardamos el tiempo de la última comida
		philo->last_meal = timestamp();
		//printf ("LastMeal [%lli]\n", philo->last_meal);
		philo_sleep (philo->data->time_to_eat);	
		// Soltamos los tenedores
		pthread_mutex_unlock(philo->mutex_fork_left);	
		status_print(philo->num_philo, &philo->data->print_mtx, "has release left fork", philo->data->start_time, KYEL);
		pthread_mutex_unlock(philo->mutex_fork_right);
		status_print(philo->num_philo, &philo->data->print_mtx, "has release right fork", philo->data->start_time, KYEL);
		// Dormimos
		status_print(philo->num_philo, &philo->data->print_mtx, "is sleeping", philo->data->start_time, KCYN);
		philo_sleep (philo->data->time_to_sleep);	
		// Despertamos y pensamos hasta encontrar tenedor
		status_print(philo->num_philo, &philo->data->print_mtx, "is thinking", philo->data->start_time, KWHT);
	}
	return NULL;
}

void * monitor (void *table_info)
{
	int i;
	unsigned int time;
	unsigned int diff;
	t_table	*table;

	table = (t_table *)table_info;
	// Checkea si hay algún philo que ha pasado el tiempo máximo desde la última comida
	while (1 && !table->data.dead)
	{
		//printf ("Dead [%d]\n", table->data.dead);
		//printf ("Monitoring\n");
		i = 0;
		while (i < table->num_philos)
		{
			//printf ("Monitoring\n");
			time = real_time(table->philos[i].last_meal);
			//printf ("Time Since Last Meal [%d] - [%d]\n", time, table->philos[i].data->time_to_die);
			if (time > table->philos[i].data->time_to_die)
			{
				table->philos[i].data->dead = 1;
				printf ("Philo [%d] DIE\n", table->philos[i].num_philo);
			}
			i++;
		}
		usleep(100);
	}
	return NULL;
}

void	thread_start(t_table *table)
{
	int		i;

	// Inicializamos el clock
	table->data.start_time = timestamp();
	i = 0;
	while (i < table->num_philos)
	{
		// Creamos los hilos de cada philo
		if (pthread_create(&table->philos[i].thread_id, NULL, philo_thread, &table->philos[i]))
			ft_error (ENOMEM, table);
		// Asignamos el tiempo de le última comida
		table->philos[i].last_meal = timestamp();
		i++;
	}
}

void	init_threads_and_mutex(t_table *table)
{
	int		i;

	//	Alocamos memoria para los id de los threads
	if (!(table->philos = malloc (sizeof(t_philo) * table->num_philos)))
		ft_error (ENOMEM, table);
	//	Alocamos memoria para los forks
	if (!(table->forks = malloc (sizeof(pthread_mutex_t)* table->num_philos)))
		ft_error (ENOMEM, table);
	// Inicializamos el mutex del printf
	pthread_mutex_init(&table->data.print_mtx, NULL);
	// Creamos los mutex de los forks
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			ft_error (ENOMEM, table);
		i++;
	}
	i = 0;
	// Inicializamos los philosophos
	while (i < table->num_philos)
	{
		// Escribimos el numero de philo
		table->philos[i].num_philo = i + 1;
		// Asignamos los tenedores
		table->philos[i].mutex_fork_left = &table->forks[i];
		if (i == 0)
			table->philos[i].mutex_fork_right = &table->forks[table->num_philos - 1];
		else
			table->philos[i].mutex_fork_right = &table->forks[i - 1];
		table->data.dead = 0;
		// Asignamos los datos a cada philo
		table->philos[i].data = &table->data;
		i++;
	}
	thread_start(table);
	// Arrancamos el hilo monitor
	if (pthread_create(&table->monitor, NULL, monitor, table))
			ft_error (ENOMEM, table);	
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
	unsigned long	time;
	// Parseamos
	parsing_args(argv, argc, &table);
	// Inicializamos threads and mutex
	init_threads_and_mutex(&table);	
	// Esperamos a que terminen todos los hilos
	threads_join (&table);


/*
	while (1)
	{
		time = timestamp();
		philo_sleep (100);	
		time =  timestamp() - time;
		printf("Clock [%lu ms]\n", time);
	}
*/


	// Liberamos los mallocs
	free(table.philos);
	free(table.forks);		
	return(0);
}