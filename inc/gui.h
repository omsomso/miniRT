/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:22:41 by kpawlows          #+#    #+#             */
/*   Updated: 2023/09/26 16:05:39 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "minirt.h"

int			gui(t_data *data, t_gui *gui, t_pos mouse_pos, int button);
int			modify_objects(t_data *data, t_gui *gui, int button);
int			draw_gui(t_data *data, t_gui *gui);
int			draw_gui_loop(t_gui *gui);
void		conditional_retrace(t_data *data, int button);

int			find_selected_param(t_pos mouse_pos);
int			find_selected_ui_element(t_data *data, t_pos mouse_pos);
t_object	*find_object(t_object *obj, int id);
void		wrap_gui(t_gui *gui);
int			count_objects(t_object *objects);
int			compute_gui_height(int obj_count);
int			compute_gui_width(int obj_count);
t_gui		*update_gui_struct(t_data *data, t_gui *gui, t_pos mouse_pos);
t_gui		*init_gui_struct(t_data *data);

void		modify_camera_b(t_data *data, t_gui *gui, int button, int sel);
void		modify_camera(t_data *data, t_gui *gui, int button, int sel);
void		modify_cylinder_c(t_cylinder *cy, int button, int sel);
void		modify_cylinder_b(t_cylinder *cy, int button, int sel);
void		modify_cylinder(t_cylinder *cy, int button, int sel);
void		modify_plane_c(t_gui *gui, t_plane *plane, int button, int sel);
void		modify_plane_b(t_gui *gui, t_plane *plane, int button, int sel);
void		modify_plane(t_gui *gui, t_plane *plane, int button, int sel);
void		modify_sphere(t_sphere *sphere, int button, int sel_param);
void		modify_light(t_data *data, int button, int sel);

t_v3		get_pos_sphere(t_sphere *sphere);
t_v3		get_pos_plane(t_plane *plane);
t_v3		get_pos_cylinder(t_cylinder *cylinder);
t_v3		get_light_pos(t_light *light);
t_v3		get_camera_pos(t_camera *camera);
t_v3		get_rot_plane(t_plane *plane);
t_v3		get_rot_cylinder(t_cylinder *cylinder);

int			draw_pl_ctrls(t_gui *gui, t_plane *plane, int id);
int			draw_sp_radius(t_gui *gui, t_mlx *m, float radius);
int			draw_sp_ctrls(t_gui *gui, t_sphere *sphere, int id);
int			draw_cy_ctrls(t_gui *gui, t_cylinder *cylinder, int id);
int			draw_light_ctrls(t_light *light, t_gui *gui, t_mlx *m);
int			draw_camera_ctrls(t_camera *camera, t_gui *gui, t_mlx *m);
int			draw_sel_param_bckg(t_gui *gui, t_mlx *m, int id);
int			draw_background(t_gui *gui, t_mlx *m, int obj_id);
void		fill_background(t_gui *gui, t_mlx *m);
int			draw_rot_data(t_gui *gui, t_mlx *m, t_pos obj_ang_offset);
int			draw_pos_data(t_gui *gui, t_mlx *m, t_v3 pos);
int			draw_object_name(t_gui *gui, char *name, int id);
int			draw_rot_data_cam(t_gui *gui, t_mlx *m, t_pos obj_ang_offset);

int			handle_mouse(int button, int x, int y, t_data *data);
int			handle_mouse_gui(int button, int x, int y, t_data *data);

#endif