/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   born_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:06:38 by sglass            #+#    #+#             */
/*   Updated: 2021/04/01 10:33:49 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	born_philos(t_philos *philos, t_input_args *inp_args, t_all *all)
{
	int i;

	i = 0;
	inp_args->pid = malloc(sizeof(pid_t) * inp_args->num_of_philo);
	while (i < inp_args->num_of_philo)
	{
		philos[i].number = i + 1;
		philos[i].times2eat = 0;
		philos[i].flag_born = 0;
		all[i].philos = &philos[i];
		all[i].inp_args = inp_args;
		inp_args->pid[i] = fork();
		if (inp_args->pid[i] < 0)
			exit(1);
		if (inp_args->pid[i] == 0)
		{
			philos[i].hungy_time = my_ms(&inp_args->current_time);
			philo_manager(&all[i]);
		}
		usleep(100);
		i++;
	}
	wait_all_and_clean(philos, all, inp_args);
}

void	philo_manager(t_all *all)
{
	pthread_create(&all->inp_args->doomsday, NULL, (void *)exit_philo, all);
	pthread_create(&all->inp_args->monitor, NULL, (void *)monic, all);
	philo_live(all);
}
