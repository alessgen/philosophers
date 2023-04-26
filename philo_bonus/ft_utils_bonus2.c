/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:43:03 by agenoves          #+#    #+#             */
/*   Updated: 2022/05/24 11:43:05 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strcmp(char *s, char *str)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != str[i])
			return (1);
	}
	return (0);
}
