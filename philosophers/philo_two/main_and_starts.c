/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_and_starts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 13:06:06 by sglass            #+#    #+#             */
/*   Updated: 2021/03/31 18:17:01 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

int		main(int argc, char **argv)
{
	int				ret;
	t_philos		*philos;
	t_input_args	inp_args;
	t_all			*all;

	if (argc < 5 || argc > 6)
	{
		write(1, "wrong number of args\n", 21);
		return (1);
	}
	ret = take_options(argc, argv, &inp_args);
	if (ret == 1 || inp_args.times_must_eat == 0)
		return (1);
	inp_args.time_start = my_ms(&inp_args.current_time);
	if (!(philos = malloc(inp_args.num_of_philo * sizeof(t_philos))))
		return (1);
	if (!(all = malloc(inp_args.num_of_philo * sizeof(t_all))))
		return (1);
	ret = born_philos_and_tablos(philos, &inp_args, all);
	if (ret == 1)
		return (1);
	born_monitor_and_join_threads(all, &inp_args);
	cleaner(philos, all, &inp_args);
	return (0);
}

void	born_monitor_and_join_threads(t_all *all, t_input_args *inp_args)
{
	int i;

	i = 0;
	pthread_create(&inp_args->monitor, NULL, (void *)monic, all);
	while (i < inp_args->num_of_philo)
	{
		pthread_join(all[i].philos->philosopher, NULL);
		i++;
	}
	inp_args->flag_end = 1;
	pthread_join(inp_args->monitor, NULL);
}

int		born_philos_and_tablos(t_philos *philos, t_input_args *inp_args,
		t_all *all)
{
	int i;

	i = 0;
	if (born_semaphores(inp_args) == 1)
		return (1);
	while (i < inp_args->num_of_philo)
	{
		philos[i].number = i + 1;
		philos[i].flag_born = 0;
		philos[i].times2eat = 0;
		philos[i].eating = 0;
		all[i].inp_args = inp_args;
		all[i].philos = &philos[i];
		pthread_create(&philos[i].philosopher, NULL, (void *)philo_live,
		&all[i]);
		philos[i].hungy_time = my_ms(&inp_args->current_time);
		philos[i].flag_born = 1;
		i++;
		usleep(100);
	}
	return (0);
}

int		take_options(int argc, char **argv, t_input_args *inp_args)
{
	int i;

	i = 0;
	if (check_symbols(argc, argv) == 1)
		return (1);
	inp_args->num_of_philo = ft_atoi(argv[1]);
	if (inp_args->num_of_philo < 1 || inp_args->num_of_philo > 200)
		return (1);
	inp_args->t2d = ft_atoi(argv[2]);
	if (inp_args->t2d < 60)
		return (1);
	inp_args->t2eat = ft_atoi(argv[3]);
	if (inp_args->t2eat < 60)
		return (1);
	inp_args->t2sleep = ft_atoi(argv[4]);
	if (inp_args->t2sleep < 60)
		return (1);
	if (argc == 6)
		inp_args->times_must_eat = ft_atoi(argv[5]);
	else
		inp_args->times_must_eat = -1;
	return (0);
}

int		check_symbols(int argc, char **argv)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
