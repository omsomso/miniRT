/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:52:43 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/28 12:40:05 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	calculate_selected_bckg(t_data *data, t_pos mouse_pos)
{
	int		obj_count;
	float	obj_selected;

	obj_selected = 0;
	obj_count = count_objects(data->objects) + 2;
	obj_selected = (mouse_pos.x / GUI_EL_WIDTH);
		obj_selected = obj_selected + ((mouse_pos.y / GUI_EL_HEIGHT) \
		* (GUI_MAX_WIDTH / GUI_EL_WIDTH));
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

int	cut_values_int(int *a, int max_a, int min_a)
{
	if (*a > max_a)
		*a = max_a;
	if (*a < min_a)
		*a = min_a;
	return (*a);
}

float	cut_values(float *a, float max_a, float min_a)
{
	if (*a > max_a)
		*a = max_a;
	if (*a < min_a)
		*a = min_a;
	return (*a);
}

int	modify_sphere(t_data *data, t_sphere *sphere, int button, int sel_param)
{
	if (sel_param == 1 && button == 4)
		sphere->center->x += RESIZE_AMOUNT;
	else if (sel_param == 1 && button == 5)
		sphere->center->x -= RESIZE_AMOUNT;
	else if (sel_param == 2 && button == 4)
		sphere->center->y += RESIZE_AMOUNT;
	else if (sel_param == 2 && button == 5)
		sphere->center->y -= RESIZE_AMOUNT;
	else if (sel_param == 3 && button == 4)
		sphere->center->z += RESIZE_AMOUNT;
	else if (sel_param == 3 && button == 5)
		sphere->center->z -= RESIZE_AMOUNT;
	else if (sel_param == 4 && button == 4)
		sphere->radius += RESIZE_AMOUNT;
	else if (sel_param == 4 && button == 5)
		sphere->radius -= RESIZE_AMOUNT;
	else if (sel_param)
		return (1);
	cut_values(&sphere->radius, 100000, 0.1);
	return (0);
}

int	rotate_plane(t_data *data, t_plane *plane, int button, int sel_param)
{
	if (sel_param == 5 && button == 4)
		plane->normal_vec->x += RESIZE_AMOUNT;
	else if (sel_param == 5 && button == 5)
		plane->normal_vec->x -= RESIZE_AMOUNT;
	else if (sel_param == 6 && button == 4)
		plane->normal_vec->y += RESIZE_AMOUNT;
	else if (sel_param == 6 && button == 5)
		plane->normal_vec->y -= RESIZE_AMOUNT;
	else if (sel_param == 7 && button == 4)
		plane->normal_vec->z += RESIZE_AMOUNT;
	else if (sel_param == 7 && button == 5)
		plane->normal_vec->z -= RESIZE_AMOUNT;
	else if (sel_param)
		return (1);
	cut_values(&plane->normal_vec->x, 1, -1);
	cut_values(&plane->normal_vec->y, 1, -1);
	cut_values(&plane->normal_vec->z, 1, -1);
	return (0);
}

int	modify_plane(t_data *data, t_plane *plane, int button, int sel_param)
{
	int	mod;

	mod = 0;
	if (sel_param == 1 && button == 4)
		mod = plane->point->x += RESIZE_AMOUNT;
	else if (sel_param == 1 && button == 5)
		mod = plane->point->x -= RESIZE_AMOUNT;
	else if (sel_param == 2 && button == 4)
		mod = plane->point->y += RESIZE_AMOUNT;
	else if (sel_param == 2 && button == 5)
		mod = plane->point->y -= RESIZE_AMOUNT;
	else if (sel_param == 3 && button == 4)
		mod = plane->point->z += RESIZE_AMOUNT;
	else if (sel_param == 3 && button == 5)
		mod = plane->point->z -= RESIZE_AMOUNT;
	return (mod += (rotate_plane(data, plane, button, sel_param)));
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

int	modify_cylinder_b(t_data *data, t_cylinder *cy, int button, int sel)
{
	if (sel == 5 && button == 4)
		cy->normal_vec->x += RESIZE_AMOUNT;
	else if (sel == 5 && button == 5)
		cy->normal_vec->x -= RESIZE_AMOUNT;
	else if (sel == 6 && button == 4)
		cy->normal_vec->y += RESIZE_AMOUNT;
	else if (sel == 6 && button == 5)
		cy->normal_vec->y -= RESIZE_AMOUNT;
	else if (sel == 7 && button == 4)
		cy->normal_vec->z += RESIZE_AMOUNT;
	else if (sel == 7 && button == 5)
		cy->normal_vec->z -= RESIZE_AMOUNT;
	else if (sel == 8 && button == 4)
		cy->height += RESIZE_AMOUNT;
	else if (sel == 8 && button == 5)
		cy->height -= RESIZE_AMOUNT;
	cut_values(&cy->normal_vec->x, 1, -1);
	cut_values(&cy->normal_vec->y, 1, -1);
	cut_values(&cy->normal_vec->z, 1, -1);
	cut_values(&cy->diameter, 100000, 0.1);
	cut_values(&cy->height, 100000, 0.1);
	return (0);
}

int	modify_cylinder(t_data *data, t_cylinder *cy, int button, int sel)
{
	if (sel == 1 && button == 4)
		cy->center->x += RESIZE_AMOUNT;
	else if (sel == 1 && button == 5)
		cy->center->x -= RESIZE_AMOUNT;
	else if (sel == 2 && button == 4)
		cy->center->y += RESIZE_AMOUNT;
	else if (sel == 2 && button == 5)
		cy->center->y -= RESIZE_AMOUNT;
	else if (sel == 3 && button == 4)
		cy->center->z += RESIZE_AMOUNT;
	else if (sel == 3 && button == 5)
		cy->center->z -= RESIZE_AMOUNT;
	else if (sel == 4 && button == 4)
		cy->radius += RESIZE_AMOUNT;
	else if (sel == 4 && button == 5)
		cy->radius -= RESIZE_AMOUNT;
	modify_cylinder_b(data, cy, button, sel);
	return (0);
}

int	modify_light(t_data *data, int button, int sel)
{
	if (sel == 1 && button == 4)
		data->light->pos->x += RESIZE_AMOUNT;
	else if (sel == 1 && button == 5)
		data->light->pos->x -= RESIZE_AMOUNT;
	else if (sel == 2 && button == 4)
		data->light->pos->y += RESIZE_AMOUNT;
	else if (sel == 2 && button == 5)
		data->light->pos->y -= RESIZE_AMOUNT;
	else if (sel == 3 && button == 4)
		data->light->pos->z += RESIZE_AMOUNT;
	else if (sel == 3 && button == 5)
		data->light->pos->z -= RESIZE_AMOUNT;
	return (0);
}

int	modify_camera(t_data *data, int button, int sel)
{
	if (sel == 1 && button == 4)
		data->camera->pos->x += RESIZE_AMOUNT;
	else if (sel == 1 && button == 5)
		data->camera->pos->x -= RESIZE_AMOUNT;
	else if (sel == 2 && button == 4)
		data->camera->pos->y += RESIZE_AMOUNT;
	else if (sel == 2 && button == 5)
		data->camera->pos->y -= RESIZE_AMOUNT;
	else if (sel == 3 && button == 4)
		data->camera->pos->z += RESIZE_AMOUNT;
	else if (sel == 3 && button == 5)
		data->camera->pos->z -= RESIZE_AMOUNT;
	else if (sel == 4 && button == 4)
		data->camera->fov += 2;
	else if (sel == 4 && button == 5)
		data->camera->fov -= 2;
	cut_values_int(&data->camera->fov, 180, 0);
	return (0);
}

int	modify_objects(t_data *data, t_pos mouse_pos, int button)
{
	t_object	*obj;
	int			sel_par;
	int			sel_obj_id;
	int			mod;

	sel_par = 0;
	sel_par = calculate_selected_param(data, mouse_pos);
	if (sel_par && (button == 4 || button == 5))
	{
		sel_obj_id = calculate_selected_bckg(data, mouse_pos);
		obj = find_object(data->objects, sel_obj_id);
		if (sel_obj_id == count_objects(data->objects) - 1)
			modify_light(data, button, sel_par);
		else if (sel_obj_id == count_objects(data->objects))
			modify_camera(data, button, sel_par);
		else if (obj->type == SPHERE)
			mod = modify_sphere(data, obj->object, button, sel_par);
		else if (obj->type == PLANE)
			mod = modify_plane(data, obj->object, button, sel_par);
		else if (obj->type == CYLINDER)
			mod = modify_cylinder(data, obj->object, button, sel_par);
	}
	// if (!mod)
		// printf("modified param %d of object %d\n", sel_par, sel_obj_id);
	return (mod);
}

void	conditional_retrace(t_data *data, int button)
{
	if (data->auto_retrace)
	{
		generate_rays(data);
		draw_gui(data, (t_pos){0, 0});
	}
	else
	{
		if (button == 2)
			generate_rays(data);
	}
	// generate_rays(data);
}

int handle_mouse(int button, int x, int y, t_data *data)
{
	t_pos		mouse_pos;
	int			sel_param;
	int			mod;

	mouse_pos.x = x;
	mouse_pos.y = y;
	mod = 0;
	// printf("Mouse button %d pressed at %d, %d\n", button, x, y);
	mod = modify_objects(data, mouse_pos, button);
	draw_gui(data, mouse_pos);
	conditional_retrace(data, button);
	// generate_rays(data);
	// if (!mod)
	return (0);
}

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
	mlx_string_put(m->ptr, m->win_gui, p.x + 10, p.y + 15, 0xFFFFFF, s);
	free(s);
	return (0);
}

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

	slider_pos.x = 10 * ((pos.x * 100) / GUI_EL_WIDTH) + GUI_EL_WIDTH / 2;
	cut_values(&slider_pos.x, 80, 5);
	slider_pos.y = 10 * ((pos.y * 100) / GUI_EL_WIDTH) + GUI_EL_WIDTH / 2;
	cut_values(&slider_pos.y, 80, 5);
	slider_pos.z = 10 * ((pos.z * 100) / GUI_EL_WIDTH) + GUI_EL_WIDTH / 2;
	cut_values(&slider_pos.z, 80, 5);
	return (slider_pos);
}

