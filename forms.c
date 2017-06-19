#include "rtv1.h"

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
	if (dn < 0.00001)
		return (0);
	fill_coord(&hit, pix->x, pix->y, 0);
	dot_sub(&hit, &view->ray.origin, &tmp);
	t = (dot_prod(&tmp, &plane->norm) / dn);
	if (t <= RAY_MIN || t >= RAY_MAX)
		return (0);
	view->inter.dist = t;
	view->inter.shape = PLANE;
		printf("t %f\n", t);
	//	print_coord(&view->ray.direction);
	//	print_coord(&view->ray.origin);
	//	printf("%f\n", dn);
	return (1);
}

float	smallest_non_negativ(float a, float b)
{
	if (a > 0.00001 || b > 0.00001)
	{
		if (a > 0.00001 && b > 0.00001)
			return ((a < b) ? a : b);
		else
			return ((a > 0.00001) ? a : b);
	}
	return (-1);
}

int		is_sphere(t_view *view, t_sphere *sphere, t_pix *pix)
{
	return (1);
}

void	check_collision(t_env *e)
{
	int		xy;

	init_ray(&e->view, &e->pix);
	xy = e->pix.y * WIN_Y + e->pix.x;
//	if (is_sphere(&e->view, &e->sphere, &e->pix))
//		e->img.img[xy] = e->sphere.col;
		if (is_plane(&e->view, &e->plane, &e->pix))
			e->img.img[xy] = e->plane.col;
}
