/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 13:00:40 by sglass            #+#    #+#             */
/*   Updated: 2021/04/01 10:33:18 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	died_flag(t_all *all, int ret, int i, struct timeval current_time)
{
	all[0].inp_args->dead = 1;
	if (ret != 1)
	{
		usleep(5);
		printf("%lld %d is died\n", my_ms(&current_time) -
		all[0].inp_args->time_start, i + 1);
	}
}

int		check_countmeals(t_all *all)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (all[0].inp_args->times_must_eat > 0)
		while (i < all[0].inp_args->num_of_philo)
		{
			if (all[i].philos->times2eat >= all[0].inp_args->times_must_eat)
				j++;
			if (j == all[0].inp_args->num_of_philo)
				return (1);
			i++;
		}
	return (0);
}

void	*monic(t_all *all)
{
	struct timeval	current_time;
	int				i;
	int				ret;
	long long		curr;

	i = 0;
	while (1)
	{
		while (i < all[0].inp_args->num_of_philo)
		{
			curr = my_ms(&current_time) - all[i].philos->hungy_time;
			ret = check_countmeals(all);
			if ((all[i].philos->flag_born == 1 && curr >= all[0].inp_args->t2d
			&& all[i].philos->eating == 0)
			|| ret == 1)
			{
				died_flag(all, ret, i, current_time);
				return (NULL);
			}
			i++;
		}
		usleep(10);
		i = 0;
	}
}
