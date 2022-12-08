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
#ifndef FORKING_H
# define FORKING_H

# include "../inc/defines.h"

int		free_resources(t_table *table);
int		start_routines(t_table *table);
#endif
