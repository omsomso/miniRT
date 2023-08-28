/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:52:43 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/28 02:19:53 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	calculate_selected_bckg(t_data *data, t_pos mouse_pos)
{
	int		obj_count;
	float	obj_selected;

	obj_selected = 0;
	obj_count = count_objects(data->objects);
	obj_selected = (mouse_pos.x / GUI_EL_WIDTH);
		obj_selected = obj_selected + ((mouse_pos.y / GUI_EL_HEIGHT) * (GUI_MAX_WIDTH / GUI_EL_WIDTH));
	if (obj_selected > obj_count)
		return (-1);
	return (obj_selected + 1);
}

t_object *find_object(t_object *obj, int id)
{
	int	count;

	count = 0;
	while (obj)
	{
		count++;
		if (count == id)
			return (obj);
		obj = obj->next;
	}
	return (NULL);
}

int	modify_sphere(t_data *data, t_sphere *sphere, int button, int sel_param)
{
	if (sel_param == 1 && button == 4)
		sphere->center->x += RESIZE_AMOUNT;
	if (sel_param == 1 && button == 5)
		sphere->center->x -= RESIZE_AMOUNT;
	if (sel_param == 2 && button == 4)
		sphere->center->y += RESIZE_AMOUNT;
	if (sel_param == 2 && button == 5)
		sphere->center->y -= RESIZE_AMOUNT;
	if (sel_param == 3 && button == 4)
		sphere->center->z += RESIZE_AMOUNT;
	if (sel_param == 3 && button == 5)
		sphere->center->z -= RESIZE_AMOUNT;
	if (sel_param == 4 && button == 4)
		sphere->radius += RESIZE_AMOUNT;
	if (sel_param == 4 && button == 5)
	{
		if (sphere->radius < RESIZE_AMOUNT)
			sphere->radius = 0.1;
		else
			sphere->radius -= RESIZE_AMOUNT;
	}
	return (0);
}

float	cut_values(float *a, float max_a, float min_a)
{
	if (*a > max_a)
		*a = max_a;
	if (*a < min_a)
		*a = min_a;
	return (*a);
}

int	rotate_plane(t_data *data, t_plane *plane, int button, int sel_param)
{
	if (sel_param == 5 && button == 4)
		plane->normal_vec->x += RESIZE_AMOUNT;
	if (sel_param == 5 && button == 5)
		plane->normal_vec->x -= RESIZE_AMOUNT;
	if (sel_param == 6 && button == 4)
		plane->normal_vec->y += RESIZE_AMOUNT;
	if (sel_param == 6 && button == 5)
		plane->normal_vec->y -= RESIZE_AMOUNT;
	if (sel_param == 7 && button == 4)
		plane->normal_vec->z += RESIZE_AMOUNT;
	if (sel_param == 7 && button == 5)
		plane->normal_vec->z -= RESIZE_AMOUNT;
	cut_values(&plane->normal_vec->x, 1, -1);
	cut_values(&plane->normal_vec->y, 1, -1);
	cut_values(&plane->normal_vec->z, 1, -1);
	return (0);
}

int	modify_plane(t_data *data, t_plane *plane, int button, int sel_param)
{
	if (sel_param == 1 && button == 4)
		plane->point->x += RESIZE_AMOUNT;
	if (sel_param == 1 && button == 5)
		plane->point->x -= RESIZE_AMOUNT;
	if (sel_param == 2 && button == 4)
		plane->point->y += RESIZE_AMOUNT;
	if (sel_param == 2 && button == 5)
		plane->point->y -= RESIZE_AMOUNT;
	if (sel_param == 3 && button == 4)
		plane->point->z += RESIZE_AMOUNT;
	if (sel_param == 3 && button == 5)
		plane->point->z -= RESIZE_AMOUNT;
	rotate_plane(data, plane, button, sel_param);
	return (0);
}

