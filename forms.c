#include "rtv1.h"

void	print_coord(t_coor *coord)
{
	printf("x %f y %f z %f\n", coord->x, coord->y, coord->z);
}

int		is_plane(t_view *view, t_plane *plane, t_pix *pix)
{
	float		dn;
	float		ppn;
	float		prn;
	float		t;
	t_coor		tmp;
	t_coor		hit;

	dn = dot_prod(&view->ray.direction, &plane->norm);
	if (dn < 0.00001)
		return (0);
	t = dot_prod(&plane->center, &plane->norm);
	t -= dot_prod(&view->ray.direction, &plane->norm);
	t /= dn;
	if (t <= RAY_MIN || t >= RAY_MAX)
		return (0);
	plane->dist = t;
	return (1);
}

float	smallest_non_negativ(float a, float b)
{
	if (a > 0.00001 || b > 0.00001)
			return ((a > 0.00001) ? a : b);
	return (0);
}

int		is_sphere(t_view *view, t_sphere *sphere, t_pix *pix)
{
	float		a;
	float		b;
	float		c;
	float		delt;
	t_ray		tmp;

	dot_cpy(&view->ray.origin, &tmp.origin);
	dot_cpy(&view->ray.direction, &tmp.direction);
	dot_sub(&tmp.origin, &sphere->coord, &tmp.origin);
	dot_sub(&tmp.direction, &sphere->coord, &tmp.direction);
	a = vect_pow(&tmp.direction);
	b = 2 * (dot_prod(&tmp.origin, &tmp.direction));
	c = vect_pow(&tmp.direction) - pow(sphere->r, 2);
	if ((delt = pow(b, 2) - 4 * a * c) < -0.00001)
		return (0);
	sphere->hit_1 = (-b - sqrt(delt)) / (2 * a);
	sphere->hit_2 = (-b + sqrt(delt)) / (2 * a);
	sphere->dist = smallest_non_negativ(sphere->hit_1, sphere->hit_2);
//	printf("k1 %f k2 %f\n", sphere->hit_1, sphere->hit_2);
//	printf("dist %f\n", sphere->dist);

	/*need to check why there's a padding of 1 here*/

	if (sphere->dist < 1)
		return (sphere->dist = 0);
	return (1);
}

void	check_collision(t_env *e)
{
	int		xy;
	float	plane;
	float	sphere;

	init_ray(&e->view, &e->pix);
	xy = e->pix.y * WIN_Y + e->pix.x;
	is_plane(&e->view, &e->plane, &e->pix);
	is_sphere(&e->view, &e->sphere, &e->pix);
	plane = e->plane.dist;
	sphere = e->sphere.dist;
	if ((sphere > 0.00001))
		e->img.img[xy] = e->sphere.col;
	else if ((plane && sphere > plane) || (plane && sphere < 0.00001))
		e->img.img[xy] = e->plane.col;
}
