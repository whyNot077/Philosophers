/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:17:51 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/04 14:10:32 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	is_full(t_philo *philo, t_monitoring *monitoring)
{
	pthread_mutex_lock(philo->change_remaining_meal_count);
	if (monitoring->required_meal_count == 0)
	{
		pthread_mutex_unlock(philo->change_remaining_meal_count);
		return (FALSE);
	}
	pthread_mutex_unlock(philo->change_remaining_meal_count);
	pthread_mutex_lock(monitoring->change_well_dying);
	monitoring->well_dying++;
	if (monitoring->well_dying == monitoring->number_of_philosophers)
	{
		pthread_mutex_unlock(monitoring->change_well_dying);
		return (FIN);
	}
	pthread_mutex_unlock(monitoring->change_well_dying);
	return (TRUE);
}

static int	is_living(t_philo *philo)
{
	unsigned int	current;

	pthread_mutex_lock(philo->monitoring->change_starvation);
	if (philo->monitoring->starvation == TRUE)
	{
		pthread_mutex_unlock(philo->monitoring->change_starvation);
		return (FALSE);
	}
	pthread_mutex_unlock(philo->monitoring->change_starvation);
	pthread_mutex_lock(philo->change_last_meal_time);
	current = get_time();
	if (current >= philo->last_meal_time + philo->time_to_die)
	{
		print_state(philo, "died");
		pthread_mutex_lock(philo->monitoring->change_starvation);
		philo->monitoring->starvation = TRUE;
		pthread_mutex_unlock(philo->monitoring->change_starvation);
		pthread_mutex_unlock(philo->change_last_meal_time);
		return (FALSE);
	}
	pthread_mutex_unlock(philo->change_last_meal_time);
	return (TRUE);
}

int	check_philosopher_status(t_monitoring *monitoring, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < monitoring->number_of_philosophers)
	{
		if (is_living(philos[i]) == FALSE)
			return (ERROR);
		if (is_full(philos[i], monitoring) == FIN)
			return (ERROR);
		i++;
	}
	return (0);
}
