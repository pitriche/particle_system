/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   All.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 20:59:50 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/22 13:11:30 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_HPP
# define ALL_HPP

# include "Display.hpp"
# include "Event.hpp"
# include "Time.hpp"

struct All
{
	public :
		Time	time;
		Display	disp;
		Event	event;

		All(void);
		virtual ~All(void);

		void	init(void);

	protected:
	private:

		All(const All &);
		void	operator=(const All &);
};

extern All	all;

#endif