#include "rtv1.h"

int		is_cyli(t_view *view, t_cyli *cyli, t_pix *pix)
{
	return (0);
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
