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
#ifndef _MAINMEMORY_CPP
#define _MAINMEMORY_CPP

#include "MainMemory.h"
#include "Processor.h"

MainMemory::MainMemory () {
	this->mainMemory.fill(0); // Un-necessary by implementation of g++, this will be done automatically. But other compilers will complain.
									// g++ optimises it away anyways. :P. All hail g++. All hail Stallman. GNU FTW!.
	this->mainMemory[255] = 0x01; //STOP
}

MainMemory::~MainMemory () {

}

MainMemory::MainMemory (std::string path) {
	std::ifstream infile;
	infile.open(path , std::ios::binary);
	if (!infile)
		throw FILE_NOT_READABLE;
	infile.read(this->mainMemory.data() , sizeof(mainMemory));
	infile.close();
	this->mainMemory[255] = 0x01;
}

MainMemory::MainMemory (std::fstream infile) {
	if (!infile.is_open())
		throw INVALID_STREAM;
	infile.read(this->mainMemory.data() , sizeof(mainMemory));
	infile.close();
}

MainMemory::MainMemory (std::ifstream infile) {
	if (!infile.is_open())
		throw INVALID_STREAM;
	infile.read(this->mainMemory.data() , sizeof(mainMemory));
	infile.close();
}

void MainMemory::setContent ( int content ) {
	this->mainMemory[ memoryAddress->getContent() ] = (char) content;
}

int MainMemory::getContent () {
	return (int) ((this->mainMemory [ memoryAddress->getContent() ]) & 0xFF);
}

void MainMemory::processSignalRisingEdge(){
	if(microinstruction->RD) {
		std::cout << "RD\t";
		databus->setContent(this->getContent());
	}
}

void MainMemory::processSignalFallingEdge(){
	if(microinstruction->WR) {
		std::cout << "WR\t";
		this->setContent(databus->getContent());
	}
}

std::string hexed(int a) {
	if(a < 10)
		return std::to_string(a);
	if(a == 10)
		return "A";
	if(a == 11)
		return "B";
	if(a == 12)
		return "C";
	if(a == 13)
		return "D";
	if(a == 14)
		return "E";
	if(a == 15)
		return "F";
	return NULL;
}

std::string MainMemory::toString() {
	std::string buffer;
	buffer = "X |";
	for(int i=0;i<16;i++) {
		buffer += "\t" + hexed(i);
	}
	buffer += "\n\n0 |\t";
	for(int i=0;i<256;i++) {
		buffer += std::to_string((unsigned int)(this->mainMemory[i] & 0xFF)) + "\t";
		if(!((i+1)%16) && (i+1)/16 != 16) {
			buffer +="\n" + hexed((i+1)/16) + " |\t";
		}
	}
	return buffer;
}

#endif
