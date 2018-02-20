/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquesnel <vquesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 12:08:41 by vquesnel          #+#    #+#             */
/*   Updated: 2018/02/20 12:10:13 by vquesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
#define IOPERAND_HPP

#include <iostream>

enum eOperandType { Int8, Int16, Int32, Float, Double };

typedef struct	limits
{
	double max[5];
	double min[5];
}								t_type;

class IOperand {
	public:
		virtual int 					getPrecision(void) const = 0;
		virtual eOperandType 	getType(void) const = 0;

		virtual	IOperand 	const 	*operator+(IOperand const &ref) const = 0;
		virtual	IOperand 	const 	*operator-(IOperand const &ref) const = 0;
		virtual	IOperand 	const 	*operator*(IOperand const &ref) const = 0;
		virtual	IOperand 	const 	*operator/(IOperand const &ref) const = 0;
		virtual	IOperand 	const 	*operator%(IOperand const &ref) const = 0;
		virtual std::string const &toString(void) const = 0;

		virtual ~IOperand( void ) {}
};

#endif
