#include "rtv1.h"

void	init_view(t_view *view)
{
	fill_coord(&view->coord, WIN_X / 2, WIN_Y / 2, -100);
	rot_y(&view->coord.x, &view->coord.x, &view->coord.x, 0);
}


void	init_sphere(t_sphere *sphere)
{
	fill_coord(&sphere->coord, WIN_X / 2, WIN_Y / 2, 0);
	sphere->r = 100;
	sphere->col = 0x00FF0000;
	sphere->dist = 0;
}

void	init_plane(t_plane *plane)
{
	fill_coord(&plane->center, 0, WIN_Y / 2, 0);
	normalize(&plane->center, &plane->norm);
	plane->dist = 0;
	plane->col = 0x00FFFFFF;
}

void	init_ray(t_view *view, t_pix *pix)
{
	dot_cpy(&view->coord, &view->ray.origin);
	fill_coord(&view->ray.direction, WIN_X - pix->x, WIN_Y - pix->y, 0);
	//dot_cpy(&tmp, &view->ray.direction);
}
