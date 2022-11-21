/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:32:54 by tbabayan          #+#    #+#             */
/*   Updated: 2022/08/30 11:27:13 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

unsigned long long	now(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec * 0.001);
}

void	ft_usleep(unsigned long long time_to_smth)
{
	unsigned long long	start;

	start = now();
	while (now() - start <= time_to_smth)
		;
}

void	print_event(char *color, char *str, t_philo *p)
{
	pthread_mutex_lock(p->my_print);
	printf("%s%llu\t%d\t%s\n", color, now() - p->creating_time, p->index + 1,
		str);
	if (*str != 'D')
		pthread_mutex_unlock(p->my_print);
}
