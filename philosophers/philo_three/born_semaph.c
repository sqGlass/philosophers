/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   born_semaph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:04:38 by sglass            #+#    #+#             */
/*   Updated: 2021/03/31 21:05:43 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int		born_semaphores(t_input_args *inp_args)
{
	sem_unlink("forks");
	sem_unlink("ft_write");
	sem_unlink("count");
	sem_unlink("die_flag");
	sem_unlink("bullet");
	sem_unlink("ate");
	if ((inp_args->forks = sem_open("forks", O_CREAT, 0666,
	inp_args->num_of_philo)) == SEM_FAILED)
		return (1);
	if ((inp_args->f_write = sem_open("ft_write", O_CREAT,
	0666, 1)) == SEM_FAILED)
		return (1);
	if ((inp_args->count = sem_open("count", O_CREAT, 0666, 1)) == SEM_FAILED)
		return (1);
	if ((inp_args->die_flag = sem_open("die_flag", O_CREAT,
	0666, 1)) == SEM_FAILED)
		return (1);
	if ((inp_args->bullet = sem_open("bullet", O_CREAT, 0666, 0)) == SEM_FAILED)
		return (1);
	if ((inp_args->ate = sem_open("ate", O_CREAT, 0666, 0)) == SEM_FAILED)
		return (1);
	return (0);
}
