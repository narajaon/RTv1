#include "rtv1.h"

void	init_view(t_view *view)
{
	fill_coord(&view->coord, WIN_X / 2 + 1, WIN_Y / 2 + 1, -300);
	//rot_z(&view->coord.x, &view->coord.x, &view->coord.x, 0.5);
}

void	init_sphere(t_sphere *sphere)
{
	fill_coord(&sphere->coord, WIN_X / 2, WIN_Y / 2, 1);
	//rot_y(&sphere->coord.x, &sphere->coord.x, &sphere->coord.x, 0.7);
	sphere->r = 100;
	sphere->dist = 0;
	sphere->col = 0x00FF0000;
}

void	init_plane(t_plane *plane)
{
	fill_coord(&plane->center, 0, WIN_Y / 2, 0);
	normalize(&plane->center, &plane->norm);
	plane->dist = 0;
	plane->col = 0x000FF0DE;
}

void	init_ray(t_view *view, t_pix *pix)
{
	dot_cpy(&view->coord, &view->ray.origin);
	fill_coord(&view->ray.direction, WIN_X - pix->x, WIN_Y - pix->y, 0);
	//dot_cpy(&tmp, &view->ray.direction);
}

void	init_cyli(t_cyli *cyli)
{
	fill_coord(&cyli->cap, WIN_X / 2, WIN_Y / 2, 0);
	cyli->r = 75;
	cyli->l = 100;
	cyli->dist = 0;
	cyli->col = 0x00FF00FF;
}

void	init_light(t_light *light)
{
	//light->col = 0x00FFFFFF;
}
