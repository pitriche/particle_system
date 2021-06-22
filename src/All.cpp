/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   All.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:03:42 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/22 14:03:00 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "All.hpp"
#include "Defines.hpp"

All::All(void) { }
All::All(const All &) { }
All::~All(void) { }

void	All::init(void)
{
	this->disp.init();
	this->time.set_fps(BASE_FPS);
}

void	All::operator=(const All &) { }
