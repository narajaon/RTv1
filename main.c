#include "rtv1.h"

int		key_hook(int key, t_env *e)
{
	if (key == EX_KEY)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(error_msg(0));
	}
	return (key);
}

void	do_rt(t_env *e)
{
	init_view(&e->view);
	init_sphere(&e->sphere);
	init_plane(&e->plane);
	init_cyli(&e->cyli);
	init_light(&e->light);
	init_cone(&e->cone);
	print_rt(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	mlx_loop(e->mlx);
}

int		main(int ac, char **av)
{
	t_env	e;

	if (ac != 2)
		exit(error_msg(1));
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, WIN_X, WIN_Y, "RT scene");
	e.img.img_ptr = mlx_new_image(e.mlx, WIN_X, WIN_Y);
	e.img.img = (int *)mlx_get_data_addr(e.img.img_ptr,
			&e.img.bpp, &e.img.size_line, &e.img.endian);
	e.view.rot_y = 0;
	mlx_key_hook(e.win, &rot_view, &e);
	do_rt(&e);
	return (0);
}
