/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 13:18:41 by sglass            #+#    #+#             */
/*   Updated: 2021/03/30 18:01:08 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int		born_semaphores(t_input_args *inp_args)
{
	sem_unlink("forks");
	sem_unlink("ft_write");
	sem_unlink("count");
	if ((inp_args->forks = sem_open("forks", O_CREAT, 0666,
	inp_args->num_of_philo)) == SEM_FAILED)
		return (1);
	if ((inp_args->f_write = sem_open("ft_write", O_CREAT, 0666, 1))
	== SEM_FAILED)
		return (1);
	if ((inp_args->count = sem_open("count", O_CREAT, 0666, 1)) == SEM_FAILED)
		return (1);
	return (0);
}
