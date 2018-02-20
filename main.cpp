/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquesnel <vquesnel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 12:28:24 by vquesnel          #+#    #+#             */
/*   Updated: 2018/02/20 13:25:51 by vquesnel         ###   ########.fr       */
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
		catch (Reader::ExitException & e) {
			std::cout << e.what() << std::endl;
			exit(1);
		}
	}
	else if (argc == 1) {
		try {
			reader.read_from_stdin();
		}
		catch (Reader::ExitException & e) {
			std::cout << e.what() << std::endl;
			exit(1);
		}
	}
	else
		std::cout << "usage: ./avm <file> or ./avm" << std::endl;
	if (!reader.getProgressFlag())
		exit(1);
	try {
		vm.find_command(reader.getVector());
	}
	catch (VM::emptystack &e) {
		 std::cout << e.what() << std::endl;
	 }
	catch (VM::assertInstruction &e) 			{ std::cout << e.what() << std::endl; }
	catch (Operand::OverflowException_res & e) 	{ std::cout << e.what() << std::endl; }
	catch (Operand::UnderflowException_res & e) { std::cout << e.what() << std::endl; }
	catch (Operand::OverflowException_val & e) 	{ std::cout << e.what() << std::endl; }
	catch (Operand::UnderflowException_val & e) { std::cout << e.what() << std::endl; }
	catch (VM::less_than_two_instruction & e) 	{ std::cout << e.what() << std::endl; }
	catch (VM::division_modulo & e)				{ std::cout << e.what() << std::endl; }
	catch (VM::print_exception & e)				{ std::cout << e.what() << std::endl; }


	return 0;
}
