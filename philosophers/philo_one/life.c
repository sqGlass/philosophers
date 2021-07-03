/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:30:36 by sglass            #+#    #+#             */
/*   Updated: 2021/03/31 17:51:32 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	*philo_live(t_philos *philos)
{
	struct timeval		current_time;
	long long			now;

	while (philos->inp_args->dead != 1)
	{
		pthread_mutex_lock(&philos->forks[philos->left_fork]);
		now = my_ms1(&current_time, *philos->ms);
		ne_printf(now - philos->inp_args->time_start, philos->number,
		" has taken a fork\n", philos);
		pthread_mutex_lock(&philos->forks[philos->right_fork]);
		now = my_ms1(&current_time, *philos->ms);
		ne_printf(now - philos->inp_args->time_start, philos->number,
		" has taken a fork\n", philos);
		eating(philos, &current_time);
		pthread_mutex_unlock(&philos->forks[philos->left_fork]);
		pthread_mutex_unlock(&philos->forks[philos->right_fork]);
		philos->times2eat++;
		sleeping(philos, &current_time);
	}
	return (NULL);
}

void	sleeping(t_philos *philos, struct timeval *current_time)
{
	long long now;
	long long tmp;

	now = my_ms1(current_time, *philos->ms);
	ne_printf(now - philos->inp_args->time_start, philos->number,
	" is sleeping\n", philos);
	tmp = now + philos->t2sleep;
	while (now < tmp && philos->inp_args->dead != 1)
	{
		now = my_ms1(current_time, *philos->ms);
		usleep(100);
	}
	ne_printf(now - philos->inp_args->time_start, philos->number,
	" is thinking\n", philos);
}

void	eating(t_philos *philos, struct timeval *current_time)
{
	long long now;
	long long tmp;

	now = my_ms1(current_time, *philos->ms);
	ne_printf(now - philos->inp_args->time_start, philos->number,
	" is eating\n", philos);
	philos->is_eating = 1;
	philos->hungy_time = now;
	tmp = now + philos->t2eat;
	while (now < tmp && philos->inp_args->dead != 1)
	{
		now = my_ms1(current_time, *philos->ms);
		usleep(100);
	}
	philos->is_eating = 0;
}