int	calculate_selected_param(t_data *data, t_pos mouse_pos)
{
	float	sel_param;
	float	sel_row;

	sel_row = 0;
	while (sel_row * GUI_EL_HEIGHT < mouse_pos.y)
		sel_row++;
	sel_row--;
	sel_param = (mouse_pos.y - (sel_row * GUI_EL_HEIGHT)) / 10;
	sel_param -= 1;
	return (sel_param);
}

int	rotate_cylinder(t_data *data, t_cylinder *cylinder, int button, int sel_param)
{
	if (sel_param == 6 && button == 4)
		cylinder->normal_vec->x += RESIZE_AMOUNT;
	if (sel_param == 6 && button == 5)
		cylinder->normal_vec->x -= RESIZE_AMOUNT;
	if (sel_param == 7 && button == 4)
		cylinder->normal_vec->y += RESIZE_AMOUNT;
	if (sel_param == 7 && button == 5)
		cylinder->normal_vec->y -= RESIZE_AMOUNT;
	if (sel_param == 8 && button == 4)
		cylinder->normal_vec->z += RESIZE_AMOUNT;
	if (sel_param == 8 && button == 5)
		cylinder->normal_vec->z -= RESIZE_AMOUNT;
	cut_values(&cylinder->normal_vec->x, 1, -1);
	cut_values(&cylinder->normal_vec->y, 1, -1);
	cut_values(&cylinder->normal_vec->z, 1, -1);
	return (0);
}

int	modify_cylinder(t_data *data, t_cylinder *cylinder, int button, int sel_param)
{
	if (sel_param == 1 && button == 4)
		cylinder->center->x += RESIZE_AMOUNT;
	if (sel_param == 1 && button == 5)
		cylinder->center->x -= RESIZE_AMOUNT;
	if (sel_param == 2 && button == 4)
		cylinder->center->y += RESIZE_AMOUNT;
	if (sel_param == 2 && button == 5)
		cylinder->center->y -= RESIZE_AMOUNT;
	if (sel_param == 3 && button == 4)
		cylinder->center->z += RESIZE_AMOUNT;
	if (sel_param == 3 && button == 5)
		cylinder->center->z -= RESIZE_AMOUNT;
	if (sel_param == 4 && button == 4)
		cylinder->diameter += RESIZE_AMOUNT;
	if (sel_param == 4 && button == 5)
			cylinder->diameter -= RESIZE_AMOUNT;
	cut_values(&cylinder->diameter, 0.1, 100000);
	if (sel_param == 5 && button == 4)
		cylinder->height += RESIZE_AMOUNT;
	cut_values(&cylinder->height, 0.1, 100000);
	rotate_cylinder(data, cylinder, button, sel_param);
	return (0);
}

int	modify_objects(t_data *data, t_pos mouse_pos, int button)
{
	t_object	*found_obj;
	int			sel_param;
	int			selected_obj;

	sel_param = calculate_selected_param(data, mouse_pos);
	if (sel_param && (button == 4 || button == 5))
	{
		selected_obj = calculate_selected_bckg(data, mouse_pos);
		found_obj = find_object(data->objects, selected_obj);
		if (!found_obj)
		return (1);
		printf("modyfying param %d of object %d\n", sel_param, selected_obj);
		if (sel_param >= 1 && sel_param <= 4 && found_obj->type == SPHERE)
			modify_sphere(data, found_obj->object, button, sel_param);
		if (sel_param >= 1 && sel_param <= 7 && found_obj->type == PLANE)
			modify_plane(data, found_obj->object, button, sel_param);
		if (found_obj->type == CYLINDER)
			modify_cylinder(data, found_obj->object, button, sel_param);
			
	}
	return (0);
}

int handle_mouse(int button, int x, int y, t_data *data)
{
	t_pos		mouse_pos;
	int			sel_param;

	mouse_pos.x = x;
	mouse_pos.y = y;
	// printf("Mouse button %d pressed at %d, %d\n", button, x, y);
	modify_objects(data, mouse_pos, button);
	draw_gui(data, mouse_pos);
	generate_rays(data);
	return (0);
}

