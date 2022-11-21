/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:08:50 by tbabayan          #+#    #+#             */
/*   Updated: 2022/08/30 11:16:42 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

static void	eat(t_philo *p);

static void	fork_taking(t_philo *p)
{
	pthread_mutex_lock(p->right_fork);
	print_event(WHITE, "Has taken right fork", p);
	pthread_mutex_lock(p->left_fork);
	print_event(WHITE, "Has taken left fork", p);
}

static void	put_down_forks(t_philo *p)
{
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}

static void	is_sleeping(t_philo *p)
{
	print_event(BLUE, "Is sleeping", p);
	ft_usleep(p->times.time_to_sleep);
	print_event(CYAN, "Is thinking", p);
	eat(p);
}

static void	eat(t_philo *p)
{
	fork_taking(p);
	print_event(YELLOW, "Is eating", p);
	ft_usleep(p->times.time_to_eat);
	p->till_eating_time = now();
	p->number_of_times_philosopher_ate++;
	put_down_forks(p);
	is_sleeping(p);
}

void	*event(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	p->till_eating_time = now();
	if (p->index % 2 == 0)
	{
		eat(p);
	}
	else
	{
		ft_usleep(p->times.time_to_eat);
		eat(p);
	}
	return (NULL);
}
