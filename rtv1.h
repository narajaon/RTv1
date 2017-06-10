/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 18:43:12 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/10 19:19:25 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <math.h>
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <stdio.h>

# define WIN_X 800
# define WIN_Y 800

/*view coordinates*/

typedef struct		s_view
{
	double				x;
	double				y;
	double				z;
	unsigned int		dist;
}					t_view;

/*pixel coordinates*/

typedef struct		s_pix
{
	int					x;
	int					y;
	int					z;
	unsigned int		col;
}					t_pix;

/*sphere coordinates*/

typedef struct		s_sphere
{
	double				r;
	double				x;
	double				y;
	double				z;
	double				k;
	double				a;
	double				b;
	double				c;
	unsigned int		col;
}					t_sphere;

/*plan coordinates*/

typedef struct		s_plan
{
	double				x;
	double				y;
	double				z;
	double				k;
	unsigned int		col;
}					t_plan;

/*primary ray coordinates*/

typedef struct		s_prim
{
	double			x;
	double			y;
	double			z;
	double			dist_min;
	unsigned int	col;
}					t_prim;

/*shadow ray coordinates*/

typedef struct		s_shad
{
	double			x;
	double			y;
	double			z;
	unsigned int	col;
}					t_shad;

typedef struct		s_img
{
	void			*img_ptr;
	int				*img;
	int				bpp;
	int				size_line;
	int			endian;
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
	int				scene;
}					t_env;

int		error_msg(int error);
void	is_sphere(t_env *e);
void	check_collision(t_env *e);
void	print_rt(t_env *e);
#endif