int	draw_button(t_data *data, int x, int y)
{
	mlx_put_image_to_window(data->mlx->ptr, data->mlx->win_gui, data->mlx->slider, x, y);
	return (0);
}

int	draw_object_name(t_gui *gui, char *name, int id)
{
	char	*id_str;
	char	*s;

	id_str = ft_itoa(id);
	s = ft_strjoin_ff(id_str, name);
	if (!s)
		return (1);
	mlx_string_put(gui->mlx->ptr, gui->mlx->win_gui, gui->draw_pos.x + 10, gui->draw_pos.y + 15, 0xFFFFFF, s);
	free(s);
	// mlx_string_put(data->mlx->ptr, data->mlx->win_gui, x, y, 0xFFFFFF, "SPHERE");
	return (0);
}

int	draw_background(t_gui *gui, int obj_id)
{
	if (obj_id == gui->sel_bckg)
		mlx_put_image_to_window(gui->mlx->ptr, gui->mlx->win_gui, gui->mlx->sel, gui->draw_pos.x, gui->draw_pos.y);
	else
		mlx_put_image_to_window(gui->mlx->ptr, gui->mlx->win_gui, gui->mlx->bckg, gui->draw_pos.x, gui->draw_pos.y);
	// printf("bckg draw_pos.x: %d\n", gui->draw_pos.x);
	return (0);
}

t_v3	get_pos_sphere(t_sphere *sphere)
{
	t_v3	pos;

	pos.x = sphere->center->x;
	pos.y = sphere->center->y;
	pos.z = sphere->center->z;
	return (pos);
}

t_v3	get_pos_plane(t_plane *plane)
{
	t_v3	pos;

	pos.x = plane->point->x;
	pos.y = plane->point->y;
	pos.z = plane->point->z;
	return (pos);
}

t_v3	get_pos_cylinder(t_cylinder *cylinder)
{
	t_v3	pos;

	pos.x = cylinder->center->x;
	pos.y = cylinder->center->y;
	pos.z = cylinder->center->z;
	return (pos);
}

t_v3	get_rot_plane(t_plane *plane)
{
	t_v3	rot;

	rot.x = plane->normal_vec->x;
	rot.y = plane->normal_vec->y;
	rot.z = plane->normal_vec->z;
	return (rot);
}

t_v3	get_rot_cylinder(t_cylinder *cylinder)
{
	t_v3	rot;

	rot.x = cylinder->normal_vec->x;
	rot.y = cylinder->normal_vec->y;
	rot.z = cylinder->normal_vec->z;
	return (rot);
}

t_v3	calculate_pos_sliders(t_gui *gui, t_v3 pos)
{
	t_v3	slider_pos;

	slider_pos.x = 4 * ((pos.x * 100) / GUI_EL_WIDTH) + GUI_EL_WIDTH / 2;
	cut_values(&slider_pos.x, GUI_EL_WIDTH - GUI_EL_MARGIN, 0);
	slider_pos.y = 4 * ((pos.y * 100) / GUI_EL_WIDTH) + GUI_EL_WIDTH / 2;
	cut_values(&slider_pos.x, GUI_EL_WIDTH - GUI_EL_MARGIN, 0);
	slider_pos.z = 4 * ((pos.z * 100) / GUI_EL_WIDTH) + GUI_EL_WIDTH / 2;
	cut_values(&slider_pos.x, GUI_EL_WIDTH - GUI_EL_MARGIN, 0);
	return (slider_pos);
}

t_v3	calculate_rot_sliders(t_gui *gui, t_v3 normal_vec)
{
	t_v3	slider_pos;

	slider_pos.x = normal_vec.x * 50 + 50;
	cut_values(&slider_pos.x, GUI_EL_WIDTH - GUI_EL_MARGIN, 0);
	slider_pos.y = normal_vec.y * 50 + 50;
	cut_values(&slider_pos.y, GUI_EL_WIDTH - GUI_EL_MARGIN, 0);
	slider_pos.z = normal_vec.z * 50 + 50;
	cut_values(&slider_pos.z, GUI_EL_WIDTH - GUI_EL_MARGIN, 0);
	return (slider_pos);
}

