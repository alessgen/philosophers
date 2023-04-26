/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:10:28 by agenoves          #+#    #+#             */
/*   Updated: 2022/05/05 12:15:48 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_smart_action(long long time, t_philo *philo)
{
	long long	past;

	past = ft_get_time();
	while (!check_is_died(philo))
	{
		if (ft_get_time() - past >= time)
			break ;
		usleep(100);
	}
	return ;
}

int	check_is_died(t_philo *philo)
{
	int	a;

	pthread_mutex_lock(&philo->init_ph->death);
	a = philo->init_ph->is_dead;
	pthread_mutex_unlock(&philo->init_ph->death);
	return (a);
}

int	check_all_eat(t_philo *philo)
{
	int	c;

	pthread_mutex_lock(&philo->init_ph->allate);
	c = philo->init_ph->alleat;
	pthread_mutex_unlock(&philo->init_ph->allate);
	return (c);
}

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->init_ph->ph_forks[philo->lfork]);
	ft_printing(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->init_ph->ph_forks[philo->lfork]);
	usleep(philo->init_ph->to_die * 1000);
	ft_printing(philo, "died");
	return (NULL);
}

int	ft_clean_thread(pthread_t *th, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->init_ph->num_philo)
		if (pthread_join(th[i], NULL) != 0)
			return (printf("Error: Thread not Joined!!\n"));
	i = -1;
	while (++i < philo->init_ph->num_philo)
		if (pthread_mutex_destroy(&philo->init_ph->ph_forks[i]))
			return (printf("Error: Mutex not Destroyed!!\n"));
	return (0);
}
