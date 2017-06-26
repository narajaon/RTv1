#include "rtv1.h"

void	init_view(t_view *view)
{
	fill_coord(&view->coord, WIN_X / 2, WIN_Y / 2 + 100, -500);
	//rot_y(&view->coord.x, &view->coord.y, &view->coord.z, -0.2);
}

void	init_sphere(t_sphere *sphere)
{
	fill_coord(&sphere->coord, WIN_X / 2, WIN_Y / 2, 0);
	//rot_z(&sphere->coord.x, &sphere->coord.y, &sphere->coord.z, 0.1);
	sphere->r = 100;
	sphere->dist = 0;
	init_col(&sphere->col, 0, 255, 0);
}

void	init_inter(t_inter *inter)
{
	init_col(&inter->col, 0x00, 0x00, 0x00);
	inter->shape = NONE;
	inter->dist_min = 0;
}

void	init_plane(t_plane *plane)
{
	t_coor		norm;

	fill_coord(&plane->center, WIN_X / 2, WIN_Y / 2, 0);
	//rot_y(&plane->center.x, &plane->center.y, &plane->center.z, 0.5);
	fill_coord(&norm, plane->center.x, plane->center.y + 10, plane->center.z);
	dot_sub(&norm, &plane->center, &plane->norm);
	//print_coord(&norm);
	normalize(&plane->norm, &plane->norm);
	print_coord(&plane->norm);
	plane->dist = 0;
	init_col(&plane->col, 0xFF, 0xFF, 0xFF);
}

void	init_ray(t_view *view, t_pix *pix)
{
	dot_cpy(&view->coord, &view->ray.origin);
	fill_coord(&view->ray.direction, pix->x, pix->y, 0);
//	rot_y(&view->ray.direction.x, &view->ray.direction.y,
//	&view->ray.direction.z, -0.2);
	dot_sub(&view->ray.direction, &view->ray.origin, &view->ray.direction);
	normalize(&view->ray.direction, &view->ray.direction);
	view->ray.len = 0;
}

void	init_cyli(t_cyli *cyli)
{
	fill_coord(&cyli->center, WIN_X / 2, WIN_Y / 2, 0);
	cyli->hei = 200;
	fill_coord(&cyli->cap_u, cyli->center.x,
			cyli->center.y - cyli->hei, cyli->center.z);
	cyli->r = 70;
	dot_sub(&cyli->center, &cyli->cap_u, &cyli->norm);
	normalize(&cyli->norm, &cyli->norm);
	init_col(&cyli->col, 0xFF, 0x00, 0x00);
}

void	init_light(t_light *light)
{
	light->col.i = 0x00FFFFFF;
	init_col(&light->col, 0xFF, 0xFF, 0xFF);
	fill_coord(&light->coord, WIN_X / 2, WIN_Y, -300);
//	rot_z(&light->coord.x, &light->coord.y, &light->coord.z, -0.7);
	light->intens = 1;
}
