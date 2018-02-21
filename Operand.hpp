/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquesnel <vquesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 11:55:37 by vquesnel          #+#    #+#             */
/*   Updated: 2018/02/21 11:33:47 by vquesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include "FactoryMethod.hpp"
#include <cfloat>


class Operand : public IOperand {
	private:
		static FactoryMethod	_FACTORY_METHOD;
		static const t_type		_LIMITS;
		eOperandType 					_eType;
		std::string 					_data;
		Operand(void);
		Operand & operator=(Operand const & rhs);
		Operand(Operand const & rhs);
	public:
		Operand(const std::string &data);
		Operand(eOperandType eType, const std::string &data);
		~Operand();

		IOperand const 		*operator+(IOperand const & rhs) const;
		IOperand const 		*operator-(IOperand const & rhs) const;
		IOperand const 		*operator*(IOperand const & rhs) const;
		IOperand const 		*operator/(IOperand const & rhs) const;
		IOperand const 		*operator%(IOperand const & rhs) const;
		int 							getPrecision(void) const;
		eOperandType 			getType(void) const;
		std::string const &toString(void) const;
		class Operand_Exceptions: public std::exception {};

		class OverflowException_res: public Operand_Exceptions {
			public:
				const char* what() const throw();
		};
		class UnderflowException_res: public Operand_Exceptions {
			public:
				const char* what() const throw();
		};
		class OverflowException_val: public Operand_Exceptions {
			public:
				const char* what() const throw();
		};
		class UnderflowException_val: public Operand_Exceptions {
		public:
			const char* what() const throw();
		};
};

#endif
