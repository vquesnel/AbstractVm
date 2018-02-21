/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquesnel <vquesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 12:28:24 by vquesnel          #+#    #+#             */
/*   Updated: 2018/02/21 11:33:47 by vquesnel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <regex>
#include "IOperand.hpp"
#include "FactoryMethod.hpp"
#include "Reader.hpp"
#include "VM.hpp"
#include "Operand.hpp"


int main(int argc, char **argv) {
	Reader 	reader;
	VM 		vm;

	if (argc == 2) {
		try {
			 reader.read_from_file(argv[1]);
		}
		catch (Reader::ExitException &e) {
			std::cout << e.what() << std::endl;
			exit(1);
		}
	}
	else if (argc == 1) {
		try {
			reader.read_from_stdin();
		}
		catch (Reader::ExitException &e) {
			std::cout << e.what() << std::endl;
			exit(1);
		}
	}
	else
		std::cout << "usage: ./avm <file> or ./avm" << std::endl;
	if (!reader.getProgressFlag())
		exit(1);
	try {
		vm.dispatcher(reader.getVector());
	}
	catch (VM::VM_Exceptions &e) {
		 std::cout << e.what() << std::endl;
	 }
	catch (Operand::Operand_Exceptions &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
