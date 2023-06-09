/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:14:22 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/15 14:39:15 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	release_forks(t_philo *philo)
{
	sem_post(philo->resources->forks);
	sem_post(philo->resources->forks);
}

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->resources->prevention);
	sem_wait(philo->resources->forks);
	print_state(philo, "has taken a fork");
	sem_wait(philo->resources->forks);
	print_state(philo, "has taken a fork");
	sem_post(philo->resources->prevention);
}

static void	start_eating(t_philo *philo)
{
	print_state(philo, "is eating");
	time_lapse(philo->info->time_to_eat);
	if (philo->info->must_eat_times != -1)
	{
		philo->eat_count++;
		if (philo->eat_count == philo->info->must_eat_times)
		{
			release_forks(philo);
			exit(0);
		}
	}
}

void	update_last_meal_time(t_philo *philo)
{
	sem_wait(philo->resources->last_meal);
	philo->last_meal_time = get_time();
	sem_post(philo->resources->last_meal);
}

void	eating(t_philo *philo)
{
	take_forks(philo);
	update_last_meal_time(philo);
	start_eating(philo);
	release_forks(philo);
}
