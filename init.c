#include "rtv1.h"

void	init_inter(t_inter *inter)
{
	init_col(&inter->col, 0x00, 0x00, 0x00);
	inter->shape = NONE;
	inter->dist_min = INFINITY;
}

void	init_ray(t_view *view, t_pix *pix)
{
	dot_cpy(&view->coord, &view->ray.origin);
	fill_coord(&view->ray.direction, pix->x, pix->y, 0);
	dot_sub(&view->ray.direction, &view->ray.origin, &view->ray.direction);
	normalize(&view->ray.direction, &view->ray.direction);
	view->ray.len = 0;
}
