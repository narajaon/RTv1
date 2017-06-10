/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 10:31:49 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/10 14:37:46 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		error_msg(int error)
{
	if (error == 1)
		ft_putstr_fd("Usage : ./rtv1 <value>\n1- sphere\
				\n2- cylender\n3- cones\
				\n4- mix\n", 2);
	else if (error == 2)
		ft_putstr_fd("Couldn't allocate memory :(\n", 2);
	else if (error == 3)
		ft_putstr_fd("Invalid scene :(\n", 2);
	else
		ft_putstr_fd("Window closed, cya\n", 1);
	return (error);
}

void	print_rt(t_env *e)
{
	e->pix.x = 0;
	while (e->pix.x < WIN_X)
	{
		e->pix.y = 0;
		while (e->pix.y < WIN_Y)
		{
			check_collision(e);
			e->pix.y++;
		}
		e->pix.x++;
	}
}
