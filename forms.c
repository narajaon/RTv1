#include "rtv1.h"

void	init_view(t_view *view)
{
	fill_coord(&view->coord, 0, 250, 10);
}

void	init_plane(t_plane *plane)
{
	fill_coord(&plane->center, 0, WIN_X / 2, WIN_Y / 2);
	normalize(&plane->center, &plane->norm);
	plane->col = 0x00FFFFFF;
}

void	init_ray(t_view *view, t_pix *pix)
{
	t_coor		tmp;

	tmp.x = pix->x;
	tmp.y = pix->y;
	tmp.z = 0;
	dot_cpy(&view->coord, &view->ray.origin);
	dot_cpy(&tmp, &view->ray.direction);
}

void	print_coord(t_coor *coord)
{
	printf("x %f y %f z %f\n", coord->x, coord->y, coord->z);
}

int		is_plane(t_view *view, t_plane *plane, t_pix *pix)
{
	float		dn;
	float		t;
	t_coor		tmp;
	t_coor		hit;

	dn = dot_prod(&view->ray.direction, &plane->norm);
	if (fabs(dn) < 0.00001)
		return (0);
	fill_coord(&hit, pix->x, pix->y, 0);
	dot_sub(&hit, &view->ray.origin, &tmp);
	t = dot_prod(&tmp, &plane->norm);
	t /= dn;
	if (t <= RAY_MIN || t >= RAY_MAX)
		return (0);
//	printf("t %f\n", t);
//	print_coord(&view->ray.direction);
//	print_coord(&view->ray.origin);
//	printf("%f\n", dn);
	return (1);
}

void	check_collision(t_env *e)
{
	int		xy;

	init_ray(&e->view, &e->pix);
	xy = e->pix.y * WIN_Y + e->pix.x;
	if (is_plane(&e->view, &e->plane, &e->pix))
		e->img.img[xy] = e->plane.col;
}
