/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:10:47 by agenoves          #+#    #+#             */
/*   Updated: 2022/04/28 16:11:51 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_fill_philo(t_init *init)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * init->num_philo);
	while (i < init->num_philo)
	{
		philo[i].ph_id = i + 1;
		philo[i].last_meal = 0;
		philo[i].n_meals = 0;
		philo[i].lfork = i;
		philo[i].rfork = (i + 1) % init->num_philo;
		philo[i].init_ph = init;
		pthread_mutex_init(&init->ph_forks[i], NULL);
		i++;
	}
	return (philo);
}

int	ft_init_philo(t_init *init, char **argv)
{
	init->num_philo = ft_atoi(argv[1]);
	init->to_die = ft_atoi(argv[2]);
	init->to_eat = ft_atoi(argv[3]);
	init->to_sleep = ft_atoi(argv[4]);
	init->is_dead = 0;
	init->alleat = 0;
	init->ph_forks = malloc(sizeof(pthread_mutex_t) * init->num_philo);
	pthread_mutex_init(&init->locker, NULL);
	pthread_mutex_init(&init->checkeat, NULL);
	pthread_mutex_init(&init->allate, NULL);
	pthread_mutex_init(&init->death, NULL);
	pthread_mutex_init(&init->meal, NULL);
	if (argv[5])
	{
		init->n_toeat = ft_atoi(argv[5]);
		if (init->n_toeat <= 0)
			return (0);
	}
	else
		init->n_toeat = -1;
	return (1);
}

int	ft_check_for_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_input(int ac, char **av)
{
	int	i;

	i = 1;
	while (av[i] && i < ac)
	{
		if (ft_check_for_chars(av[i]))
			return (printf("Error: check the input for wrong characters!\n"));
		i++;
	}
	if (ft_check_args(ac, av))
		return (1);
	return (0);
}
