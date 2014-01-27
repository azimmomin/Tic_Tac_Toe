/****************************************************************************************** 
 *	Chili DirectX Framework Version 11.12.17											  *	
 *	Game.h																				  *
 *	Copyright 2011 PlanetChili.net														  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "D3DGraphics.h"
#include "Keyboard.h"

class Game
{
public:
	Game( HWND hWnd,const KeyboardServer& kServer );
	void Go();
private:
	enum XOState
	{
		EMPTY,
		X,
		O
	};
private:
	void ComposeFrame();
	/********************************/
	/*  User Functions              */
	/** Create a Tic Tac Toe Grid at position (X, Y). */
	void DrawGrid(int x, int y);
	/** Draw the X-marker at (X, Y).*/
	void DrawX(int x, int y);
	/** Draw the O-marker at (X, Y). */
	void DrawO(int x, int y);
	/** Draw the cursor at (X, Y). */
	void DrawCursor(int x, int y);
	/** Draw cursor on box at INDEX. */
	void DrawCursor(int index);
	/** Accesses and sets the XOState of the box at INDEX to STATE. */
	void SetSquareState(int index, XOState state);
	/** Accesses and returns the XOSTATE of the box at INDEX. */
	XOState GetSquareState(int index);
	/** Accesses and sets the XOState of the box at coordinate (IX, IY) to STATE. */
	void SetSquareState(int ix, int iy, XOState state);
	/** Accesses and returns the XOSTATE of the box at coordinate (IX, IY). */
	XOState GetSquareState(int ix, int iy);
	/** Handles keyboard input from active player. */
	void DoUserInput();
	/** Switches between players. */
	void EndTurn();
	/** Checks for a win. */
	XOState CheckForVictory();
	/** Draws Toilet End Screen. */
	void DrawToilet(int x, int y);
	/** Draws X win End Screen. */
	void DrawXWin(int x, int y);
	/** Draws O win End Screen. */
	void DrawOWin(int x, int y);
	/** Draws Tie End Screen. */
	void DrawTie(int x, int y);
	/** Draws the End Screen depending on who won. */
	void DrawEndScreen(int x, int y, XOState state);
	/** Create random AI Move. */
	void AIGetNextMoveRand();
	/** Create a non-random AI Move. */
	void AIGetNextMoveSmart();
	/** Implement random AI Move. */
	void DoAITurnRand();
	/** Implement a non-random AI Move. */
	void DoAITurnSmart();
	/** Checks if PLAYER has two in a row on the board. */
	int GetTwoInARow(XOState player);
	/** Returns the opponent of the CURPLAYER. */
	XOState Opponent(XOState curPlayer);
	/********************************/
private:
	D3DGraphics gfx;
	KeyboardClient kbd;
	/********************************/
	/*  User Variables              */
	XOState s0;
	XOState s1;
	XOState s2;
	XOState s3;
	XOState s4;
	XOState s5;
	XOState s6;
	XOState s7;
	XOState s8;
	XOState activePlayer;
	bool keysPressedLastFrame;
	int cursorX, cursorY;
	int nTurns;

	int AIMoveX;
	int AIMoveY;

	int AIMoveIndex;
	
	/********************************/
};