/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:05:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/30 15:27:43 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	release_forks(t_philo *philo, t_monitoring *monitoring)
{
	if (philo->id % 2)
	{
		pthread_mutex_unlock(&monitoring->forks[philo->right_fork]);
		pthread_mutex_unlock(&monitoring->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&monitoring->forks[philo->left_fork]);
		pthread_mutex_unlock(&monitoring->forks[philo->right_fork]);
	}
}

static void	take_forks(t_philo *philo, t_monitoring *monitoring)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&monitoring->forks[philo->right_fork]);
		pthread_mutex_lock(&monitoring->forks[philo->left_fork]);
		if (monitoring->all_live == FALSE)
		{
			release_forks(philo, monitoring);
			return ;
		}
		print_state(philo, "has taken a fork");
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&monitoring->forks[philo->left_fork]);
		pthread_mutex_lock(&monitoring->forks[philo->right_fork]);
		if (monitoring->all_live == FALSE)
		{
			release_forks(philo, monitoring);
			return ;
		}
		print_state(philo, "has taken a fork");
		print_state(philo, "has taken a fork");
	}
}

static void	update_last_eat(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	philo->last_eat = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	philo->current_meal_count++;
}

static int	is_full(t_philo *philo)
{
	if (philo->monitoring->required_meal_count == 0 \
		|| philo->current_meal_count != philo->monitoring->required_meal_count)
		return (FALSE);
	philo->is_living = FALSE;
	philo->monitoring->well_dying++;
	release_forks(philo, philo->monitoring);
	return (TRUE);
}

int	eating(t_philo *philo)
{
	t_monitoring	*monitoring;

	monitoring = philo->monitoring;
	take_forks(philo, monitoring);
	if (monitoring->all_live == FALSE)
	{
		release_forks(philo, monitoring);
		return (FALSE);
	}
	print_state(philo, "is eating");
	if (monitoring->all_live == TRUE)
		update_last_eat(philo);
	if (is_full(philo) == TRUE)
		return (FALSE);
	usleep(monitoring->time_to_eat * 1000);
	release_forks(philo, monitoring);
	return (TRUE);
}
