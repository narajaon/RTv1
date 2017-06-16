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
#define EX_KEY 53
#define UP_KEY 126
#define DOWN_KEY 125
#define LEFT_KEY 123
#define RIGHT_KEY 124
#define A_KEY 0
#define S_KEY 1
#define D_KEY 2
#define W_KEY 13
#define R_KEY 15
#define Q_KEY 12
#define E_KEY 14

typedef struct		s_coor
{
	double			x;
	double			y;
	double			z;
}					t_coor;

/*shadow ray coordinates*/

typedef struct		s_shad
{
	t_coor				coord;
	unsigned int	col;
}					t_shad;

/*view coordinates*/

typedef struct		s_view
{
	t_coor			coord;
	unsigned int	dist;
}					t_view;

/*pixel coordinates*/

typedef struct		s_pix
{
	t_coor			coord;
	unsigned int	col;
}					t_pix;

/*sphere coordinates*/

typedef struct		s_sphere
{
	t_coor			coord;
	double			r;
	double			k;
	double			k1;
	double			k2;
	double			delt;
	unsigned int	col;
	t_shad			shadow;
}					t_sphere;

/*plan coordinates*/

typedef struct		s_plan
{
	double			k;
	unsigned int	col;
	t_coor			coord;
	t_shad			shadow;
}					t_plan;

/*primary ray coordinates*/

typedef struct		s_prim
{
	t_coor			coord;
	double			dist_min;
	unsigned int	col;
}					t_prim;

/*light source coordinates*/

typedef struct		s_light
{
	t_coor			coord;
}					t_light;

typedef struct		s_img
{
	void			*img_ptr;
	int				*img;
	int				bpp;
	int				size_line;
	int				endian;
}					t_img;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*key;
	void			*mouse;
	t_img			img;
	t_pix			pix;
	t_view			view;
	t_prim			prim;
	t_sphere		sphere;
	t_plan			plan;
	t_shad			shad;
	t_light			light1;
	double			rot_y;
	double			rot_z;
	int				scene;
}					t_env;

int		error_msg(int error);
void	is_sphere(t_env *e);
void	check_collision(t_env *e);
void	print_rt(t_env *e);
int		rot_view(int keycode, t_env *e);
void	rot_x(double *x, double *y, double *z, double angle);
void	rot_y(double *x, double *y, double *z, double angle);
void	rot_z(double *x, double *y, double *z, double angle);
int		rot_view(int keycode, t_env *e);
void	init_sphere(t_env *e);
void	init_plan(t_env *e);
void	init_view1(t_env *e);
void	init_shad(t_env *e, unsigned int col);
void	init_prim(t_env *e);
void	init_light1(t_env *e);
void	is_sphere(t_env *e);
void	is_plan(t_env *e);
void	do_rt(t_env *e);
double	dot_prod(t_coor *a, t_coor *b);
double	vect_len(t_coor *a);
void	cross_prod(t_coor *a, t_coor *b, t_coor *tmp);
void	dot_sub(t_coor *a, t_coor *b, t_coor *tmp);
void	dot_sum(t_coor *a, t_coor *b, t_coor *tmp);
void	dot_mult(t_coor *a, t_coor *tmp, double nb);
void		vect_norm(t_coor *a, t_coor *tmp, double len_a);
#endif
