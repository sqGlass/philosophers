/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 12:24:14 by sglass            #+#    #+#             */
/*   Updated: 2021/03/29 13:39:21 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void		cleaner(t_philos *philos, t_all *all, t_input_args *inp_args)
{
	sem_close(inp_args->forks);
	sem_close(inp_args->f_write);
	sem_close(inp_args->count);
	sem_unlink("forks");
	sem_unlink("ft_write");
	sem_unlink("count");
	free(all);
	free(philos);
}

void		ne_printf(long long time, int phil_num, const char *message,
			t_all *all)
{
	sem_wait(all->inp_args->f_write);
	if (all->inp_args->dead == 1)
	{
		sem_post(all->inp_args->f_write);
		return ;
	}
	ft_putnbr_fd(time);
	write(1, " ", 1);
	ft_putnbr_fd(phil_num);
	write(1, message, ft_strlen(message));
	sem_post(all->inp_args->f_write);
}

long long	my_ms(struct timeval *current_time)
{
	long long time_in_mill;

	gettimeofday(current_time, NULL);
	time_in_mill = (current_time->tv_sec) * 1000 +
	(current_time->tv_usec) / 1000;
	return (time_in_mill);
}
