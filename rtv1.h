/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 18:43:12 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/14 13:41:07 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <math.h>
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <stdio.h>

# define WIN_X 500
# define WIN_Y 500
# define EX_KEY 53
# define UP_KEY 126
# define DOWN_KEY 125
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define W_KEY 13
# define R_KEY 15
# define Q_KEY 12
# define E_KEY 14
# define RAY_MIN 0.0001f
# define RAY_MAX INFINITY

# define PLANE 0
# define SPHERE 1
# define CONE 0

typedef struct		s_coor
{
	double			x;
	double			y;
	double			z;
}					t_coor;

/*intersection point infos*/

typedef struct		s_inter
{
	t_coor			inter;
	float			dist;
	int				shape;
}					t_inter;

/*ray origin, direction coordinates && length*/

typedef struct		s_ray
{
	t_coor			origin;
	t_coor			direction;
	t_inter			inter;
	double			len;
}					t_ray;

/*view coordinates*/

typedef struct		s_view
{
	t_coor			coord;
	t_ray			ray;
	t_inter			inter;
	unsigned int	dist;
}					t_view;

/*sphere coordinates*/

typedef struct		s_sphere
{
	t_coor			coord;
	double			r;
	double			hit_1;
	double			hit_2;
	float			hit;
	unsigned int	col;
}					t_sphere;

typedef struct		s_plane
{
	t_coor			center;
	t_coor			norm;
	t_coor			hit_p;
	unsigned int	col;
}					t_plane;

typedef struct		s_shapes
{
	void			*shap_tab[4]; //shape pointers
	void			*does_inter[4]; //fun pointers
	int				nb_shapes;
}					t_shapes;

typedef struct		s_img
{
	void			*img_ptr;
	int				*img;
	int				bpp;
	int				size_line;
	int				endian;
}					t_img;

/*pixel coordinates*/

typedef struct		s_pix
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	col;
}					t_pix;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*key;
	void			*mouse;
	t_img			img;
	t_pix			pix;
	t_plane			plane;
	t_view			view;
	t_sphere		sphere;
	double			rot_y;
	double			rot_z;
}					t_env;

int					error_msg(int error);
void				print_coord(t_coor *coord); //attention printf

int					rot_view(int keycode, t_env *e);
int					rot_view(int keycode, t_env *e);
void				rot_x(double *x, double *y, double *z, double angle);
void				rot_y(double *x, double *y, double *z, double angle);
void				rot_z(double *x, double *y, double *z, double angle);

void				cross_prod(t_coor *a, t_coor *b, t_coor *tmp);
void				dot_sub(t_coor *a, t_coor *b, t_coor *tmp);
void				dot_sum(t_coor *a, t_coor *b, t_coor *tmp);
void				dot_mult(t_coor *a, t_coor *tmp, double nb);
void				dot_cpy(t_coor *src, t_coor *dst);
void				normalize(t_coor *a, t_coor *tmp);
void				point_on_ray(t_coor *ori, t_coor *dir, t_coor *res, float len);
void				fill_coord(t_coor *coord, float x, float y, float z);
double				dot_prod(t_coor *a, t_coor *b);
double				vect_len(t_coor *a);

void				init_sphere(t_sphere *sphere);
void				init_view(t_view *view);
void				init_plane(t_plane *plane);
void				init_ray(t_view *view, t_pix *pix);

void				check_collision(t_env *e);
void				print_rt(t_env *e);
#endif
