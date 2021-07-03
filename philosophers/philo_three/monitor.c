/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:02:35 by sglass            #+#    #+#             */
/*   Updated: 2021/03/31 21:05:00 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	*monic(t_all *all)
{
	struct timeval	current_time;
	int				i;
	int				ret;
	long long		curr;

	i = 0;
	ret = 0;
	while (1)
	{
		curr = my_ms(&current_time) - all->philos->hungy_time;
		if ((all->philos->flag_born == 1 && curr >= all->inp_args->t2d
		&& all->philos->eating == 0) || ret == 1)
		{
			sem_wait(all->inp_args->die_flag);
			died_flag(all, ret, all->philos->number, current_time);
			return (NULL);
		}
		usleep(10);
	}
}

void	died_flag(t_all *all, int ret, int i, struct timeval current_time)
{
	int f;

	f = 0;
	sem_wait(all->inp_args->f_write);
	if (ret != 1)
	{
		usleep(5);
		ne_printf2(my_ms(&current_time) -
		all->inp_args->time_start, i, " died\n", all);
	}
	sem_post(all->inp_args->bullet);
}
