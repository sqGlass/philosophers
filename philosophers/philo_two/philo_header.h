/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 13:31:18 by sglass            #+#    #+#             */
/*   Updated: 2021/03/31 18:15:35 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_HEADER_H
# define PHILO_HEADER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct		s_input_args
{
	long long		time_start;
	int				num_of_philo;
	int				t2d;
	int				t2eat;
	int				t2sleep;
	int				times_must_eat;
	int				dead;
	int				flag_end;
	sem_t			*forks;
	sem_t			*f_write;
	sem_t			*count;
	pthread_t		monitor;
	struct timeval	current_time;
}					t_input_args;

typedef struct		s_philos
{
	int				number;
	int				flag_born;
	long long		hungy_time;
	int				times2eat;
	int				eating;
	pthread_t		philosopher;

}					t_philos;

typedef struct		s_all
{
	t_philos		*philos;
	t_input_args	*inp_args;
}					t_all;

int					main(int argc, char **argv);
void				cleaner(t_philos *philos, t_all *all,
					t_input_args *inp_args);
void				born_monitor_and_join_threads(t_all *all,
					t_input_args *inp_args);
int					born_philos_and_tablos(t_philos *philos, t_input_args
					*inp_args, t_all *all);
int					born_semaphores(t_input_args *inp_args);
void				*philo_live(t_all *all);
void				sleeping(t_all *all, struct timeval *current_time);
void				eating(t_all *all, struct timeval *current_time);
void				ne_printf(long long time, int phil_num,
					const char *message, t_all *all);
void				*monic(t_all *all);
int					check_countmeals(t_all *all);
void				died_flag(t_all *all, int ret, int i,
					struct timeval current_time);
int					take_options(int argc, char **argv, t_input_args *inp_args);
int					check_symbols(int argc, char **argv);
int					ft_isdigit(int c);
long long			my_ms(struct timeval *current_time);
int					ft_atoi(char *str);
void				ft_putnbr_fd(long long n);
size_t				ft_strlen(const char *str);

#endif
