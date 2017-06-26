#include "rtv1.h"

unsigned int	put_col_cyli(t_light *light, t_inter *inter, t_cyli *cyli)
{
	t_col		col;
	double		b;
	double		g;
	double		r;

	b = clamp_col(cyli->col.tab[0], inter->cos_alph, light->col.tab[0]) * 255;
	g = clamp_col(cyli->col.tab[1], inter->cos_alph, light->col.tab[1]) * 255;
	r = clamp_col(cyli->col.tab[2], inter->cos_alph, light->col.tab[2]) * 255;
	init_col(&inter->col, r, g, b);
	inter->col.i = mult_col(&inter->col, &light->col);
	//printf("cyli col %x\n", cyli->col.i);
	//printf("inter col %x\n", inter->col.i);
	//printf("cos alph %f\n", inter->cos_alph);
	//printf("b %f g %f r %f\n", b, g, r);
	return (inter->col.i);
}

void			fill_inter_cyli(t_light *light, t_cyli *cyli,
		t_inter *inter, t_view *view)
{
	t_coor		norm_cyli;
	t_coor		norm_dir;
	t_coor		view_norm;

	point_on_ray(&view->ray.origin, &view->ray.direction,
			&inter->ray.origin, cyli->dist);
	dot_sub(&light->coord, &inter->ray.origin, &inter->ray.direction);
	normalize(&cyli->norm, &norm_cyli);
	normalize(&inter->ray.direction, &norm_dir);
	inter->cos_alph = dot_prod(&norm_cyli, &norm_dir);
	inter->col.i = put_col_cyli(light, inter, cyli);
	inter->shape = CYLI;
}

int		is_cyli(t_view *view, t_cyli *cyli, t_light *light, t_inter *inter)
{
	float		a;
	float		b;
	float		c;
	float		delt;
	t_ray		local;

	dot_sub(&view->ray.origin, &cyli->center, &local.origin);
	a = pow(view->ray.direction.x, 2) + pow(view->ray.direction.z, 2);
	b = 2 * (local.origin.x * view->ray.direction.x +
			local.origin.z * view->ray.direction.z);
	c = pow(local.origin.x, 2) + pow(local.origin.z, 2) - pow(cyli->r, 2);
	//printf("a %f b %f c %f\n", a, b, c);
	if ((delt = pow(b, 2) - 4 * a * c) < 0)
		return (cyli->dist = 0);
	cyli->hit_1 = (-b - sqrt(delt)) / (2 * a);
	cyli->hit_2 = (-b + sqrt(delt)) / (2 * a);
	cyli->dist = smallest_non_negativ(cyli->hit_1, cyli->hit_2);
	if (cyli->dist < 0)
		return (cyli->dist = 0);
	fill_inter_cyli(light, cyli, inter, view);
	return (1);
}
