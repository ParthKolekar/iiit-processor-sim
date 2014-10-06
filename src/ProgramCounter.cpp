#ifndef _PROGRAMCOUNTER_CPP
#define _PROGRAMCOUNTER_CPP

#include "ProgramCounter.h"
#include "Processor.h"

ProgramCounter::ProgramCounter () {

}

ProgramCounter::~ProgramCounter () {

}

void ProgramCounter::processSignal () {
	if (microinstruction->EPC)
		databus->setContent(this->getContent());
	if (microinstruction->IPC)
		this->setContent(this->getContent() + 1);
	if (microinstruction->LPC)
		this->setContent(databus->getContent());
}

#endif
