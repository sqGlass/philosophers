/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_philos_and_count_meal.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:07:56 by sglass            #+#    #+#             */
/*   Updated: 2021/03/31 21:23:28 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	*count_meal(t_input_args *inp_args)
{
	int i;

	i = 0;
	while (i < inp_args->num_of_philo)
	{
		sem_wait(inp_args->ate);
		i++;
		if (i == inp_args->num_of_philo)
		{
			sem_wait(inp_args->f_write);
			sem_post(inp_args->bullet);
			return (NULL);
		}
	}
	return (NULL);
}

void	*exit_philo(t_all *all)
{
	sem_wait(all->inp_args->bullet);
	sem_post(all->inp_args->bullet);
	exit(0);
}
