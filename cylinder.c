#include "rtv1.h"

void			fill_inter_cyli(t_light *light, t_cyli *cyli,
		t_inter *inter, t_ray *view)
{
	t_coor		norm_cyli;
	t_coor		norm_dir;
	t_coor		actual_center;

	point_on_ray(&view->origin, &view->direction,
			&inter->ray.origin, cyli->dist);
	fill_coord(&actual_center, cyli->center.x, inter->ray.origin.y,
			cyli->center.z);
	dot_sub(&light->coord, &inter->ray.origin, &inter->ray.direction);
	//cyli->center.y = inter->ray.direction.y;
	dot_sub(&inter->ray.origin, &actual_center, &norm_cyli);
	normalize(&norm_cyli, &norm_cyli);
	normalize(&inter->ray.direction, &norm_dir);
	inter->cos_alph = dot_prod(&norm_cyli, &norm_dir);
	//inter->cos_alph *= -1;
	//printf("cos %f\n", inter->cos_alph);
	inter->col.i = put_col(light, inter, &cyli->col);
	inter->shape = CYLI;
	inter->dist_min = cyli->dist;
}

int		is_cyli(t_ray *view, t_cyli *cyli, t_light *light, t_inter *inter)
{
	float		a;
	float		b;
	float		c;
	float		delt;
	t_ray		local;
	t_coor		x_ray;

	dot_sub(&view->origin, &cyli->center, &local.origin);
	dot_sub(&view->origin, &cyli->cap_u, &x_ray);
	a = dot_prod(&view->direction, &view->direction) -
		pow(dot_prod(&view->direction, &cyli->hei), 2);
	b = 2 * (dot_prod(&view->direction, &x_ray) -
		dot_prod(&view->direction, &cyli->hei) *
		dot_prod(&x_ray, &cyli->hei));
	c = dot_prod(&x_ray, &x_ray) -
		pow(dot_prod(&x_ray, &cyli->hei), 2) - pow(cyli->r, 2);
//	printf("a %f b %f c %f\n", a, b, c);
	if ((delt = pow(b, 2) - 4 * a * c) < 0)
		return (cyli->dist = 0);
	cyli->hit_1 = (-b - sqrt(delt)) / (2 * a);
	cyli->hit_2 = (-b + sqrt(delt)) / (2 * a);
	cyli->dist = smallest_non_negativ(cyli->hit_1, cyli->hit_2);
//	printf("dist %f\n", cyli->dist);
	if (cyli->dist < 0)
		return (cyli->dist = 0);
	if (cyli->dist < inter->dist_min)
		fill_inter_cyli(light, cyli, inter, view);
	return (cyli->dist);
}
