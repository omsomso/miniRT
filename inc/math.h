/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaphod <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:10:38 by zaphod           #+#    #+#             */
/*   Updated: 2023/09/26 14:59:57 by zaphod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include "types.h"

t_v3	add_v(t_v3 a, t_v3 b);
t_v3	sub_v(t_v3 a, t_v3 b);
t_v3	mvs(t_v3 a, double s);
t_v3	normalize(t_v3 a);
float	distance_to_point(t_v3 a, t_v3 b);
float	vector_length(t_v3 a);
t_v3	cross_product(t_v3 a, t_v3 b);
float	dot_p(t_v3 a, t_v3 b);
float	deg_to_rad(float deg);
t_v3	new_v3(float x, float y, float z);
int		v3_equal(t_v3 v1, t_v3 v2);
t_v3	get_orthogonal(t_v3 v);
t_v3	multiply_matrix_vector(const t_matrix4 matrix, const t_v3 v);
t_v3	calculate_sphere_normal(t_v3 sphere_center, t_v3 point_on_surface);
float	compute_discriminant(float a, float b, float c);
t_coeff	compute_abc(t_ray ray, t_cylinder *cylinder);

#endif
