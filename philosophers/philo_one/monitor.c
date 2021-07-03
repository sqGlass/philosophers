/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:27:19 by sglass            #+#    #+#             */
/*   Updated: 2021/04/01 10:32:04 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	*monic(t_philos *philos)
{
	struct timeval	current_time;
	int				i;
	int				ret;
	long long		curr;

	i = 0;
	while (1)
	{
		while (i < philos[0].inp_args->num_of_philo)
		{
			curr = my_ms1(&current_time, *philos[i].ms) - philos[i].hungy_time;
			ret = check_countmeals(philos);
			if ((philos[i].flag_born == 1 && curr >= philos[i].t2die
			&& philos[i].is_eating == 0) || ret == 1)
			{
				died_flag(philos, ret, i, current_time);
				return (NULL);
			}
			i++;
		}
		usleep(10);
		i = 0;
	}
}

void	died_flag(t_philos *philos, int ret, int i, struct timeval current_time)
{
	philos[i].inp_args->dead = 1;
	if (ret != 1)
	{
		philos[i].inp_args->dead = 1;
		usleep(5);
		printf("%lld %d is died\n", my_ms1(&current_time, *philos[i].ms) -
		philos->inp_args->time_start, i + 1);
		unlock_forks(philos);
	}
}

void	unlock_forks(t_philos *philos)
{
	int i;

	i = 0;
	while (i < philos[0].num_of_philo)
	{
		pthread_mutex_unlock(&philos[0].inp_args->forks[i]);
		i++;
	}
}

int		check_countmeals(t_philos *philos)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (philos[0].times_must_eat > 0)
		while (i < philos[0].inp_args->num_of_philo)
		{
			if (philos[i].times2eat >= philos[i].times_must_eat)
				j++;
			if (j == philos[i].inp_args->num_of_philo)
				return (1);
			i++;
		}
	return (0);
}
