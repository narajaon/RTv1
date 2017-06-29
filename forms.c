#include "rtv1.h"

void	check_collision(t_env *e)
{
	int		xy;
	double	plane;
	double	sphere;
	double	cyli;

	init_inter(&e->inter);
	init_ray(&e->view, &e->pix);
	xy = e->pix.y * WIN_Y + e->pix.x;
	is_plane(&e->view, &e->plane, &e->light, &e->inter);
	is_sphere(&e->view, &e->sphere, &e->light, &e->inter);
	is_cyli(&e->view, &e->cyli, &e->light, &e->inter);
	plane = e->plane.dist;
	sphere = e->sphere.dist;
	cyli = e->cyli.dist;
//	if ((sphere > plane && sphere > 0) || (sphere > 0 && plane < RAY_MIN))
//	printf("cyli %f\n", cyli);
	//	e->img.img[xy] = e->inter.col.i;
	if (sphere > 0)
		e->img.img[xy] = e->inter.col.i;
	//if ((plane > RAY_MIN && sphere < plane) ||
	//		(plane > RAY_MIN && sphere < 0))
	else if (plane > RAY_MIN)
		e->img.img[xy] = e->inter.col.i;
	else if (cyli > 0.00001)
		e->img.img[xy] = e->inter.col.i;
	else
		e->img.img[xy] = 0x00000000;
}
