/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:36:41 by kpawlows          #+#    #+#             */
/*   Updated: 2023/09/01 22:48:11 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gui.h"

// Gets and draws plane parameters on ui window
int	draw_pl_ctrls(t_gui *gui, t_plane *plane, int id)
{
	draw_object_name(gui, " PLANE ", id);
	draw_pos_data(gui, gui->mlx, get_pos_plane(plane));
	draw_rot_data(gui, gui->mlx, plane->pl_ang_offset);
	return (0);
}

// Gets and draws name and value of sphere radius
int	draw_sp_radius(t_gui *gui, t_mlx *m, float radius)
{
	char	*value;
	t_pos	p;

	value = ft_ftoa(radius);
	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y + 50;
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 10, COL_GREY_L, "RAD");
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 10, COL_GREY_D, value);
	free(value);
	return (0);
}

// Gets and draws sphere parameters on ui window
int	draw_sp_ctrls(t_gui *gui, t_sphere *sphere, int id)
{
	draw_object_name(gui, " SPHERE ", id);
	draw_pos_data(gui, gui->mlx, get_pos_sphere(sphere));
	draw_sp_radius(gui, gui->mlx, sphere->radius);
	return (0);
}

// Gets and draws cylinder parameters on ui window
int	draw_cy_ctrls(t_gui *gui, t_cylinder *cylinder, int id)
{
	t_v3		pos_cylinder;
	t_mlx		*m;
	t_pos		p;
	char		*s[2];

	m = gui->mlx;
	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	pos_cylinder = get_pos_cylinder(cylinder);
	s[0] = ft_ftoa (cylinder->radius);
	s[1] = ft_ftoa (cylinder->height);
	draw_object_name(gui, " CYLINDER ", id);
	draw_pos_data(gui, gui->mlx, pos_cylinder);
	draw_rot_data(gui, gui->mlx, cylinder->cy_ang_offset);
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 60, COL_GREY_L, "WIDTH");
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 60, COL_GREY_D, s[0]);
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 100, COL_GREY_L, "HGHT");
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 100, COL_GREY_D, s[1]);
	free(s[0]);
	free(s[1]);
	return (0);
}

// Gets and draws light parameters
int	draw_light_ctrls(t_light *light, t_gui *gui, t_mlx *m)
{
	t_v3	light_pos;
	t_pos	p;

	draw_background(gui, m, gui->obj_count - 1);
	gui->draw_pos.x += GUI_EL_MARGIN;
	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	light_pos = get_light_pos(light);
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 16, COL_WHITE, "LIGHT");
	draw_pos_data(gui, gui->mlx, light_pos);
	gui->draw_pos.x -= GUI_EL_MARGIN;
	wrap_gui(gui);
	return (0);
}