t_v3	calculate_rot_sliders(t_gui *gui, t_v3 normal_vec)
{
	t_v3	slider_pos;

	slider_pos.x = normal_vec.x * 50 + 50;
	cut_values(&slider_pos.x, 80, 5);
	slider_pos.y = normal_vec.y * 50 + 50;
	cut_values(&slider_pos.y, 80, 5);
	slider_pos.z = normal_vec.z * 50 + 50;
	cut_values(&slider_pos.z, 80, 5);
	return (slider_pos);
}

int	draw_pos_sliders(t_gui *gui, t_pics *pics, t_v3 pos_sliders)
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
	mlx_put_image_to_window(m->ptr, m->win_gui, pics->slider, p.x, y + 20);
	mlx_put_image_to_window(m->ptr, m->win_gui, pics->slider, p.y, y + 30);
	mlx_put_image_to_window(m->ptr, m->win_gui, pics->slider, p.z, y + 40);
	return (0);
}

int	draw_rot_sliders(t_gui *gui, t_pics *pics, t_v3 rot_sliders)
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
	mlx_put_image_to_window(m->ptr, m->win_gui, pics->slider, p.x, y + 60);
	mlx_put_image_to_window(m->ptr, m->win_gui, pics->slider, p.y, y + 70);
	mlx_put_image_to_window(m->ptr, m->win_gui, pics->slider, p.z, y + 80);
	return (0);
}

