/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:59:45 by sglass            #+#    #+#             */
/*   Updated: 2021/04/01 10:34:16 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void		cleaner(t_all *all, t_input_args *inp_args, t_philos *philos)
{
	sem_close(inp_args->bullet);
	sem_close(inp_args->f_write);
	sem_close(inp_args->forks);
	sem_close(inp_args->count);
	sem_close(inp_args->die_flag);
	sem_close(inp_args->ate);
	sem_unlink("forks");
	sem_unlink("ft_write");
	sem_unlink("count");
	sem_unlink("die_flag");
	sem_unlink("bullet");
	sem_unlink("ate");
	free(all);
	free(philos);
}

void		ne_printf(long long time, int phil_num,
			const char *message, t_all *all)
{
	sem_wait(all->inp_args->f_write);
	ft_putnbr_fd(time);
	write(1, " ", 1);
	ft_putnbr_fd(phil_num);
	write(1, message, ft_strlen(message));
	sem_post(all->inp_args->f_write);
}

void		ne_printf2(long long time, int phil_num,
const char *message, t_all *all)
{
	sem_wait(all->inp_args->count);
	ft_putnbr_fd(time);
	write(1, " ", 1);
	ft_putnbr_fd(phil_num);
	write(1, message, ft_strlen(message));
}

long long	my_ms(struct timeval *current_time)
{
	long long	time_in_mill;

	gettimeofday(current_time, NULL);
	time_in_mill = (current_time->tv_sec)
		* 1000 + (current_time->tv_usec) / 1000;
	return (time_in_mill);
}

void		wait_all_and_clean(t_philos *philos,
			t_all *all, t_input_args *inp_args)
{
	int i;

	i = 0;
	while (i < inp_args->num_of_philo)
	{
		waitpid(inp_args->pid[i], NULL, 0);
		i++;
	}
	cleaner(all, inp_args, philos);
}
