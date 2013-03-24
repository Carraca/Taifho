#pragma once
#include "BoardEvent.h"
#include "vector_2d.h"

class ProcessingEvent : public BoardEvent {
public:
	ProcessingEvent();

	bool isProcessing();

};