int	draw_radius_slider(t_gui *gui, t_pics *pics, float radius)
{
	t_mlx	*m;
	float	pos;
	int		x;
	int		y;

	m = gui->mlx;
	x = gui->draw_pos.x;
	y = gui->draw_pos.y + 50;
	pos = ((radius * GUI_MAX_WIDTH) / GUI_EL_WIDTH);
	cut_values(&pos, 80, 5);
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 10, 0x8A8A8A, "RADIUS");
	mlx_put_image_to_window(m->ptr, m->win_gui, pics->slider, x + pos, y);
	return (0);
}

int	draw_wh_sliders(t_gui *gui, t_mlx *m, int w, int h)
{
	int		x;
	int		y;
	float	pw;
	float	ph;

	x = gui->draw_pos.x;
	y = gui->draw_pos.y;
	pw = w * 10 + gui->draw_pos.x;
	ph = h * 10 + gui->draw_pos.x;
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 60, 0x8A8A8A, "WIDTH");
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 100, 0x8A8A8A, "HEIGHT");
	mlx_put_image_to_window(m->ptr, m->win_gui, gui->pics->slider, pw, y + 50);
	mlx_put_image_to_window(m->ptr, m->win_gui, gui->pics->slider, ph, y + 90);
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
	rot_sliders = calculate_rot_sliders(gui, get_rot_cylinder(cylinder));
	draw_object_name(gui, " - CYLINDER ", id);
	draw_pos_sliders(gui, gui->pics, pos_sliders);
	draw_rot_sliders(gui, gui->pics, rot_sliders);
	draw_wh_sliders(gui, gui->mlx, cylinder->radius, cylinder->height);
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
	draw_pos_sliders(gui, gui->pics, pos_sliders);
	draw_rot_sliders(gui, gui->pics, rot_sliders);
	return (0);
}

