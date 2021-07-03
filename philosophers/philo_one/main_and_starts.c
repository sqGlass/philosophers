/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_and_starts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:11:09 by sglass            #+#    #+#             */
/*   Updated: 2021/04/01 10:32:29 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

void	born_tablos(t_input_args *inp_args)
{
	int i;

	i = 0;
	inp_args->forks = malloc(inp_args->num_of_philo * sizeof(pthread_mutex_t));
	while (i < inp_args->num_of_philo)
	{
		pthread_mutex_init(&inp_args->forks[i], NULL);
		i++;
	}
}

void	born_monitor(t_philos *philos, t_input_args *inp_args,
		pthread_t monitor)
{
	int ret;

	ret = 0;
	pthread_create(&monitor, NULL, (void *)monic, philos);
	while (ret < inp_args->num_of_philo)
	{
		pthread_join(philos[ret].philosopher, NULL);
		ret++;
	}
	philos[0].inp_args->flag_end = 1;
	pthread_join(monitor, NULL);
}

int		main(int argc, char **argv)
{
	int				ret;
	t_philos		*philos;
	t_input_args	inp_args;
	pthread_t		monitor;

	monitor = NULL;
	if (argc < 5 || argc > 6)
	{
		write(1, "wrong number of args\n", 21);
		return (1);
	}
	ret = take_options(argc, argv, &inp_args);
	if (ret == 1 || inp_args.times_must_eat == 0)
		return (1);
	inp_args.time_start = my_ms2(&inp_args.current_time);
	philos = malloc(inp_args.num_of_philo * sizeof(t_philos));
	if (philos == NULL)
		return (1);
	born_tablos(&inp_args);
	born_philos(philos, &inp_args);
	born_monitor(philos, &inp_args, monitor);
	cleaner(&inp_args, philos);
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
	pthread_mutex_init(&inp_args->ms, NULL);
	pthread_mutex_init(&inp_args->f_write, NULL);
	pthread_mutex_init(&inp_args->count, NULL);
	return (0);
}
