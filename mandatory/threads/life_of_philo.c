/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:32:22 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/30 15:23:53 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	sleeping(t_philo *philo)
{
	print_state(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
}

static void	thinking(t_philo *philo)
{
	print_state(philo, "is thinking");
}

void	life_of_philo(void *arg)
{
	t_monitoring	*monitoring;
	t_philo			*philo;

	philo = (t_philo *)arg;
	monitoring = philo->monitoring;
	usleep(philo->time_to_eat * 500);
	while (monitoring->all_live)
	{
		if (monitoring->all_live == FALSE)
			return ;
		if (eating(philo) == FALSE)
			return ;
		if (monitoring->all_live == FALSE)
			return ;
		sleeping(philo);
		if (monitoring->all_live == FALSE)
			return ;
		thinking(philo);
	}
}
