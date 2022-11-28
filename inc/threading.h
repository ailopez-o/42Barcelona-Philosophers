/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:37:08 by ailopez-          #+#    #+#             */
/*   Updated: 2022/11/28 09:37:11 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/defines.h"
void	free_mutex(t_table *table);
void	threads_start(t_table *table);
void	threads_join(t_table *table);
void *	monitor (void *table_info);
void *	philo_thread(void *philosopher);
