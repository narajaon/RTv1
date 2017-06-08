/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 18:43:12 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/08 18:36:28 by narajaon         ###   ########.fr       */
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

typedef struct		s_view
{
	int				x;
	int				y;
	int				z;
	unsigned int	dist;
}					t_view;

typedef struct		s_pix
{
	int				x;
	int				y;
	int				z;
	unsigned int	col;
}					t_pix;

typedef struct		s_sphere
{
	int				r;
	int				x;
	int				y;
	int				z;
	unsigned int	col;
}					t_sphere;

typedef struct		s_prim
{
	double			x;
	double			y;
	double			z;
	double			dist_min;
}					t_prim;

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
	unsigned int	scene;
	void			*mlx;
	void			*win;
	void			*key;
	void			*mouse;
	t_img			img;
	t_pix			pix;
	t_sphere		sphere;
	t_view			view;
	t_prim			prim;
}					t_env;

int		error_msg(int error);
void	check_sphere(t_env *e);
void	print_rt(t_env *e);
#endif
