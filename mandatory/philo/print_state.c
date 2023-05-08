/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:11:32 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/08 15:30:57 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	print_state(t_philo *philo, const char *statement)
{
	unsigned int	philo_time;

	philo_time = get_time() - philo->info.start_time;
	if (ft_strcmp(statement, "died") == 0)
	{
		pthread_mutex_lock(&philo->resources->living);
		philo->resources->live = FALSE;
		pthread_mutex_unlock(&philo->resources->living);
		pthread_mutex_lock(&philo->resources->print);
		printf(RED "%u %d %s" DEFAULT "\n", philo_time, philo->id, statement);
		release_forks(philo);
	}
	else if (ft_strcmp(statement, "is eating") == 0)
	{
		pthread_mutex_lock(&philo->resources->print);
		pthread_mutex_lock(&philo->resources->living);
		if (philo->resources->live == FALSE)
		{
			pthread_mutex_unlock(&philo->resources->living);
			pthread_mutex_unlock(&philo->resources->print);
			return (FIN);
		}
		pthread_mutex_unlock(&philo->resources->living);
		printf(GREEN "%u %d %s" DEFAULT "\n", philo_time, philo->id, statement);
	}
	else
	{
		pthread_mutex_lock(&philo->resources->print);
		pthread_mutex_lock(&philo->resources->living);
		if (philo->resources->live == FALSE)
		{
			pthread_mutex_unlock(&philo->resources->living);
			pthread_mutex_unlock(&philo->resources->print);
			return (FIN);
		}
		pthread_mutex_unlock(&philo->resources->living);
		printf("%u %d %s\n", philo_time, philo->id, statement);
	}
	pthread_mutex_unlock(&philo->resources->print);
	return (0);
}
