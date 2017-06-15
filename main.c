/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 18:08:43 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/14 18:31:42 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		mouse_move(int x, int y, t_env *e)
{
	printf("x %d y %d", x, y);
	return (0);
}

void	check_collision(t_env *e)
{
	//place rotation fun here
	rot_y(&e->prim.x, &e->prim.y, &e->prim.z, e->rot_y);
	rot_z(&e->prim.x, &e->prim.y, &e->prim.z, e->rot_z);
	is_plan(e);
	is_sphere(e);
	//take the smallest (or biggest ?) non-negative k from all objects
	if (e->sphere.k > 0.00001 || e->plan.k > 0.00001)
	{
		if (e->sphere.k > 0.00001 && e->plan.k > 0.00001)
			e->img.img[e->pix.y * WIN_Y + e->pix.x] = (e->sphere.k > e->plan.k) ? e->sphere.col : e->plan.col;
		else
			e->img.img[e->pix.y * WIN_Y + e->pix.x] = (e->sphere.k > 0.00001) ? e->sphere.col : e->plan.k;
	}
	else
		e->img.img[e->pix.y * WIN_Y + e->pix.x] = 0x00000000;
}

void	do_rt(t_env *e)
{
	mlx_key_hook(e->win, &rot_view, e);
	init_sphere(e);
	init_view1(e);
	init_light1(e);
	rot_y(&e->view.x, &e->view.y, &e->view.z, e->rot_y);
	rot_z(&e->view.x, &e->view.y, &e->view.z, e->rot_z);
	print_rt(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	mlx_loop(e->mlx);
}

void	print_rt(t_env *e)
{
	e->pix.y = 0;
	while (e->pix.y < WIN_Y)
	{
		e->pix.x = 0;
		while (e->pix.x < WIN_X)
		{
			init_prim(e);
			check_collision(e);
			e->pix.x++;
		}
		e->pix.y++;
	}
}

int		main(int ac, char **av)
{
	t_env	e;

	if (ac != 2)
		exit(error_msg(1));
	e.scene = ft_atoi(av[1]);
	e.rot_y = 0;
	e.rot_z = 0;
	if (e.scene == 4 || e.scene > 4 || e.scene <= 0)
		exit(error_msg(4));
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, WIN_X, WIN_Y, "Displaying RT scene");
	e.img.img_ptr = mlx_new_image(e.mlx, WIN_X, WIN_Y);
	e.img.img = (int *)mlx_get_data_addr(e.img.img_ptr,
			&e.img.bpp, &e.img.size_line, &e.img.endian);
	do_rt(&e);
	return (0);
}
