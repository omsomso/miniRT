/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:02:27 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/25 15:23:55 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minirt.h"

void		add_object(t_object **obj_head, void *o, t_type t, char **s);
t_object	*create_obj(void *object, t_type type, char **s);

t_object	*merge_sort(t_object *head);
double		compute_distance(t_v3 origin, t_object *obj);
void		sort_objects_by_distance(t_v3 origin, t_object **head);
void		fb_split(t_object *s, t_object **fr, t_object **br);
void		front_back_loop(t_object *fast, t_object *slow);
t_object	*sorted_merge(t_object *a, t_object *b);

int			get_color(t_color *color, char **s);
t_v3		*get_vec(char **s);

int			parser(char *filename, t_object **objects, t_data *data);
int			parse_spc(char **s, t_object **objects);
void	free_acl(t_amb *ambient_light, t_camera *camera, t_light *light);
int			parse_a(char **s, t_data **data);
int			parse_c(char **s, t_data **data);
int			parse_l(char **s, t_data **data);
int			parse_sp(char **s, t_object **objects);
int			parse_pl(char **s, t_object **objects);
int			parse_cy(char **s, t_object **objects);

int			check_a(char **s);
int			check_l(char **s);
int			check_l_brightness(float ratio);
int			check_c(char **s);
int			check_sp(char **s);
int			check_cy(char **s);
int			check_pl(char **s);
int			check_color(char *color);
int			check_pos(char *pos);
int			check_normal(char *s);
int			ch_nb(char *s);

void		free_sp(void *object);
void		free_pl(void *object);
void		free_cy(void *object);
void		free_objects(t_object *objects_head);
void		free_acl(t_amb *ambient_light, t_camera *camera, t_light *light);

int			check_line(char *line, char *name);
int			line_isspace(char *line);
char		*line_fixspace(char *line);
void		fix_last_whitespace(char **s);
int			check_spaces(char *line);

int			parse_loop(int fd, t_object **objects, t_data *data);
int			parser(char *filename, t_object **objects, t_data *data);

int			init_scene(t_data *data);
int			check_scene(t_data *data);

void		dbg_parser(t_data *data);

#endif