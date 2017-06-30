#include "rtv1.h"

unsigned int	put_col_cone(t_light *light, t_inter *inter, t_cone *cone)
{
	t_col		col;
	double		b;
	double		g;
	double		r;

	b = clamp_col(cone->col.tab[0], inter->cos_alph, light->col.tab[0]) * 255;
	g = clamp_col(cone->col.tab[1], inter->cos_alph, light->col.tab[1]) * 255;
	r = clamp_col(cone->col.tab[2], inter->cos_alph, light->col.tab[2]) * 255;
	init_col(&inter->col, r, g, b);
	inter->col.i = mult_col(&inter->col, &light->col);
	return (inter->col.i);
}

void			fill_inter_cone(t_light *light, t_cone *cone,
		t_inter *inter, t_view *view)
{
	t_coor		norm_cone;
	t_coor		norm_dir;
	t_coor		actual_center;
	t_coor		pc;
	t_coor		kvm;
	double		m;

	m = cone->angle * cone->r;
	point_on_ray(&view->ray.origin, &view->ray.direction,
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
	inter->col.i = put_col_cone(light, inter, cone);
	inter->shape = CONE;
}

int		is_cone(t_view *view, t_cone *cone, t_light *light, t_inter *inter)
{
	float		a;
	float		b;
	float		c;
	float		delt;
	t_ray		local;
	t_coor		x_ray;
	t_coor		k_ray;

	dot_sub(&view->ray.origin, &cone->center, &local.origin);
	dot_sub(&view->ray.origin, &cone->vertex, &x_ray);
	a = dot_prod(&view->ray.direction, &view->ray.direction) -
		(1 + pow(cone->angle, 2)) *
		pow(dot_prod(&view->ray.direction, &cone->hei), 2);
	b = 2 * (dot_prod(&view->ray.direction, &x_ray) -
		(1 + pow(cone->angle, 2)) *
		dot_prod(&view->ray.direction, &cone->hei) *
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
	//fill_inter_cone(light, cone, inter, view);
	return (cone->dist);
}
