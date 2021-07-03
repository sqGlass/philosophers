/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:48:59 by sglass            #+#    #+#             */
/*   Updated: 2021/03/31 21:13:39 by sglass           ###   ########.fr       */
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
# include <signal.h>

typedef struct		s_input_args
{
	long long		time_start;
	int				num_of_philo;
	int				t2d;
	int				t2eat;
	int				t2sleep;
	int				times_must_eat;
	int				flag_end;
	sem_t			*forks;
	sem_t			*f_write;
	sem_t			*count;
	sem_t			*die_flag;
	sem_t			*bullet;
	sem_t			*ate;
	pid_t			*pid;
	pthread_t		monitor;
	pthread_t		doomsday;
	pthread_t		countmeal;
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
void				*count_meal(t_input_args *inp_args);
int					born_semaphores(t_input_args *inp_args);
void				born_philos(t_philos *philos,
					t_input_args *inp_args, t_all *all);
void				wait_all_and_clean(t_philos *philos,
					t_all *all, t_input_args *inp_args);
void				cleaner(t_all *all, t_input_args *inp_args,
					t_philos *philos);
void				philo_manager(t_all *all);
void				*exit_philo(t_all *all);
void				*monic(t_all *all);
void				died_flag(t_all *all, int ret,
					int i, struct timeval current_time);
void				*philo_live(t_all *all);
void				sleeping(t_all *all, struct timeval *current_time);
void				eating(t_all *all, struct timeval *current_time);
void				ne_printf2(long long time, int phil_num,
					const char *message, t_all *all);
void				ne_printf(long long time, int phil_num,
					const char *message, t_all *all);
int					take_options(int argc, char **argv, t_input_args *inp_args);
int					check_symbols(int argc, char **argv);
int					ft_isdigit(int c);
long long			my_ms(struct timeval *current_time);
int					ft_atoi(char *str);
void				ft_putnbr_fd(long long n);
size_t				ft_strlen(const char *str);

#endif
