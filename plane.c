#include "rtv1.h"

void			fill_inter_plane(t_light *light, t_plane *plane,
		t_inter *inter, t_ray *view)
{
	t_coor		norm_plane;
	t_coor		norm_dir;
	t_coor		view_norm;

	point_on_ray(&view->origin, &view->direction,
			&inter->ray.origin, plane->dist);
	dot_sub(&light->coord, &inter->ray.origin, &inter->ray.direction);
	normalize(&plane->norm, &norm_plane);
	normalize(&inter->ray.direction, &norm_dir);
	inter->cos_alph = dot_prod(&norm_plane, &norm_dir);
	inter->col.i = put_col(light, inter, &plane->col);
	inter->shape = PLANE;
	inter->dist_min = plane->dist;
//	printf("inter->col plane %x\n", inter->col.i);
}

int				is_plane(t_ray *view, t_plane *plane,
		t_light *light, t_inter *inter)
{
	double		dv;
	double		xv;
	double		t;
	t_coor		x_point;

	dot_sub(&plane->center, &view->origin, &x_point);
	dv = dot_prod(&view->direction, &plane->norm);
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
//	printf("plane->dist %f dist_min %f\n", plane->dist, inter->dist_min);
	if (plane->dist < inter->dist_min)
		fill_inter_plane(light, plane, inter, view);
	return (plane->dist);
}
