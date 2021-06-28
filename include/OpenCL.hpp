/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenCL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:13:45 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/28 15:13:09 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENCL_HPP
# define OPENCL_HPP

# include <OpenCL/cl.h>

struct OpenCL
{
	public :
		OpenCL(void);

		cl_device_id		device;
		cl_context			context;
		cl_command_queue	queue;

		cl_program			program;
		cl_kernel			kernel_update_speed;
		cl_kernel			kernel_update_position;

		cl_mem				buffer_pos;
		cl_mem				buffer_speed;
		cl_mem				buffer_cursor;

		// float				tempo;

		void	init(void);

	private:
};

#endif
