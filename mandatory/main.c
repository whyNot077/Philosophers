/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:30:35 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/02 13:29:46 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_monitoring	*monitoring;
	t_philo			**philos;

	if (init(argc, argv, &monitoring, &philos) == ERROR)
		return (1);
	if (start_threads(monitoring, philos) == ERROR)
		return (1);
	while (check_philosopher_status(monitoring, philos) == 0)
		usleep(50);
	close_free(monitoring, philos);
	return (0);
}
