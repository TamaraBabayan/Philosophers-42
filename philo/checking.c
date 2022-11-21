/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:55:24 by tbabayan          #+#    #+#             */
/*   Updated: 2022/08/30 11:30:47 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

int	is_right(t_final *var)
{
	int	i;

	i = 0;
	while (i < var->time.number_of_philosophers)
	{
		if (var->time.number_of_times_each_philosopher_must_eat == 0
			|| var->philo[i].number_of_times_philosopher_ate
			< var->time.number_of_times_each_philosopher_must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	end(t_final *var)
{
	int	i;

	i = 0;
	while (i < var->time.number_of_philosophers)
	{
		pthread_detach(var->thread[i]);
		pthread_mutex_destroy(&var->fork[i]);
		pthread_mutex_destroy(var->philo[i].right_fork);
		pthread_mutex_destroy(var->philo[i].left_fork);
		pthread_mutex_destroy(var->philo[i].my_print);
		i++;
	}
	pthread_mutex_destroy(var->print);
}

void	check_if_died(t_final *var)
{
	int	i;

	while (1)
	{
		if (is_right(var))
		{
			ft_usleep(10);
			printf("%s%s\n", GREEN, "SUCCESS");
			return ;
		}
		i = 0;
		while (i < var->time.number_of_philosophers)
		{
			if (now() - var->philo[i].till_eating_time > var->time.time_to_die)
			{
				print_event(RED, "Died", &var->philo[i]);
				return ;
			}
			i++;
		}
	}
}
