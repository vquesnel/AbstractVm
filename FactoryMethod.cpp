/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FactoryMethod.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquesnel <vquesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 12:12:00 by vquesnel          #+#    #+#             */
/*   Updated: 2018/02/20 12:16:10 by vquesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FactoryMethod.hpp"
#include "Operand.hpp"


FactoryMethod::~FactoryMethod()
{
	return;
}

FactoryMethod::FactoryMethod()
{
	return;
}

IOperand const *FactoryMethod::createOperand(eOperandType type, std::string const &value) const
{
	typedef IOperand const *(FactoryMethod::*functions)(std::string const & value) const;
	functions myArray[5];

	myArray[eOperandType::Int8] = &FactoryMethod::createInt8;
	myArray[eOperandType::Int16] = &FactoryMethod::createInt16;
	myArray[eOperandType::Int32] = &FactoryMethod::createInt32;
	myArray[eOperandType::Float] = &FactoryMethod::createFloat;
	myArray[eOperandType::Double] = &FactoryMethod::createDouble;

	return dynamic_cast<const IOperand *>((this->*myArray[type])(value));
}

IOperand const *FactoryMethod::createInt8(std::string const &value) const
{
	if (value[0] == '-' && value.length() > 4)
		throw Operand::UnderflowException_val();
	else if (value[0] != '-' && value.length() > 3)
		throw Operand::OverflowException_val();
	auto a = std::stoi(value);
	if (a <= INT8_MAX && a >= INT8_MIN)
		return new Operand(eOperandType::Int8, value);
	else if (value[0] == '-')
		throw Operand::UnderflowException_val();
	else
		throw Operand::OverflowException_val();
}

IOperand const *FactoryMethod::createInt16(std::string const &value) const
{
	if (value[0] == '-' && value.length() > 6)
		throw Operand::UnderflowException_val();
	else if (value[0] != '-' && value.length() > 5)
		throw Operand::OverflowException_val();
	auto a = std::stoi(value);
	if (a <= INT16_MAX && a >= INT16_MIN)
		return new Operand(eOperandType::Int16, value);
	else if (value[0] == '-')
		throw Operand::UnderflowException_val();
	else
		throw Operand::OverflowException_val();
}

IOperand const *FactoryMethod::createInt32(std::string const &value) const
{
	try {
		std::stoi(value);
		return new Operand(eOperandType::Int32, value);
	}
	catch (...)
	{
		if (value[0] == '-')
			throw Operand::UnderflowException_val();
		else
			throw Operand::OverflowException_val();
	}
}

IOperand const *FactoryMethod::createFloat(std::string const &value) const
{
	try {
		std::stof(value);
		return new Operand(eOperandType::Float, value);
	}
	catch (...)
	{
		if (value[0] == '-')
			throw Operand::UnderflowException_val();
		else
			throw Operand::OverflowException_val();
	}
}

IOperand const *FactoryMethod::createDouble(std::string const &value) const
{
	try {
		std::stod(value);
		return new Operand(eOperandType::Double, value);
	}
	catch (...)
	{
		if (value[0] == '-')
			throw Operand::UnderflowException_val();
		else
			throw Operand::OverflowException_val();
	}
}
