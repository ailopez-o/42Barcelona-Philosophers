/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:37:18 by ailopez-          #+#    #+#             */
/*   Updated: 2022/11/28 09:37:29 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef UTILS_H
# define UTILS_H

# include "../inc/defines.h"

unsigned int	real_time(long long time);
void			philo_sleep(long long time);
long long		timestamp(void);
void			ft_error(int error, t_table *table);
int			    status_print(t_philo *philo, char *str, char *color);
int	            ft_atoi(const char *str);
#endif
