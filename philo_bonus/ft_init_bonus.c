/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:42:16 by agenoves          #+#    #+#             */
/*   Updated: 2022/05/24 11:42:17 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*ft_fill_philo(t_init *init)
{
	int		i;
	t_philo	*philo;
	char	*s;

	i = 0;
	philo = malloc(sizeof(t_philo) * init->num_philo);
	while (i < init->num_philo)
	{
		philo[i].ph_id = i + 1;
		philo[i].last_meal = 0;
		philo[i].n_meals = 0;
		philo[i].init_ph = init;
		s = ft_itoa(philo[i].ph_id);
		sem_unlink(s);
		philo[i].sem_philos = sem_open(s, O_CREAT, 0644, 1);
		free(s);
		i++;
	}
	return (philo);
}

unsigned int	selection(int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	number;
	unsigned int	a;
	char			*string;

	a = selection(n);
	number = n;
	if (n < 0)
	{
		number *= -1;
		a++;
	}
	string = malloc(sizeof(char) * (a + 1));
	if (!string)
		return (NULL);
	*(string + a) = '\0';
	while (a-- != 0)
	{
		*(string + a) = (number % 10) + '0';
		number = number / 10;
	}
	if (n < 0)
		*(string + 0) = '-';
	return (string);
}

void	set_eaten(t_philo *philo)
{
	sem_wait(philo->init_ph->eaten);
	philo->init_ph->eat_all = 1;
	sem_post(philo->init_ph->eaten);
}

int	check_eaten(t_philo *philo)
{
	int	a;

	sem_wait(philo->init_ph->eaten);
	a = philo->init_ph->eat_all;
	sem_post(philo->init_ph->eaten);
	return (a);
}
