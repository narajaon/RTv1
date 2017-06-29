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
	//printf("cone col %x\n", cone->col.i);
	//printf("inter col %x\n", inter->col.i);
	//printf("cos alph %f\n", inter->cos_alph);
	//printf("b %f g %f r %f\n", b, g, r);
	return (inter->col.i);
}

void			fill_inter_cone(t_light *light, t_cone *cone,
		t_inter *inter, t_view *view)
{
	t_coor		norm_cone;
	t_coor		norm_dir;
	t_coor		actual_center;

	point_on_ray(&view->ray.origin, &view->ray.direction,
			&inter->ray.origin, cone->dist);
	fill_coord(&actual_center, cone->center.x, inter->ray.origin.y,
			cone->center.z);
	dot_sub(&light->coord, &inter->ray.origin, &inter->ray.direction);
	//cone->center.y = inter->ray.direction.y;
	dot_sub(&inter->ray.origin, &actual_center, &norm_cone);
	normalize(&norm_cone, &norm_cone);
	normalize(&inter->ray.direction, &norm_dir);
	inter->cos_alph = dot_prod(&norm_cone, &norm_dir);
	//printf("cos %f\n", inter->cos_alph);
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

	//dot_sub(&view->ray.origin, &cone->center, &local.origin);
	dot_sub(&view->ray.origin, &cone->center, &local.origin);
	dot_sub(&view->ray.origin, &cone->vertex, &x_ray);
	a = pow(view->ray.direction.x, 2) + pow(view->ray.direction.z, 2) -
		pow(view->ray.direction.y, 2);
	b = 2 * (local.origin.x * view->ray.direction.x + local.origin.z *
		view->ray.direction.z - local.origin.y * view->ray.direction.y);
	c = pow(local.origin.x, 2) + pow(local.origin.z, 2) - pow(local.origin.y, 2);
	if ((delt = pow(b, 2) - 4 * a * c) < 0)
		return (cone->dist = 0);
	cone->hit_1 = (-b - sqrt(delt)) / (2 * a);
	cone->hit_2 = (-b + sqrt(delt)) / (2 * a);
	cone->dist = smallest_non_negativ(cone->hit_1, cone->hit_2);
	printf("dist %f\n", cone->dist);
	if (cone->dist < 0)
		return (cone->dist = 0);
	fill_inter_cone(light, cone, inter, view);
	return (1);
}
