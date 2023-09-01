/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:36:41 by kpawlows          #+#    #+#             */
/*   Updated: 2023/09/01 22:01:16 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gui.h"

// Gets and draws camera parameters
int	draw_camera_ctrls(t_camera *camera, t_gui *gui, t_mlx *m)
{
	t_v3	camera_pos;
	t_pos	p;
	char	*fov_s;

	draw_background(gui, m, gui->obj_count);
	gui->draw_pos.x += GUI_EL_MARGIN;
	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 60, COL_GREY_L, "FOV");
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 16, COL_WHITE, "CAMERA");
	fov_s = ft_itoa(camera->fov);
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 60, COL_GREY_D, fov_s);
	free(fov_s);
	camera_pos = get_camera_pos(camera);
	draw_pos_data(gui, gui->mlx, camera_pos);
	draw_rot_data_cam(gui, gui->mlx, gui->cam_ang_offset);
	gui->draw_pos.x -= GUI_EL_MARGIN;
	wrap_gui(gui);
	return (0);
}

// Draws selection highlight on the ui
int	draw_sel_param_bckg(t_gui *gui, t_mlx *m, int id)
{
	t_pos	p;

	if (id == gui->sel_bckg && gui->sel_par >= 1 && gui->sel_par <= 8)
	{
		p.x = gui->draw_pos.x;
		p.y = gui->draw_pos.y + 10 + (gui->sel_par * 10);
		mlx_put_image_to_window(m->ptr, m->win_gui, \
		gui->pics->sel_p, p.x, p.y);
	}
	return (0);
}

// Draws background for each object on the ui
int	draw_background(t_gui *gui, t_mlx *m, int obj_id)
{
	t_pics	*pics;
	int		x;
	int		y;

	pics = gui->pics;
	x = gui->draw_pos.x;
	y = gui->draw_pos.y;
	if (obj_id == gui->sel_bckg)
		mlx_put_image_to_window(m->ptr, m->win_gui, pics->sel, x, y);
	else
		mlx_put_image_to_window(m->ptr, m->win_gui, pics->bckg, x, y);
	draw_sel_param_bckg(gui, gui->mlx, obj_id);
	return (0);
}

// Fills background of empty ui space
void	fill_background(t_gui *gui, t_mlx *m)
{
	int		el_per_row;
	t_pos	p;

	p.y = gui->draw_pos.y;
	p.x = gui->draw_pos.x;
	while (p.x < GUI_MAX_WIDTH)
	{
		mlx_put_image_to_window(m->ptr, m->win_gui, gui->pics->empty, p.x, p.y);
		p.x += GUI_EL_WIDTH;
	}
}
