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
#ifndef THREADING_H
# define THREADING_H

# include "../inc/defines.h"

int		free_mutex(t_table *table);
int		threads_start(t_table *table);
int		threads_join(t_table *table);
void	*monitor(void *table_info);
void	*philo_thread(void *philosopher);
#endif
