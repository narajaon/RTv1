/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:30:21 by narajaon          #+#    #+#             */
/*   Updated: 2018/01/31 14:58:47 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int		error_msg(int error)
{
	if (error == 1)
		ft_putstr_fd("Usage : ./rtv1 <scene>\n", 2);
	else if (error == 2)
		ft_putstr_fd("Couldn't allocate memory :(\n", 2);
	else if (error == 3)
		ft_putstr_fd("Invalid scene :(\n", 2);
	else
		ft_putstr_fd("Window closed, cya\n", 1);
	exit(error);
}

double	smallest_non_negativ(double a, double b)
{
	if (a > RAY_MIN && a < RAY_MAX)
		return (a);
	if (b > RAY_MIN && b < RAY_MAX)
		return (b);
	return (0);
}

void	free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	print_rt(t_env *e)
{
	e->pix.y = 0;
	while (e->pix.y < WIN_Y)
	{
		e->pix.x = 0;
		while (e->pix.x < WIN_X)
		{
			if (!(e->pix.x % SPEED) && !(e->pix.y % SPEED))
				check_collision(e);
			e->pix.x++;
		}
		e->pix.y++;
	}
}
