/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:34:16 by sglass            #+#    #+#             */
/*   Updated: 2021/03/31 21:13:32 by sglass           ###   ########.fr       */
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

typedef struct		s_input_args
{
	int				*flag_take_fork;
	long long		time_start;
	int				num_of_philo;
	int				t2d;
	int				t2eat;
	int				t2sleep;
	int				times_must_eat;
	int				dead;
	int				flag_end;
	pthread_mutex_t	f_write;
	pthread_mutex_t ms;
	pthread_mutex_t count;
	pthread_mutex_t *forks;
	struct timeval	current_time;
}					t_input_args;

typedef struct		s_philos
{
	int				number;
	int				left_fork;
	int				right_fork;
	int				flag_born;
	long long		hungy_time;
	long long		time_start;
	int				t2die;
	int				all_philo;
	int				times2eat;
	int				is_eating;
	pthread_mutex_t	*ms;
	pthread_mutex_t	*f_write;
	pthread_mutex_t	*forks;
	int				*flag_take_fork;
	int				num_of_philo;
	int				t2d;
	int				t2eat;
	int				t2sleep;
	int				times_must_eat;
	int				dead;
	int				flag_end;
	t_input_args	*inp_args;
	pthread_t		philosopher;

}					t_philos;

long long			my_ms1(struct timeval *current_time, pthread_mutex_t ms);
long long			my_ms2(struct timeval *current_time);
size_t				ft_strlen(const char *str);
void				ft_putnbr_fd(long long n);
int					ft_atoi(char *str);
int					take_options(int argc, char **argv, t_input_args *inp_args);
void				born_tablos(t_input_args *inp_args);
void				ne_printf(long long time, int phil_num, const char *message,
					t_philos *philos);
void				eating(t_philos *philos, struct timeval *current_time);
void				sleeping(t_philos *philos, struct timeval *current_time);
void				start_live (t_philos *philos,
					int i);
void				*philo_live(t_philos *philos);
void				give_nums_and_forks(t_philos *philos,
					t_input_args *inp_args);
void				born_philos(t_philos *philos, t_input_args *inp_args);
int					check_countmeals(t_philos *philos);
void				unlock_forks(t_philos *philos);
void				died_flag(t_philos *philos, int ret, int i,
					struct timeval current_time);
void				*monic(t_philos *philos);
void				cleaner(t_input_args *inp_args, t_philos *philos);
void				born_monitor(t_philos *philos, t_input_args *inp_args,
					pthread_t monitor);
int					main(int argc, char **argv);
int					ft_isdigit(int c);

#endif
