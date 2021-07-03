/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   born_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:21:59 by sglass            #+#    #+#             */
/*   Updated: 2021/03/31 17:50:57 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	born_philos(t_philos *philos, t_input_args *inp_args)
{
	int i;

	i = -1;
	while (++i < inp_args->num_of_philo)
	{
		philos[i].flag_born = 0;
		philos[i].all_philo = inp_args->num_of_philo;
		philos[i].time_start = inp_args->time_start;
		philos[i].t2die = inp_args->t2d;
		philos[i].hungy_time = 0;
		philos[i].times2eat = 0;
		philos[i].time_start = 0;
		philos[i].inp_args = inp_args;
		philos[i].num_of_philo = inp_args->num_of_philo;
		philos[i].t2eat = inp_args->t2eat;
		philos[i].t2sleep = inp_args->t2sleep;
		philos[i].times_must_eat = inp_args->times_must_eat;
		philos[i].dead = 0;
		philos[i].flag_end = 0;
		philos[i].forks = inp_args->forks;
		philos[i].ms = &inp_args->ms;
		philos[i].f_write = &inp_args->f_write;
		philos[i].is_eating = 0;
	}
	give_nums_and_forks(philos, inp_args);
}

void	give_nums_and_forks(t_philos *philos, t_input_args *inp_args)
{
	int i;

	i = 0;
	while (i < inp_args->num_of_philo)
	{
		if (inp_args->num_of_philo == 1)
		{
			philos[0].number = 1;
			philos[0].left_fork = 0;
		}
		else if (i != inp_args->num_of_philo - 1)
		{
			philos[i].number = i + 1;
			philos[i].left_fork = i;
			philos[i].right_fork = i + 1;
		}
		else
		{
			philos[i].number = i + 1;
			philos[i].left_fork = i;
			philos[i].right_fork = 0;
		}
		start_live(philos, i);
		i++;
	}
}

void	start_live(t_philos *philos, int i)
{
	philos[i].hungy_time = my_ms1(&philos[i].inp_args->current_time,
	*philos->ms);
	philos[i].flag_born = 1;
	pthread_create(&philos[i].philosopher, NULL, (void *)philo_live,
	&philos[i]);
	usleep(100);
}
