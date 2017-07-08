#include "rtv1.h"

void		get_coord(t_coor *coord, char **buff)
{
	char	*tmp;
	char	**tab_coord;

	tmp = *buff;
	while (*tmp != ' ' && *tmp)
		tmp++;
	tab_coord = ft_strsplit(tmp, ' ');
	coord->x = ft_atoi(tab_coord[0]);
	coord->y = ft_atoi(tab_coord[1]);
	coord->z = ft_atoi(tab_coord[2]);
	free_tab(tab_coord);
}

void		get_shape_col(t_col *col, char **buff)
{
	char	*tmp;
	char	**tab_col;

	tmp = *buff;
	while (*tmp != ' ' && *tmp)
		tmp++;
	tab_col = ft_strsplit(tmp, ' ');
	if (!ft_strcmp(tab_col[0], "RED"))
		col->i = RED;
	else if (!ft_strcmp(tab_col[0], "GREEN"))
		col->i = GREEN;
	else if (!ft_strcmp(tab_col[0], "YELLOW"))
		col->i = YELLOW;
	else if (!ft_strcmp(tab_col[0], "WHITE"))
		col->i = WHITE;
	else
		error_msg(3);
	free_tab(tab_col);
}

void		parse_plane(t_plane *plane, char **buff)
{
	char	**tab_line;

	tab_line = ft_strsplit(*buff, ' ');
	if (!ft_strcmp(tab_line[0], "center"))
		get_coord(&plane->center, buff);
	else if (!ft_strcmp(tab_line[0], "colour"))
		get_shape_col(&plane->col, buff);
	else if (!ft_strcmp(tab_line[0], "direction"))
		get_coord(&plane->norm, buff);
	else if (ft_strcmp(tab_line[0], "}"))
		error_msg(3);
	free_tab(tab_line);
}

void		plane_values(int fd, t_plane *plane)
{
	char	*buff;

	get_next_line(fd, &buff);
	//printf("plane %s\n", buff);
	while (!ft_strchr(buff, '}'))
	{
		get_next_line(fd, &buff);
		parse_plane(plane, &buff);
	}
}

void		parse_view(t_view *view, char **buff)
{
	char	**tab_line;

	tab_line = ft_strsplit(*buff, ' ');
	if (!ft_strcmp(tab_line[0], "center"))
		get_coord(&view->coord, buff);
	else if (ft_strcmp(tab_line[0], "}"))
		error_msg(3);
	free_tab(tab_line);
}

void		view_values(int fd, t_view *view)
{
	char	*buff;

	get_next_line(fd, &buff);
	//printf("view  %s\n", buff);
	while (!ft_strchr(buff, '}') && buff)
	{
		get_next_line(fd, &buff);
		parse_view(view, &buff);
	}
}

void		parse_cyli(t_cyli *cyli, char **buff)
{
	char	**tab_line;

	tab_line = ft_strsplit(*buff, ' ');
	if (!ft_strcmp(tab_line[0], "center"))
		get_coord(&cyli->center, buff);
	else if (!ft_strcmp(tab_line[0], "direction"))
		get_coord(&cyli->cap_u, buff);
	else if (!ft_strcmp(tab_line[0], "colour"))
		get_shape_col(&cyli->col, buff);
	else if (!ft_strcmp(tab_line[0], "width"))
		cyli->r = ft_atoi(tab_line[1]);
	else if (ft_strcmp(tab_line[0], "}"))
		error_msg(3);
	free_tab(tab_line);
}

void		cyli_values(int fd, t_cyli *cyli)
{
	char	*buff;

	get_next_line(fd, &buff);
	//printf("cyli %s\n", buff);
	while (!ft_strchr(buff, '}') && buff)
	{
		get_next_line(fd, &buff);
		parse_cyli(cyli, &buff);
	}
}

void		parse_cone(t_cone *cone, char **buff)
{
	char	**tab_line;

	tab_line = ft_strsplit(*buff, ' ');
	if (!ft_strcmp(tab_line[0], "center"))
		get_coord(&cone->center, buff);
	else if (!ft_strcmp(tab_line[0], "direction"))
		get_coord(&cone->vertex, buff);
	else if (!ft_strcmp(tab_line[0], "colour"))
		get_shape_col(&cone->col, buff);
	else if (!ft_strcmp(tab_line[0], "angle"))
		cone->angle = tan(ft_atoi(tab_line[1]) * PI / 180);
	else if (ft_strcmp(tab_line[0], "}"))
		error_msg(3);
	free_tab(tab_line);
}

void		cone_values(int fd, t_cone *cone)
{
	char	*buff;

	get_next_line(fd, &buff);
	//printf("cone %s\n", buff);
	while (!ft_strchr(buff, '}') && buff)
	{
		get_next_line(fd, &buff);
		parse_cone(cone, &buff);
	}
}

void		parse_sphere(t_sphere *sphere, char **buff)
{
	char	**tab_line;

	tab_line = ft_strsplit(*buff, ' ');
	if (!ft_strcmp(tab_line[0], "center"))
		get_coord(&sphere->coord, buff);
	else if (!ft_strcmp(tab_line[0], "colour"))
		get_shape_col(&sphere->col, buff);
	else if (!ft_strcmp(tab_line[0], "width"))
		sphere->r = ft_atoi(tab_line[1]);
	else if (ft_strcmp(tab_line[0], "}"))
		error_msg(3);
	free_tab(tab_line);
}

void		sphere_values(int fd, t_sphere *sphere)
{
	char	*buff;

	get_next_line(fd, &buff);
	//printf("sphere %s\n", buff);
	while (!ft_strchr(buff, '}') && buff)
	{
		get_next_line(fd, &buff);
		parse_sphere(sphere, &buff);
	}
}

void		parse_light(t_light *light, char **buff)
{
	char	**tab_line;

	tab_line = ft_strsplit(*buff, ' ');
	if (!ft_strcmp(tab_line[0], "center"))
		get_coord(&light->coord, buff);
	else if (!ft_strcmp(tab_line[0], "colour"))
		get_shape_col(&light->col, buff);
	else if (ft_strcmp(tab_line[0], "}"))
		error_msg(3);
	free_tab(tab_line);
}

void		light_values(int fd, t_light *light)
{
	char	*buff;

	get_next_line(fd, &buff);
	//printf("light %s\n", buff);
	while (!ft_strchr(buff, '}') && buff)
	{
		get_next_line(fd, &buff);
		parse_light(light, &buff);
	}
}

void		get_values(int fd, t_env *e)
{
	char	*buff;

	while (get_next_line(fd, &buff) > 0)
	{
		if (!ft_strcmp(buff, "view"))
			view_values(fd, &e->view);
		else if (!ft_strcmp(buff, "plane"))
			plane_values(fd, &e->plane);
		else if (!ft_strcmp(buff, "cylinder"))
			cyli_values(fd, &e->cyli);
		else if (!ft_strcmp(buff, "cone"))
			cone_values(fd, &e->cone);
		else if (!ft_strcmp(buff, "sphere"))
			sphere_values(fd, &e->sphere);
		else if (!ft_strcmp(buff, "light"))
			light_values(fd, &e->light);
	}
}
