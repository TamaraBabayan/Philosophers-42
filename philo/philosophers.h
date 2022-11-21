/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:29:23 by tbabayan          #+#    #+#             */
/*   Updated: 2022/08/30 10:48:47 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define YELLOW	"\033[0;33m"
# define BLUE	"\033[0;34m"
# define WHITE	"\033[0;37m"
# define CYAN	"\033[0;36m"

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_times
{
	unsigned long long	time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_philosophers;
	int					number_of_times_each_philosopher_must_eat;
}				t_times;

typedef struct s_philo
{
	int					number_of_times_philosopher_ate;
	t_times				times;
	unsigned long long	creating_time;
	unsigned long long	till_eating_time;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*my_print;
	int					index;
}				t_philo;

typedef struct s_final
{
	t_times			time;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	pthread_t		*thread;
}				t_final;

void				check_if_died(t_final *var);
void				end(t_final *var);
void				*event(void *philo);
int					create_mutexes(t_final *var);
int					create_philos(t_final *var);
int					create_threads(t_final *var);
unsigned long long	now(void);
void				check_if_died(t_final *var);
void				print_event(char *color, char *str, t_philo *p);
void				ft_usleep(unsigned long long time_to_smth);
void				end(t_final *var);

#endif
