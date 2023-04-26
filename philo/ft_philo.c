/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:02:38 by agenoves          #+#    #+#             */
/*   Updated: 2022/09/05 11:04:29 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	phi_eat(t_philo *philo)
{
	if (philo->rfork % 2 == 0)
	{
		pthread_mutex_lock(&philo->init_ph->ph_forks[philo->lfork]);
		ft_printing(philo, "has taken a fork");
		pthread_mutex_lock(&philo->init_ph->ph_forks[philo->rfork]);
		ft_printing(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->init_ph->ph_forks[philo->rfork]);
		ft_printing(philo, "has taken a fork");
		pthread_mutex_lock(&philo->init_ph->ph_forks[philo->lfork]);
		ft_printing(philo, "has taken a fork");
	}
	pthread_mutex_lock(&philo->init_ph->checkeat);
	pthread_mutex_lock(&philo->init_ph->meal);
	ft_printing(philo, "is eating");
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->init_ph->meal);
	pthread_mutex_unlock(&philo->init_ph->checkeat);
	ft_smart_action(philo->init_ph->to_eat, philo);
	philo->n_meals++;
	printf("ID: %d \t Meals: %d\n", philo->ph_id, philo->n_meals);
	pthread_mutex_unlock(&philo->init_ph->ph_forks[philo->lfork]);
	pthread_mutex_unlock(&philo->init_ph->ph_forks[philo->rfork]);
}

void	check_if_dead(t_philo *philo)
{
	int		i;

	while (!check_all_eat(philo))
	{
		i = -1;
		while (++i < philo->init_ph->num_philo && !philo->init_ph->is_dead)
		{
			pthread_mutex_lock(&philo->init_ph->checkeat);
			if (ft_get_time() - philo[i].last_meal > philo->init_ph->to_die)
			{
				ft_printing(&philo[i], "died");
				pthread_mutex_lock(&philo->init_ph->death);
				philo->init_ph->is_dead = 1;
				pthread_mutex_unlock(&philo->init_ph->death);
			}
			pthread_mutex_unlock(&philo->init_ph->checkeat);
			usleep(100);
		}
		if (philo->init_ph->is_dead)
			break ;
	}
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->init_ph->num_philo == 1)
		return (one_philo(philo));
	while (!check_is_died(philo))
	{
		phi_eat(philo);
		if (philo->n_meals == philo->init_ph->n_toeat)
		{
			pthread_mutex_lock(&philo->init_ph->allate);
			philo->init_ph->alleat++;
			if (philo->init_ph->alleat == philo->init_ph->num_philo)
				pthread_mutex_unlock(&philo->init_ph->allate);
			pthread_mutex_unlock(&philo->init_ph->allate);
			return (NULL);
		}
		ft_printing(philo, "Is sleeping");
		ft_smart_action(philo->init_ph->to_sleep, philo);
		ft_printing(philo, "Is thinking");
		if (philo->n_meals == philo->init_ph->n_toeat)
			break ;
	}
	return (NULL);
}

int	ft_create_thread(t_philo *philo, t_init	*init)
{
	int			i;
	pthread_t	*th;

	i = 0;
	th = malloc(sizeof(pthread_t) * philo->init_ph->num_philo);
	if (!th)
		return (1);
	philo->init_ph->timestart = ft_get_time();
	while (i < philo->init_ph->num_philo)
	{
		if (pthread_create(&th[i], NULL, ft_routine, &philo[i]) != 0)
			return (printf("Error: Thread not created!!\n"));
		pthread_mutex_lock(&philo->init_ph->meal);
		philo[i].last_meal = ft_get_time();
		pthread_mutex_unlock(&philo->init_ph->meal);
		i++;
	}
	check_if_dead(philo);
	ft_clean_thread(th, philo);
	free(th);
	free(init->ph_forks);
	free(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_init	init;
	t_philo	*philo;

	if (ft_check_input(argc, argv) != 0)
		return (1);
	if (!ft_init_philo(&init, argv))
		return (0);
	philo = ft_fill_philo(&init);
	ft_create_thread(philo, &init);
	return (0);
}
