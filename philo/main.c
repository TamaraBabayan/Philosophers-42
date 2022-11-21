/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabayan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:39:13 by tbabayan          #+#    #+#             */
/*   Updated: 2022/08/30 11:20:50 by tbabayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

static int	is(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static int	ft_atoi(const char *str)
{
	int	a;
	int	n;

	a = 0;
	n = 1;
	while (is(*str, "\t\n\v\f\r "))
		str++;
	if (*str == '-')
	{
		n = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		a *= 10;
		a += *str - 48;
		str++;
	}
	return (n * a);
}

static int	fill_times(char **argv, t_final *var, int argc)
{
	if (argc < 5 || argc > 6)
		return (0);
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0)
		return (0);
	var -> time.time_to_die = ft_atoi(argv[2]);
	var -> time.time_to_eat = ft_atoi(argv[3]);
	var -> time.time_to_sleep = ft_atoi(argv[4]);
	var -> time.number_of_philosophers = ft_atoi(argv[1]);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) <= 0)
			return (0);
		var -> time.number_of_times_each_philosopher_must_eat
			= ft_atoi(argv[5]);
	}
	else
		var -> time.number_of_times_each_philosopher_must_eat = 0;
	return (1);
}

static void	free_all(t_final *var)
{
	free(var->print);
	free(var->fork);
	free(var->philo);
	free(var->thread);
	free(var);
}

int	main(int argc, char **argv)
{
	t_final	*var;

	var = malloc(sizeof(t_final));
	if (!var)
		return (1);
	if (fill_times(argv, var, argc))
	{
		if (!create_mutexes(var) || !create_philos(var) || !create_threads(var))
			return (2);
		else
		{
			check_if_died(var);
			end(var);
		}
	}
	else
		return (3);
	free_all(var);
	return (0);
}
