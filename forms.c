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
	if (fabs(dn) < 0.00001)
		return (0);
	fill_coord(&hit, pix->x, pix->y, 0);
	dot_sub(&hit, &view->ray.origin, &tmp);
	t = (dot_prod(&tmp, &plane->norm) / dn);
	if (t <= RAY_MIN || t >= RAY_MAX)
		return (0);
	view->inter.dist = t;
	view->inter.shape = PLANE;
//	printf("t %f\n", t);
//	print_coord(&view->ray.direction);
//	print_coord(&view->ray.origin);
//	printf("%f\n", dn);
	return (1);
}

int		is_sphere(t_view *view, t_sphere *sphere, t_pix *pix)
{
	float		abc[3];
	float		delt;
	t_ray		zero;
	t_coor		tmp;

	dot_cpy(&view->coord, &zero.origin);
	dot_cpy(&view->ray.direction, &zero.direction);
	dot_cpy(&sphere->coord, &tmp);
	dot_mult(&zero.origin, &zero.origin, -1);
	dot_sum(&tmp, &zero.origin, &zero.origin);
	abc[0] = vect_len(&zero.direction);
	abc[1] = dot_prod(&zero.origin, &zero.direction);
	abc[2] = vect_len(&zero.origin) - pow(sphere->r, 2);
	delt = pow(abc[1], 2) - 4 * abc[0] * abc[2];
//	print_coord(&sphere->coord);
	print_coord(&zero.origin);
	if (delt < 0.0f)
		return (0);
	sphere->hit_1 = (-abc[1] - sqrt(delt)) / (2 * abc[0]);
	sphere->hit_2 = (-abc[1] + sqrt(delt)) / (2 * abc[0]);
	if (sphere->hit_1 > RAY_MIN && sphere->hit_1 < RAY_MAX)
		view->inter.dist = sphere->hit_1;
	else if (sphere->hit_2 > RAY_MIN && sphere->hit_2 < RAY_MAX)
		view->inter.dist = sphere->hit_2;
	else
		return (0);
	return (1);
}

void	check_collision(t_env *e)
{
	int		xy;

	init_ray(&e->view, &e->pix);
	xy = e->pix.y * WIN_Y + e->pix.x;
	if (is_sphere(&e->view, &e->sphere, &e->pix))
		e->img.img[xy] = e->sphere.col;
//	if (is_plane(&e->view, &e->plane, &e->pix))
//		e->img.img[xy] = e->plane.col;
}
