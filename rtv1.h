/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:31:31 by narajaon          #+#    #+#             */
/*   Updated: 2017/07/24 18:50:24 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <math.h>
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"

# define WIN_X 700
# define WIN_Y 700
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
# define SP_KEY 49
# define PAG_UP_KEY 116
# define PAG_DOWN_KEY 121

# define RAY_MIN 0.0001f
# define RAY_MAX 5000
# define PI 3.141592

# define NONE 0
# define PLANE 1
# define SPHERE 2
# define CONE 3
# define CYLI 4
# define AMBIENT 0.5
# define SPEED 1

# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00
# define WHITE 0x00FFFFFF

typedef struct		s_coor
{
	double			x;
	double			y;
	double			z;
}					t_coor;

typedef union		u_col
{
	unsigned int	i;
	char			tab[4];
}					t_col;

typedef struct		s_ray
{
	t_coor			origin;
	t_coor			direction;
	double			len;
}					t_ray;

typedef struct		s_inter
{
	t_ray			ray;
	t_coor			norm;
	t_col			col;
	unsigned int	shape;
	double			cos_alph;
	double			dist_min;
}					t_inter;

typedef struct		s_view
{
	t_inter			inter;
	t_ray			ray;
	t_coor			coord;
	unsigned int	dist;
	double			rot_x;
	double			rot_y;
	double			rot_z;
	double			x_value;
	double			y_value;
	double			z_value;
}					t_view;

typedef struct		s_light
{
	t_coor			coord;
	t_col			col;
	double			ambient;
}					t_light;

typedef struct		s_sphere
{
	t_coor			coord;
	t_coor			norm;
	t_col			col;
	double			r;
	double			hit_1;
	double			hit_2;
	double			dist;
	double			a;
	double			b;
	double			c;
	double			delt;
	unsigned int	place;
}					t_sphere;

typedef struct		s_plane
{
	t_coor			center;
	t_coor			norm;
	t_col			col;
	double			dist;
	unsigned int	place;
}					t_plane;

typedef struct		s_cyli
{
	t_coor			center;
	t_coor			cap_u;
	t_coor			norm;
	t_coor			hei;
	t_col			col;
	double			r;
	double			hit_1;
	double			hit_2;
	double			dist;
	double			a;
	double			b;
	double			c;
	double			delt;
	unsigned int	place;
}					t_cyli;

typedef struct		s_cone
{
	t_coor			center;
	t_coor			vertex;
	t_coor			norm;
	t_coor			hei;
	t_col			col;
	double			r;
	double			hit_1;
	double			hit_2;
	double			dist;
	double			angle;
	double			a;
	double			b;
	double			c;
	double			delt;
	unsigned int	place;
}					t_cone;

typedef struct		s_img
{
	void			*img_ptr;
	int				*img;
	int				bpp;
	int				size_line;
	int				endian;
}					t_img;

typedef struct		s_pix
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	col;
	unsigned int	decal;
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
	t_list			*spheres;
	t_list			*cylinders;
	t_list			*cones;
	t_list			*planes;
	t_sphere		sphere;
	t_cyli			cyli;
	t_cone			cone;
	t_light			light;
	t_inter			inter;
	int				fd;
}					t_env;

int					error_msg(int error);
void				print_coord(t_coor *coord);
double				smallest_non_negativ(double a, double b);
void				free_tab(char **tab);
void				free_list(t_list **shape);
void				exit_rt(t_env *e);

void				get_values(int fd, t_env *e);
void				ft_lstback(t_list **alst, void const *content, size_t size);

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
void				point_on_ray(t_coor *ori, t_coor *dir,
		t_coor *res, double len);
void				fill_coord(t_coor *coord, double x, double y, double z);
double				dot_prod(t_coor *a, t_coor *b);
double				vect_len(t_coor *a);
double				vect_pow(t_coor *a);
void				vect_project(t_coor *a, t_coor *b, t_coor *res);

void				init_cone(t_cone *cone);
void				init_sphere(t_sphere *sphere);
void				init_view(t_view *view);
void				init_plane(t_plane *plane);
void				init_ray(t_view *view, t_pix *pix);
void				init_cyli(t_cyli *cyli);
void				init_light(t_light *light);
void				init_inter(t_inter *inter);
void				init_col(t_col *col, char r, char g, char b);

int					is_sphere(t_ray *view, t_sphere *sphere,
		t_light *light, t_inter *inter);
int					is_plane(t_ray *view, t_plane *plane,
		t_light *light, t_inter *inter);
int					is_cyli(t_ray *view, t_cyli *cyli,
		t_light *light, t_inter *inter);
int					is_cone(t_ray *view, t_cone *cone,
		t_light *light, t_inter *inter);

void				closest_sphere(t_list *spheres, t_env *e);
void				closest_cylinder(t_list *cylinders, t_env *e);
void				closest_cone(t_list *cones, t_env *e);
void				closest_plane(t_list *planes, t_env *e);

double				shad_sphere(t_ray *view, t_sphere *sphere);
double				shad_cone(t_ray *view, t_cone *cone);
double				shad_cyli(t_ray *view, t_cyli *cyli);
double				shad_plane(t_ray *view, t_plane *plane);
double				check_shadow_sphere(t_list *spheres, t_env *e);
double				check_shadow_cylinder(t_list *cylinders, t_env *e);
double				check_shadow_cone(t_list *cones, t_env *e);
double				check_shadow_plane(t_list *planes, t_env *e);

void				fill_inter_sphere(t_light *light, t_sphere *sphere,
		t_inter *inter, t_ray *view);
void				fill_inter_cone(t_light *light, t_cone *cone,
		t_inter *inter, t_ray *view);
void				fill_inter_cyli(t_light *light, t_cyli *cyli,
		t_inter *inter, t_ray *view);
void				fill_inter_plane(t_light *light, t_plane *plane,
		t_inter *inter, t_ray *view);

void				sphere_values(int fd, t_sphere *sphere, t_list **list);
void				plane_values(int fd, t_plane *plane, t_list **list);
void				cone_values(int fd, t_cone *cone, t_list **list);
void				cyli_values(int fd, t_cyli *cyli, t_list **list);
void				view_values(int fd, t_view *view);
void				light_values(int fd, t_light *light);
void				get_coord(t_coor *coord, char **buff);
void				get_shape_col(t_col *col, char **buff);

void				init_col(t_col *col, char r, char g, char b);
int					mult_col(t_col *col1, t_col *col2);
int					add_col(t_col *col1, t_col *col2);
int					div_col_int(t_col *col1, double cap);
double				clamp_col(double col, double cos);
unsigned int		put_col(t_light *light, t_inter *inter, t_col *plane);
unsigned int		shad_col(t_inter *inter, int shape, t_light *light);

int					check_collision(t_env *e);
void				print_rt(t_env *e);
void				do_rt(t_env *e, int fd);
#endif
