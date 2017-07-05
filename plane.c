#include "rtv1.h"

unsigned int	put_col_plane(t_light *light, t_inter *inter, t_plane *plane)
{
	t_col		col;
	double		b;
	double		g;
	double		r;

	b = clamp_col(plane->col.tab[0], inter->cos_alph, light->col.tab[0]) * 255;
	g = clamp_col(plane->col.tab[1], inter->cos_alph, light->col.tab[1]) * 255;
	r = clamp_col(plane->col.tab[2], inter->cos_alph, light->col.tab[2]) * 255;
	init_col(&inter->col, r, g, b);
	inter->col.i = mult_col(&inter->col, &light->col);
	return (inter->col.i);
}

void			fill_inter_plane(t_light *light, t_plane *plane,
		t_inter *inter, t_view *view)
{
	t_coor		norm_plane;
	t_coor		norm_dir;
	t_coor		view_norm;

	point_on_ray(&view->ray.origin, &view->ray.direction,
			&inter->ray.origin, plane->dist);
	dot_sub(&light->coord, &inter->ray.origin, &inter->ray.direction);
	normalize(&plane->norm, &norm_plane);
	normalize(&inter->ray.direction, &norm_dir);
	inter->cos_alph = dot_prod(&norm_plane, &norm_dir);
	inter->col.i = put_col_plane(light, inter, plane);
	inter->shape = PLANE;
	inter->dist_min = plane->dist;
	printf("inter->col plane %x\n", inter->col.i);
}

int				is_plane(t_view *view, t_plane *plane,
		t_light *light, t_inter *inter)
{
	double		dv;
	double		xv;
	double		t;
	t_coor		x_point;

	dot_sub(&plane->center, &view->ray.origin, &x_point);
	dv = dot_prod(&view->ray.direction, &plane->norm);
	if (fabs(dv) < 0.00001)
		return (plane->dist = 0);
	xv = dot_prod(&x_point, &plane->norm);
//	printf("xv %f\n", xv);
//	print_coord(&plane->norm);
//	printf("dv %f\n", dv);
	t = -xv / dv;
//	printf("dn %f\n", dn);
	//printf("t %f\n", t);
	plane->dist = t;
	if (t <= RAY_MIN || t >= RAY_MAX)
		return (plane->dist = 0);
	printf("plane->dist %f dist_min %f\n", plane->dist, inter->dist_min);
	if (plane->dist < inter->dist_min)
		fill_inter_plane(light, plane, inter, view);
	return (plane->dist);
}
