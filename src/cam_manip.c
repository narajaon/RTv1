/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 12:28:12 by narajaon          #+#    #+#             */
/*   Updated: 2018/01/31 15:04:01 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	move_cam(int keycode, t_env *e)
{
	if (keycode == W_KEY)
		e->view.z_value += 50;
	else if (keycode == S_KEY)
		e->view.z_value -= 50;
	else if (keycode == D_KEY)
		e->view.x_value += 50;
	else if (keycode == A_KEY)
		e->view.x_value -= 50;
	else if (keycode == PAG_UP_KEY)
		e->view.y_value -= 50;
	else if (keycode == PAG_DOWN_KEY)
		e->view.y_value += 50;
}

void	rot_cam(int keycode, t_env *e)
{
	if (keycode == RIGHT_KEY)
		e->view.rot_y += 0.2;
	else if (keycode == LEFT_KEY)
		e->view.rot_y -= 0.2;
	else if (keycode == UP_KEY)
		e->view.rot_x += 0.2;
	else if (keycode == DOWN_KEY)
		e->view.rot_x -= 0.2;
	else if (keycode == E_KEY)
		e->view.rot_z -= 0.2;
	else if (keycode == Q_KEY)
		e->view.rot_z += 0.2;
}

int		rot_view(int keycode, t_env *e)
{
	rot_cam(keycode, e);
	move_cam(keycode, e);
	if (keycode == EX_KEY)
		exit_rt(e);
	else if (keycode == R_KEY)
	{
		e->view.rot_x = 0;
		e->view.rot_y = 0;
		e->view.rot_z = 0;
		e->view.x_value = 0;
		e->view.y_value = 0;
		e->view.z_value = 0;
	}
	print_rt(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	return (keycode);
}
