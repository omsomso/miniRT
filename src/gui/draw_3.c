/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:36:41 by kpawlows          #+#    #+#             */
/*   Updated: 2023/10/07 14:10:53 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gui.h"

// Draws object rotation names and values
int	draw_rot_data(t_gui *gui, t_mlx *m, t_pos obj_ang_offset)
{
	char	*ang_x;
	char	*ang_y;
	char	*ang_z;
	t_pos	p;

	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	ang_x = ft_itoa(obj_ang_offset.x);
	ang_y = ft_itoa(obj_ang_offset.y);
	ang_z = ft_itoa(obj_ang_offset.z);
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 70, COL_GREY_L, "ANG X");
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 80, COL_GREY_L, "ANG Y");
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 90, COL_GREY_L, "ANG Z");
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 70, COL_GREY_D, ang_x);
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 80, COL_GREY_D, ang_y);
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 90, COL_GREY_D, ang_z);
	free(ang_x);
	free(ang_y);
	free(ang_z);
	return (0);
}

// Draws object position names and values
int	draw_pos_data(t_gui *gui, t_mlx *m, t_v3 pos)
{
	int		x;
	int		y;
	char	*s[3];

	x = gui->draw_pos.x;
	y = gui->draw_pos.y;
	s[0] = ft_ftoa(pos.x);
	s[1] = ft_ftoa(pos.y);
	s[2] = ft_ftoa(pos.z);
	mlx_string_put(m->ptr, m->win_gui, x, y + 30, COL_GREY_L, "POS X");
	mlx_string_put(m->ptr, m->win_gui, x, y + 40, COL_GREY_L, "POS Y");
	mlx_string_put(m->ptr, m->win_gui, x, y + 50, COL_GREY_L, "POS Z");
	mlx_string_put(m->ptr, m->win_gui, x + DM, y + 30, COL_GREY_D, s[0]);
	mlx_string_put(m->ptr, m->win_gui, x + DM, y + 40, COL_GREY_D, s[1]);
	mlx_string_put(m->ptr, m->win_gui, x + DM, y + 50, COL_GREY_D, s[2]);
	free(s[0]);
	free(s[1]);
	free(s[2]);
	return (0);
}

// Draws name on the ui
int	draw_object_name(t_gui *gui, char *name, int id)
{
	t_mlx	*m;
	t_pos	p;
	char	*id_str;
	char	*s;

	m = gui->mlx;
	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	id_str = ft_itoa(id);
	s = ft_strjoin_ff(id_str, name);
	if (!s)
		return (1);
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 16, COL_WHITE, s);
	free(s);
	return (0);
}

// Draws object position names and values
int	draw_rot_data_cam(t_gui *gui, t_mlx *m, t_pos obj_ang_offset)
{
	char	*ang_x;
	char	*ang_y;
	t_pos	p;

	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	ang_x = ft_itoa(obj_ang_offset.x);
	ang_y = ft_itoa(obj_ang_offset.y);
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 70, COL_GREY_L, "ANG X");
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 80, COL_GREY_L, "ANG Y");
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 70, COL_GREY_D, ang_x);
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 80, COL_GREY_D, ang_y);
	free(ang_x);
	free(ang_y);
	return (0);
}
