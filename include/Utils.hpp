/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:13:45 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/24 13:24:37 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>	/* std::string */
# include "OpenCL.hpp"
# include "OpenGL.hpp"

namespace Utils
{
	void		error_quit(const std::string &str);
	std::string	read_file(const char *filename);
	void		openCL_error_log(const OpenCL &cl, cl_int err_code);
	void		openGL_error_log(unsigned int shader, int err_code,
		const char *filename);
}

#endif
