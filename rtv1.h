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

# define NONE 0
# define PLANE 1
# define SPHERE 2
# define CONE 3
# define CYLI 4

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

/*ray origin, direction coordinates && length*/

typedef struct		s_ray
{
	t_coor			origin;
	t_coor			direction;
	double			len;
}					t_ray;

/*intersection point infos*/

typedef struct		s_inter
{
	t_ray			ray;
	t_coor			norm;
	t_col			col;
	unsigned int	shape;
	double			cos_alph;
	double			dist_min;
}					t_inter;

/*view coordinates*/

typedef struct		s_view
{
	t_inter			inter;
	t_ray			ray;
	t_coor			coord;
	unsigned int	dist;
	double			rot_y;
	double			rot_z;
}					t_view;

typedef struct		s_light
{
	t_coor			coord;
	t_col			col;
	double			intens;
}					t_light;

/*sphere coordinates*/

typedef struct		s_sphere
{
	t_coor			coord;
	t_coor			norm;
	t_col			col;
	double			r;
	double			hit_1;
	double			hit_2;
	double			dist;
}					t_sphere;

typedef struct		s_plane
{
	t_coor			center;
	t_coor			norm;
	t_col			col;
	double			dist;
}					t_plane;

typedef struct		s_cyli
{
	t_coor			cap;
	t_col			col;
	double			r;
	double			l;
	double			hit_1;
	double			hit_2;
	double			dist;
}					t_cyli;

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
	t_cyli			cyli;
	t_light			light;
	t_inter			inter;
	double			rot_y;
	double			rot_z;
}					t_env;

int					error_msg(int error);
void				print_coord(t_coor *coord); //attention printf
double				smallest_non_negativ(double a, double b);

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

void				init_sphere(t_sphere *sphere);
void				init_view(t_view *view);
void				init_plane(t_plane *plane);
void				init_ray(t_view *view, t_pix *pix);
void				init_cyli(t_cyli *cyli);
void				init_light(t_light *light);
void				init_inter(t_inter *inter);
void				init_col(t_col *col, char r, char g, char b);

int					is_sphere(t_view *view, t_sphere *sphere,
		t_light *light, t_inter *inter);
int					is_plane(t_view *view, t_plane *plane,
		t_light *light, t_inter *inter);
int					is_cyli(t_view *view, t_cyli *cyli, t_pix *pix);

void				init_col(t_col *col, char r, char g, char b);
int					mult_col(t_col *col1, t_col *col2); //absorbtion
int					add_col(t_col *col1, t_col *col2); //mixing 2 colours
int					div_col_int(t_col *col1, double cap);
double				clamp_col(double col, double cos, char light);

void				check_collision(t_env *e);
void				print_rt(t_env *e);
void				do_rt(t_env *e);
#endif
