/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:16:32 by sglass            #+#    #+#             */
/*   Updated: 2021/03/31 21:14:30 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

long long	my_ms1(struct timeval *current_time, pthread_mutex_t ms)
{
	long long time_in_mill;

	(void)ms;
	gettimeofday(current_time, NULL);
	time_in_mill = (current_time->tv_sec) * 1000 +
	(current_time->tv_usec) / 1000;
	return (time_in_mill);
}

long long	my_ms2(struct timeval *current_time)
{
	long long time_in_mill;

	gettimeofday(current_time, NULL);
	time_in_mill = (current_time->tv_sec) * 1000 +
	(current_time->tv_usec) / 1000;
	return (time_in_mill);
}

void		ne_printf(long long time, int phil_num, const char *message,
		t_philos *philos)
{
	pthread_mutex_lock(philos->f_write);
	if (philos->inp_args->dead == 1)
	{
		pthread_mutex_unlock(philos->f_write);
		return ;
	}
	ft_putnbr_fd(time);
	write(1, " ", 1);
	ft_putnbr_fd(phil_num);
	write(1, message, ft_strlen(message));
	pthread_mutex_unlock(philos->f_write);
}

void		cleaner(t_input_args *inp_args, t_philos *philos)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&inp_args->f_write);
	pthread_mutex_destroy(&inp_args->ms);
	while (i < inp_args->num_of_philo)
	{
		pthread_mutex_destroy(&inp_args->forks[i]);
		i++;
	}
	free(philos);
}
