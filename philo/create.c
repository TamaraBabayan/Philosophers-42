/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:51:37 by tbabayan          #+#    #+#             */
/*   Updated: 2022/08/30 11:14:11 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

int	create_mutexes(t_final *var)
{
	int	i;

	i = 0;
	var->print = malloc(sizeof(pthread_mutex_t));
	var->fork = malloc(sizeof(pthread_mutex_t)
			* var->time.number_of_philosophers);
	if (!var->fork || !var->print)
		return (0);
	pthread_mutex_init(var->print, NULL);
	while (i < var->time.number_of_philosophers)
	{
		if (pthread_mutex_init(&var->fork[i], NULL) != 0)
			return (0);
		++i;
	}
	return (1);
}

static void	fill_forks(t_final *var, int i)
{
	int	j;

	if (i == var->time.number_of_philosophers - 1)
		j = 0;
	else
		j = i + 1;
	var->philo[i].right_fork = &var->fork[i];
	var->philo[i].left_fork = &var->fork[j];
}

int	create_philos(t_final *var)
{
	int	i;

	i = 0;
	var->philo = malloc(sizeof(t_philo) * var->time.number_of_philosophers);
	if (!var->philo)
		return (0);
	while (i < var->time.number_of_philosophers)
	{
		var->philo[i].number_of_times_philosopher_ate = 0;
		var->philo[i].times = var->time;
		var->philo[i].index = i;
		var->philo[i].my_print = var->print;
		var->philo[i].till_eating_time = now();
		var->philo[i].creating_time = now();
		fill_forks(var, i);
		i++;
	}	
	return (1);
}

int	create_threads(t_final *var)
{
	int	i;

	i = 0;
	var->thread = malloc(sizeof(pthread_t) * var->time.number_of_philosophers);
	if (!var->thread)
		return (0);
	while (i < var->time.number_of_philosophers)
	{
		if (pthread_create(&var->thread[i], NULL, event,
				(void *)&var->philo[i]))
			return (0);
		i++;
	}
	return (1);
}
