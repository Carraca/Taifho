#pragma once

class BoardEvent{
public:
	bool virtual isMove() {return false;}
	bool virtual isAvailableMoves() {return false;}
	bool virtual isWin() {return false;}
	bool virtual isPass() { return false; }
	bool virtual isTurn() { return false; }
	bool virtual isProcessing(){ return false; }
private:

};