int	draw_sp_ctrls(t_gui *gui, int id)
{
	char	*s;
	float	radius;
	t_v3	pos_sliders;
	t_sphere	*sphere;

	sphere = gui->objects->object;
	pos_sliders = calculate_pos_sliders(gui, get_pos_sphere(sphere));
	draw_object_name(gui, " - SPHERE ", id);
	draw_pos_sliders(gui, gui->pics, pos_sliders);
	draw_radius_slider(gui, gui->pics, sphere->radius);
	return (0);
}

int	count_objects(t_object *objects)
{
	int			count;
	t_object	*obj;

	count = 2;
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

t_gui	*init_gui_struct(t_data *data, t_pos mouse_pos)
{
	t_gui	*gui;

	gui = malloc(sizeof(t_gui));
	if (!gui)
		return (NULL);
	if (mouse_pos.x < 0 || mouse_pos.y < 0)
		return (NULL);
	gui->data = data;
	gui->mouse_pos = mouse_pos;
	gui->pics = data->pics;
	gui->sel_bckg = calculate_selected_bckg(data, gui->mouse_pos);
	if (gui->sel_bckg < 0)
		return (NULL);
	gui->objects = data->objects;
	gui->mlx = data->mlx;
	gui->draw_pos.x = 0;
	gui->draw_pos.y = 0;
	gui->obj_count = count_objects(gui->objects);
	return (gui);
}

int	draw_gui_loop(t_gui *gui)
{
	int	obj_id;

	obj_id = 0;
	while (gui->objects)
	{
		obj_id++;
		draw_background(gui, gui->mlx, obj_id);
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
	return (0);
}

t_v3	get_light_pos(t_light *light)
{
	t_v3	pos;

	pos.x = light->pos->x;
	pos.y = light->pos->y;
	pos.z = light->pos->z;
	return (pos);
}

t_v3	get_camera_pos(t_camera *camera)
{
	t_v3	pos;

	pos.x = camera->pos->x;
	pos.y = camera->pos->y;
	pos.z = camera->pos->z;
	return (pos);
}

int	draw_light(t_light *light, t_gui *gui, t_mlx *m)
{
	t_v3	pos_sliders;
	t_v3	light_pos;
	t_pos	p;

	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	draw_background(gui, m, gui->obj_count - 1);
	light_pos = get_light_pos(light);
	pos_sliders = calculate_pos_sliders(gui, light_pos);
	mlx_string_put(m->ptr, m->win_gui, p.x + 10, p.y + 15, 0xFFFFFF, "LIGHT");
	draw_pos_sliders(gui, gui->pics, pos_sliders);
	gui->draw_pos.x += GUI_EL_WIDTH;
	if (gui->draw_pos.x >= GUI_MAX_WIDTH)
	{
		gui->draw_pos.x = 0;
		gui->draw_pos.y += GUI_EL_HEIGHT;
	}
	return (0);
}

int	draw_camera(t_camera *camera, t_gui *gui, t_mlx *m)
{
	t_v3	pos_sliders;
	t_v3	camera_pos;
	t_pos	p;

	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	draw_background(gui, m, gui->obj_count);
	camera_pos = get_camera_pos(camera);
	pos_sliders = calculate_pos_sliders(gui, camera_pos);
	mlx_string_put(m->ptr, m->win_gui, p.x + 10, p.y + 15, 0xFFFFFF, "CAMERA");
	draw_pos_sliders(gui, gui->pics, pos_sliders);
	mlx_string_put(m->ptr, m->win_gui, p.x + 10, p.y + 60, 0x8A8A8A, "FOV");
	mlx_put_image_to_window(m->ptr, m->win_gui, gui->pics->slider, p.x, p.y + 50);
	return (0);
}

int	draw_gui(t_data *data, t_pos mouse_pos)
{
	t_gui	*gui;

	gui = init_gui_struct(data, mouse_pos);
	if (!gui)
		return (1);
	mlx_clear_window(data->mlx->ptr, data->mlx->win_gui);
	draw_gui_loop(gui);
	draw_light(data->light, gui, data->mlx);
	draw_camera(data->camera, gui, data->mlx);
	free(gui);
	return (0);
}