int	draw_pos_sliders(t_gui *gui, t_v3 pos_sliders)
{
	t_mlx	*m;
	t_v3	p;
	int		x;
	int		y;

	x = gui->draw_pos.x;
	y = gui->draw_pos.y;
	p.x = gui->draw_pos.x + pos_sliders.x;
	p.y = gui->draw_pos.x + pos_sliders.y;
	p.z = gui->draw_pos.x + pos_sliders.z;
	m = gui->mlx;
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 30, 0x8A8A8A, "POS X");
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 40, 0x8A8A8A, "POS Y");
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 50, 0x8A8A8A, "POS Z");
	mlx_put_image_to_window(m->ptr, m->win_gui, m->slider, p.x, y + 20);
	mlx_put_image_to_window(m->ptr, m->win_gui, m->slider, p.y, y + 30);
	mlx_put_image_to_window(m->ptr, m->win_gui, m->slider, p.z, y + 40);
	return (0);
}

int	draw_rot_sliders(t_gui *gui, t_v3 rot_sliders)
{
	t_mlx	*m;
	t_v3	p;
	int		x;
	int		y;

	m = gui->mlx;
	x = gui->draw_pos.x;
	y = gui->draw_pos.y;
	p.x = gui->draw_pos.x + rot_sliders.x;
	p.y = gui->draw_pos.x + rot_sliders.y;
	p.z = gui->draw_pos.x + rot_sliders.z;
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 70, 0x8A8A8A, "ROT X");
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 80, 0x8A8A8A, "ROT Y");
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 90, 0x8A8A8A, "ROT Z");
	mlx_put_image_to_window(m->ptr, m->win_gui, m->slider, p.x, y + 60);
	mlx_put_image_to_window(m->ptr, m->win_gui, m->slider, p.y, y + 70);
	mlx_put_image_to_window(m->ptr, m->win_gui, m->slider, p.z, y + 80);
	return (0);
}

int	draw_radius_slider(t_gui *gui, float radius)
{
	t_mlx	*m;
	float	pos;
	int		x;
	int		y;

	m = gui->mlx;
	x = gui->draw_pos.x;
	y = gui->draw_pos.y;
	pos = ((radius * GUI_MAX_WIDTH) / GUI_EL_WIDTH);
	cut_values(&pos, GUI_MAX_WIDTH - GUI_EL_MARGIN, 0);
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 60, 0x8A8A8A, "RADIUS");
	mlx_put_image_to_window(m->ptr, m->win_gui, m->slider, x + pos, y + 50);
	return (0);
}

int	draw_wh_sliders(t_gui *gui, t_mlx *m, int w, int h)
{
	int		x;
	int		y;
	int		pw;
	int		ph;
	
	x = gui->draw_pos.x;
	y = gui->draw_pos.y;
	pw = ((w * GUI_MAX_WIDTH) / GUI_EL_WIDTH);
	ph = ((h * GUI_MAX_WIDTH) / GUI_EL_WIDTH);
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 60, 0x8A8A8A, "WIDTH");
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 100, 0x8A8A8A, "HEIGHT");
	mlx_put_image_to_window(m->ptr, m->win_gui, m->slider, x, y + 50);
	mlx_put_image_to_window(m->ptr, m->win_gui, m->slider, x, y + 90);
	return (0);
}

int	draw_cy_ctrls(t_gui *gui, int id)
{
	char		*s;
	t_v3		pos_sliders;
	t_v3		rot_sliders;
	t_cylinder	*cylinder;

	cylinder = gui->objects->object;
	pos_sliders = calculate_pos_sliders(gui, get_pos_cylinder(cylinder));
	rot_sliders = calculate_pos_sliders(gui, get_rot_cylinder(cylinder));
	draw_object_name(gui, " - CYLINDER ", id);
	draw_pos_sliders(gui, pos_sliders);
	draw_rot_sliders(gui, pos_sliders);
	draw_wh_sliders(gui, gui->mlx, cylinder->diameter, cylinder->height);
	return (0);
}

