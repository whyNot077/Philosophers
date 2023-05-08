/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:10:16 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/08 18:31:52 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	release_forks(t_philo *philo)
{
	if (philo->id & 1)
	{
		pthread_mutex_unlock(&philo->resources->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->resources->forks[philo->right_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->resources->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->resources->forks[philo->left_fork]);
	}
}

static int	take_forks(t_philo *philo)
{
	if (philo->id & 1)
	{
		pthread_mutex_lock(&philo->resources->forks[philo->left_fork]);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(&philo->resources->forks[philo->right_fork]);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->resources->forks[philo->right_fork]);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(&philo->resources->forks[philo->left_fork]);
		print_state(philo, "has taken a fork");
	}
	return (0);
}

static int	start_eating(t_philo *philo)
{
	int	eat_count;

	print_state(philo, "is eating");
	time_lapse(philo->info.time_to_eat);
	if (philo->info.must_eat_times != -1)
	{
		pthread_mutex_lock(&philo->resources->eat_count);
		philo->eat_count++;
		eat_count = philo->eat_count;
		pthread_mutex_unlock(&philo->resources->eat_count);
		if (eat_count == philo->info.must_eat_times)
		{
			pthread_mutex_lock(&philo->resources->full);
			philo->resources->full_count++;
			pthread_mutex_unlock(&philo->resources->full);
			release_forks(philo);
			return (FULL);
		}
	}
	return (0);
}

static void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->resources->last_meal_time);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->resources->last_meal_time);
}

int	eating(t_philo *philo)
{
	int	error;

	error = 0;
	if (take_forks(philo) == ERROR)
		error = 1;
	if (error == 0)
	{
		update_last_meal_time(philo);
		if (start_eating(philo) == FULL)
			return (FULL);
	}
	release_forks(philo);
	return (0);
}
