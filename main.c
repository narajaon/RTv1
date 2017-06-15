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

void	is_plan(t_env *e)
{
	double		prim;
	double		view;

	init_plan(e);
	prim = e->prim.x + e->prim.y + e->prim.z;
	view = e->view.x + e->view.y + e->view.z;
	e->plan.k = -(view) / (prim);
//	printf("plan %f\n", view);
//	if (fabs(e->prim.z) >= 200)
//		e->plan.k = -(e->view.z / e->prim.z);
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

void	init_pad(t_env *e)
{
	e->pad[0] = 0;
	e->pad[1] = 0;
	e->pad[2] = 0;
}

int		prim_hook(int keycode, t_env *e)
{
	printf("%d\n", keycode);
	if (keycode == EX_KEY)
	{
		mlx_destroy_image(e->mlx, e->img.img_ptr);
		mlx_destroy_window(e->mlx, e->win);
		exit(error_msg(0));
	}
	if (keycode == Q_KEY)
		e->pad[0] += 10;
	else if (keycode == E_KEY)
		e->pad[0] -= 10;
	else if (keycode == D_KEY)
		e->pad[1] += 10;
	else if (keycode == A_KEY)
		e->pad[1] -= 10;
	else if (keycode == W_KEY)
		e->pad[2] += 10;
	else if (keycode == S_KEY)
		e->pad[2] -= 10;
	else if (keycode == R_KEY)
		init_pad(e);
	print_rt(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	return (keycode);
}

int		rot_view(int keycode, t_env *e)
{
	printf("%d\n", keycode);
	if (keycode == EX_KEY)
	{
		mlx_destroy_image(e->mlx, e->img.img_ptr);
		mlx_destroy_window(e->mlx, e->win);
		exit(error_msg(0));
	}
	else if (keycode == UP_KEY)
		rot_y(&e->view.x, &e->view.y, &e->view.z, 0.125);
	else if (keycode == DOWN_KEY)
		rot_y(&e->view.x, &e->view.y, &e->view.z, -0.125);
	else if (keycode == LEFT_KEY)
		rot_z(&e->view.x, &e->view.y, &e->view.z, 0.125);
	else if (keycode == RIGHT_KEY)
		rot_z(&e->view.x, &e->view.y, &e->view.z, -0.125);
	else if (keycode == R_KEY)
		init_view1(e);
	print_rt(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	return (keycode);
}

void	check_collision(t_env *e)
{
	init_prim(e);
	is_sphere(e);
	is_plan(e);
	if (e->pix.x == WIN_X / 2 && e->pix.y == WIN_Y / 2)
		printf("plan %f sphere %f\n", e->plan.k, e->sphere.k);
	//if (e->plan.k)
	//	e->img.img[e->pix.y * WIN_Y + e->pix.x] = e->plan.col;
	if (e->sphere.k)
		e->img.img[e->pix.y * WIN_Y + e->pix.x] = e->sphere.col;
	else
		e->img.img[e->pix.y * WIN_Y + e->pix.x] = 0x00000000;
}

void	do_rt(t_env *e)
{
	init_sphere(e);
	init_view1(e);
	init_pad(e);
	//e->rot = &init_prim;
	print_rt(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	//mlx_key_hook(e->win, &prim_hook, e);
	mlx_key_hook(e->win, &rot_view, e);
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
