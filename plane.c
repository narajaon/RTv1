#include "rtv1.h"

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
