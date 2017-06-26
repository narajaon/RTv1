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
	//printf("plane col %x\n", plane->col.i);
	//printf("inter col %x\n", inter->col.i);
	//printf("cos alph %f\n", inter->cos_alph);
	//printf("b %f g %f r %f\n", b, g, r);
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
	//printf("inter->col %x\n", inter->col.i);
}

int				is_plane(t_view *view, t_plane *plane,
		t_light *light, t_inter *inter)
{
	double		dn;
	double		ppn;
	double		prn;
	double		t;
	t_coor		tmp;
	t_coor		hit;

	dn = dot_prod(&view->ray.direction, &plane->norm);
//	print_coord(&plane->norm);
//	print_coord(&view->ray.direction);
	if (dn < 0.00001)
		return (plane->dist = 0);
//	printf("dn %f\n", dn);
	ppn = dot_prod(&plane->center, &plane->norm);
	prn = dot_prod(&view->ray.origin, &plane->norm);
	t = (ppn - prn) / dn;
	//printf("t %f\n", t);
	if (t <= RAY_MIN || t >= RAY_MAX)
		return (plane->dist = 0);
	plane->dist = t;
//	printf("plane->dist %f\n", plane->dist);
	fill_inter_plane(light, plane, inter, view);
	return (1);
}
