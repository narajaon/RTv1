#include "rtv1.h"

void			fill_inter_cone(t_light *light, t_cone *cone,
		t_inter *inter, t_ray *view)
{
	t_coor		norm_cone;
	t_coor		norm_dir;
	t_coor		actual_center;
	t_coor		pc;
	t_coor		kvm;
	double		m;

	m = cone->angle * cone->r;
	point_on_ray(&view->origin, &view->direction,
			&inter->ray.origin, cone->dist);
	fill_coord(&actual_center, cone->center.x, inter->ray.origin.y,
			cone->center.z);
	dot_sub(&light->coord, &inter->ray.origin, &inter->ray.direction);
	dot_sub(&inter->ray.origin, &actual_center, &norm_cone);
	//dot_sub(&inter->ray.origin, &cone->vertex, &pc);
	//m *= (1 + pow(cone->angle, 2));
	//dot_mult(&cone->hei, &kvm, m);
	//dot_mult(&kvm, &kvm, (1 + pow(cone->angle, 2)));
	//dot_sub(&pc, &kvm, &norm_cone);
	normalize(&norm_cone, &norm_cone);
	normalize(&inter->ray.direction, &norm_dir);
	inter->cos_alph = dot_prod(&norm_cone, &norm_dir);
	inter->col.i = put_col(light, inter, &cone->col);
	inter->shape = CONE;
	inter->dist_min = cone->dist;
}

int		is_cone(t_ray *view, t_cone *cone, t_light *light, t_inter *inter)
{
	float		a;
	float		b;
	float		c;
	float		delt;
	t_ray		local;
	t_coor		x_ray;
	t_coor		k_ray;

	dot_sub(&view->origin, &cone->center, &local.origin);
	dot_sub(&view->origin, &cone->vertex, &x_ray);
	a = dot_prod(&view->direction, &view->direction) -
		(1 + pow(cone->angle, 2)) *
		pow(dot_prod(&view->direction, &cone->hei), 2);
	b = 2 * (dot_prod(&view->direction, &x_ray) -
		(1 + pow(cone->angle, 2)) *
		dot_prod(&view->direction, &cone->hei) *
		dot_prod(&x_ray, &cone->hei));
	c = dot_prod(&x_ray, &x_ray) - (1 + pow(cone->angle, 2)) *
		pow(dot_prod(&x_ray, &cone->hei), 2);
//	printf("a %f b %f c %f\n", a, b, c);
	if ((delt = pow(b, 2) - 4 * a * c) < 0)
		return (cone->dist = 0);
	//printf("delt %f\n", delt);
	cone->hit_1 = (-b - sqrt(delt)) / (2 * a);
	cone->hit_2 = (-b + sqrt(delt)) / (2 * a);
	cone->dist = smallest_non_negativ(cone->hit_1, cone->hit_2);
	//printf("dist %f\n", cone->dist);
	if (cone->dist < 0)
		return (cone->dist = 0);
	if (cone->dist < inter->dist_min)
		fill_inter_cone(light, cone, inter, view);
	return (cone->dist);
}
