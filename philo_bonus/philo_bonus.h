/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:42:44 by agenoves          #+#    #+#             */
/*   Updated: 2022/05/24 11:43:08 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_init
{
	pthread_t	monitor;
	sem_t		*semfork;
	sem_t		*semwrite;
	sem_t		*semstop;
	sem_t		*sem_death;
	sem_t		*semeatall;
	sem_t		*eaten;
	pid_t		*pid;
	long		timestart;
	int			num_philo;
	int			to_die;
	int			to_eat;
	int			to_sleep;
	int			n_toeat;
	int			alleat;
	int			eat_all;
	int			parent_pid;
	int			start_check;
}			t_init;

typedef struct s_philo
{
	long long	last_meal;
	sem_t		*sem_philos;
	t_init		*init_ph;
	int			n_meals;
	int			ph_id;
}				t_philo;

int				ft_strcmp(char *s, char *str);
int				check_eaten(t_philo *philo);
int				wait_for_it(t_philo *philo);
int				ft_atoi(const char *str);
int				ft_check_for_chars(char *str);
int				ft_check_input(int ac, char **av);
int				ft_check_args(int argc, char **argv);
int				ft_init_semaphore(t_init *init);
int				ft_init_philo(t_init *init, char **argv, int argc);
void			*ft_death(void *arg);
void			*ft_eat_check(void *arg);
void			ft_routine(t_philo *philo);
void			set_eaten(t_philo *philo);
void			ft_smart_action(long long time);
void			ft_kill_process(t_philo *philo);
void			ft_printing(t_philo *philo, char *string);
void			*ft_monitoring(void *ptr);
char			*ft_itoa(int n);
long long		ft_get_time(void);
unsigned int	selection(int n);
t_philo			*ft_fill_philo(t_init *init);

#endif