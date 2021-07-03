/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sglass <sglass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:58:49 by sglass            #+#    #+#             */
/*   Updated: 2021/03/31 21:05:11 by sglass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_header.h"

size_t		ft_strlen(const char *str)
{
	int x;

	x = 0;
	while (str[x] != 0)
		x++;
	return (x);
}

void		ft_putnbr_fd(long long n)
{
	char				stroka[20];
	long long			x;
	int					i;

	i = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	while (n != 0)
	{
		x = (n % 10);
		n = (n / 10);
		*(stroka + (i++)) = x + '0';
	}
	while ((i--) != 0)
		write(1, (stroka + i), 1);
}

int			ft_atoi(char *str)
{
	int i;
	int z;
	int t;

	i = 0;
	z = 1;
	t = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			z = z * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		t = t * 10 + (str[i] - '0');
		if (str[i + 1] < '0' && str[i + 1] > 9)
			return (t * z);
		i++;
	}
	return (t * z);
}
