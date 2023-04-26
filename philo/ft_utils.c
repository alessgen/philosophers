/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:11:37 by agenoves          #+#    #+#             */
/*   Updated: 2022/04/26 18:11:40 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printing(t_philo *philo, char *string)
{
	long long	current;

	current = ft_get_time() - philo->init_ph->timestart;
	pthread_mutex_lock(&philo->init_ph->locker);
	if (!check_is_died(philo))
		printf("%lld %d %s\n", current, philo->ph_id, string);
	pthread_mutex_unlock(&philo->init_ph->locker);
}

long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

int	ft_check_args(int argc, char **argv)
{
	if (argc > 4 && argc <= 6)
	{
		if (ft_atoi(argv[1]) < 1)
			return (printf("Error: At least one phisolopher needed!\n"));
		if (ft_atoi(argv[2]) < 1)
			return (printf("Error: time_to_die must be at least 1 ms and\
not higher then Max int!\n"));
		if (ft_atoi(argv[3]) < 1)
			return (printf("Error: time_to_eat must be at least 1 ms and\
not higher then Max int!\n"));
		if (ft_atoi(argv[4]) < 1)
			return (printf("Error: time_to_sleep must be at least 1 ms and\
not higher then Max int!\n"));
		if (argc == 6 && ft_atoi(argv[5]) < 1)
			return (printf("Error: number_of_times_each_philosopher_must_eat \
must be at least 1!\n"));
	}
	else
		return (printf("Error: INVALID ARGUMENT! You need to compile with: \
number_of_philosophers, time_to_die, time_to_eat, time_to_sleep \
and optional number_of_times_each_philosopher_must_eat\n"));
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10;
		result = result + (*str - 48);
		str++;
	}
	return (result * sign);
}
