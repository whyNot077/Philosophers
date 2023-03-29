/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:30:35 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/29 19:44:10 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_monitoring	*monitoring;
	t_philo			**philos;

	if (init(argc, argv, &monitoring, &philos) == ERROR)
		return (1);
	start_threads(monitoring, philos);
	monitor(monitoring, philos);
	// close_free(monitoring, philos);
	free(monitoring);
	return (0);
}
