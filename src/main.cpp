/*
 * This file is part of Std-Arch-Sim.
 *
 * Std-Arch-Sim is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Std-Arch-Sim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Std-Arch-Sim.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

#include "Processor.h"

Accumulator *accumulator;
ALU *alu;
Databus *databus;
Decoder *decoder;
Flag *flag;
Instruction *instruction;
IO_RF *io;
MainMemory *mainMemory;
MemoryAddress *memoryAddress;
Microinstruction *microinstruction;
MicroprogramSequencer *microprogramSequencer;
Operand *operand;
ProgramCounter *programCounter;
RegisterArray *registerArray;
ROM *rom;
StackPointer *stackPointer;

void init(std::string path) {
	accumulator = new Accumulator();
	alu = new ALU();
	databus = new Databus();
	decoder = new Decoder();
	flag = new Flag();
	instruction = new Instruction();
	io = new IO_RF();
	mainMemory = new MainMemory(path);
	memoryAddress = new MemoryAddress();
	microinstruction = new Microinstruction();
	microprogramSequencer = new MicroprogramSequencer();
	operand = new Operand();
	programCounter = new ProgramCounter();
	registerArray = new RegisterArray();
	rom = new ROM();
	stackPointer = new StackPointer();
	microinstruction->resetContent();
}

void cleanup () {
	delete accumulator;
	delete alu;
	delete databus;
	delete decoder;
	delete flag;
	delete instruction;
	delete io;
	delete mainMemory;
	delete memoryAddress;
	delete microinstruction;
	delete microprogramSequencer;
	delete operand;
	delete programCounter;
	delete registerArray;
	delete rom;
	delete stackPointer;
}

int main(int argc, char const *argv[]) {
	init("./Assembler/assemble.out");
	
	std::cout <<registerArray->toString();

	for (int i = 0 ; i <= 255 ; i++)
	{
		memoryAddress->setContent(i);
		memoryAddress->clockPulse();
		std::cout <<(unsigned int)mainMemory->getContent()<<" ";
		if (!((i + 1) % 16))
			std::cout <<std::endl;
	}
	memoryAddress->setContent(0);
	memoryAddress->clockPulse();

	for(int i = 0 ; instruction->getContent() != 0x01 ; i++)
	{
		std::cout <<"\n\nBefore : " <<i<<std::endl; 
		std::cout <<"ALU : "<<alu->getContent()<<std::endl;
		std::cout <<"Accumulator : "<<accumulator->getContent()<<std::endl;
		std::cout <<"Databus : "<<databus->getContent()<<std::endl;
		std::cout <<"Decoder : " <<decoder->getContent()<<std::endl;
		std::cout <<"Program Counter : "<<programCounter->getContent()<<std::endl;
		std::cout <<"mainMemory : "<<mainMemory->getContent()<<std::endl;
		std::cout <<"flag : "<<flag->getContent()<<std::endl;
		std::cout <<"io : "<<io->getContent()<<std::endl;
		std::cout <<"instruction : "<<instruction->getContent()<<std::endl;
		std::cout <<"memoryAddress : "<<memoryAddress->getContent()<<std::endl;
		std::cout <<"Register : "<<registerArray->getContent()<<std::endl;
		std::cout <<"MicroSequen : "<<microprogramSequencer->getContent()<<std::endl;
		std::cout <<std::endl;

		databus->resetBusy();
		
		accumulator->processSignalRisingEdge();
		flag->processSignalRisingEdge();
		instruction->processSignalRisingEdge();
		io->processSignalRisingEdge();
		memoryAddress->processSignalRisingEdge();
		memoryAddress->updateImmediate();
		mainMemory->processSignalRisingEdge();
		microprogramSequencer->processSignalRisingEdge();
		operand->processSignalRisingEdge();
		programCounter->processSignalRisingEdge();
		registerArray->processSignalRisingEdge();
		stackPointer->processSignalRisingEdge();

		accumulator->processSignalFallingEdge();
		flag->processSignalFallingEdge();
		instruction->processSignalFallingEdge();
		io->processSignalFallingEdge();
		memoryAddress->processSignalFallingEdge();
		memoryAddress->updateImmediate();
		mainMemory->processSignalFallingEdge();
		microprogramSequencer->processSignalFallingEdge();
		operand->processSignalFallingEdge();
		programCounter->processSignalFallingEdge();
		registerArray->processSignalFallingEdge();
		stackPointer->processSignalFallingEdge();

		accumulator->clockPulse();
		flag->clockPulse();
		instruction->clockPulse();
		io->clockPulse();
		memoryAddress->clockPulse();
		microprogramSequencer->clockPulse();
		operand->clockPulse();
		programCounter->clockPulse();
		registerArray->clockPulse();
		stackPointer->clockPulse();

		microprogramSequencer->processSignalRisingEdge();
		microprogramSequencer->processSignalFallingEdge();
		microprogramSequencer->updateImmediate();
		
		rom->setMicroinstruction();

		std::cout <<"\n\nAfter : "<< i << std::endl; 
		std::cout <<"ALU : "<<alu->getContent()<<std::endl;
		std::cout <<"Accumulator : "<<accumulator->getContent()<<std::endl;
		std::cout <<"Databus : "<<databus->getContent()<<std::endl;
		std::cout <<"Decoder : " <<decoder->getContent()<<std::endl;
		std::cout <<"Program Counter : "<<programCounter->getContent()<<std::endl;
		std::cout <<"mainMemory : "<<mainMemory->getContent()<<std::endl;
		std::cout <<"flag : "<<flag->getContent()<<std::endl;
		std::cout <<"io : "<<io->getContent()<<std::endl;
		std::cout <<"instruction : "<<instruction->getContent()<<std::endl;
		std::cout <<"memoryAddress : "<<memoryAddress->getContent()<<std::endl;
		std::cout <<"Register : "<<registerArray->getContent()<<std::endl;
		std::cout <<"MicroSequen : "<<microprogramSequencer->getContent()<<std::endl;
		std::cout <<std::endl;
	}

	std::cout <<registerArray->toString();

	for (int i = 0 ; i <= 255 ; i++)
	{
		memoryAddress->setContent(i);
		memoryAddress->clockPulse();
		std::cout <<(unsigned int)mainMemory->getContent()<<" ";
		if (!((i + 1) % 16))
			std::cout <<std::endl;
	}



	// std::cout <<stackPointer->getContent();

	//	registerArray->clockPulse();
	//	databus->setContent(1);
	//	microinstruction->LIO = true;
	//	io->processSignal();
	//	io->clockPulse();
	//	std::cout <<io->SFL<<std::endl;
	//	std::cout <<flag->getFlag()<<std::endl;
	//	flag->setNZ();
	//	databus->resetBusy();
	//	databus->setContent(2);
	//	microinstruction->LIO = true;
	//	io->processSignal();
	//	io->clockPulse();
	//	std::cout <<io->SFL<<std::endl;
	//	std::cout <<flag->getFlag()<<std::endl;

	//	operand->setContent( 0 );
	//	databus->setContent( 127 );
	//	operand->clockPulse();
	//	microinstruction->SAF = 1;
	//	std::cout <<alu->getContent()<<std::endl;
	// 	std::cout <<flag->getC()<<std::endl;
	//	std::cout <<flag->getS()<<std::endl;
	//	std::cout <<flag->getNS()<<std::endl;


	//	flag->setS();
	//	std::cout <<flag->getS();
	//	flag->resetS();
	//	std::cout <<flag->getS();
	//	std::cout <<flag->getU();

	//	databus->setContent( 10 );
	//	operand->setContent ( 20 );
	//	operand->clockPulse();
	//	microinstruction->SAF = 1;
	//	std::cout <<(microinstruction->SAF & 15)<<std::endl;
	//	std::cout <<alu->getContent()<<std::endl;

	cleanup();
	return 0;
}
