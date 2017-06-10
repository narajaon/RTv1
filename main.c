/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 18:08:43 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/10 19:23:08 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		mouse_move(int x, int y, t_env *e)
{
	printf("x %d y %d", x, y);
	return (0);
}

void	init_sphere(t_env *e)
{
	e->sphere.col = 0x00FF0000;
	e->sphere.r = 200;
	e->sphere.x = 0;
	e->sphere.y = 0;
	e->sphere.z = 0;
}

void	init_plan(t_env *e)
{
	e->plan.col = 0x000000FF;
	e->plan.x = 0;
	e->plan.y = 0;
	e->plan.z = 0;
	e->plan.k = 0;
}

void	init_view1(t_env *e)
{
	e->view.x = -300;
	e->view.y = 0;
	e->view.z = 0;
	e->view.dist = 100;
}

void	init_prim(t_env *e)
{
	e->prim.x = e->view.dist;
	e->prim.y = WIN_X / 2 - e->pix.x;
	e->prim.z = WIN_Y / 2 - e->pix.y;
}

void	is_plan(t_env *e)
{
	init_plan(e);
	if (fabs(e->prim.z) >= 0.00001)
		e->plan.k = -(e->view.z / e->prim.z);
//	printf("view %d prim %f\n", e->view.z, e->prim.z);
}

void	init_shad(t_env *e, unsigned int col)
{
	e->shad.x = e->prim.x;
	e->shad.y = e->prim.y;
	e->shad.z = e->prim.z;
	e->shad.col = col;
}

void	is_sphere(t_env *e)
{
	double		delt;
	double		k1;
	double		k2;

	e->sphere.a = pow(e->prim.x, 2) + pow(e->prim.y, 2) + pow(e->prim.z, 2);
	e->sphere.b = 2 * (e->view.x * e->prim.x + e->view.y * e->prim.y + e->view.z * e->prim.z);
	e->sphere.c = pow(e->view.x, 2) + pow(e->view.y, 2) + pow(e->view.z, 2) - pow(e->sphere.r, 2);
	delt = pow(e->sphere.b, 2) - 4 * e->sphere.a * e->sphere.c;
	if (delt >= 0.00001)
	{
		k1 = (-e->sphere.b + sqrt(delt)) / 2 * e->sphere.a;
		k2 = (-e->sphere.b - sqrt(delt)) / 2 * e->sphere.a;
		e->sphere.k = (k1 < k2) ? k1 : k2;
		init_shad(e, e->sphere.col);
	}
	else
		e->sphere.k = 0;
}

void	check_collision(t_env *e)
{
	init_prim(e);
	is_sphere(e);
	is_plan(e);
//	printf("plan %f sphere %f\n", e->plan.k, e->sphere.k);
	if (e->plan.k >= 0.00001 && (fabs(e->sphere.k) <= 0.00001))
		e->img.img[e->pix.y * WIN_Y + e->pix.x] = e->plan.col;
	else if (e->sphere.k >= 0.00001)
		e->img.img[e->pix.y * WIN_Y + e->pix.x] = e->sphere.col;
	else
		e->img.img[e->pix.y * WIN_Y + e->pix.x] = 0x00000000;
}

int		key_hook(int keycode, t_env *e)
{
	if (keycode == 53)
	{
		mlx_destroy_image(e->mlx, e->img.img_ptr);
		mlx_destroy_window(e->mlx, e->win);
		exit(error_msg(0));
	}
	/*
	if (keycode == 126)
	{
		init_sphere(e);
		//init_view1(e);
		e->view.z += 10;
		print_rt(e);
		mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	}
	*/
	return (keycode);
}

void	do_rt(t_env *e)
{
	init_sphere(e);
	init_view1(e);
	print_rt(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	mlx_key_hook(e->win, &key_hook, e);
	mlx_loop(e->mlx);
}

int		main(int ac, char **av)
{
	t_env	e;

	if (ac != 2)
		exit(error_msg(1));
	e.scene = ft_atoi(av[1]);
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
