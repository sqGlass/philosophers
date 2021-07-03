/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:08:31 by sglass            #+#    #+#             */
/*   Updated: 2021/03/31 21:10:50 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	*philo_live(t_all *all)
{
	struct timeval	current_time;
	long long		now;

	all->philos->flag_born = 1;
	while (1)
	{
		sem_wait(all->inp_args->forks);
		now = my_ms(&current_time);
		ne_printf(now - all->inp_args->time_start,
		all->philos->number, " has taken a fork\n", all);
		sem_wait(all->inp_args->forks);
		now = my_ms(&current_time);
		ne_printf(now - all->inp_args->time_start,
		all->philos->number, " has taken a fork\n", all);
		eating(all, &current_time);
		sem_post(all->inp_args->forks);
		sem_post(all->inp_args->forks);
		all->philos->times2eat++;
		if (all->inp_args->times_must_eat > 0 &&
		all->philos->times2eat == all->inp_args->times_must_eat)
			sem_post(all->inp_args->ate);
		sleeping(all, &current_time);
	}
	return (NULL);
}

void	eating(t_all *all, struct timeval *current_time)
{
	long long now;
	long long tmp;

	now = my_ms(current_time);
	ne_printf(now - all->inp_args->time_start,
	all->philos->number, " is eating\n", all);
	all->philos->eating = 1;
	all->philos->hungy_time = now;
	tmp = now + all->inp_args->t2eat;
	while (now < tmp)
	{
		now = my_ms(current_time);
		usleep(100);
	}
	all->philos->eating = 0;
}

void	sleeping(t_all *all, struct timeval *current_time)
{
	long long now;
	long long tmp;

	now = my_ms(current_time);
	ne_printf(now - all->inp_args->time_start,
	all->philos->number, " is sleeping\n", all);
	tmp = now + all->inp_args->t2sleep;
	while (now < tmp)
	{
		now = my_ms(current_time);
		usleep(100);
	}
	ne_printf(now - all->inp_args->time_start,
	all->philos->number, " is thinking\n", all);
}
