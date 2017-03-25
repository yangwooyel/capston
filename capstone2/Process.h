#pragma once

#include "Board.h"

void setWeight(Board *board);

void doPut(State state, Board *board, Points pt); // Process.cpp

State getWinner(Board board);