int	draw_pl_ctrls(t_gui *gui, int id)
{
	char	*s;
	t_v3	pos_sliders;
	t_v3	rot_sliders;
	t_plane	*plane;

	plane = gui->objects->object;
	pos_sliders = calculate_pos_sliders(gui, get_pos_plane(plane));
	rot_sliders = calculate_rot_sliders(gui, get_rot_plane(plane));
	draw_object_name(gui, " - PLANE ", id);
	draw_pos_sliders(gui, pos_sliders);
	draw_rot_sliders(gui, rot_sliders);
	// draw_radius_slider(gui, sphere->radius);
	return (0);
}

int	draw_sp_ctrls(t_gui *gui, int id)
{
	char	*s;
	float	radius;
	t_v3	pos_sliders;
	// t_v3	rot_sliders;
	t_sphere	*sphere;

	sphere = gui->objects->object;
	pos_sliders = calculate_pos_sliders(gui, get_pos_sphere(sphere));
	draw_object_name(gui, " - SPHERE ", id);
	draw_pos_sliders(gui, pos_sliders);
	draw_radius_slider(gui, sphere->radius);
	return (0);
}

int	count_objects(t_object *objects)
{
	int			count;
	t_object	*obj;

	count = 0;
	obj = objects;
	while (obj)
	{
		count++;
		obj = obj->next;
	}
	return (count);
}

int	calculate_gui_height(int obj_count)
{
	int	height;

	height = 0;
	while (obj_count > 0)
	{
		obj_count -= (GUI_MAX_WIDTH / GUI_EL_WIDTH);
		height += GUI_EL_HEIGHT;
	}
	return (height);
}

int	calculate_gui_width(int obj_count)
{
	int	width;

	width = 0;
	while (obj_count > 0 && width < GUI_MAX_WIDTH)
	{
		obj_count -= 1;
		width += GUI_EL_WIDTH;
	}
	return (width);
}

t_gui	*init_gui_struct(t_data *data, int mouse_x, int mouse_y)
{
	t_gui	*gui;

	gui = malloc(sizeof(t_gui));
	if (!gui)
		return (NULL);
	gui->mouse_pos.x = mouse_x;
	gui->mouse_pos.y = mouse_y;
	gui->sel_bckg = calculate_selected_bckg(data, gui->mouse_pos);
	if (gui->sel_bckg < 0)
		return (NULL);
	gui->objects = data->objects;
	gui->mlx = data->mlx;
	gui->draw_pos.x = 0;
	gui->draw_pos.y = 0;
	return (gui);
}

int	draw_gui(t_data *data, t_pos mouse_pos)
{
	t_pos		draw_pos;
	int			sel;
	int			obj_id;

	t_gui	*gui;
	gui = init_gui_struct(data, mouse_pos.x, mouse_pos.y);
	if (!gui)
		return (1);
	// data->mlx->sphere = mlx_xpm_file_to_image(data->mlx->ptr, "assets/sph.xpm", &x, &y);
	// data->mlx->sphere = mlx_png_file_to_image(data->mlx->ptr, "assets/sphere.png", &x, &y);
	if (mouse_pos.x < 0 || mouse_pos.y < 0)
		return (1);
	obj_id = 0;	
	while (gui->objects)
	{
		obj_id++;
		draw_background(gui, obj_id);
		if (gui->objects->type == SPHERE)
			draw_sp_ctrls(gui, obj_id);
		else if (gui->objects->type == PLANE)
			draw_pl_ctrls(gui, obj_id);
		else if (gui->objects->type == CYLINDER)
			draw_cy_ctrls(gui, obj_id);
		gui->objects = gui->objects->next;
		gui->draw_pos.x += GUI_EL_WIDTH;

		if (gui->draw_pos.x >= GUI_MAX_WIDTH)
		{
			gui->draw_pos.x = 0;
			gui->draw_pos.y += GUI_EL_HEIGHT;
		}
	}
	obj_id = 0;
	return (0);
}
