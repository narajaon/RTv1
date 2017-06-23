#include "rtv1.h"

void	init_view(t_view *view)
{
	fill_coord(&view->coord, WIN_X / 2, WIN_Y / 2, -300);
	//rot_z(&view->coord.x, &view->coord.x, &view->coord.x, 0.5);
}

void	init_sphere(t_sphere *sphere)
{
	fill_coord(&sphere->coord, WIN_X / 2, WIN_Y / 2, 0);
	sphere->r = 100;
	sphere->dist = 0;
	init_col(&sphere->col, 255, 0, 0);
}

void	init_inter(t_inter *inter)
{
	init_col(&inter->col, 0x00, 0x00, 0x00);
	inter->shape = NONE;
}

void	init_plane(t_plane *plane)
{
	fill_coord(&plane->center, 0, WIN_Y / 2, 0);
	normalize(&plane->center, &plane->norm);
	plane->dist = 0;
	init_col(&plane->col, 0x42, 0x42, 0x42);
}

void	init_ray(t_view *view, t_pix *pix)
{
	dot_cpy(&view->coord, &view->ray.origin);
	fill_coord(&view->ray.direction, WIN_X / 2 + pix->x, WIN_Y / 2 + pix->y, 0);
	dot_sub(&view->ray.direction, &view->ray.origin, &view->ray.direction);
	print_coord(&view->ray.direction);
}

void	init_cyli(t_cyli *cyli)
{
	fill_coord(&cyli->cap, 0, 0, 0);
	cyli->r = 100;
	cyli->l = 100;
	cyli->dist = 0;
	init_col(&cyli->col, 0xFF, 0x00, 0xFF);
}

void	init_light(t_light *light)
{
	light->col.i = 0x00FFFFFF;
	init_col(&light->col, 0xFF, 0xFF, 0xFF);
	fill_coord(&light->coord, WIN_X / 2, WIN_Y / 2, -300);
	light->intens = 1;
}
