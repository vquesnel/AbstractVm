/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FactoryMethod.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquesnel <vquesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 12:10:27 by vquesnel          #+#    #+#             */
/*   Updated: 2018/02/20 12:11:44 by vquesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FACTORYMETHOD_HPP
#define FACTORYMETHOD_HPP
#include "IOperand.hpp"

class FactoryMethod {
	private:
		FactoryMethod(FactoryMethod const &);

		IOperand const *createInt8(std::string const & value) const;
		IOperand const *createInt16(std::string const & value) const;
		IOperand const *createInt32(std::string const & value) const;
		IOperand const *createFloat(std::string const & value) const;
		IOperand const *createDouble(std::string const & value) const;
		FactoryMethod &operator=(FactoryMethod const &);
	public:
		~FactoryMethod();
		FactoryMethod();
		IOperand const *createOperand(eOperandType type, std::string const & value) const;

};

#endif
