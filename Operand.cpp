/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquesnel <vquesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 12:04:37 by vquesnel          #+#    #+#             */
/*   Updated: 2018/02/20 13:25:56 by vquesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"
#include "FactoryMethod.hpp"
#include "IOperand.hpp"

const t_type Operand::LIMITS = {
	{ INT8_MAX, INT16_MAX, INT32_MAX, FLT_MAX, DBL_MAX},
	{ INT8_MIN, INT16_MIN, INT32_MIN, -FLT_MAX, -DBL_MAX }
};

FactoryMethod	Operand::FACTORY_METHOD;

Operand::Operand()
{
	return;
}

Operand::Operand(const std::string &data) :
 _data(data)
{
	return;
}


Operand::Operand(eOperandType eType, const std::string &data) :
	_eType(eType),
	_data(data)
{
	return;
}

Operand::~Operand()
{
	return;
}

int Operand::getPrecision(void) const { return this->_eType; }

eOperandType Operand::getType(void) const { return this->_eType; }

std::string const &Operand::toString(void) const { return this->_data; }


IOperand const *Operand::operator+(IOperand const &rhs) const
{
	eOperandType 	type = std::max(this->getType(), rhs.getType());

	if (type <= eOperandType::Int32) {
		auto res = std::stoll(this->_data) + std::stoll(rhs.toString());
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
	else {
		auto res = std::stold(this->_data) + std::stold(rhs.toString());
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
}

IOperand const *Operand::operator-(IOperand const &rhs) const
{
	eOperandType 	type = std::max(this->getType(), rhs.getType());
	if (type <= eOperandType::Int32) {
		auto res = std::stoll(this->_data) - std::stoll(rhs.toString());
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
	else {
		auto res = std::stold(this->_data) - std::stold(rhs.toString());
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
}


IOperand const *Operand::operator*(IOperand const &rhs) const
{
	eOperandType 	type = std::max(this->getType(), rhs.getType());
	if (type <= eOperandType::Int32) {
		auto res = std::stoll(this->_data) * std::stoll(rhs.toString());
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
	else {
		auto res = std::stold(this->_data) * std::stold(rhs.toString());
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
}

const char *Operand::OverflowException_res::what() const throw()
{
	return ("\033[31;1mOverflow on the result of an operation\033[0m");
}

const char *Operand::UnderflowException_res::what() const throw()
{
	return ("\033[31;1mUnderflow on the result of an operation\033[0m");
}

const char *Operand::OverflowException_val::what() const throw()
{
	return ("\033[31;1mOverflow on a value\033[0m");
}

const char *Operand::UnderflowException_val::what() const throw()
{
	return ("\033[31;1mUnderflow on a value\033[0m");
}

IOperand const *Operand::operator/(IOperand const &rhs) const
{
	eOperandType 	type = std::max(this->getType(), rhs.getType());
	if (type <= eOperandType::Int32) {
		auto res = std::stoll(this->_data) / std::stoll(rhs.toString());
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
	else {
		auto res = std::stold(this->_data) / std::stold(rhs.toString());
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
}

const IOperand *Operand::operator%(const IOperand &rhs) const
{
	eOperandType 	type = std::max(this->getType(), rhs.getType());
	if (type <= eOperandType::Int32) {
		auto res = std::stoll(this->_data) % std::stoll(rhs.toString());
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
	else {
		auto res = static_cast<int64_t>(std::stold(this->_data)) % static_cast<int64_t >(std::stold(rhs.toString()));
		if (res > Operand::LIMITS.max[type])
			throw Operand::OverflowException_res();
		else if (res < Operand::LIMITS.min[type])
			throw Operand::UnderflowException_res();
		return FACTORY_METHOD.createOperand(type, std::to_string(res));
	}
}
