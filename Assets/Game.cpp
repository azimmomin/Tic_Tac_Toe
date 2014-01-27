/****************************************************************************************** 
 *	Chili DirectX Framework Version 11.12.17											  *	
 *	Game.cpp																			  *
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
#include "Game.h"
#include <stdlib.h>
#include <time.h>

Game::Game( HWND hWnd,const KeyboardServer& kServer )
:	gfx ( hWnd ),
	kbd( kServer ),
	cursorX(1),
	cursorY(1),
	keysPressedLastFrame(false),
	activePlayer(X), //Change to O if you want human to go first
	nTurns(0),
	AIMoveX(1),
	AIMoveY(1),
	AIMoveIndex(4)
{
	for (int index = 0; index < 9; index += 1)
	{
		SetSquareState(index, EMPTY);
	}
	srand((unsigned int) time(NULL));
}

void Game::Go()
{
	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::DrawGrid(int x, int y)
{
	gfx.DrawLine(0 + x, 99 + y, 299 + x, 99 + y, 255, 255, 255);
	gfx.DrawLine(0 + x, 199 + y, 299 + x, 199 + y, 255, 255, 255);
	gfx.DrawLine(99 + x, 0 + y, 99 + x, 299 + y, 255, 255, 255);
	gfx.DrawLine(199 + x, 0 + y, 199 + x, 299 + y, 255, 255, 255);
}

void Game::DrawX(int x, int y)
{
	gfx.DrawLine(x + 15, y + 15, x + 84, y + 84, 255, 0, 0);
	gfx.DrawLine(x + 15, y + 84, x + 84, y + 15, 255, 0, 0);
}

void Game::DrawO(int x, int y)
{
	gfx.DrawCircle(x + 49, y + 49, 35, 0, 0, 255);
}

void Game::DrawCursor(int x, int y)
{
	gfx.DrawLine(x + 8, y + 8, x + 48, y + 8, 0, 255, 0);
	gfx.DrawLine(x + 8, y + 9, x + 8, y + 48, 0, 255, 0);
	gfx.DrawLine(x + 91, y + 91, x + 51, y + 91, 0, 255, 0);
	gfx.DrawLine(x + 91, y + 90, x + 91, y + 51, 0, 255, 0);

}

void Game::DrawCursor(int index)
{
	const int baseX = 250;
	const int baseY = 150;
	const int squareSize = 100;

	switch (index)
	{
	case 0:
		DrawCursor(baseX , baseY);
		break;
	case 1:
		DrawCursor(baseX, baseY + squareSize);
		break;
	case 2:
		DrawCursor(baseX, baseY + 2 * squareSize);
		break;
	case 3:
		DrawCursor(baseX + squareSize, baseY);
		break;
	case 4:
		DrawCursor(baseX + squareSize, baseY + squareSize);
		break;
	case 5:
		DrawCursor(baseX + squareSize, baseY + 2*squareSize);
		break;
	case 6:
		DrawCursor(baseX + 2*squareSize, baseY);
		break;
	case 7:
		DrawCursor(baseX + 2*squareSize, baseY);
		break;
	case 8:
		DrawCursor(baseX + 2*squareSize, baseY + 2*squareSize);
		break;
	default:
		break;
	}
}

void Game::DrawToilet(int x, int y)
{
	gfx.PutPixel( 49 + x,0 + y,0,146,14 );
	gfx.PutPixel( 50 + x,0 + y,0,146,14 );
	gfx.PutPixel( 51 + x,0 + y,0,146,14 );
	gfx.PutPixel( 49 + x,1 + y,0,146,14 );
	gfx.PutPixel( 50 + x,1 + y,0,146,14 );
	gfx.PutPixel( 51 + x,1 + y,0,146,14 );
	gfx.PutPixel( 52 + x,1 + y,0,146,14 );
	gfx.PutPixel( 38 + x,2 + y,0,146,14 );
	gfx.PutPixel( 39 + x,2 + y,0,146,14 );
	gfx.PutPixel( 40 + x,2 + y,0,146,14 );
	gfx.PutPixel( 41 + x,2 + y,0,146,14 );
	gfx.PutPixel( 50 + x,2 + y,0,146,14 );
	gfx.PutPixel( 51 + x,2 + y,0,146,14 );
	gfx.PutPixel( 52 + x,2 + y,0,146,14 );
	gfx.PutPixel( 36 + x,3 + y,0,146,14 );
	gfx.PutPixel( 37 + x,3 + y,0,146,14 );
	gfx.PutPixel( 38 + x,3 + y,0,146,14 );
	gfx.PutPixel( 39 + x,3 + y,0,146,14 );
	gfx.PutPixel( 40 + x,3 + y,0,146,14 );
	gfx.PutPixel( 41 + x,3 + y,0,146,14 );
	gfx.PutPixel( 42 + x,3 + y,0,146,14 );
	gfx.PutPixel( 43 + x,3 + y,0,146,14 );
	gfx.PutPixel( 50 + x,3 + y,0,146,14 );
	gfx.PutPixel( 51 + x,3 + y,0,146,14 );
	gfx.PutPixel( 52 + x,3 + y,0,146,14 );
	gfx.PutPixel( 53 + x,3 + y,0,146,14 );
	gfx.PutPixel( 35 + x,4 + y,0,146,14 );
	gfx.PutPixel( 36 + x,4 + y,0,146,14 );
	gfx.PutPixel( 37 + x,4 + y,0,146,14 );
	gfx.PutPixel( 38 + x,4 + y,0,146,14 );
	gfx.PutPixel( 39 + x,4 + y,0,146,14 );
	gfx.PutPixel( 40 + x,4 + y,0,146,14 );
	gfx.PutPixel( 41 + x,4 + y,0,146,14 );
	gfx.PutPixel( 42 + x,4 + y,0,146,14 );
	gfx.PutPixel( 43 + x,4 + y,0,146,14 );
	gfx.PutPixel( 44 + x,4 + y,0,146,14 );
	gfx.PutPixel( 51 + x,4 + y,0,146,14 );
	gfx.PutPixel( 52 + x,4 + y,0,146,14 );
	gfx.PutPixel( 53 + x,4 + y,0,146,14 );
	gfx.PutPixel( 68 + x,4 + y,0,146,14 );
	gfx.PutPixel( 69 + x,4 + y,0,146,14 );
	gfx.PutPixel( 70 + x,4 + y,0,146,14 );
	gfx.PutPixel( 71 + x,4 + y,0,146,14 );
	gfx.PutPixel( 72 + x,4 + y,0,146,14 );
	gfx.PutPixel( 73 + x,4 + y,0,146,14 );
	gfx.PutPixel( 74 + x,4 + y,0,146,14 );
	gfx.PutPixel( 75 + x,4 + y,0,146,14 );
	gfx.PutPixel( 76 + x,4 + y,0,146,14 );
	gfx.PutPixel( 77 + x,4 + y,0,146,14 );
	gfx.PutPixel( 78 + x,4 + y,0,146,14 );
	gfx.PutPixel( 79 + x,4 + y,0,146,14 );
	gfx.PutPixel( 34 + x,5 + y,0,118,11 );
	gfx.PutPixel( 35 + x,5 + y,0,146,14 );
	gfx.PutPixel( 36 + x,5 + y,0,146,14 );
	gfx.PutPixel( 37 + x,5 + y,0,146,14 );
	gfx.PutPixel( 38 + x,5 + y,0,146,14 );
	gfx.PutPixel( 39 + x,5 + y,0,146,14 );
	gfx.PutPixel( 40 + x,5 + y,0,146,14 );
	gfx.PutPixel( 41 + x,5 + y,0,146,14 );
	gfx.PutPixel( 42 + x,5 + y,0,146,14 );
	gfx.PutPixel( 43 + x,5 + y,0,146,14 );
	gfx.PutPixel( 44 + x,5 + y,0,146,14 );
	gfx.PutPixel( 51 + x,5 + y,0,142,13 );
	gfx.PutPixel( 52 + x,5 + y,0,146,14 );
	gfx.PutPixel( 53 + x,5 + y,0,146,14 );
	gfx.PutPixel( 54 + x,5 + y,0,146,14 );
	gfx.PutPixel( 66 + x,5 + y,0,146,14 );
	gfx.PutPixel( 67 + x,5 + y,0,146,14 );
	gfx.PutPixel( 68 + x,5 + y,0,146,14 );
	gfx.PutPixel( 69 + x,5 + y,0,146,14 );
	gfx.PutPixel( 70 + x,5 + y,0,146,14 );
	gfx.PutPixel( 71 + x,5 + y,0,146,14 );
	gfx.PutPixel( 72 + x,5 + y,0,146,14 );
	gfx.PutPixel( 73 + x,5 + y,0,146,14 );
	gfx.PutPixel( 74 + x,5 + y,0,146,14 );
	gfx.PutPixel( 75 + x,5 + y,0,146,14 );
	gfx.PutPixel( 76 + x,5 + y,0,146,14 );
	gfx.PutPixel( 77 + x,5 + y,0,146,14 );
	gfx.PutPixel( 78 + x,5 + y,0,146,14 );
	gfx.PutPixel( 79 + x,5 + y,0,146,14 );
	gfx.PutPixel( 80 + x,5 + y,0,146,14 );
	gfx.PutPixel( 34 + x,6 + y,0,146,14 );
	gfx.PutPixel( 35 + x,6 + y,0,146,14 );
	gfx.PutPixel( 36 + x,6 + y,0,146,14 );
	gfx.PutPixel( 37 + x,6 + y,0,146,14 );
	gfx.PutPixel( 38 + x,6 + y,0,146,14 );
	gfx.PutPixel( 39 + x,6 + y,0,146,14 );
	gfx.PutPixel( 40 + x,6 + y,0,146,14 );
	gfx.PutPixel( 41 + x,6 + y,0,146,14 );
	gfx.PutPixel( 42 + x,6 + y,0,146,14 );
	gfx.PutPixel( 43 + x,6 + y,0,146,14 );
	gfx.PutPixel( 44 + x,6 + y,0,146,14 );
	gfx.PutPixel( 45 + x,6 + y,0,146,14 );
	gfx.PutPixel( 52 + x,6 + y,0,146,14 );
	gfx.PutPixel( 53 + x,6 + y,0,146,14 );
	gfx.PutPixel( 54 + x,6 + y,0,146,14 );
	gfx.PutPixel( 55 + x,6 + y,0,146,14 );
	gfx.PutPixel( 65 + x,6 + y,0,146,14 );
	gfx.PutPixel( 66 + x,6 + y,0,146,14 );
	gfx.PutPixel( 67 + x,6 + y,0,146,14 );
	gfx.PutPixel( 68 + x,6 + y,0,146,14 );
	gfx.PutPixel( 69 + x,6 + y,0,146,14 );
	gfx.PutPixel( 70 + x,6 + y,0,146,14 );
	gfx.PutPixel( 71 + x,6 + y,0,146,14 );
	gfx.PutPixel( 72 + x,6 + y,0,146,14 );
	gfx.PutPixel( 73 + x,6 + y,0,146,14 );
	gfx.PutPixel( 74 + x,6 + y,0,146,14 );
	gfx.PutPixel( 75 + x,6 + y,0,146,14 );
	gfx.PutPixel( 76 + x,6 + y,0,146,14 );
	gfx.PutPixel( 77 + x,6 + y,0,146,14 );
	gfx.PutPixel( 78 + x,6 + y,0,146,14 );
	gfx.PutPixel( 79 + x,6 + y,0,146,14 );
	gfx.PutPixel( 80 + x,6 + y,0,146,14 );
	gfx.PutPixel( 81 + x,6 + y,0,146,14 );
	gfx.PutPixel( 34 + x,7 + y,0,146,14 );
	gfx.PutPixel( 35 + x,7 + y,0,146,14 );
	gfx.PutPixel( 36 + x,7 + y,0,146,14 );
	gfx.PutPixel( 37 + x,7 + y,0,146,14 );
	gfx.PutPixel( 38 + x,7 + y,0,146,14 );
	gfx.PutPixel( 39 + x,7 + y,0,146,14 );
	gfx.PutPixel( 40 + x,7 + y,0,146,14 );
	gfx.PutPixel( 41 + x,7 + y,0,146,14 );
	gfx.PutPixel( 42 + x,7 + y,0,146,14 );
	gfx.PutPixel( 43 + x,7 + y,0,146,14 );
	gfx.PutPixel( 44 + x,7 + y,0,146,14 );
	gfx.PutPixel( 45 + x,7 + y,0,146,14 );
	gfx.PutPixel( 53 + x,7 + y,0,146,14 );
	gfx.PutPixel( 54 + x,7 + y,0,146,14 );
	gfx.PutPixel( 55 + x,7 + y,0,146,14 );
	gfx.PutPixel( 65 + x,7 + y,0,146,14 );
	gfx.PutPixel( 66 + x,7 + y,0,146,14 );
	gfx.PutPixel( 67 + x,7 + y,0,146,14 );
	gfx.PutPixel( 68 + x,7 + y,0,142,13 );
	gfx.PutPixel( 79 + x,7 + y,0,146,14 );
	gfx.PutPixel( 80 + x,7 + y,0,146,14 );
	gfx.PutPixel( 81 + x,7 + y,0,146,14 );
	gfx.PutPixel( 82 + x,7 + y,0,146,14 );
	gfx.PutPixel( 34 + x,8 + y,0,146,14 );
	gfx.PutPixel( 35 + x,8 + y,0,146,14 );
	gfx.PutPixel( 36 + x,8 + y,0,146,14 );
	gfx.PutPixel( 37 + x,8 + y,0,146,14 );
	gfx.PutPixel( 38 + x,8 + y,0,146,14 );
	gfx.PutPixel( 39 + x,8 + y,0,146,14 );
	gfx.PutPixel( 40 + x,8 + y,0,146,14 );
	gfx.PutPixel( 41 + x,8 + y,0,146,14 );
	gfx.PutPixel( 42 + x,8 + y,0,146,14 );
	gfx.PutPixel( 43 + x,8 + y,0,146,14 );
	gfx.PutPixel( 44 + x,8 + y,0,146,14 );
	gfx.PutPixel( 45 + x,8 + y,0,146,14 );
	gfx.PutPixel( 53 + x,8 + y,0,146,14 );
	gfx.PutPixel( 54 + x,8 + y,0,146,14 );
	gfx.PutPixel( 55 + x,8 + y,0,146,14 );
	gfx.PutPixel( 56 + x,8 + y,0,146,14 );
	gfx.PutPixel( 64 + x,8 + y,0,146,14 );
	gfx.PutPixel( 65 + x,8 + y,0,146,14 );
	gfx.PutPixel( 66 + x,8 + y,0,146,14 );
	gfx.PutPixel( 67 + x,8 + y,0,146,14 );
	gfx.PutPixel( 80 + x,8 + y,0,146,14 );
	gfx.PutPixel( 81 + x,8 + y,0,146,14 );
	gfx.PutPixel( 82 + x,8 + y,0,146,14 );
	gfx.PutPixel( 34 + x,9 + y,0,146,14 );
	gfx.PutPixel( 35 + x,9 + y,0,146,14 );
	gfx.PutPixel( 36 + x,9 + y,0,146,14 );
	gfx.PutPixel( 37 + x,9 + y,0,146,14 );
	gfx.PutPixel( 38 + x,9 + y,0,146,14 );
	gfx.PutPixel( 39 + x,9 + y,0,146,14 );
	gfx.PutPixel( 40 + x,9 + y,0,146,14 );
	gfx.PutPixel( 41 + x,9 + y,0,146,14 );
	gfx.PutPixel( 42 + x,9 + y,0,146,14 );
	gfx.PutPixel( 43 + x,9 + y,0,146,14 );
	gfx.PutPixel( 44 + x,9 + y,0,146,14 );
	gfx.PutPixel( 45 + x,9 + y,0,146,14 );
	gfx.PutPixel( 54 + x,9 + y,0,146,14 );
	gfx.PutPixel( 55 + x,9 + y,0,146,14 );
	gfx.PutPixel( 56 + x,9 + y,0,146,14 );
	gfx.PutPixel( 57 + x,9 + y,0,146,14 );
	gfx.PutPixel( 64 + x,9 + y,0,146,14 );
	gfx.PutPixel( 65 + x,9 + y,0,146,14 );
	gfx.PutPixel( 66 + x,9 + y,0,146,14 );
	gfx.PutPixel( 80 + x,9 + y,0,146,14 );
	gfx.PutPixel( 81 + x,9 + y,0,146,14 );
	gfx.PutPixel( 82 + x,9 + y,0,146,14 );
	gfx.PutPixel( 83 + x,9 + y,0,118,11 );
	gfx.PutPixel( 34 + x,10 + y,0,146,14 );
	gfx.PutPixel( 35 + x,10 + y,0,146,14 );
	gfx.PutPixel( 36 + x,10 + y,0,146,14 );
	gfx.PutPixel( 37 + x,10 + y,0,146,14 );
	gfx.PutPixel( 38 + x,10 + y,0,146,14 );
	gfx.PutPixel( 39 + x,10 + y,0,146,14 );
	gfx.PutPixel( 40 + x,10 + y,0,146,14 );
	gfx.PutPixel( 41 + x,10 + y,0,146,14 );
	gfx.PutPixel( 42 + x,10 + y,0,146,14 );
	gfx.PutPixel( 43 + x,10 + y,0,146,14 );
	gfx.PutPixel( 44 + x,10 + y,0,146,14 );
	gfx.PutPixel( 45 + x,10 + y,0,146,14 );
	gfx.PutPixel( 55 + x,10 + y,0,146,14 );
	gfx.PutPixel( 56 + x,10 + y,0,146,14 );
	gfx.PutPixel( 57 + x,10 + y,0,146,14 );
	gfx.PutPixel( 64 + x,10 + y,0,146,14 );
	gfx.PutPixel( 65 + x,10 + y,0,146,14 );
	gfx.PutPixel( 66 + x,10 + y,0,146,14 );
	gfx.PutPixel( 81 + x,10 + y,0,146,14 );
	gfx.PutPixel( 82 + x,10 + y,0,146,14 );
	gfx.PutPixel( 83 + x,10 + y,0,146,14 );
	gfx.PutPixel( 28 + x,11 + y,0,146,14 );
	gfx.PutPixel( 29 + x,11 + y,0,146,14 );
	gfx.PutPixel( 30 + x,11 + y,0,146,14 );
	gfx.PutPixel( 31 + x,11 + y,0,146,14 );
	gfx.PutPixel( 32 + x,11 + y,0,146,14 );
	gfx.PutPixel( 35 + x,11 + y,0,146,14 );
	gfx.PutPixel( 36 + x,11 + y,0,146,14 );
	gfx.PutPixel( 37 + x,11 + y,0,146,14 );
	gfx.PutPixel( 38 + x,11 + y,0,146,14 );
	gfx.PutPixel( 39 + x,11 + y,0,146,14 );
	gfx.PutPixel( 40 + x,11 + y,0,146,14 );
	gfx.PutPixel( 41 + x,11 + y,0,146,14 );
	gfx.PutPixel( 42 + x,11 + y,0,146,14 );
	gfx.PutPixel( 43 + x,11 + y,0,146,14 );
	gfx.PutPixel( 44 + x,11 + y,0,146,14 );
	gfx.PutPixel( 55 + x,11 + y,0,146,14 );
	gfx.PutPixel( 56 + x,11 + y,0,146,14 );
	gfx.PutPixel( 57 + x,11 + y,0,146,14 );
	gfx.PutPixel( 58 + x,11 + y,0,146,14 );
	gfx.PutPixel( 64 + x,11 + y,0,146,14 );
	gfx.PutPixel( 65 + x,11 + y,0,146,14 );
	gfx.PutPixel( 66 + x,11 + y,0,146,14 );
	gfx.PutPixel( 81 + x,11 + y,0,146,14 );
	gfx.PutPixel( 82 + x,11 + y,0,146,14 );
	gfx.PutPixel( 83 + x,11 + y,0,146,14 );
	gfx.PutPixel( 27 + x,12 + y,0,146,14 );
	gfx.PutPixel( 28 + x,12 + y,0,146,14 );
	gfx.PutPixel( 29 + x,12 + y,0,146,14 );
	gfx.PutPixel( 30 + x,12 + y,0,146,14 );
	gfx.PutPixel( 31 + x,12 + y,0,146,14 );
	gfx.PutPixel( 32 + x,12 + y,0,146,14 );
	gfx.PutPixel( 33 + x,12 + y,0,146,14 );
	gfx.PutPixel( 35 + x,12 + y,0,142,13 );
	gfx.PutPixel( 36 + x,12 + y,0,146,14 );
	gfx.PutPixel( 37 + x,12 + y,0,146,14 );
	gfx.PutPixel( 38 + x,12 + y,0,146,14 );
	gfx.PutPixel( 39 + x,12 + y,0,146,14 );
	gfx.PutPixel( 40 + x,12 + y,0,146,14 );
	gfx.PutPixel( 41 + x,12 + y,0,146,14 );
	gfx.PutPixel( 42 + x,12 + y,0,146,14 );
	gfx.PutPixel( 43 + x,12 + y,0,146,14 );
	gfx.PutPixel( 56 + x,12 + y,0,146,14 );
	gfx.PutPixel( 57 + x,12 + y,0,146,14 );
	gfx.PutPixel( 58 + x,12 + y,0,146,14 );
	gfx.PutPixel( 64 + x,12 + y,0,146,14 );
	gfx.PutPixel( 65 + x,12 + y,0,146,14 );
	gfx.PutPixel( 66 + x,12 + y,0,146,14 );
	gfx.PutPixel( 67 + x,12 + y,0,146,14 );
	gfx.PutPixel( 68 + x,12 + y,0,146,14 );
	gfx.PutPixel( 69 + x,12 + y,0,146,14 );
	gfx.PutPixel( 70 + x,12 + y,0,146,14 );
	gfx.PutPixel( 71 + x,12 + y,0,146,14 );
	gfx.PutPixel( 72 + x,12 + y,0,146,14 );
	gfx.PutPixel( 73 + x,12 + y,0,146,14 );
	gfx.PutPixel( 74 + x,12 + y,0,146,14 );
	gfx.PutPixel( 75 + x,12 + y,0,146,14 );
	gfx.PutPixel( 76 + x,12 + y,0,146,14 );
	gfx.PutPixel( 77 + x,12 + y,0,146,14 );
	gfx.PutPixel( 78 + x,12 + y,0,146,14 );
	gfx.PutPixel( 79 + x,12 + y,0,146,14 );
	gfx.PutPixel( 80 + x,12 + y,0,146,14 );
	gfx.PutPixel( 81 + x,12 + y,0,146,14 );
	gfx.PutPixel( 82 + x,12 + y,0,146,14 );
	gfx.PutPixel( 83 + x,12 + y,0,146,14 );
	gfx.PutPixel( 26 + x,13 + y,0,146,14 );
	gfx.PutPixel( 27 + x,13 + y,0,146,14 );
	gfx.PutPixel( 28 + x,13 + y,0,146,14 );
	gfx.PutPixel( 29 + x,13 + y,0,146,14 );
	gfx.PutPixel( 30 + x,13 + y,0,146,14 );
	gfx.PutPixel( 31 + x,13 + y,0,146,14 );
	gfx.PutPixel( 32 + x,13 + y,0,146,14 );
	gfx.PutPixel( 33 + x,13 + y,0,146,14 );
	gfx.PutPixel( 34 + x,13 + y,0,146,14 );
	gfx.PutPixel( 37 + x,13 + y,0,146,14 );
	gfx.PutPixel( 38 + x,13 + y,0,146,14 );
	gfx.PutPixel( 39 + x,13 + y,0,146,14 );
	gfx.PutPixel( 40 + x,13 + y,0,146,14 );
	gfx.PutPixel( 41 + x,13 + y,0,146,14 );
	gfx.PutPixel( 42 + x,13 + y,0,146,14 );
	gfx.PutPixel( 56 + x,13 + y,0,142,13 );
	gfx.PutPixel( 57 + x,13 + y,0,146,14 );
	gfx.PutPixel( 58 + x,13 + y,0,146,14 );
	gfx.PutPixel( 59 + x,13 + y,0,146,14 );
	gfx.PutPixel( 64 + x,13 + y,0,146,14 );
	gfx.PutPixel( 65 + x,13 + y,0,146,14 );
	gfx.PutPixel( 66 + x,13 + y,0,146,14 );
	gfx.PutPixel( 67 + x,13 + y,0,146,14 );
	gfx.PutPixel( 68 + x,13 + y,0,146,14 );
	gfx.PutPixel( 69 + x,13 + y,0,146,14 );
	gfx.PutPixel( 70 + x,13 + y,0,146,14 );
	gfx.PutPixel( 71 + x,13 + y,0,146,14 );
	gfx.PutPixel( 72 + x,13 + y,0,146,14 );
	gfx.PutPixel( 73 + x,13 + y,0,146,14 );
	gfx.PutPixel( 74 + x,13 + y,0,146,14 );
	gfx.PutPixel( 75 + x,13 + y,0,146,14 );
	gfx.PutPixel( 76 + x,13 + y,0,146,14 );
	gfx.PutPixel( 77 + x,13 + y,0,146,14 );
	gfx.PutPixel( 78 + x,13 + y,0,146,14 );
	gfx.PutPixel( 79 + x,13 + y,0,146,14 );
	gfx.PutPixel( 80 + x,13 + y,0,146,14 );
	gfx.PutPixel( 81 + x,13 + y,0,146,14 );
	gfx.PutPixel( 82 + x,13 + y,0,146,14 );
	gfx.PutPixel( 83 + x,13 + y,0,146,14 );
	gfx.PutPixel( 25 + x,14 + y,0,146,14 );
	gfx.PutPixel( 26 + x,14 + y,0,146,14 );
	gfx.PutPixel( 27 + x,14 + y,0,146,14 );
	gfx.PutPixel( 28 + x,14 + y,0,146,14 );
	gfx.PutPixel( 29 + x,14 + y,0,146,14 );
	gfx.PutPixel( 30 + x,14 + y,0,146,14 );
	gfx.PutPixel( 31 + x,14 + y,0,146,14 );
	gfx.PutPixel( 32 + x,14 + y,0,146,14 );
	gfx.PutPixel( 33 + x,14 + y,0,146,14 );
	gfx.PutPixel( 34 + x,14 + y,0,146,14 );
	gfx.PutPixel( 57 + x,14 + y,0,146,14 );
	gfx.PutPixel( 58 + x,14 + y,0,146,14 );
	gfx.PutPixel( 59 + x,14 + y,0,146,14 );
	gfx.PutPixel( 60 + x,14 + y,0,146,14 );
	gfx.PutPixel( 64 + x,14 + y,0,146,14 );
	gfx.PutPixel( 65 + x,14 + y,0,146,14 );
	gfx.PutPixel( 66 + x,14 + y,0,146,14 );
	gfx.PutPixel( 67 + x,14 + y,0,146,14 );
	gfx.PutPixel( 68 + x,14 + y,0,146,14 );
	gfx.PutPixel( 69 + x,14 + y,0,146,14 );
	gfx.PutPixel( 70 + x,14 + y,0,146,14 );
	gfx.PutPixel( 71 + x,14 + y,0,146,14 );
	gfx.PutPixel( 72 + x,14 + y,0,146,14 );
	gfx.PutPixel( 73 + x,14 + y,0,146,14 );
	gfx.PutPixel( 74 + x,14 + y,0,146,14 );
	gfx.PutPixel( 75 + x,14 + y,0,146,14 );
	gfx.PutPixel( 76 + x,14 + y,0,146,14 );
	gfx.PutPixel( 77 + x,14 + y,0,146,14 );
	gfx.PutPixel( 78 + x,14 + y,0,146,14 );
	gfx.PutPixel( 79 + x,14 + y,0,146,14 );
	gfx.PutPixel( 80 + x,14 + y,0,146,14 );
	gfx.PutPixel( 81 + x,14 + y,0,146,14 );
	gfx.PutPixel( 82 + x,14 + y,0,146,14 );
	gfx.PutPixel( 83 + x,14 + y,0,146,14 );
	gfx.PutPixel( 24 + x,15 + y,0,25,2 );
	gfx.PutPixel( 25 + x,15 + y,0,146,14 );
	gfx.PutPixel( 26 + x,15 + y,0,146,14 );
	gfx.PutPixel( 27 + x,15 + y,0,146,14 );
	gfx.PutPixel( 28 + x,15 + y,0,146,14 );
	gfx.PutPixel( 29 + x,15 + y,0,146,14 );
	gfx.PutPixel( 30 + x,15 + y,0,146,14 );
	gfx.PutPixel( 31 + x,15 + y,0,146,14 );
	gfx.PutPixel( 32 + x,15 + y,0,146,14 );
	gfx.PutPixel( 33 + x,15 + y,0,146,14 );
	gfx.PutPixel( 34 + x,15 + y,0,146,14 );
	gfx.PutPixel( 58 + x,15 + y,0,146,14 );
	gfx.PutPixel( 59 + x,15 + y,0,146,14 );
	gfx.PutPixel( 60 + x,15 + y,0,146,14 );
	gfx.PutPixel( 64 + x,15 + y,0,146,14 );
	gfx.PutPixel( 65 + x,15 + y,0,146,14 );
	gfx.PutPixel( 66 + x,15 + y,0,146,14 );
	gfx.PutPixel( 81 + x,15 + y,0,146,14 );
	gfx.PutPixel( 82 + x,15 + y,0,146,14 );
	gfx.PutPixel( 83 + x,15 + y,0,146,14 );
	gfx.PutPixel( 24 + x,16 + y,0,146,14 );
	gfx.PutPixel( 25 + x,16 + y,0,146,14 );
	gfx.PutPixel( 26 + x,16 + y,0,146,14 );
	gfx.PutPixel( 27 + x,16 + y,0,146,14 );
	gfx.PutPixel( 28 + x,16 + y,0,146,14 );
	gfx.PutPixel( 29 + x,16 + y,0,146,14 );
	gfx.PutPixel( 30 + x,16 + y,0,146,14 );
	gfx.PutPixel( 31 + x,16 + y,0,146,14 );
	gfx.PutPixel( 32 + x,16 + y,0,146,14 );
	gfx.PutPixel( 33 + x,16 + y,0,146,14 );
	gfx.PutPixel( 34 + x,16 + y,0,146,14 );
	gfx.PutPixel( 58 + x,16 + y,0,146,14 );
	gfx.PutPixel( 59 + x,16 + y,0,146,14 );
	gfx.PutPixel( 60 + x,16 + y,0,146,14 );
	gfx.PutPixel( 61 + x,16 + y,0,146,14 );
	gfx.PutPixel( 64 + x,16 + y,0,146,14 );
	gfx.PutPixel( 65 + x,16 + y,0,146,14 );
	gfx.PutPixel( 66 + x,16 + y,0,146,14 );
	gfx.PutPixel( 81 + x,16 + y,0,146,14 );
	gfx.PutPixel( 82 + x,16 + y,0,146,14 );
	gfx.PutPixel( 83 + x,16 + y,0,146,14 );
	gfx.PutPixel( 23 + x,17 + y,0,146,14 );
	gfx.PutPixel( 24 + x,17 + y,0,146,14 );
	gfx.PutPixel( 25 + x,17 + y,0,146,14 );
	gfx.PutPixel( 26 + x,17 + y,0,146,14 );
	gfx.PutPixel( 27 + x,17 + y,0,146,14 );
	gfx.PutPixel( 28 + x,17 + y,0,146,14 );
	gfx.PutPixel( 29 + x,17 + y,0,146,14 );
	gfx.PutPixel( 30 + x,17 + y,0,146,14 );
	gfx.PutPixel( 31 + x,17 + y,0,146,14 );
	gfx.PutPixel( 32 + x,17 + y,0,146,14 );
	gfx.PutPixel( 33 + x,17 + y,0,146,14 );
	gfx.PutPixel( 34 + x,17 + y,0,146,14 );
	gfx.PutPixel( 59 + x,17 + y,0,146,14 );
	gfx.PutPixel( 60 + x,17 + y,0,146,14 );
	gfx.PutPixel( 61 + x,17 + y,0,146,14 );
	gfx.PutPixel( 62 + x,17 + y,0,146,14 );
	gfx.PutPixel( 64 + x,17 + y,0,146,14 );
	gfx.PutPixel( 65 + x,17 + y,0,146,14 );
	gfx.PutPixel( 66 + x,17 + y,0,146,14 );
	gfx.PutPixel( 81 + x,17 + y,0,146,14 );
	gfx.PutPixel( 82 + x,17 + y,0,146,14 );
	gfx.PutPixel( 83 + x,17 + y,0,146,14 );
	gfx.PutPixel( 22 + x,18 + y,0,146,14 );
	gfx.PutPixel( 23 + x,18 + y,0,146,14 );
	gfx.PutPixel( 24 + x,18 + y,0,146,14 );
	gfx.PutPixel( 25 + x,18 + y,0,146,14 );
	gfx.PutPixel( 26 + x,18 + y,0,146,14 );
	gfx.PutPixel( 27 + x,18 + y,0,146,14 );
	gfx.PutPixel( 28 + x,18 + y,0,146,14 );
	gfx.PutPixel( 29 + x,18 + y,0,146,14 );
	gfx.PutPixel( 30 + x,18 + y,0,146,14 );
	gfx.PutPixel( 31 + x,18 + y,0,146,14 );
	gfx.PutPixel( 32 + x,18 + y,0,146,14 );
	gfx.PutPixel( 33 + x,18 + y,0,146,14 );
	gfx.PutPixel( 34 + x,18 + y,0,146,14 );
	gfx.PutPixel( 60 + x,18 + y,0,146,14 );
	gfx.PutPixel( 61 + x,18 + y,0,146,14 );
	gfx.PutPixel( 62 + x,18 + y,0,146,14 );
	gfx.PutPixel( 64 + x,18 + y,0,146,14 );
	gfx.PutPixel( 65 + x,18 + y,0,146,14 );
	gfx.PutPixel( 66 + x,18 + y,0,146,14 );
	gfx.PutPixel( 81 + x,18 + y,0,146,14 );
	gfx.PutPixel( 82 + x,18 + y,0,146,14 );
	gfx.PutPixel( 83 + x,18 + y,0,146,14 );
	gfx.PutPixel( 21 + x,19 + y,0,146,14 );
	gfx.PutPixel( 22 + x,19 + y,0,146,14 );
	gfx.PutPixel( 23 + x,19 + y,0,146,14 );
	gfx.PutPixel( 24 + x,19 + y,0,146,14 );
	gfx.PutPixel( 25 + x,19 + y,0,146,14 );
	gfx.PutPixel( 26 + x,19 + y,0,146,14 );
	gfx.PutPixel( 27 + x,19 + y,0,146,14 );
	gfx.PutPixel( 28 + x,19 + y,0,146,14 );
	gfx.PutPixel( 29 + x,19 + y,0,146,14 );
	gfx.PutPixel( 30 + x,19 + y,0,146,14 );
	gfx.PutPixel( 31 + x,19 + y,0,146,14 );
	gfx.PutPixel( 32 + x,19 + y,0,146,14 );
	gfx.PutPixel( 33 + x,19 + y,0,146,14 );
	gfx.PutPixel( 34 + x,19 + y,0,146,14 );
	gfx.PutPixel( 60 + x,19 + y,0,146,14 );
	gfx.PutPixel( 61 + x,19 + y,0,146,14 );
	gfx.PutPixel( 62 + x,19 + y,0,146,14 );
	gfx.PutPixel( 63 + x,19 + y,0,146,14 );
	gfx.PutPixel( 64 + x,19 + y,0,146,14 );
	gfx.PutPixel( 65 + x,19 + y,0,146,14 );
	gfx.PutPixel( 66 + x,19 + y,0,146,14 );
	gfx.PutPixel( 81 + x,19 + y,0,146,14 );
	gfx.PutPixel( 82 + x,19 + y,0,146,14 );
	gfx.PutPixel( 83 + x,19 + y,0,146,14 );
	gfx.PutPixel( 20 + x,20 + y,0,146,14 );
	gfx.PutPixel( 21 + x,20 + y,0,146,14 );
	gfx.PutPixel( 22 + x,20 + y,0,146,14 );
	gfx.PutPixel( 23 + x,20 + y,0,146,14 );
	gfx.PutPixel( 24 + x,20 + y,0,146,14 );
	gfx.PutPixel( 25 + x,20 + y,0,146,14 );
	gfx.PutPixel( 26 + x,20 + y,0,146,14 );
	gfx.PutPixel( 27 + x,20 + y,0,146,14 );
	gfx.PutPixel( 28 + x,20 + y,0,146,14 );
	gfx.PutPixel( 29 + x,20 + y,0,146,14 );
	gfx.PutPixel( 30 + x,20 + y,0,146,14 );
	gfx.PutPixel( 31 + x,20 + y,0,146,14 );
	gfx.PutPixel( 32 + x,20 + y,0,146,14 );
	gfx.PutPixel( 33 + x,20 + y,0,146,14 );
	gfx.PutPixel( 34 + x,20 + y,0,146,14 );
	gfx.PutPixel( 61 + x,20 + y,0,146,14 );
	gfx.PutPixel( 62 + x,20 + y,0,146,14 );
	gfx.PutPixel( 63 + x,20 + y,0,146,14 );
	gfx.PutPixel( 64 + x,20 + y,0,146,14 );
	gfx.PutPixel( 65 + x,20 + y,0,146,14 );
	gfx.PutPixel( 66 + x,20 + y,0,146,14 );
	gfx.PutPixel( 81 + x,20 + y,0,146,14 );
	gfx.PutPixel( 82 + x,20 + y,0,146,14 );
	gfx.PutPixel( 83 + x,20 + y,0,146,14 );
	gfx.PutPixel( 19 + x,21 + y,0,146,14 );
	gfx.PutPixel( 20 + x,21 + y,0,146,14 );
	gfx.PutPixel( 21 + x,21 + y,0,146,14 );
	gfx.PutPixel( 22 + x,21 + y,0,146,14 );
	gfx.PutPixel( 23 + x,21 + y,0,146,14 );
	gfx.PutPixel( 24 + x,21 + y,0,146,14 );
	gfx.PutPixel( 25 + x,21 + y,0,146,14 );
	gfx.PutPixel( 26 + x,21 + y,0,146,14 );
	gfx.PutPixel( 27 + x,21 + y,0,146,14 );
	gfx.PutPixel( 28 + x,21 + y,0,146,14 );
	gfx.PutPixel( 29 + x,21 + y,0,146,14 );
	gfx.PutPixel( 30 + x,21 + y,0,146,14 );
	gfx.PutPixel( 31 + x,21 + y,0,146,14 );
	gfx.PutPixel( 32 + x,21 + y,0,146,14 );
	gfx.PutPixel( 33 + x,21 + y,0,146,14 );
	gfx.PutPixel( 34 + x,21 + y,0,146,14 );
	gfx.PutPixel( 61 + x,21 + y,0,146,14 );
	gfx.PutPixel( 62 + x,21 + y,0,146,14 );
	gfx.PutPixel( 63 + x,21 + y,0,146,14 );
	gfx.PutPixel( 64 + x,21 + y,0,146,14 );
	gfx.PutPixel( 65 + x,21 + y,0,146,14 );
	gfx.PutPixel( 66 + x,21 + y,0,146,14 );
	gfx.PutPixel( 81 + x,21 + y,0,146,14 );
	gfx.PutPixel( 82 + x,21 + y,0,146,14 );
	gfx.PutPixel( 83 + x,21 + y,0,146,14 );
	gfx.PutPixel( 18 + x,22 + y,0,146,14 );
	gfx.PutPixel( 19 + x,22 + y,0,146,14 );
	gfx.PutPixel( 20 + x,22 + y,0,146,14 );
	gfx.PutPixel( 21 + x,22 + y,0,146,14 );
	gfx.PutPixel( 22 + x,22 + y,0,146,14 );
	gfx.PutPixel( 23 + x,22 + y,0,146,14 );
	gfx.PutPixel( 24 + x,22 + y,0,146,14 );
	gfx.PutPixel( 25 + x,22 + y,0,146,14 );
	gfx.PutPixel( 26 + x,22 + y,0,146,14 );
	gfx.PutPixel( 27 + x,22 + y,0,146,14 );
	gfx.PutPixel( 28 + x,22 + y,0,146,14 );
	gfx.PutPixel( 29 + x,22 + y,0,146,14 );
	gfx.PutPixel( 30 + x,22 + y,0,146,14 );
	gfx.PutPixel( 31 + x,22 + y,0,146,14 );
	gfx.PutPixel( 32 + x,22 + y,0,146,14 );
	gfx.PutPixel( 33 + x,22 + y,0,146,14 );
	gfx.PutPixel( 34 + x,22 + y,0,146,14 );
	gfx.PutPixel( 35 + x,22 + y,0,25,2 );
	gfx.PutPixel( 62 + x,22 + y,0,146,14 );
	gfx.PutPixel( 63 + x,22 + y,0,146,14 );
	gfx.PutPixel( 64 + x,22 + y,0,146,14 );
	gfx.PutPixel( 65 + x,22 + y,0,146,14 );
	gfx.PutPixel( 66 + x,22 + y,0,146,14 );
	gfx.PutPixel( 81 + x,22 + y,0,146,14 );
	gfx.PutPixel( 82 + x,22 + y,0,146,14 );
	gfx.PutPixel( 83 + x,22 + y,0,146,14 );
	gfx.PutPixel( 17 + x,23 + y,0,3,0 );
	gfx.PutPixel( 18 + x,23 + y,0,146,14 );
	gfx.PutPixel( 19 + x,23 + y,0,146,14 );
	gfx.PutPixel( 20 + x,23 + y,0,146,14 );
	gfx.PutPixel( 21 + x,23 + y,0,146,14 );
	gfx.PutPixel( 22 + x,23 + y,0,146,14 );
	gfx.PutPixel( 23 + x,23 + y,0,146,14 );
	gfx.PutPixel( 24 + x,23 + y,0,146,14 );
	gfx.PutPixel( 25 + x,23 + y,0,146,14 );
	gfx.PutPixel( 26 + x,23 + y,0,146,14 );
	gfx.PutPixel( 27 + x,23 + y,0,146,14 );
	gfx.PutPixel( 28 + x,23 + y,0,146,14 );
	gfx.PutPixel( 30 + x,23 + y,0,146,14 );
	gfx.PutPixel( 31 + x,23 + y,0,146,14 );
	gfx.PutPixel( 32 + x,23 + y,0,146,14 );
	gfx.PutPixel( 33 + x,23 + y,0,146,14 );
	gfx.PutPixel( 34 + x,23 + y,0,146,14 );
	gfx.PutPixel( 35 + x,23 + y,0,25,2 );
	gfx.PutPixel( 63 + x,23 + y,0,146,14 );
	gfx.PutPixel( 64 + x,23 + y,0,146,14 );
	gfx.PutPixel( 65 + x,23 + y,0,146,14 );
	gfx.PutPixel( 66 + x,23 + y,0,146,14 );
	gfx.PutPixel( 81 + x,23 + y,0,146,14 );
	gfx.PutPixel( 82 + x,23 + y,0,146,14 );
	gfx.PutPixel( 83 + x,23 + y,0,146,14 );
	gfx.PutPixel( 17 + x,24 + y,0,146,14 );
	gfx.PutPixel( 18 + x,24 + y,0,146,14 );
	gfx.PutPixel( 19 + x,24 + y,0,146,14 );
	gfx.PutPixel( 20 + x,24 + y,0,146,14 );
	gfx.PutPixel( 21 + x,24 + y,0,146,14 );
	gfx.PutPixel( 22 + x,24 + y,0,146,14 );
	gfx.PutPixel( 23 + x,24 + y,0,146,14 );
	gfx.PutPixel( 24 + x,24 + y,0,146,14 );
	gfx.PutPixel( 25 + x,24 + y,0,146,14 );
	gfx.PutPixel( 26 + x,24 + y,0,146,14 );
	gfx.PutPixel( 27 + x,24 + y,0,146,14 );
	gfx.PutPixel( 30 + x,24 + y,0,146,14 );
	gfx.PutPixel( 31 + x,24 + y,0,146,14 );
	gfx.PutPixel( 32 + x,24 + y,0,146,14 );
	gfx.PutPixel( 33 + x,24 + y,0,146,14 );
	gfx.PutPixel( 34 + x,24 + y,0,146,14 );
	gfx.PutPixel( 35 + x,24 + y,0,146,14 );
	gfx.PutPixel( 36 + x,24 + y,0,146,14 );
	gfx.PutPixel( 37 + x,24 + y,0,146,14 );
	gfx.PutPixel( 38 + x,24 + y,0,146,14 );
	gfx.PutPixel( 39 + x,24 + y,0,146,14 );
	gfx.PutPixel( 40 + x,24 + y,0,146,14 );
	gfx.PutPixel( 41 + x,24 + y,0,146,14 );
	gfx.PutPixel( 42 + x,24 + y,0,146,14 );
	gfx.PutPixel( 43 + x,24 + y,0,146,14 );
	gfx.PutPixel( 44 + x,24 + y,0,146,14 );
	gfx.PutPixel( 45 + x,24 + y,0,146,14 );
	gfx.PutPixel( 46 + x,24 + y,0,146,14 );
	gfx.PutPixel( 47 + x,24 + y,0,146,14 );
	gfx.PutPixel( 48 + x,24 + y,0,146,14 );
	gfx.PutPixel( 49 + x,24 + y,0,146,14 );
	gfx.PutPixel( 50 + x,24 + y,0,146,14 );
	gfx.PutPixel( 51 + x,24 + y,0,146,14 );
	gfx.PutPixel( 52 + x,24 + y,0,146,14 );
	gfx.PutPixel( 53 + x,24 + y,0,146,14 );
	gfx.PutPixel( 54 + x,24 + y,0,146,14 );
	gfx.PutPixel( 55 + x,24 + y,0,146,14 );
	gfx.PutPixel( 56 + x,24 + y,0,146,14 );
	gfx.PutPixel( 57 + x,24 + y,0,146,14 );
	gfx.PutPixel( 58 + x,24 + y,0,146,14 );
	gfx.PutPixel( 59 + x,24 + y,0,146,14 );
	gfx.PutPixel( 60 + x,24 + y,0,146,14 );
	gfx.PutPixel( 61 + x,24 + y,0,146,14 );
	gfx.PutPixel( 62 + x,24 + y,0,146,14 );
	gfx.PutPixel( 63 + x,24 + y,0,146,14 );
	gfx.PutPixel( 64 + x,24 + y,0,146,14 );
	gfx.PutPixel( 65 + x,24 + y,0,146,14 );
	gfx.PutPixel( 66 + x,24 + y,0,146,14 );
	gfx.PutPixel( 81 + x,24 + y,0,146,14 );
	gfx.PutPixel( 82 + x,24 + y,0,146,14 );
	gfx.PutPixel( 83 + x,24 + y,0,146,14 );
	gfx.PutPixel( 16 + x,25 + y,0,146,14 );
	gfx.PutPixel( 17 + x,25 + y,0,146,14 );
	gfx.PutPixel( 18 + x,25 + y,0,146,14 );
	gfx.PutPixel( 19 + x,25 + y,0,146,14 );
	gfx.PutPixel( 20 + x,25 + y,0,146,14 );
	gfx.PutPixel( 21 + x,25 + y,0,146,14 );
	gfx.PutPixel( 22 + x,25 + y,0,146,14 );
	gfx.PutPixel( 23 + x,25 + y,0,146,14 );
	gfx.PutPixel( 24 + x,25 + y,0,146,14 );
	gfx.PutPixel( 25 + x,25 + y,0,146,14 );
	gfx.PutPixel( 26 + x,25 + y,0,146,14 );
	gfx.PutPixel( 30 + x,25 + y,0,146,14 );
	gfx.PutPixel( 31 + x,25 + y,0,146,14 );
	gfx.PutPixel( 32 + x,25 + y,0,146,14 );
	gfx.PutPixel( 33 + x,25 + y,0,146,14 );
	gfx.PutPixel( 34 + x,25 + y,0,146,14 );
	gfx.PutPixel( 35 + x,25 + y,0,146,14 );
	gfx.PutPixel( 36 + x,25 + y,0,146,14 );
	gfx.PutPixel( 37 + x,25 + y,0,146,14 );
	gfx.PutPixel( 38 + x,25 + y,0,146,14 );
	gfx.PutPixel( 39 + x,25 + y,0,146,14 );
	gfx.PutPixel( 40 + x,25 + y,0,146,14 );
	gfx.PutPixel( 41 + x,25 + y,0,146,14 );
	gfx.PutPixel( 42 + x,25 + y,0,146,14 );
	gfx.PutPixel( 43 + x,25 + y,0,146,14 );
	gfx.PutPixel( 44 + x,25 + y,0,146,14 );
	gfx.PutPixel( 45 + x,25 + y,0,146,14 );
	gfx.PutPixel( 46 + x,25 + y,0,146,14 );
	gfx.PutPixel( 47 + x,25 + y,0,146,14 );
	gfx.PutPixel( 48 + x,25 + y,0,146,14 );
	gfx.PutPixel( 49 + x,25 + y,0,146,14 );
	gfx.PutPixel( 50 + x,25 + y,0,146,14 );
	gfx.PutPixel( 51 + x,25 + y,0,146,14 );
	gfx.PutPixel( 52 + x,25 + y,0,146,14 );
	gfx.PutPixel( 53 + x,25 + y,0,146,14 );
	gfx.PutPixel( 54 + x,25 + y,0,146,14 );
	gfx.PutPixel( 55 + x,25 + y,0,146,14 );
	gfx.PutPixel( 56 + x,25 + y,0,146,14 );
	gfx.PutPixel( 57 + x,25 + y,0,146,14 );
	gfx.PutPixel( 58 + x,25 + y,0,146,14 );
	gfx.PutPixel( 59 + x,25 + y,0,146,14 );
	gfx.PutPixel( 60 + x,25 + y,0,146,14 );
	gfx.PutPixel( 61 + x,25 + y,0,146,14 );
	gfx.PutPixel( 62 + x,25 + y,0,146,14 );
	gfx.PutPixel( 63 + x,25 + y,0,146,14 );
	gfx.PutPixel( 64 + x,25 + y,0,146,14 );
	gfx.PutPixel( 65 + x,25 + y,0,146,14 );
	gfx.PutPixel( 66 + x,25 + y,0,146,14 );
	gfx.PutPixel( 81 + x,25 + y,0,146,14 );
	gfx.PutPixel( 82 + x,25 + y,0,146,14 );
	gfx.PutPixel( 83 + x,25 + y,0,146,14 );
	gfx.PutPixel( 15 + x,26 + y,0,146,14 );
	gfx.PutPixel( 16 + x,26 + y,0,146,14 );
	gfx.PutPixel( 17 + x,26 + y,0,146,14 );
	gfx.PutPixel( 18 + x,26 + y,0,146,14 );
	gfx.PutPixel( 19 + x,26 + y,0,146,14 );
	gfx.PutPixel( 20 + x,26 + y,0,146,14 );
	gfx.PutPixel( 21 + x,26 + y,0,146,14 );
	gfx.PutPixel( 22 + x,26 + y,0,146,14 );
	gfx.PutPixel( 23 + x,26 + y,0,146,14 );
	gfx.PutPixel( 24 + x,26 + y,0,146,14 );
	gfx.PutPixel( 25 + x,26 + y,0,146,14 );
	gfx.PutPixel( 30 + x,26 + y,0,146,14 );
	gfx.PutPixel( 31 + x,26 + y,0,146,14 );
	gfx.PutPixel( 32 + x,26 + y,0,146,14 );
	gfx.PutPixel( 33 + x,26 + y,0,146,14 );
	gfx.PutPixel( 34 + x,26 + y,0,146,14 );
	gfx.PutPixel( 35 + x,26 + y,0,146,14 );
	gfx.PutPixel( 36 + x,26 + y,0,146,14 );
	gfx.PutPixel( 37 + x,26 + y,0,146,14 );
	gfx.PutPixel( 38 + x,26 + y,0,146,14 );
	gfx.PutPixel( 39 + x,26 + y,0,146,14 );
	gfx.PutPixel( 40 + x,26 + y,0,146,14 );
	gfx.PutPixel( 41 + x,26 + y,0,146,14 );
	gfx.PutPixel( 42 + x,26 + y,0,146,14 );
	gfx.PutPixel( 43 + x,26 + y,0,146,14 );
	gfx.PutPixel( 44 + x,26 + y,0,146,14 );
	gfx.PutPixel( 45 + x,26 + y,0,146,14 );
	gfx.PutPixel( 46 + x,26 + y,0,146,14 );
	gfx.PutPixel( 47 + x,26 + y,0,146,14 );
	gfx.PutPixel( 48 + x,26 + y,0,146,14 );
	gfx.PutPixel( 49 + x,26 + y,0,146,14 );
	gfx.PutPixel( 50 + x,26 + y,0,146,14 );
	gfx.PutPixel( 51 + x,26 + y,0,146,14 );
	gfx.PutPixel( 52 + x,26 + y,0,146,14 );
	gfx.PutPixel( 53 + x,26 + y,0,146,14 );
	gfx.PutPixel( 54 + x,26 + y,0,146,14 );
	gfx.PutPixel( 55 + x,26 + y,0,146,14 );
	gfx.PutPixel( 56 + x,26 + y,0,146,14 );
	gfx.PutPixel( 57 + x,26 + y,0,146,14 );
	gfx.PutPixel( 58 + x,26 + y,0,146,14 );
	gfx.PutPixel( 59 + x,26 + y,0,146,14 );
	gfx.PutPixel( 60 + x,26 + y,0,146,14 );
	gfx.PutPixel( 61 + x,26 + y,0,146,14 );
	gfx.PutPixel( 62 + x,26 + y,0,146,14 );
	gfx.PutPixel( 63 + x,26 + y,0,146,14 );
	gfx.PutPixel( 64 + x,26 + y,0,146,14 );
	gfx.PutPixel( 65 + x,26 + y,0,146,14 );
	gfx.PutPixel( 66 + x,26 + y,0,146,14 );
	gfx.PutPixel( 81 + x,26 + y,0,146,14 );
	gfx.PutPixel( 82 + x,26 + y,0,146,14 );
	gfx.PutPixel( 83 + x,26 + y,0,146,14 );
	gfx.PutPixel( 14 + x,27 + y,0,146,14 );
	gfx.PutPixel( 15 + x,27 + y,0,146,14 );
	gfx.PutPixel( 16 + x,27 + y,0,146,14 );
	gfx.PutPixel( 17 + x,27 + y,0,146,14 );
	gfx.PutPixel( 18 + x,27 + y,0,146,14 );
	gfx.PutPixel( 19 + x,27 + y,0,146,14 );
	gfx.PutPixel( 20 + x,27 + y,0,146,14 );
	gfx.PutPixel( 21 + x,27 + y,0,146,14 );
	gfx.PutPixel( 22 + x,27 + y,0,146,14 );
	gfx.PutPixel( 23 + x,27 + y,0,146,14 );
	gfx.PutPixel( 24 + x,27 + y,0,146,14 );
	gfx.PutPixel( 30 + x,27 + y,0,146,14 );
	gfx.PutPixel( 31 + x,27 + y,0,146,14 );
	gfx.PutPixel( 32 + x,27 + y,0,146,14 );
	gfx.PutPixel( 33 + x,27 + y,0,146,14 );
	gfx.PutPixel( 34 + x,27 + y,0,146,14 );
	gfx.PutPixel( 35 + x,27 + y,0,146,14 );
	gfx.PutPixel( 36 + x,27 + y,0,146,14 );
	gfx.PutPixel( 37 + x,27 + y,0,146,14 );
	gfx.PutPixel( 38 + x,27 + y,0,146,14 );
	gfx.PutPixel( 39 + x,27 + y,0,146,14 );
	gfx.PutPixel( 40 + x,27 + y,0,146,14 );
	gfx.PutPixel( 41 + x,27 + y,0,146,14 );
	gfx.PutPixel( 42 + x,27 + y,0,146,14 );
	gfx.PutPixel( 43 + x,27 + y,0,146,14 );
	gfx.PutPixel( 44 + x,27 + y,0,146,14 );
	gfx.PutPixel( 45 + x,27 + y,0,146,14 );
	gfx.PutPixel( 46 + x,27 + y,0,146,14 );
	gfx.PutPixel( 64 + x,27 + y,0,146,14 );
	gfx.PutPixel( 65 + x,27 + y,0,146,14 );
	gfx.PutPixel( 66 + x,27 + y,0,146,14 );
	gfx.PutPixel( 81 + x,27 + y,0,146,14 );
	gfx.PutPixel( 82 + x,27 + y,0,146,14 );
	gfx.PutPixel( 83 + x,27 + y,0,146,14 );
	gfx.PutPixel( 13 + x,28 + y,0,146,14 );
	gfx.PutPixel( 14 + x,28 + y,0,146,14 );
	gfx.PutPixel( 15 + x,28 + y,0,146,14 );
	gfx.PutPixel( 16 + x,28 + y,0,146,14 );
	gfx.PutPixel( 17 + x,28 + y,0,146,14 );
	gfx.PutPixel( 18 + x,28 + y,0,146,14 );
	gfx.PutPixel( 19 + x,28 + y,0,146,14 );
	gfx.PutPixel( 20 + x,28 + y,0,146,14 );
	gfx.PutPixel( 21 + x,28 + y,0,146,14 );
	gfx.PutPixel( 22 + x,28 + y,0,146,14 );
	gfx.PutPixel( 23 + x,28 + y,0,146,14 );
	gfx.PutPixel( 30 + x,28 + y,0,146,14 );
	gfx.PutPixel( 31 + x,28 + y,0,146,14 );
	gfx.PutPixel( 32 + x,28 + y,0,146,14 );
	gfx.PutPixel( 33 + x,28 + y,0,146,14 );
	gfx.PutPixel( 34 + x,28 + y,0,146,14 );
	gfx.PutPixel( 35 + x,28 + y,0,146,14 );
	gfx.PutPixel( 36 + x,28 + y,0,146,14 );
	gfx.PutPixel( 37 + x,28 + y,0,146,14 );
	gfx.PutPixel( 38 + x,28 + y,0,146,14 );
	gfx.PutPixel( 39 + x,28 + y,0,146,14 );
	gfx.PutPixel( 40 + x,28 + y,0,146,14 );
	gfx.PutPixel( 41 + x,28 + y,0,146,14 );
	gfx.PutPixel( 42 + x,28 + y,0,146,14 );
	gfx.PutPixel( 43 + x,28 + y,0,146,14 );
	gfx.PutPixel( 44 + x,28 + y,0,146,14 );
	gfx.PutPixel( 45 + x,28 + y,0,146,14 );
	gfx.PutPixel( 46 + x,28 + y,0,146,14 );
	gfx.PutPixel( 47 + x,28 + y,0,146,14 );
	gfx.PutPixel( 64 + x,28 + y,0,146,14 );
	gfx.PutPixel( 65 + x,28 + y,0,146,14 );
	gfx.PutPixel( 66 + x,28 + y,0,146,14 );
	gfx.PutPixel( 81 + x,28 + y,0,146,14 );
	gfx.PutPixel( 82 + x,28 + y,0,146,14 );
	gfx.PutPixel( 83 + x,28 + y,0,146,14 );
	gfx.PutPixel( 12 + x,29 + y,0,146,14 );
	gfx.PutPixel( 13 + x,29 + y,0,146,14 );
	gfx.PutPixel( 14 + x,29 + y,0,146,14 );
	gfx.PutPixel( 15 + x,29 + y,0,146,14 );
	gfx.PutPixel( 16 + x,29 + y,0,146,14 );
	gfx.PutPixel( 17 + x,29 + y,0,146,14 );
	gfx.PutPixel( 18 + x,29 + y,0,146,14 );
	gfx.PutPixel( 19 + x,29 + y,0,146,14 );
	gfx.PutPixel( 20 + x,29 + y,0,146,14 );
	gfx.PutPixel( 21 + x,29 + y,0,146,14 );
	gfx.PutPixel( 22 + x,29 + y,0,146,14 );
	gfx.PutPixel( 23 + x,29 + y,0,146,14 );
	gfx.PutPixel( 30 + x,29 + y,0,146,14 );
	gfx.PutPixel( 31 + x,29 + y,0,146,14 );
	gfx.PutPixel( 32 + x,29 + y,0,146,14 );
	gfx.PutPixel( 33 + x,29 + y,0,146,14 );
	gfx.PutPixel( 34 + x,29 + y,0,146,14 );
	gfx.PutPixel( 35 + x,29 + y,0,146,14 );
	gfx.PutPixel( 36 + x,29 + y,0,146,14 );
	gfx.PutPixel( 37 + x,29 + y,0,146,14 );
	gfx.PutPixel( 38 + x,29 + y,0,146,14 );
	gfx.PutPixel( 39 + x,29 + y,0,146,14 );
	gfx.PutPixel( 40 + x,29 + y,0,146,14 );
	gfx.PutPixel( 41 + x,29 + y,0,146,14 );
	gfx.PutPixel( 42 + x,29 + y,0,146,14 );
	gfx.PutPixel( 43 + x,29 + y,0,146,14 );
	gfx.PutPixel( 44 + x,29 + y,0,146,14 );
	gfx.PutPixel( 45 + x,29 + y,0,146,14 );
	gfx.PutPixel( 46 + x,29 + y,0,146,14 );
	gfx.PutPixel( 47 + x,29 + y,0,146,14 );
	gfx.PutPixel( 63 + x,29 + y,0,25,2 );
	gfx.PutPixel( 64 + x,29 + y,0,146,14 );
	gfx.PutPixel( 65 + x,29 + y,0,146,14 );
	gfx.PutPixel( 66 + x,29 + y,0,146,14 );
	gfx.PutPixel( 81 + x,29 + y,0,146,14 );
	gfx.PutPixel( 82 + x,29 + y,0,146,14 );
	gfx.PutPixel( 83 + x,29 + y,0,146,14 );
	gfx.PutPixel( 11 + x,30 + y,0,146,14 );
	gfx.PutPixel( 12 + x,30 + y,0,146,14 );
	gfx.PutPixel( 13 + x,30 + y,0,146,14 );
	gfx.PutPixel( 14 + x,30 + y,0,146,14 );
	gfx.PutPixel( 15 + x,30 + y,0,146,14 );
	gfx.PutPixel( 16 + x,30 + y,0,146,14 );
	gfx.PutPixel( 17 + x,30 + y,0,146,14 );
	gfx.PutPixel( 18 + x,30 + y,0,146,14 );
	gfx.PutPixel( 19 + x,30 + y,0,146,14 );
	gfx.PutPixel( 20 + x,30 + y,0,146,14 );
	gfx.PutPixel( 21 + x,30 + y,0,146,14 );
	gfx.PutPixel( 22 + x,30 + y,0,146,14 );
	gfx.PutPixel( 30 + x,30 + y,0,146,14 );
	gfx.PutPixel( 31 + x,30 + y,0,146,14 );
	gfx.PutPixel( 32 + x,30 + y,0,146,14 );
	gfx.PutPixel( 33 + x,30 + y,0,146,14 );
	gfx.PutPixel( 34 + x,30 + y,0,146,14 );
	gfx.PutPixel( 35 + x,30 + y,0,146,14 );
	gfx.PutPixel( 36 + x,30 + y,0,146,14 );
	gfx.PutPixel( 37 + x,30 + y,0,146,14 );
	gfx.PutPixel( 38 + x,30 + y,0,146,14 );
	gfx.PutPixel( 39 + x,30 + y,0,146,14 );
	gfx.PutPixel( 40 + x,30 + y,0,146,14 );
	gfx.PutPixel( 41 + x,30 + y,0,146,14 );
	gfx.PutPixel( 42 + x,30 + y,0,146,14 );
	gfx.PutPixel( 43 + x,30 + y,0,146,14 );
	gfx.PutPixel( 44 + x,30 + y,0,146,14 );
	gfx.PutPixel( 45 + x,30 + y,0,146,14 );
	gfx.PutPixel( 46 + x,30 + y,0,146,14 );
	gfx.PutPixel( 47 + x,30 + y,0,146,14 );
	gfx.PutPixel( 63 + x,30 + y,0,146,14 );
	gfx.PutPixel( 64 + x,30 + y,0,146,14 );
	gfx.PutPixel( 65 + x,30 + y,0,146,14 );
	gfx.PutPixel( 66 + x,30 + y,0,146,14 );
	gfx.PutPixel( 80 + x,30 + y,0,25,2 );
	gfx.PutPixel( 81 + x,30 + y,0,146,14 );
	gfx.PutPixel( 82 + x,30 + y,0,146,14 );
	gfx.PutPixel( 83 + x,30 + y,0,146,14 );
	gfx.PutPixel( 10 + x,31 + y,0,70,6 );
	gfx.PutPixel( 11 + x,31 + y,0,146,14 );
	gfx.PutPixel( 12 + x,31 + y,0,146,14 );
	gfx.PutPixel( 13 + x,31 + y,0,146,14 );
	gfx.PutPixel( 14 + x,31 + y,0,146,14 );
	gfx.PutPixel( 15 + x,31 + y,0,146,14 );
	gfx.PutPixel( 16 + x,31 + y,0,146,14 );
	gfx.PutPixel( 17 + x,31 + y,0,146,14 );
	gfx.PutPixel( 18 + x,31 + y,0,146,14 );
	gfx.PutPixel( 19 + x,31 + y,0,146,14 );
	gfx.PutPixel( 20 + x,31 + y,0,146,14 );
	gfx.PutPixel( 21 + x,31 + y,0,146,14 );
	gfx.PutPixel( 30 + x,31 + y,0,146,14 );
	gfx.PutPixel( 31 + x,31 + y,0,146,14 );
	gfx.PutPixel( 32 + x,31 + y,0,146,14 );
	gfx.PutPixel( 33 + x,31 + y,0,146,14 );
	gfx.PutPixel( 34 + x,31 + y,0,146,14 );
	gfx.PutPixel( 35 + x,31 + y,0,146,14 );
	gfx.PutPixel( 36 + x,31 + y,0,146,14 );
	gfx.PutPixel( 37 + x,31 + y,0,146,14 );
	gfx.PutPixel( 38 + x,31 + y,0,146,14 );
	gfx.PutPixel( 39 + x,31 + y,0,146,14 );
	gfx.PutPixel( 40 + x,31 + y,0,146,14 );
	gfx.PutPixel( 41 + x,31 + y,0,146,14 );
	gfx.PutPixel( 42 + x,31 + y,0,146,14 );
	gfx.PutPixel( 43 + x,31 + y,0,146,14 );
	gfx.PutPixel( 44 + x,31 + y,0,146,14 );
	gfx.PutPixel( 45 + x,31 + y,0,146,14 );
	gfx.PutPixel( 46 + x,31 + y,0,146,14 );
	gfx.PutPixel( 47 + x,31 + y,0,146,14 );
	gfx.PutPixel( 63 + x,31 + y,0,146,14 );
	gfx.PutPixel( 64 + x,31 + y,0,146,14 );
	gfx.PutPixel( 65 + x,31 + y,0,146,14 );
	gfx.PutPixel( 66 + x,31 + y,0,146,14 );
	gfx.PutPixel( 67 + x,31 + y,0,146,14 );
	gfx.PutPixel( 80 + x,31 + y,0,146,14 );
	gfx.PutPixel( 81 + x,31 + y,0,146,14 );
	gfx.PutPixel( 82 + x,31 + y,0,146,14 );
	gfx.PutPixel( 10 + x,32 + y,0,146,14 );
	gfx.PutPixel( 11 + x,32 + y,0,146,14 );
	gfx.PutPixel( 12 + x,32 + y,0,146,14 );
	gfx.PutPixel( 13 + x,32 + y,0,146,14 );
	gfx.PutPixel( 14 + x,32 + y,0,146,14 );
	gfx.PutPixel( 15 + x,32 + y,0,146,14 );
	gfx.PutPixel( 16 + x,32 + y,0,146,14 );
	gfx.PutPixel( 17 + x,32 + y,0,146,14 );
	gfx.PutPixel( 18 + x,32 + y,0,146,14 );
	gfx.PutPixel( 19 + x,32 + y,0,146,14 );
	gfx.PutPixel( 20 + x,32 + y,0,146,14 );
	gfx.PutPixel( 32 + x,32 + y,0,146,14 );
	gfx.PutPixel( 33 + x,32 + y,0,146,14 );
	gfx.PutPixel( 34 + x,32 + y,0,146,14 );
	gfx.PutPixel( 35 + x,32 + y,0,146,14 );
	gfx.PutPixel( 36 + x,32 + y,0,146,14 );
	gfx.PutPixel( 37 + x,32 + y,0,146,14 );
	gfx.PutPixel( 38 + x,32 + y,0,146,14 );
	gfx.PutPixel( 39 + x,32 + y,0,146,14 );
	gfx.PutPixel( 40 + x,32 + y,0,146,14 );
	gfx.PutPixel( 41 + x,32 + y,0,146,14 );
	gfx.PutPixel( 42 + x,32 + y,0,146,14 );
	gfx.PutPixel( 43 + x,32 + y,0,146,14 );
	gfx.PutPixel( 44 + x,32 + y,0,146,14 );
	gfx.PutPixel( 45 + x,32 + y,0,146,14 );
	gfx.PutPixel( 46 + x,32 + y,0,118,11 );
	gfx.PutPixel( 62 + x,32 + y,0,146,14 );
	gfx.PutPixel( 63 + x,32 + y,0,146,14 );
	gfx.PutPixel( 64 + x,32 + y,0,146,14 );
	gfx.PutPixel( 65 + x,32 + y,0,146,14 );
	gfx.PutPixel( 66 + x,32 + y,0,146,14 );
	gfx.PutPixel( 67 + x,32 + y,0,146,14 );
	gfx.PutPixel( 68 + x,32 + y,0,25,2 );
	gfx.PutPixel( 79 + x,32 + y,0,146,14 );
	gfx.PutPixel( 80 + x,32 + y,0,146,14 );
	gfx.PutPixel( 81 + x,32 + y,0,146,14 );
	gfx.PutPixel( 82 + x,32 + y,0,146,14 );
	gfx.PutPixel( 9 + x,33 + y,0,146,14 );
	gfx.PutPixel( 10 + x,33 + y,0,146,14 );
	gfx.PutPixel( 11 + x,33 + y,0,146,14 );
	gfx.PutPixel( 12 + x,33 + y,0,146,14 );
	gfx.PutPixel( 13 + x,33 + y,0,146,14 );
	gfx.PutPixel( 14 + x,33 + y,0,146,14 );
	gfx.PutPixel( 15 + x,33 + y,0,146,14 );
	gfx.PutPixel( 16 + x,33 + y,0,146,14 );
	gfx.PutPixel( 17 + x,33 + y,0,146,14 );
	gfx.PutPixel( 18 + x,33 + y,0,146,14 );
	gfx.PutPixel( 19 + x,33 + y,0,146,14 );
	gfx.PutPixel( 35 + x,33 + y,0,146,14 );
	gfx.PutPixel( 36 + x,33 + y,0,146,14 );
	gfx.PutPixel( 37 + x,33 + y,0,146,14 );
	gfx.PutPixel( 62 + x,33 + y,0,146,14 );
	gfx.PutPixel( 63 + x,33 + y,0,146,14 );
	gfx.PutPixel( 64 + x,33 + y,0,146,14 );
	gfx.PutPixel( 65 + x,33 + y,0,146,14 );
	gfx.PutPixel( 66 + x,33 + y,0,146,14 );
	gfx.PutPixel( 67 + x,33 + y,0,146,14 );
	gfx.PutPixel( 68 + x,33 + y,0,146,14 );
	gfx.PutPixel( 69 + x,33 + y,0,146,14 );
	gfx.PutPixel( 70 + x,33 + y,0,146,14 );
	gfx.PutPixel( 71 + x,33 + y,0,146,14 );
	gfx.PutPixel( 72 + x,33 + y,0,146,14 );
	gfx.PutPixel( 73 + x,33 + y,0,146,14 );
	gfx.PutPixel( 74 + x,33 + y,0,146,14 );
	gfx.PutPixel( 75 + x,33 + y,0,146,14 );
	gfx.PutPixel( 76 + x,33 + y,0,146,14 );
	gfx.PutPixel( 77 + x,33 + y,0,146,14 );
	gfx.PutPixel( 78 + x,33 + y,0,146,14 );
	gfx.PutPixel( 79 + x,33 + y,0,146,14 );
	gfx.PutPixel( 80 + x,33 + y,0,146,14 );
	gfx.PutPixel( 81 + x,33 + y,0,146,14 );
	gfx.PutPixel( 82 + x,33 + y,0,25,2 );
	gfx.PutPixel( 8 + x,34 + y,0,146,14 );
	gfx.PutPixel( 9 + x,34 + y,0,146,14 );
	gfx.PutPixel( 10 + x,34 + y,0,146,14 );
	gfx.PutPixel( 11 + x,34 + y,0,146,14 );
	gfx.PutPixel( 12 + x,34 + y,0,146,14 );
	gfx.PutPixel( 13 + x,34 + y,0,146,14 );
	gfx.PutPixel( 14 + x,34 + y,0,146,14 );
	gfx.PutPixel( 15 + x,34 + y,0,146,14 );
	gfx.PutPixel( 16 + x,34 + y,0,146,14 );
	gfx.PutPixel( 17 + x,34 + y,0,146,14 );
	gfx.PutPixel( 18 + x,34 + y,0,146,14 );
	gfx.PutPixel( 35 + x,34 + y,0,146,14 );
	gfx.PutPixel( 36 + x,34 + y,0,146,14 );
	gfx.PutPixel( 37 + x,34 + y,0,146,14 );
	gfx.PutPixel( 38 + x,34 + y,0,146,14 );
	gfx.PutPixel( 61 + x,34 + y,0,146,14 );
	gfx.PutPixel( 62 + x,34 + y,0,146,14 );
	gfx.PutPixel( 63 + x,34 + y,0,146,14 );
	gfx.PutPixel( 64 + x,34 + y,0,146,14 );
	gfx.PutPixel( 65 + x,34 + y,0,146,14 );
	gfx.PutPixel( 66 + x,34 + y,0,146,14 );
	gfx.PutPixel( 67 + x,34 + y,0,146,14 );
	gfx.PutPixel( 68 + x,34 + y,0,146,14 );
	gfx.PutPixel( 69 + x,34 + y,0,146,14 );
	gfx.PutPixel( 70 + x,34 + y,0,146,14 );
	gfx.PutPixel( 71 + x,34 + y,0,146,14 );
	gfx.PutPixel( 72 + x,34 + y,0,146,14 );
	gfx.PutPixel( 73 + x,34 + y,0,146,14 );
	gfx.PutPixel( 74 + x,34 + y,0,146,14 );
	gfx.PutPixel( 75 + x,34 + y,0,146,14 );
	gfx.PutPixel( 76 + x,34 + y,0,146,14 );
	gfx.PutPixel( 77 + x,34 + y,0,146,14 );
	gfx.PutPixel( 78 + x,34 + y,0,146,14 );
	gfx.PutPixel( 79 + x,34 + y,0,146,14 );
	gfx.PutPixel( 80 + x,34 + y,0,146,14 );
	gfx.PutPixel( 81 + x,34 + y,0,146,14 );
	gfx.PutPixel( 8 + x,35 + y,0,146,14 );
	gfx.PutPixel( 9 + x,35 + y,0,146,14 );
	gfx.PutPixel( 10 + x,35 + y,0,146,14 );
	gfx.PutPixel( 11 + x,35 + y,0,146,14 );
	gfx.PutPixel( 12 + x,35 + y,0,146,14 );
	gfx.PutPixel( 13 + x,35 + y,0,146,14 );
	gfx.PutPixel( 14 + x,35 + y,0,146,14 );
	gfx.PutPixel( 15 + x,35 + y,0,146,14 );
	gfx.PutPixel( 16 + x,35 + y,0,146,14 );
	gfx.PutPixel( 17 + x,35 + y,0,146,14 );
	gfx.PutPixel( 36 + x,35 + y,0,146,14 );
	gfx.PutPixel( 37 + x,35 + y,0,146,14 );
	gfx.PutPixel( 38 + x,35 + y,0,146,14 );
	gfx.PutPixel( 39 + x,35 + y,0,146,14 );
	gfx.PutPixel( 60 + x,35 + y,0,146,14 );
	gfx.PutPixel( 61 + x,35 + y,0,146,14 );
	gfx.PutPixel( 62 + x,35 + y,0,146,14 );
	gfx.PutPixel( 63 + x,35 + y,0,146,14 );
	gfx.PutPixel( 64 + x,35 + y,0,146,14 );
	gfx.PutPixel( 65 + x,35 + y,0,146,14 );
	gfx.PutPixel( 66 + x,35 + y,0,146,14 );
	gfx.PutPixel( 67 + x,35 + y,0,146,14 );
	gfx.PutPixel( 68 + x,35 + y,0,146,14 );
	gfx.PutPixel( 69 + x,35 + y,0,146,14 );
	gfx.PutPixel( 70 + x,35 + y,0,146,14 );
	gfx.PutPixel( 71 + x,35 + y,0,146,14 );
	gfx.PutPixel( 72 + x,35 + y,0,146,14 );
	gfx.PutPixel( 73 + x,35 + y,0,146,14 );
	gfx.PutPixel( 74 + x,35 + y,0,146,14 );
	gfx.PutPixel( 75 + x,35 + y,0,146,14 );
	gfx.PutPixel( 76 + x,35 + y,0,146,14 );
	gfx.PutPixel( 77 + x,35 + y,0,146,14 );
	gfx.PutPixel( 78 + x,35 + y,0,146,14 );
	gfx.PutPixel( 79 + x,35 + y,0,146,14 );
	gfx.PutPixel( 8 + x,36 + y,0,146,14 );
	gfx.PutPixel( 9 + x,36 + y,0,146,14 );
	gfx.PutPixel( 10 + x,36 + y,0,146,14 );
	gfx.PutPixel( 11 + x,36 + y,0,146,14 );
	gfx.PutPixel( 12 + x,36 + y,0,146,14 );
	gfx.PutPixel( 13 + x,36 + y,0,146,14 );
	gfx.PutPixel( 14 + x,36 + y,0,146,14 );
	gfx.PutPixel( 15 + x,36 + y,0,146,14 );
	gfx.PutPixel( 16 + x,36 + y,0,146,14 );
	gfx.PutPixel( 17 + x,36 + y,0,146,14 );
	gfx.PutPixel( 18 + x,36 + y,0,146,14 );
	gfx.PutPixel( 37 + x,36 + y,0,146,14 );
	gfx.PutPixel( 38 + x,36 + y,0,146,14 );
	gfx.PutPixel( 39 + x,36 + y,0,146,14 );
	gfx.PutPixel( 40 + x,36 + y,0,146,14 );
	gfx.PutPixel( 59 + x,36 + y,0,146,14 );
	gfx.PutPixel( 60 + x,36 + y,0,146,14 );
	gfx.PutPixel( 61 + x,36 + y,0,146,14 );
	gfx.PutPixel( 62 + x,36 + y,0,146,14 );
	gfx.PutPixel( 63 + x,36 + y,0,146,14 );
	gfx.PutPixel( 64 + x,36 + y,0,146,14 );
	gfx.PutPixel( 65 + x,36 + y,0,146,14 );
	gfx.PutPixel( 66 + x,36 + y,0,146,14 );
	gfx.PutPixel( 67 + x,36 + y,0,146,14 );
	gfx.PutPixel( 68 + x,36 + y,0,146,14 );
	gfx.PutPixel( 69 + x,36 + y,0,146,14 );
	gfx.PutPixel( 70 + x,36 + y,0,146,14 );
	gfx.PutPixel( 71 + x,36 + y,0,146,14 );
	gfx.PutPixel( 72 + x,36 + y,0,146,14 );
	gfx.PutPixel( 73 + x,36 + y,0,146,14 );
	gfx.PutPixel( 74 + x,36 + y,0,146,14 );
	gfx.PutPixel( 9 + x,37 + y,0,146,14 );
	gfx.PutPixel( 10 + x,37 + y,0,146,14 );
	gfx.PutPixel( 11 + x,37 + y,0,146,14 );
	gfx.PutPixel( 12 + x,37 + y,0,146,14 );
	gfx.PutPixel( 13 + x,37 + y,0,146,14 );
	gfx.PutPixel( 14 + x,37 + y,0,146,14 );
	gfx.PutPixel( 15 + x,37 + y,0,146,14 );
	gfx.PutPixel( 16 + x,37 + y,0,146,14 );
	gfx.PutPixel( 17 + x,37 + y,0,146,14 );
	gfx.PutPixel( 18 + x,37 + y,0,146,14 );
	gfx.PutPixel( 19 + x,37 + y,0,146,14 );
	gfx.PutPixel( 37 + x,37 + y,0,70,6 );
	gfx.PutPixel( 38 + x,37 + y,0,146,14 );
	gfx.PutPixel( 39 + x,37 + y,0,146,14 );
	gfx.PutPixel( 40 + x,37 + y,0,146,14 );
	gfx.PutPixel( 41 + x,37 + y,0,146,14 );
	gfx.PutPixel( 58 + x,37 + y,0,146,14 );
	gfx.PutPixel( 59 + x,37 + y,0,146,14 );
	gfx.PutPixel( 60 + x,37 + y,0,146,14 );
	gfx.PutPixel( 61 + x,37 + y,0,146,14 );
	gfx.PutPixel( 62 + x,37 + y,0,146,14 );
	gfx.PutPixel( 63 + x,37 + y,0,146,14 );
	gfx.PutPixel( 64 + x,37 + y,0,146,14 );
	gfx.PutPixel( 65 + x,37 + y,0,146,14 );
	gfx.PutPixel( 66 + x,37 + y,0,146,14 );
	gfx.PutPixel( 67 + x,37 + y,0,146,14 );
	gfx.PutPixel( 68 + x,37 + y,0,146,14 );
	gfx.PutPixel( 69 + x,37 + y,0,146,14 );
	gfx.PutPixel( 70 + x,37 + y,0,146,14 );
	gfx.PutPixel( 71 + x,37 + y,0,146,14 );
	gfx.PutPixel( 72 + x,37 + y,0,146,14 );
	gfx.PutPixel( 73 + x,37 + y,0,146,14 );
	gfx.PutPixel( 74 + x,37 + y,0,146,14 );
	gfx.PutPixel( 9 + x,38 + y,0,146,14 );
	gfx.PutPixel( 10 + x,38 + y,0,146,14 );
	gfx.PutPixel( 11 + x,38 + y,0,146,14 );
	gfx.PutPixel( 12 + x,38 + y,0,146,14 );
	gfx.PutPixel( 13 + x,38 + y,0,146,14 );
	gfx.PutPixel( 14 + x,38 + y,0,146,14 );
	gfx.PutPixel( 15 + x,38 + y,0,146,14 );
	gfx.PutPixel( 16 + x,38 + y,0,146,14 );
	gfx.PutPixel( 17 + x,38 + y,0,146,14 );
	gfx.PutPixel( 18 + x,38 + y,0,146,14 );
	gfx.PutPixel( 19 + x,38 + y,0,146,14 );
	gfx.PutPixel( 20 + x,38 + y,0,146,14 );
	gfx.PutPixel( 38 + x,38 + y,0,70,6 );
	gfx.PutPixel( 39 + x,38 + y,0,146,14 );
	gfx.PutPixel( 40 + x,38 + y,0,146,14 );
	gfx.PutPixel( 41 + x,38 + y,0,146,14 );
	gfx.PutPixel( 42 + x,38 + y,0,146,14 );
	gfx.PutPixel( 43 + x,38 + y,0,146,14 );
	gfx.PutPixel( 56 + x,38 + y,0,146,14 );
	gfx.PutPixel( 57 + x,38 + y,0,146,14 );
	gfx.PutPixel( 58 + x,38 + y,0,146,14 );
	gfx.PutPixel( 59 + x,38 + y,0,146,14 );
	gfx.PutPixel( 60 + x,38 + y,0,146,14 );
	gfx.PutPixel( 61 + x,38 + y,0,146,14 );
	gfx.PutPixel( 62 + x,38 + y,0,146,14 );
	gfx.PutPixel( 63 + x,38 + y,0,146,14 );
	gfx.PutPixel( 64 + x,38 + y,0,146,14 );
	gfx.PutPixel( 65 + x,38 + y,0,146,14 );
	gfx.PutPixel( 66 + x,38 + y,0,146,14 );
	gfx.PutPixel( 67 + x,38 + y,0,146,14 );
	gfx.PutPixel( 68 + x,38 + y,0,146,14 );
	gfx.PutPixel( 69 + x,38 + y,0,146,14 );
	gfx.PutPixel( 70 + x,38 + y,0,146,14 );
	gfx.PutPixel( 71 + x,38 + y,0,146,14 );
	gfx.PutPixel( 72 + x,38 + y,0,146,14 );
	gfx.PutPixel( 73 + x,38 + y,0,146,14 );
	gfx.PutPixel( 74 + x,38 + y,0,146,14 );
	gfx.PutPixel( 10 + x,39 + y,0,146,14 );
	gfx.PutPixel( 11 + x,39 + y,0,146,14 );
	gfx.PutPixel( 12 + x,39 + y,0,146,14 );
	gfx.PutPixel( 13 + x,39 + y,0,146,14 );
	gfx.PutPixel( 14 + x,39 + y,0,146,14 );
	gfx.PutPixel( 15 + x,39 + y,0,146,14 );
	gfx.PutPixel( 16 + x,39 + y,0,146,14 );
	gfx.PutPixel( 17 + x,39 + y,0,146,14 );
	gfx.PutPixel( 18 + x,39 + y,0,146,14 );
	gfx.PutPixel( 19 + x,39 + y,0,146,14 );
	gfx.PutPixel( 20 + x,39 + y,0,146,14 );
	gfx.PutPixel( 21 + x,39 + y,0,146,14 );
	gfx.PutPixel( 40 + x,39 + y,0,146,14 );
	gfx.PutPixel( 41 + x,39 + y,0,146,14 );
	gfx.PutPixel( 42 + x,39 + y,0,146,14 );
	gfx.PutPixel( 43 + x,39 + y,0,146,14 );
	gfx.PutPixel( 44 + x,39 + y,0,146,14 );
	gfx.PutPixel( 45 + x,39 + y,0,146,14 );
	gfx.PutPixel( 46 + x,39 + y,0,146,14 );
	gfx.PutPixel( 53 + x,39 + y,0,146,14 );
	gfx.PutPixel( 54 + x,39 + y,0,146,14 );
	gfx.PutPixel( 55 + x,39 + y,0,146,14 );
	gfx.PutPixel( 56 + x,39 + y,0,146,14 );
	gfx.PutPixel( 57 + x,39 + y,0,146,14 );
	gfx.PutPixel( 58 + x,39 + y,0,146,14 );
	gfx.PutPixel( 59 + x,39 + y,0,146,14 );
	gfx.PutPixel( 60 + x,39 + y,0,146,14 );
	gfx.PutPixel( 61 + x,39 + y,0,146,14 );
	gfx.PutPixel( 62 + x,39 + y,0,146,14 );
	gfx.PutPixel( 63 + x,39 + y,0,146,14 );
	gfx.PutPixel( 64 + x,39 + y,0,146,14 );
	gfx.PutPixel( 65 + x,39 + y,0,146,14 );
	gfx.PutPixel( 66 + x,39 + y,0,146,14 );
	gfx.PutPixel( 67 + x,39 + y,0,146,14 );
	gfx.PutPixel( 68 + x,39 + y,0,146,14 );
	gfx.PutPixel( 69 + x,39 + y,0,146,14 );
	gfx.PutPixel( 70 + x,39 + y,0,146,14 );
	gfx.PutPixel( 71 + x,39 + y,0,146,14 );
	gfx.PutPixel( 72 + x,39 + y,0,146,14 );
	gfx.PutPixel( 73 + x,39 + y,0,146,14 );
	gfx.PutPixel( 74 + x,39 + y,0,146,14 );
	gfx.PutPixel( 11 + x,40 + y,0,146,14 );
	gfx.PutPixel( 12 + x,40 + y,0,146,14 );
	gfx.PutPixel( 13 + x,40 + y,0,146,14 );
	gfx.PutPixel( 14 + x,40 + y,0,146,14 );
	gfx.PutPixel( 15 + x,40 + y,0,146,14 );
	gfx.PutPixel( 16 + x,40 + y,0,146,14 );
	gfx.PutPixel( 17 + x,40 + y,0,146,14 );
	gfx.PutPixel( 18 + x,40 + y,0,146,14 );
	gfx.PutPixel( 19 + x,40 + y,0,146,14 );
	gfx.PutPixel( 20 + x,40 + y,0,146,14 );
	gfx.PutPixel( 21 + x,40 + y,0,146,14 );
	gfx.PutPixel( 22 + x,40 + y,0,146,14 );
	gfx.PutPixel( 41 + x,40 + y,0,146,14 );
	gfx.PutPixel( 42 + x,40 + y,0,146,14 );
	gfx.PutPixel( 43 + x,40 + y,0,146,14 );
	gfx.PutPixel( 44 + x,40 + y,0,146,14 );
	gfx.PutPixel( 45 + x,40 + y,0,146,14 );
	gfx.PutPixel( 46 + x,40 + y,0,146,14 );
	gfx.PutPixel( 47 + x,40 + y,0,146,14 );
	gfx.PutPixel( 48 + x,40 + y,0,146,14 );
	gfx.PutPixel( 49 + x,40 + y,0,146,14 );
	gfx.PutPixel( 50 + x,40 + y,0,146,14 );
	gfx.PutPixel( 51 + x,40 + y,0,146,14 );
	gfx.PutPixel( 52 + x,40 + y,0,146,14 );
	gfx.PutPixel( 53 + x,40 + y,0,146,14 );
	gfx.PutPixel( 54 + x,40 + y,0,146,14 );
	gfx.PutPixel( 55 + x,40 + y,0,146,14 );
	gfx.PutPixel( 56 + x,40 + y,0,146,14 );
	gfx.PutPixel( 57 + x,40 + y,0,146,14 );
	gfx.PutPixel( 58 + x,40 + y,0,146,14 );
	gfx.PutPixel( 59 + x,40 + y,0,146,14 );
	gfx.PutPixel( 60 + x,40 + y,0,146,14 );
	gfx.PutPixel( 61 + x,40 + y,0,146,14 );
	gfx.PutPixel( 62 + x,40 + y,0,146,14 );
	gfx.PutPixel( 63 + x,40 + y,0,146,14 );
	gfx.PutPixel( 64 + x,40 + y,0,146,14 );
	gfx.PutPixel( 65 + x,40 + y,0,146,14 );
	gfx.PutPixel( 66 + x,40 + y,0,146,14 );
	gfx.PutPixel( 67 + x,40 + y,0,146,14 );
	gfx.PutPixel( 68 + x,40 + y,0,146,14 );
	gfx.PutPixel( 69 + x,40 + y,0,146,14 );
	gfx.PutPixel( 70 + x,40 + y,0,146,14 );
	gfx.PutPixel( 71 + x,40 + y,0,146,14 );
	gfx.PutPixel( 72 + x,40 + y,0,146,14 );
	gfx.PutPixel( 73 + x,40 + y,0,146,14 );
	gfx.PutPixel( 74 + x,40 + y,0,146,14 );
	gfx.PutPixel( 75 + x,40 + y,0,146,14 );
	gfx.PutPixel( 76 + x,40 + y,0,146,14 );
	gfx.PutPixel( 77 + x,40 + y,0,70,6 );
	gfx.PutPixel( 12 + x,41 + y,0,146,14 );
	gfx.PutPixel( 13 + x,41 + y,0,146,14 );
	gfx.PutPixel( 14 + x,41 + y,0,146,14 );
	gfx.PutPixel( 15 + x,41 + y,0,146,14 );
	gfx.PutPixel( 16 + x,41 + y,0,146,14 );
	gfx.PutPixel( 17 + x,41 + y,0,146,14 );
	gfx.PutPixel( 18 + x,41 + y,0,146,14 );
	gfx.PutPixel( 19 + x,41 + y,0,146,14 );
	gfx.PutPixel( 20 + x,41 + y,0,146,14 );
	gfx.PutPixel( 21 + x,41 + y,0,146,14 );
	gfx.PutPixel( 22 + x,41 + y,0,146,14 );
	gfx.PutPixel( 23 + x,41 + y,0,146,14 );
	gfx.PutPixel( 40 + x,41 + y,0,146,14 );
	gfx.PutPixel( 41 + x,41 + y,0,146,14 );
	gfx.PutPixel( 42 + x,41 + y,0,146,14 );
	gfx.PutPixel( 43 + x,41 + y,0,146,14 );
	gfx.PutPixel( 44 + x,41 + y,0,146,14 );
	gfx.PutPixel( 45 + x,41 + y,0,146,14 );
	gfx.PutPixel( 46 + x,41 + y,0,146,14 );
	gfx.PutPixel( 47 + x,41 + y,0,146,14 );
	gfx.PutPixel( 48 + x,41 + y,0,146,14 );
	gfx.PutPixel( 49 + x,41 + y,0,146,14 );
	gfx.PutPixel( 50 + x,41 + y,0,146,14 );
	gfx.PutPixel( 51 + x,41 + y,0,146,14 );
	gfx.PutPixel( 52 + x,41 + y,0,146,14 );
	gfx.PutPixel( 53 + x,41 + y,0,146,14 );
	gfx.PutPixel( 54 + x,41 + y,0,146,14 );
	gfx.PutPixel( 55 + x,41 + y,0,146,14 );
	gfx.PutPixel( 56 + x,41 + y,0,146,14 );
	gfx.PutPixel( 57 + x,41 + y,0,146,14 );
	gfx.PutPixel( 58 + x,41 + y,0,146,14 );
	gfx.PutPixel( 59 + x,41 + y,0,146,14 );
	gfx.PutPixel( 60 + x,41 + y,0,146,14 );
	gfx.PutPixel( 61 + x,41 + y,0,146,14 );
	gfx.PutPixel( 62 + x,41 + y,0,146,14 );
	gfx.PutPixel( 63 + x,41 + y,0,146,14 );
	gfx.PutPixel( 64 + x,41 + y,0,146,14 );
	gfx.PutPixel( 65 + x,41 + y,0,146,14 );
	gfx.PutPixel( 66 + x,41 + y,0,146,14 );
	gfx.PutPixel( 67 + x,41 + y,0,146,14 );
	gfx.PutPixel( 68 + x,41 + y,0,146,14 );
	gfx.PutPixel( 69 + x,41 + y,0,146,14 );
	gfx.PutPixel( 70 + x,41 + y,0,146,14 );
	gfx.PutPixel( 71 + x,41 + y,0,146,14 );
	gfx.PutPixel( 72 + x,41 + y,0,146,14 );
	gfx.PutPixel( 73 + x,41 + y,0,146,14 );
	gfx.PutPixel( 74 + x,41 + y,0,146,14 );
	gfx.PutPixel( 75 + x,41 + y,0,146,14 );
	gfx.PutPixel( 76 + x,41 + y,0,146,14 );
	gfx.PutPixel( 77 + x,41 + y,0,146,14 );
	gfx.PutPixel( 78 + x,41 + y,0,146,14 );
	gfx.PutPixel( 3 + x,42 + y,0,25,2 );
	gfx.PutPixel( 4 + x,42 + y,0,146,14 );
	gfx.PutPixel( 5 + x,42 + y,0,146,14 );
	gfx.PutPixel( 6 + x,42 + y,0,25,2 );
	gfx.PutPixel( 13 + x,42 + y,0,146,14 );
	gfx.PutPixel( 14 + x,42 + y,0,146,14 );
	gfx.PutPixel( 15 + x,42 + y,0,146,14 );
	gfx.PutPixel( 16 + x,42 + y,0,146,14 );
	gfx.PutPixel( 17 + x,42 + y,0,146,14 );
	gfx.PutPixel( 18 + x,42 + y,0,146,14 );
	gfx.PutPixel( 19 + x,42 + y,0,146,14 );
	gfx.PutPixel( 20 + x,42 + y,0,146,14 );
	gfx.PutPixel( 21 + x,42 + y,0,146,14 );
	gfx.PutPixel( 22 + x,42 + y,0,146,14 );
	gfx.PutPixel( 23 + x,42 + y,0,146,14 );
	gfx.PutPixel( 24 + x,42 + y,0,146,14 );
	gfx.PutPixel( 39 + x,42 + y,0,146,14 );
	gfx.PutPixel( 40 + x,42 + y,0,146,14 );
	gfx.PutPixel( 41 + x,42 + y,0,146,14 );
	gfx.PutPixel( 42 + x,42 + y,0,146,14 );
	gfx.PutPixel( 43 + x,42 + y,0,146,14 );
	gfx.PutPixel( 44 + x,42 + y,0,146,14 );
	gfx.PutPixel( 45 + x,42 + y,0,146,14 );
	gfx.PutPixel( 46 + x,42 + y,0,146,14 );
	gfx.PutPixel( 47 + x,42 + y,0,146,14 );
	gfx.PutPixel( 48 + x,42 + y,0,146,14 );
	gfx.PutPixel( 49 + x,42 + y,0,146,14 );
	gfx.PutPixel( 50 + x,42 + y,0,146,14 );
	gfx.PutPixel( 51 + x,42 + y,0,146,14 );
	gfx.PutPixel( 52 + x,42 + y,0,146,14 );
	gfx.PutPixel( 53 + x,42 + y,0,146,14 );
	gfx.PutPixel( 54 + x,42 + y,0,146,14 );
	gfx.PutPixel( 55 + x,42 + y,0,146,14 );
	gfx.PutPixel( 56 + x,42 + y,0,146,14 );
	gfx.PutPixel( 57 + x,42 + y,0,146,14 );
	gfx.PutPixel( 58 + x,42 + y,0,146,14 );
	gfx.PutPixel( 59 + x,42 + y,0,146,14 );
	gfx.PutPixel( 60 + x,42 + y,0,146,14 );
	gfx.PutPixel( 61 + x,42 + y,0,146,14 );
	gfx.PutPixel( 62 + x,42 + y,0,146,14 );
	gfx.PutPixel( 63 + x,42 + y,0,146,14 );
	gfx.PutPixel( 64 + x,42 + y,0,146,14 );
	gfx.PutPixel( 65 + x,42 + y,0,146,14 );
	gfx.PutPixel( 66 + x,42 + y,0,146,14 );
	gfx.PutPixel( 67 + x,42 + y,0,146,14 );
	gfx.PutPixel( 68 + x,42 + y,0,146,14 );
	gfx.PutPixel( 69 + x,42 + y,0,146,14 );
	gfx.PutPixel( 70 + x,42 + y,0,146,14 );
	gfx.PutPixel( 71 + x,42 + y,0,146,14 );
	gfx.PutPixel( 72 + x,42 + y,0,146,14 );
	gfx.PutPixel( 73 + x,42 + y,0,146,14 );
	gfx.PutPixel( 74 + x,42 + y,0,146,14 );
	gfx.PutPixel( 75 + x,42 + y,0,146,14 );
	gfx.PutPixel( 76 + x,42 + y,0,146,14 );
	gfx.PutPixel( 77 + x,42 + y,0,146,14 );
	gfx.PutPixel( 78 + x,42 + y,0,146,14 );
	gfx.PutPixel( 79 + x,42 + y,0,146,14 );
	gfx.PutPixel( 1 + x,43 + y,0,146,14 );
	gfx.PutPixel( 2 + x,43 + y,0,146,14 );
	gfx.PutPixel( 3 + x,43 + y,0,146,14 );
	gfx.PutPixel( 4 + x,43 + y,0,146,14 );
	gfx.PutPixel( 5 + x,43 + y,0,146,14 );
	gfx.PutPixel( 6 + x,43 + y,0,146,14 );
	gfx.PutPixel( 7 + x,43 + y,0,146,14 );
	gfx.PutPixel( 8 + x,43 + y,0,146,14 );
	gfx.PutPixel( 9 + x,43 + y,0,146,14 );
	gfx.PutPixel( 10 + x,43 + y,0,146,14 );
	gfx.PutPixel( 11 + x,43 + y,0,146,14 );
	gfx.PutPixel( 12 + x,43 + y,0,146,14 );
	gfx.PutPixel( 13 + x,43 + y,0,146,14 );
	gfx.PutPixel( 14 + x,43 + y,0,146,14 );
	gfx.PutPixel( 15 + x,43 + y,0,146,14 );
	gfx.PutPixel( 16 + x,43 + y,0,146,14 );
	gfx.PutPixel( 17 + x,43 + y,0,146,14 );
	gfx.PutPixel( 18 + x,43 + y,0,146,14 );
	gfx.PutPixel( 19 + x,43 + y,0,146,14 );
	gfx.PutPixel( 20 + x,43 + y,0,146,14 );
	gfx.PutPixel( 21 + x,43 + y,0,146,14 );
	gfx.PutPixel( 22 + x,43 + y,0,146,14 );
	gfx.PutPixel( 23 + x,43 + y,0,146,14 );
	gfx.PutPixel( 24 + x,43 + y,0,146,14 );
	gfx.PutPixel( 25 + x,43 + y,0,146,14 );
	gfx.PutPixel( 38 + x,43 + y,0,146,14 );
	gfx.PutPixel( 39 + x,43 + y,0,146,14 );
	gfx.PutPixel( 40 + x,43 + y,0,146,14 );
	gfx.PutPixel( 41 + x,43 + y,0,146,14 );
	gfx.PutPixel( 77 + x,43 + y,0,146,14 );
	gfx.PutPixel( 78 + x,43 + y,0,146,14 );
	gfx.PutPixel( 79 + x,43 + y,0,146,14 );
	gfx.PutPixel( 0 + x,44 + y,0,146,14 );
	gfx.PutPixel( 1 + x,44 + y,0,146,14 );
	gfx.PutPixel( 2 + x,44 + y,0,146,14 );
	gfx.PutPixel( 3 + x,44 + y,0,146,14 );
	gfx.PutPixel( 4 + x,44 + y,0,146,14 );
	gfx.PutPixel( 5 + x,44 + y,0,146,14 );
	gfx.PutPixel( 6 + x,44 + y,0,146,14 );
	gfx.PutPixel( 7 + x,44 + y,0,146,14 );
	gfx.PutPixel( 8 + x,44 + y,0,146,14 );
	gfx.PutPixel( 9 + x,44 + y,0,146,14 );
	gfx.PutPixel( 10 + x,44 + y,0,146,14 );
	gfx.PutPixel( 11 + x,44 + y,0,146,14 );
	gfx.PutPixel( 12 + x,44 + y,0,146,14 );
	gfx.PutPixel( 13 + x,44 + y,0,146,14 );
	gfx.PutPixel( 14 + x,44 + y,0,146,14 );
	gfx.PutPixel( 15 + x,44 + y,0,146,14 );
	gfx.PutPixel( 16 + x,44 + y,0,146,14 );
	gfx.PutPixel( 17 + x,44 + y,0,146,14 );
	gfx.PutPixel( 18 + x,44 + y,0,146,14 );
	gfx.PutPixel( 19 + x,44 + y,0,146,14 );
	gfx.PutPixel( 20 + x,44 + y,0,146,14 );
	gfx.PutPixel( 21 + x,44 + y,0,146,14 );
	gfx.PutPixel( 22 + x,44 + y,0,146,14 );
	gfx.PutPixel( 23 + x,44 + y,0,146,14 );
	gfx.PutPixel( 24 + x,44 + y,0,146,14 );
	gfx.PutPixel( 25 + x,44 + y,0,146,14 );
	gfx.PutPixel( 26 + x,44 + y,0,146,14 );
	gfx.PutPixel( 38 + x,44 + y,0,146,14 );
	gfx.PutPixel( 39 + x,44 + y,0,146,14 );
	gfx.PutPixel( 40 + x,44 + y,0,146,14 );
	gfx.PutPixel( 77 + x,44 + y,0,3,0 );
	gfx.PutPixel( 78 + x,44 + y,0,146,14 );
	gfx.PutPixel( 79 + x,44 + y,0,146,14 );
	gfx.PutPixel( 80 + x,44 + y,0,146,14 );
	gfx.PutPixel( 0 + x,45 + y,0,146,14 );
	gfx.PutPixel( 1 + x,45 + y,0,146,14 );
	gfx.PutPixel( 2 + x,45 + y,0,146,14 );
	gfx.PutPixel( 3 + x,45 + y,0,146,14 );
	gfx.PutPixel( 4 + x,45 + y,0,146,14 );
	gfx.PutPixel( 5 + x,45 + y,0,146,14 );
	gfx.PutPixel( 6 + x,45 + y,0,146,14 );
	gfx.PutPixel( 7 + x,45 + y,0,146,14 );
	gfx.PutPixel( 8 + x,45 + y,0,146,14 );
	gfx.PutPixel( 9 + x,45 + y,0,146,14 );
	gfx.PutPixel( 10 + x,45 + y,0,146,14 );
	gfx.PutPixel( 11 + x,45 + y,0,146,14 );
	gfx.PutPixel( 12 + x,45 + y,0,146,14 );
	gfx.PutPixel( 13 + x,45 + y,0,146,14 );
	gfx.PutPixel( 14 + x,45 + y,0,146,14 );
	gfx.PutPixel( 15 + x,45 + y,0,146,14 );
	gfx.PutPixel( 16 + x,45 + y,0,146,14 );
	gfx.PutPixel( 17 + x,45 + y,0,146,14 );
	gfx.PutPixel( 18 + x,45 + y,0,146,14 );
	gfx.PutPixel( 19 + x,45 + y,0,146,14 );
	gfx.PutPixel( 20 + x,45 + y,0,146,14 );
	gfx.PutPixel( 21 + x,45 + y,0,146,14 );
	gfx.PutPixel( 22 + x,45 + y,0,146,14 );
	gfx.PutPixel( 23 + x,45 + y,0,146,14 );
	gfx.PutPixel( 24 + x,45 + y,0,146,14 );
	gfx.PutPixel( 25 + x,45 + y,0,146,14 );
	gfx.PutPixel( 26 + x,45 + y,0,146,14 );
	gfx.PutPixel( 27 + x,45 + y,0,118,11 );
	gfx.PutPixel( 38 + x,45 + y,0,146,14 );
	gfx.PutPixel( 39 + x,45 + y,0,146,14 );
	gfx.PutPixel( 40 + x,45 + y,0,146,14 );
	gfx.PutPixel( 78 + x,45 + y,0,146,14 );
	gfx.PutPixel( 79 + x,45 + y,0,146,14 );
	gfx.PutPixel( 80 + x,45 + y,0,146,14 );
	gfx.PutPixel( 0 + x,46 + y,0,146,14 );
	gfx.PutPixel( 1 + x,46 + y,0,146,14 );
	gfx.PutPixel( 2 + x,46 + y,0,146,14 );
	gfx.PutPixel( 3 + x,46 + y,0,146,14 );
	gfx.PutPixel( 4 + x,46 + y,0,146,14 );
	gfx.PutPixel( 5 + x,46 + y,0,146,14 );
	gfx.PutPixel( 6 + x,46 + y,0,146,14 );
	gfx.PutPixel( 7 + x,46 + y,0,146,14 );
	gfx.PutPixel( 8 + x,46 + y,0,146,14 );
	gfx.PutPixel( 9 + x,46 + y,0,146,14 );
	gfx.PutPixel( 10 + x,46 + y,0,146,14 );
	gfx.PutPixel( 11 + x,46 + y,0,146,14 );
	gfx.PutPixel( 12 + x,46 + y,0,146,14 );
	gfx.PutPixel( 13 + x,46 + y,0,146,14 );
	gfx.PutPixel( 14 + x,46 + y,0,146,14 );
	gfx.PutPixel( 15 + x,46 + y,0,146,14 );
	gfx.PutPixel( 16 + x,46 + y,0,146,14 );
	gfx.PutPixel( 17 + x,46 + y,0,146,14 );
	gfx.PutPixel( 18 + x,46 + y,0,146,14 );
	gfx.PutPixel( 19 + x,46 + y,0,146,14 );
	gfx.PutPixel( 20 + x,46 + y,0,146,14 );
	gfx.PutPixel( 21 + x,46 + y,0,146,14 );
	gfx.PutPixel( 22 + x,46 + y,0,146,14 );
	gfx.PutPixel( 23 + x,46 + y,0,146,14 );
	gfx.PutPixel( 24 + x,46 + y,0,146,14 );
	gfx.PutPixel( 25 + x,46 + y,0,146,14 );
	gfx.PutPixel( 26 + x,46 + y,0,146,14 );
	gfx.PutPixel( 27 + x,46 + y,0,146,14 );
	gfx.PutPixel( 38 + x,46 + y,0,146,14 );
	gfx.PutPixel( 39 + x,46 + y,0,146,14 );
	gfx.PutPixel( 40 + x,46 + y,0,146,14 );
	gfx.PutPixel( 77 + x,46 + y,0,118,11 );
	gfx.PutPixel( 78 + x,46 + y,0,146,14 );
	gfx.PutPixel( 79 + x,46 + y,0,146,14 );
	gfx.PutPixel( 80 + x,46 + y,0,146,14 );
	gfx.PutPixel( 0 + x,47 + y,0,146,14 );
	gfx.PutPixel( 1 + x,47 + y,0,146,14 );
	gfx.PutPixel( 2 + x,47 + y,0,146,14 );
	gfx.PutPixel( 3 + x,47 + y,0,146,14 );
	gfx.PutPixel( 4 + x,47 + y,0,146,14 );
	gfx.PutPixel( 5 + x,47 + y,0,146,14 );
	gfx.PutPixel( 6 + x,47 + y,0,146,14 );
	gfx.PutPixel( 7 + x,47 + y,0,146,14 );
	gfx.PutPixel( 8 + x,47 + y,0,146,14 );
	gfx.PutPixel( 9 + x,47 + y,0,146,14 );
	gfx.PutPixel( 10 + x,47 + y,0,146,14 );
	gfx.PutPixel( 11 + x,47 + y,0,146,14 );
	gfx.PutPixel( 12 + x,47 + y,0,146,14 );
	gfx.PutPixel( 13 + x,47 + y,0,146,14 );
	gfx.PutPixel( 14 + x,47 + y,0,146,14 );
	gfx.PutPixel( 15 + x,47 + y,0,146,14 );
	gfx.PutPixel( 16 + x,47 + y,0,146,14 );
	gfx.PutPixel( 17 + x,47 + y,0,146,14 );
	gfx.PutPixel( 18 + x,47 + y,0,146,14 );
	gfx.PutPixel( 19 + x,47 + y,0,146,14 );
	gfx.PutPixel( 20 + x,47 + y,0,146,14 );
	gfx.PutPixel( 21 + x,47 + y,0,146,14 );
	gfx.PutPixel( 22 + x,47 + y,0,146,14 );
	gfx.PutPixel( 23 + x,47 + y,0,146,14 );
	gfx.PutPixel( 24 + x,47 + y,0,146,14 );
	gfx.PutPixel( 25 + x,47 + y,0,146,14 );
	gfx.PutPixel( 26 + x,47 + y,0,146,14 );
	gfx.PutPixel( 27 + x,47 + y,0,146,14 );
	gfx.PutPixel( 38 + x,47 + y,0,146,14 );
	gfx.PutPixel( 39 + x,47 + y,0,146,14 );
	gfx.PutPixel( 40 + x,47 + y,0,146,14 );
	gfx.PutPixel( 41 + x,47 + y,0,146,14 );
	gfx.PutPixel( 77 + x,47 + y,0,146,14 );
	gfx.PutPixel( 78 + x,47 + y,0,146,14 );
	gfx.PutPixel( 79 + x,47 + y,0,146,14 );
	gfx.PutPixel( 0 + x,48 + y,0,146,14 );
	gfx.PutPixel( 1 + x,48 + y,0,146,14 );
	gfx.PutPixel( 2 + x,48 + y,0,146,14 );
	gfx.PutPixel( 3 + x,48 + y,0,146,14 );
	gfx.PutPixel( 4 + x,48 + y,0,146,14 );
	gfx.PutPixel( 5 + x,48 + y,0,146,14 );
	gfx.PutPixel( 6 + x,48 + y,0,146,14 );
	gfx.PutPixel( 7 + x,48 + y,0,146,14 );
	gfx.PutPixel( 8 + x,48 + y,0,146,14 );
	gfx.PutPixel( 9 + x,48 + y,0,146,14 );
	gfx.PutPixel( 10 + x,48 + y,0,146,14 );
	gfx.PutPixel( 11 + x,48 + y,0,146,14 );
	gfx.PutPixel( 12 + x,48 + y,0,146,14 );
	gfx.PutPixel( 13 + x,48 + y,0,146,14 );
	gfx.PutPixel( 14 + x,48 + y,0,146,14 );
	gfx.PutPixel( 15 + x,48 + y,0,146,14 );
	gfx.PutPixel( 16 + x,48 + y,0,146,14 );
	gfx.PutPixel( 17 + x,48 + y,0,146,14 );
	gfx.PutPixel( 18 + x,48 + y,0,146,14 );
	gfx.PutPixel( 19 + x,48 + y,0,146,14 );
	gfx.PutPixel( 20 + x,48 + y,0,146,14 );
	gfx.PutPixel( 21 + x,48 + y,0,146,14 );
	gfx.PutPixel( 22 + x,48 + y,0,146,14 );
	gfx.PutPixel( 23 + x,48 + y,0,146,14 );
	gfx.PutPixel( 24 + x,48 + y,0,146,14 );
	gfx.PutPixel( 25 + x,48 + y,0,146,14 );
	gfx.PutPixel( 26 + x,48 + y,0,146,14 );
	gfx.PutPixel( 39 + x,48 + y,0,146,14 );
	gfx.PutPixel( 40 + x,48 + y,0,146,14 );
	gfx.PutPixel( 41 + x,48 + y,0,146,14 );
	gfx.PutPixel( 42 + x,48 + y,0,146,14 );
	gfx.PutPixel( 43 + x,48 + y,0,146,14 );
	gfx.PutPixel( 44 + x,48 + y,0,146,14 );
	gfx.PutPixel( 45 + x,48 + y,0,146,14 );
	gfx.PutPixel( 46 + x,48 + y,0,146,14 );
	gfx.PutPixel( 47 + x,48 + y,0,146,14 );
	gfx.PutPixel( 48 + x,48 + y,0,146,14 );
	gfx.PutPixel( 49 + x,48 + y,0,146,14 );
	gfx.PutPixel( 50 + x,48 + y,0,146,14 );
	gfx.PutPixel( 51 + x,48 + y,0,146,14 );
	gfx.PutPixel( 52 + x,48 + y,0,146,14 );
	gfx.PutPixel( 53 + x,48 + y,0,146,14 );
	gfx.PutPixel( 54 + x,48 + y,0,146,14 );
	gfx.PutPixel( 55 + x,48 + y,0,146,14 );
	gfx.PutPixel( 56 + x,48 + y,0,146,14 );
	gfx.PutPixel( 57 + x,48 + y,0,146,14 );
	gfx.PutPixel( 58 + x,48 + y,0,146,14 );
	gfx.PutPixel( 59 + x,48 + y,0,146,14 );
	gfx.PutPixel( 60 + x,48 + y,0,146,14 );
	gfx.PutPixel( 61 + x,48 + y,0,146,14 );
	gfx.PutPixel( 62 + x,48 + y,0,146,14 );
	gfx.PutPixel( 63 + x,48 + y,0,146,14 );
	gfx.PutPixel( 64 + x,48 + y,0,146,14 );
	gfx.PutPixel( 65 + x,48 + y,0,146,14 );
	gfx.PutPixel( 66 + x,48 + y,0,146,14 );
	gfx.PutPixel( 67 + x,48 + y,0,146,14 );
	gfx.PutPixel( 68 + x,48 + y,0,146,14 );
	gfx.PutPixel( 69 + x,48 + y,0,146,14 );
	gfx.PutPixel( 70 + x,48 + y,0,146,14 );
	gfx.PutPixel( 71 + x,48 + y,0,146,14 );
	gfx.PutPixel( 72 + x,48 + y,0,146,14 );
	gfx.PutPixel( 73 + x,48 + y,0,146,14 );
	gfx.PutPixel( 74 + x,48 + y,0,146,14 );
	gfx.PutPixel( 75 + x,48 + y,0,146,14 );
	gfx.PutPixel( 76 + x,48 + y,0,146,14 );
	gfx.PutPixel( 77 + x,48 + y,0,146,14 );
	gfx.PutPixel( 78 + x,48 + y,0,146,14 );
	gfx.PutPixel( 79 + x,48 + y,0,146,14 );
	gfx.PutPixel( 0 + x,49 + y,0,142,13 );
	gfx.PutPixel( 1 + x,49 + y,0,146,14 );
	gfx.PutPixel( 2 + x,49 + y,0,146,14 );
	gfx.PutPixel( 3 + x,49 + y,0,146,14 );
	gfx.PutPixel( 4 + x,49 + y,0,146,14 );
	gfx.PutPixel( 5 + x,49 + y,0,146,14 );
	gfx.PutPixel( 6 + x,49 + y,0,146,14 );
	gfx.PutPixel( 7 + x,49 + y,0,146,14 );
	gfx.PutPixel( 8 + x,49 + y,0,146,14 );
	gfx.PutPixel( 9 + x,49 + y,0,146,14 );
	gfx.PutPixel( 10 + x,49 + y,0,146,14 );
	gfx.PutPixel( 11 + x,49 + y,0,146,14 );
	gfx.PutPixel( 12 + x,49 + y,0,146,14 );
	gfx.PutPixel( 13 + x,49 + y,0,146,14 );
	gfx.PutPixel( 14 + x,49 + y,0,146,14 );
	gfx.PutPixel( 15 + x,49 + y,0,146,14 );
	gfx.PutPixel( 16 + x,49 + y,0,146,14 );
	gfx.PutPixel( 17 + x,49 + y,0,146,14 );
	gfx.PutPixel( 18 + x,49 + y,0,146,14 );
	gfx.PutPixel( 19 + x,49 + y,0,146,14 );
	gfx.PutPixel( 20 + x,49 + y,0,146,14 );
	gfx.PutPixel( 21 + x,49 + y,0,146,14 );
	gfx.PutPixel( 22 + x,49 + y,0,146,14 );
	gfx.PutPixel( 23 + x,49 + y,0,146,14 );
	gfx.PutPixel( 24 + x,49 + y,0,146,14 );
	gfx.PutPixel( 25 + x,49 + y,0,146,14 );
	gfx.PutPixel( 26 + x,49 + y,0,146,14 );
	gfx.PutPixel( 40 + x,49 + y,0,146,14 );
	gfx.PutPixel( 41 + x,49 + y,0,146,14 );
	gfx.PutPixel( 42 + x,49 + y,0,146,14 );
	gfx.PutPixel( 43 + x,49 + y,0,146,14 );
	gfx.PutPixel( 44 + x,49 + y,0,146,14 );
	gfx.PutPixel( 45 + x,49 + y,0,146,14 );
	gfx.PutPixel( 46 + x,49 + y,0,146,14 );
	gfx.PutPixel( 47 + x,49 + y,0,146,14 );
	gfx.PutPixel( 48 + x,49 + y,0,146,14 );
	gfx.PutPixel( 49 + x,49 + y,0,146,14 );
	gfx.PutPixel( 50 + x,49 + y,0,146,14 );
	gfx.PutPixel( 51 + x,49 + y,0,146,14 );
	gfx.PutPixel( 52 + x,49 + y,0,146,14 );
	gfx.PutPixel( 53 + x,49 + y,0,146,14 );
	gfx.PutPixel( 54 + x,49 + y,0,146,14 );
	gfx.PutPixel( 55 + x,49 + y,0,146,14 );
	gfx.PutPixel( 56 + x,49 + y,0,146,14 );
	gfx.PutPixel( 57 + x,49 + y,0,146,14 );
	gfx.PutPixel( 58 + x,49 + y,0,146,14 );
	gfx.PutPixel( 59 + x,49 + y,0,146,14 );
	gfx.PutPixel( 60 + x,49 + y,0,146,14 );
	gfx.PutPixel( 61 + x,49 + y,0,146,14 );
	gfx.PutPixel( 62 + x,49 + y,0,146,14 );
	gfx.PutPixel( 63 + x,49 + y,0,146,14 );
	gfx.PutPixel( 64 + x,49 + y,0,146,14 );
	gfx.PutPixel( 65 + x,49 + y,0,146,14 );
	gfx.PutPixel( 66 + x,49 + y,0,146,14 );
	gfx.PutPixel( 67 + x,49 + y,0,146,14 );
	gfx.PutPixel( 68 + x,49 + y,0,146,14 );
	gfx.PutPixel( 69 + x,49 + y,0,146,14 );
	gfx.PutPixel( 70 + x,49 + y,0,146,14 );
	gfx.PutPixel( 71 + x,49 + y,0,146,14 );
	gfx.PutPixel( 72 + x,49 + y,0,146,14 );
	gfx.PutPixel( 73 + x,49 + y,0,146,14 );
	gfx.PutPixel( 74 + x,49 + y,0,146,14 );
	gfx.PutPixel( 75 + x,49 + y,0,146,14 );
	gfx.PutPixel( 76 + x,49 + y,0,146,14 );
	gfx.PutPixel( 77 + x,49 + y,0,146,14 );
	gfx.PutPixel( 78 + x,49 + y,0,146,14 );
	gfx.PutPixel( 2 + x,50 + y,0,146,14 );
	gfx.PutPixel( 3 + x,50 + y,0,146,14 );
	gfx.PutPixel( 4 + x,50 + y,0,146,14 );
	gfx.PutPixel( 5 + x,50 + y,0,146,14 );
	gfx.PutPixel( 6 + x,50 + y,0,146,14 );
	gfx.PutPixel( 7 + x,50 + y,0,146,14 );
	gfx.PutPixel( 8 + x,50 + y,0,146,14 );
	gfx.PutPixel( 9 + x,50 + y,0,146,14 );
	gfx.PutPixel( 10 + x,50 + y,0,146,14 );
	gfx.PutPixel( 11 + x,50 + y,0,146,14 );
	gfx.PutPixel( 12 + x,50 + y,0,146,14 );
	gfx.PutPixel( 13 + x,50 + y,0,146,14 );
	gfx.PutPixel( 14 + x,50 + y,0,146,14 );
	gfx.PutPixel( 15 + x,50 + y,0,146,14 );
	gfx.PutPixel( 16 + x,50 + y,0,146,14 );
	gfx.PutPixel( 17 + x,50 + y,0,146,14 );
	gfx.PutPixel( 18 + x,50 + y,0,146,14 );
	gfx.PutPixel( 19 + x,50 + y,0,146,14 );
	gfx.PutPixel( 20 + x,50 + y,0,146,14 );
	gfx.PutPixel( 21 + x,50 + y,0,146,14 );
	gfx.PutPixel( 22 + x,50 + y,0,146,14 );
	gfx.PutPixel( 23 + x,50 + y,0,146,14 );
	gfx.PutPixel( 24 + x,50 + y,0,146,14 );
	gfx.PutPixel( 25 + x,50 + y,0,142,13 );
	gfx.PutPixel( 41 + x,50 + y,0,146,14 );
	gfx.PutPixel( 42 + x,50 + y,0,146,14 );
	gfx.PutPixel( 43 + x,50 + y,0,146,14 );
	gfx.PutPixel( 44 + x,50 + y,0,146,14 );
	gfx.PutPixel( 45 + x,50 + y,0,146,14 );
	gfx.PutPixel( 46 + x,50 + y,0,146,14 );
	gfx.PutPixel( 47 + x,50 + y,0,146,14 );
	gfx.PutPixel( 48 + x,50 + y,0,146,14 );
	gfx.PutPixel( 49 + x,50 + y,0,146,14 );
	gfx.PutPixel( 50 + x,50 + y,0,146,14 );
	gfx.PutPixel( 51 + x,50 + y,0,146,14 );
	gfx.PutPixel( 52 + x,50 + y,0,146,14 );
	gfx.PutPixel( 53 + x,50 + y,0,146,14 );
	gfx.PutPixel( 54 + x,50 + y,0,146,14 );
	gfx.PutPixel( 55 + x,50 + y,0,146,14 );
	gfx.PutPixel( 56 + x,50 + y,0,146,14 );
	gfx.PutPixel( 57 + x,50 + y,0,146,14 );
	gfx.PutPixel( 58 + x,50 + y,0,146,14 );
	gfx.PutPixel( 59 + x,50 + y,0,146,14 );
	gfx.PutPixel( 60 + x,50 + y,0,146,14 );
	gfx.PutPixel( 61 + x,50 + y,0,146,14 );
	gfx.PutPixel( 62 + x,50 + y,0,146,14 );
	gfx.PutPixel( 63 + x,50 + y,0,146,14 );
	gfx.PutPixel( 64 + x,50 + y,0,146,14 );
	gfx.PutPixel( 65 + x,50 + y,0,146,14 );
	gfx.PutPixel( 66 + x,50 + y,0,146,14 );
	gfx.PutPixel( 67 + x,50 + y,0,146,14 );
	gfx.PutPixel( 68 + x,50 + y,0,146,14 );
	gfx.PutPixel( 69 + x,50 + y,0,146,14 );
	gfx.PutPixel( 70 + x,50 + y,0,146,14 );
	gfx.PutPixel( 71 + x,50 + y,0,146,14 );
	gfx.PutPixel( 72 + x,50 + y,0,146,14 );
	gfx.PutPixel( 73 + x,50 + y,0,146,14 );
	gfx.PutPixel( 74 + x,50 + y,0,146,14 );
	gfx.PutPixel( 75 + x,50 + y,0,146,14 );
	gfx.PutPixel( 76 + x,50 + y,0,146,14 );

}

void Game::DrawXWin(int x, int y)
{
	gfx.PutPixel( 0 + x,0 + y,255,0,0 );
	gfx.PutPixel( 1 + x,0 + y,255,0,0 );
	gfx.PutPixel( 4 + x,0 + y,255,0,0 );
	gfx.PutPixel( 5 + x,0 + y,255,0,0 );
	gfx.PutPixel( 16 + x,0 + y,0,146,14 );
	gfx.PutPixel( 17 + x,0 + y,0,146,14 );
	gfx.PutPixel( 21 + x,0 + y,0,146,14 );
	gfx.PutPixel( 22 + x,0 + y,0,146,14 );
	gfx.PutPixel( 25 + x,0 + y,0,146,14 );
	gfx.PutPixel( 26 + x,0 + y,0,146,14 );
	gfx.PutPixel( 27 + x,0 + y,0,146,14 );
	gfx.PutPixel( 28 + x,0 + y,0,146,14 );
	gfx.PutPixel( 32 + x,0 + y,0,146,14 );
	gfx.PutPixel( 33 + x,0 + y,0,146,14 );
	gfx.PutPixel( 37 + x,0 + y,0,146,14 );
	gfx.PutPixel( 38 + x,0 + y,0,146,14 );
	gfx.PutPixel( 41 + x,0 + y,0,146,14 );
	gfx.PutPixel( 42 + x,0 + y,0,146,14 );
	gfx.PutPixel( 43 + x,0 + y,0,146,14 );
	gfx.PutPixel( 44 + x,0 + y,0,146,14 );
	gfx.PutPixel( 0 + x,1 + y,255,0,0 );
	gfx.PutPixel( 1 + x,1 + y,255,0,0 );
	gfx.PutPixel( 4 + x,1 + y,255,0,0 );
	gfx.PutPixel( 5 + x,1 + y,255,0,0 );
	gfx.PutPixel( 16 + x,1 + y,0,146,14 );
	gfx.PutPixel( 17 + x,1 + y,0,146,14 );
	gfx.PutPixel( 21 + x,1 + y,0,146,14 );
	gfx.PutPixel( 22 + x,1 + y,0,146,14 );
	gfx.PutPixel( 26 + x,1 + y,0,146,14 );
	gfx.PutPixel( 27 + x,1 + y,0,146,14 );
	gfx.PutPixel( 32 + x,1 + y,0,146,14 );
	gfx.PutPixel( 33 + x,1 + y,0,146,14 );
	gfx.PutPixel( 37 + x,1 + y,0,146,14 );
	gfx.PutPixel( 38 + x,1 + y,0,146,14 );
	gfx.PutPixel( 40 + x,1 + y,0,146,14 );
	gfx.PutPixel( 41 + x,1 + y,0,146,14 );
	gfx.PutPixel( 44 + x,1 + y,0,146,14 );
	gfx.PutPixel( 45 + x,1 + y,0,146,14 );
	gfx.PutPixel( 1 + x,2 + y,255,0,0 );
	gfx.PutPixel( 2 + x,2 + y,255,0,0 );
	gfx.PutPixel( 4 + x,2 + y,255,0,0 );
	gfx.PutPixel( 16 + x,2 + y,0,146,14 );
	gfx.PutPixel( 17 + x,2 + y,0,146,14 );
	gfx.PutPixel( 21 + x,2 + y,0,146,14 );
	gfx.PutPixel( 22 + x,2 + y,0,146,14 );
	gfx.PutPixel( 26 + x,2 + y,0,146,14 );
	gfx.PutPixel( 27 + x,2 + y,0,146,14 );
	gfx.PutPixel( 32 + x,2 + y,0,146,14 );
	gfx.PutPixel( 33 + x,2 + y,0,146,14 );
	gfx.PutPixel( 34 + x,2 + y,0,146,14 );
	gfx.PutPixel( 37 + x,2 + y,0,146,14 );
	gfx.PutPixel( 38 + x,2 + y,0,146,14 );
	gfx.PutPixel( 40 + x,2 + y,0,146,14 );
	gfx.PutPixel( 41 + x,2 + y,0,146,14 );
	gfx.PutPixel( 2 + x,3 + y,255,0,0 );
	gfx.PutPixel( 3 + x,3 + y,255,0,0 );
	gfx.PutPixel( 16 + x,3 + y,0,146,14 );
	gfx.PutPixel( 17 + x,3 + y,0,146,14 );
	gfx.PutPixel( 19 + x,3 + y,0,146,14 );
	gfx.PutPixel( 21 + x,3 + y,0,146,14 );
	gfx.PutPixel( 22 + x,3 + y,0,146,14 );
	gfx.PutPixel( 26 + x,3 + y,0,146,14 );
	gfx.PutPixel( 27 + x,3 + y,0,146,14 );
	gfx.PutPixel( 32 + x,3 + y,0,146,14 );
	gfx.PutPixel( 33 + x,3 + y,0,146,14 );
	gfx.PutPixel( 34 + x,3 + y,0,146,14 );
	gfx.PutPixel( 35 + x,3 + y,0,146,14 );
	gfx.PutPixel( 37 + x,3 + y,0,146,14 );
	gfx.PutPixel( 38 + x,3 + y,0,146,14 );
	gfx.PutPixel( 41 + x,3 + y,0,146,14 );
	gfx.PutPixel( 42 + x,3 + y,0,146,14 );
	gfx.PutPixel( 2 + x,4 + y,255,0,0 );
	gfx.PutPixel( 3 + x,4 + y,255,0,0 );
	gfx.PutPixel( 16 + x,4 + y,0,146,14 );
	gfx.PutPixel( 17 + x,4 + y,0,146,14 );
	gfx.PutPixel( 19 + x,4 + y,0,146,14 );
	gfx.PutPixel( 21 + x,4 + y,0,146,14 );
	gfx.PutPixel( 22 + x,4 + y,0,146,14 );
	gfx.PutPixel( 26 + x,4 + y,0,146,14 );
	gfx.PutPixel( 27 + x,4 + y,0,146,14 );
	gfx.PutPixel( 32 + x,4 + y,0,146,14 );
	gfx.PutPixel( 33 + x,4 + y,0,146,14 );
	gfx.PutPixel( 35 + x,4 + y,0,146,14 );
	gfx.PutPixel( 36 + x,4 + y,0,146,14 );
	gfx.PutPixel( 37 + x,4 + y,0,146,14 );
	gfx.PutPixel( 38 + x,4 + y,0,146,14 );
	gfx.PutPixel( 42 + x,4 + y,0,146,14 );
	gfx.PutPixel( 43 + x,4 + y,0,146,14 );
	gfx.PutPixel( 1 + x,5 + y,255,0,0 );
	gfx.PutPixel( 3 + x,5 + y,255,0,0 );
	gfx.PutPixel( 4 + x,5 + y,255,0,0 );
	gfx.PutPixel( 16 + x,5 + y,0,146,14 );
	gfx.PutPixel( 17 + x,5 + y,0,146,14 );
	gfx.PutPixel( 19 + x,5 + y,0,146,14 );
	gfx.PutPixel( 21 + x,5 + y,0,146,14 );
	gfx.PutPixel( 22 + x,5 + y,0,146,14 );
	gfx.PutPixel( 26 + x,5 + y,0,146,14 );
	gfx.PutPixel( 27 + x,5 + y,0,146,14 );
	gfx.PutPixel( 32 + x,5 + y,0,146,14 );
	gfx.PutPixel( 33 + x,5 + y,0,146,14 );
	gfx.PutPixel( 36 + x,5 + y,0,146,14 );
	gfx.PutPixel( 37 + x,5 + y,0,146,14 );
	gfx.PutPixel( 38 + x,5 + y,0,146,14 );
	gfx.PutPixel( 43 + x,5 + y,0,146,14 );
	gfx.PutPixel( 44 + x,5 + y,0,146,14 );
	gfx.PutPixel( 0 + x,6 + y,255,0,0 );
	gfx.PutPixel( 1 + x,6 + y,255,0,0 );
	gfx.PutPixel( 4 + x,6 + y,255,0,0 );
	gfx.PutPixel( 5 + x,6 + y,255,0,0 );
	gfx.PutPixel( 17 + x,6 + y,0,146,14 );
	gfx.PutPixel( 18 + x,6 + y,0,146,14 );
	gfx.PutPixel( 20 + x,6 + y,0,146,14 );
	gfx.PutPixel( 21 + x,6 + y,0,146,14 );
	gfx.PutPixel( 26 + x,6 + y,0,146,14 );
	gfx.PutPixel( 27 + x,6 + y,0,146,14 );
	gfx.PutPixel( 32 + x,6 + y,0,146,14 );
	gfx.PutPixel( 33 + x,6 + y,0,146,14 );
	gfx.PutPixel( 37 + x,6 + y,0,146,14 );
	gfx.PutPixel( 38 + x,6 + y,0,146,14 );
	gfx.PutPixel( 44 + x,6 + y,0,146,14 );
	gfx.PutPixel( 45 + x,6 + y,0,146,14 );
	gfx.PutPixel( 0 + x,7 + y,255,0,0 );
	gfx.PutPixel( 1 + x,7 + y,255,0,0 );
	gfx.PutPixel( 4 + x,7 + y,255,0,0 );
	gfx.PutPixel( 5 + x,7 + y,255,0,0 );
	gfx.PutPixel( 17 + x,7 + y,0,146,14 );
	gfx.PutPixel( 18 + x,7 + y,0,146,14 );
	gfx.PutPixel( 20 + x,7 + y,0,146,14 );
	gfx.PutPixel( 21 + x,7 + y,0,146,14 );
	gfx.PutPixel( 26 + x,7 + y,0,146,14 );
	gfx.PutPixel( 27 + x,7 + y,0,146,14 );
	gfx.PutPixel( 32 + x,7 + y,0,146,14 );
	gfx.PutPixel( 33 + x,7 + y,0,146,14 );
	gfx.PutPixel( 37 + x,7 + y,0,146,14 );
	gfx.PutPixel( 38 + x,7 + y,0,146,14 );
	gfx.PutPixel( 40 + x,7 + y,0,146,14 );
	gfx.PutPixel( 41 + x,7 + y,0,146,14 );
	gfx.PutPixel( 44 + x,7 + y,0,146,14 );
	gfx.PutPixel( 45 + x,7 + y,0,146,14 );
	gfx.PutPixel( 0 + x,8 + y,255,0,0 );
	gfx.PutPixel( 1 + x,8 + y,255,0,0 );
	gfx.PutPixel( 4 + x,8 + y,255,0,0 );
	gfx.PutPixel( 5 + x,8 + y,255,0,0 );
	gfx.PutPixel( 17 + x,8 + y,0,146,14 );
	gfx.PutPixel( 18 + x,8 + y,0,146,14 );
	gfx.PutPixel( 20 + x,8 + y,0,146,14 );
	gfx.PutPixel( 21 + x,8 + y,0,146,14 );
	gfx.PutPixel( 25 + x,8 + y,0,146,14 );
	gfx.PutPixel( 26 + x,8 + y,0,146,14 );
	gfx.PutPixel( 27 + x,8 + y,0,146,14 );
	gfx.PutPixel( 28 + x,8 + y,0,146,14 );
	gfx.PutPixel( 32 + x,8 + y,0,146,14 );
	gfx.PutPixel( 33 + x,8 + y,0,146,14 );
	gfx.PutPixel( 37 + x,8 + y,0,146,14 );
	gfx.PutPixel( 38 + x,8 + y,0,146,14 );
	gfx.PutPixel( 41 + x,8 + y,0,146,14 );
	gfx.PutPixel( 42 + x,8 + y,0,146,14 );
	gfx.PutPixel( 43 + x,8 + y,0,146,14 );
	gfx.PutPixel( 44 + x,8 + y,0,146,14 );

}

void Game::DrawOWin(int x, int y)
{
	gfx.PutPixel( 1 + x,0 + y,0,0,255 );
	gfx.PutPixel( 2 + x,0 + y,0,0,255 );
	gfx.PutPixel( 3 + x,0 + y,0,0,255 );
	gfx.PutPixel( 4 + x,0 + y,0,0,255 );
	gfx.PutPixel( 16 + x,0 + y,0,146,14 );
	gfx.PutPixel( 17 + x,0 + y,0,146,14 );
	gfx.PutPixel( 21 + x,0 + y,0,146,14 );
	gfx.PutPixel( 22 + x,0 + y,0,146,14 );
	gfx.PutPixel( 25 + x,0 + y,0,146,14 );
	gfx.PutPixel( 26 + x,0 + y,0,146,14 );
	gfx.PutPixel( 27 + x,0 + y,0,146,14 );
	gfx.PutPixel( 28 + x,0 + y,0,146,14 );
	gfx.PutPixel( 32 + x,0 + y,0,146,14 );
	gfx.PutPixel( 33 + x,0 + y,0,146,14 );
	gfx.PutPixel( 37 + x,0 + y,0,146,14 );
	gfx.PutPixel( 38 + x,0 + y,0,146,14 );
	gfx.PutPixel( 41 + x,0 + y,0,146,14 );
	gfx.PutPixel( 42 + x,0 + y,0,146,14 );
	gfx.PutPixel( 43 + x,0 + y,0,146,14 );
	gfx.PutPixel( 44 + x,0 + y,0,146,14 );
	gfx.PutPixel( 0 + x,1 + y,0,0,255 );
	gfx.PutPixel( 1 + x,1 + y,0,0,255 );
	gfx.PutPixel( 4 + x,1 + y,0,0,255 );
	gfx.PutPixel( 5 + x,1 + y,0,0,255 );
	gfx.PutPixel( 16 + x,1 + y,0,146,14 );
	gfx.PutPixel( 17 + x,1 + y,0,146,14 );
	gfx.PutPixel( 21 + x,1 + y,0,146,14 );
	gfx.PutPixel( 22 + x,1 + y,0,146,14 );
	gfx.PutPixel( 26 + x,1 + y,0,146,14 );
	gfx.PutPixel( 27 + x,1 + y,0,146,14 );
	gfx.PutPixel( 32 + x,1 + y,0,146,14 );
	gfx.PutPixel( 33 + x,1 + y,0,146,14 );
	gfx.PutPixel( 37 + x,1 + y,0,146,14 );
	gfx.PutPixel( 38 + x,1 + y,0,146,14 );
	gfx.PutPixel( 40 + x,1 + y,0,146,14 );
	gfx.PutPixel( 41 + x,1 + y,0,146,14 );
	gfx.PutPixel( 44 + x,1 + y,0,146,14 );
	gfx.PutPixel( 45 + x,1 + y,0,146,14 );
	gfx.PutPixel( 0 + x,2 + y,0,0,255 );
	gfx.PutPixel( 1 + x,2 + y,0,0,255 );
	gfx.PutPixel( 4 + x,2 + y,0,0,255 );
	gfx.PutPixel( 5 + x,2 + y,0,0,255 );
	gfx.PutPixel( 16 + x,2 + y,0,146,14 );
	gfx.PutPixel( 17 + x,2 + y,0,146,14 );
	gfx.PutPixel( 21 + x,2 + y,0,146,14 );
	gfx.PutPixel( 22 + x,2 + y,0,146,14 );
	gfx.PutPixel( 26 + x,2 + y,0,146,14 );
	gfx.PutPixel( 27 + x,2 + y,0,146,14 );
	gfx.PutPixel( 32 + x,2 + y,0,146,14 );
	gfx.PutPixel( 33 + x,2 + y,0,146,14 );
	gfx.PutPixel( 34 + x,2 + y,0,146,14 );
	gfx.PutPixel( 37 + x,2 + y,0,146,14 );
	gfx.PutPixel( 38 + x,2 + y,0,146,14 );
	gfx.PutPixel( 40 + x,2 + y,0,146,14 );
	gfx.PutPixel( 41 + x,2 + y,0,146,14 );
	gfx.PutPixel( 0 + x,3 + y,0,0,255 );
	gfx.PutPixel( 1 + x,3 + y,0,0,255 );
	gfx.PutPixel( 4 + x,3 + y,0,0,255 );
	gfx.PutPixel( 5 + x,3 + y,0,0,255 );
	gfx.PutPixel( 16 + x,3 + y,0,146,14 );
	gfx.PutPixel( 17 + x,3 + y,0,146,14 );
	gfx.PutPixel( 19 + x,3 + y,0,146,14 );
	gfx.PutPixel( 21 + x,3 + y,0,146,14 );
	gfx.PutPixel( 22 + x,3 + y,0,146,14 );
	gfx.PutPixel( 26 + x,3 + y,0,146,14 );
	gfx.PutPixel( 27 + x,3 + y,0,146,14 );
	gfx.PutPixel( 32 + x,3 + y,0,146,14 );
	gfx.PutPixel( 33 + x,3 + y,0,146,14 );
	gfx.PutPixel( 34 + x,3 + y,0,146,14 );
	gfx.PutPixel( 35 + x,3 + y,0,146,14 );
	gfx.PutPixel( 37 + x,3 + y,0,146,14 );
	gfx.PutPixel( 38 + x,3 + y,0,146,14 );
	gfx.PutPixel( 41 + x,3 + y,0,146,14 );
	gfx.PutPixel( 42 + x,3 + y,0,146,14 );
	gfx.PutPixel( 0 + x,4 + y,0,0,255 );
	gfx.PutPixel( 1 + x,4 + y,0,0,255 );
	gfx.PutPixel( 4 + x,4 + y,0,0,255 );
	gfx.PutPixel( 5 + x,4 + y,0,0,255 );
	gfx.PutPixel( 16 + x,4 + y,0,146,14 );
	gfx.PutPixel( 17 + x,4 + y,0,146,14 );
	gfx.PutPixel( 19 + x,4 + y,0,146,14 );
	gfx.PutPixel( 21 + x,4 + y,0,146,14 );
	gfx.PutPixel( 22 + x,4 + y,0,146,14 );
	gfx.PutPixel( 26 + x,4 + y,0,146,14 );
	gfx.PutPixel( 27 + x,4 + y,0,146,14 );
	gfx.PutPixel( 32 + x,4 + y,0,146,14 );
	gfx.PutPixel( 33 + x,4 + y,0,146,14 );
	gfx.PutPixel( 35 + x,4 + y,0,146,14 );
	gfx.PutPixel( 36 + x,4 + y,0,146,14 );
	gfx.PutPixel( 37 + x,4 + y,0,146,14 );
	gfx.PutPixel( 38 + x,4 + y,0,146,14 );
	gfx.PutPixel( 42 + x,4 + y,0,146,14 );
	gfx.PutPixel( 43 + x,4 + y,0,146,14 );
	gfx.PutPixel( 0 + x,5 + y,0,0,255 );
	gfx.PutPixel( 1 + x,5 + y,0,0,255 );
	gfx.PutPixel( 4 + x,5 + y,0,0,255 );
	gfx.PutPixel( 5 + x,5 + y,0,0,255 );
	gfx.PutPixel( 16 + x,5 + y,0,146,14 );
	gfx.PutPixel( 17 + x,5 + y,0,146,14 );
	gfx.PutPixel( 19 + x,5 + y,0,146,14 );
	gfx.PutPixel( 21 + x,5 + y,0,146,14 );
	gfx.PutPixel( 22 + x,5 + y,0,146,14 );
	gfx.PutPixel( 26 + x,5 + y,0,146,14 );
	gfx.PutPixel( 27 + x,5 + y,0,146,14 );
	gfx.PutPixel( 32 + x,5 + y,0,146,14 );
	gfx.PutPixel( 33 + x,5 + y,0,146,14 );
	gfx.PutPixel( 36 + x,5 + y,0,146,14 );
	gfx.PutPixel( 37 + x,5 + y,0,146,14 );
	gfx.PutPixel( 38 + x,5 + y,0,146,14 );
	gfx.PutPixel( 43 + x,5 + y,0,146,14 );
	gfx.PutPixel( 44 + x,5 + y,0,146,14 );
	gfx.PutPixel( 0 + x,6 + y,0,0,255 );
	gfx.PutPixel( 1 + x,6 + y,0,0,255 );
	gfx.PutPixel( 4 + x,6 + y,0,0,255 );
	gfx.PutPixel( 5 + x,6 + y,0,0,255 );
	gfx.PutPixel( 17 + x,6 + y,0,146,14 );
	gfx.PutPixel( 18 + x,6 + y,0,146,14 );
	gfx.PutPixel( 20 + x,6 + y,0,146,14 );
	gfx.PutPixel( 21 + x,6 + y,0,146,14 );
	gfx.PutPixel( 26 + x,6 + y,0,146,14 );
	gfx.PutPixel( 27 + x,6 + y,0,146,14 );
	gfx.PutPixel( 32 + x,6 + y,0,146,14 );
	gfx.PutPixel( 33 + x,6 + y,0,146,14 );
	gfx.PutPixel( 37 + x,6 + y,0,146,14 );
	gfx.PutPixel( 38 + x,6 + y,0,146,14 );
	gfx.PutPixel( 44 + x,6 + y,0,146,14 );
	gfx.PutPixel( 45 + x,6 + y,0,146,14 );
	gfx.PutPixel( 0 + x,7 + y,0,0,255 );
	gfx.PutPixel( 1 + x,7 + y,0,0,255 );
	gfx.PutPixel( 4 + x,7 + y,0,0,255 );
	gfx.PutPixel( 5 + x,7 + y,0,0,255 );
	gfx.PutPixel( 17 + x,7 + y,0,146,14 );
	gfx.PutPixel( 18 + x,7 + y,0,146,14 );
	gfx.PutPixel( 20 + x,7 + y,0,146,14 );
	gfx.PutPixel( 21 + x,7 + y,0,146,14 );
	gfx.PutPixel( 26 + x,7 + y,0,146,14 );
	gfx.PutPixel( 27 + x,7 + y,0,146,14 );
	gfx.PutPixel( 32 + x,7 + y,0,146,14 );
	gfx.PutPixel( 33 + x,7 + y,0,146,14 );
	gfx.PutPixel( 37 + x,7 + y,0,146,14 );
	gfx.PutPixel( 38 + x,7 + y,0,146,14 );
	gfx.PutPixel( 40 + x,7 + y,0,146,14 );
	gfx.PutPixel( 41 + x,7 + y,0,146,14 );
	gfx.PutPixel( 44 + x,7 + y,0,146,14 );
	gfx.PutPixel( 45 + x,7 + y,0,146,14 );
	gfx.PutPixel( 1 + x,8 + y,0,0,255 );
	gfx.PutPixel( 2 + x,8 + y,0,0,255 );
	gfx.PutPixel( 3 + x,8 + y,0,0,255 );
	gfx.PutPixel( 4 + x,8 + y,0,0,255 );
	gfx.PutPixel( 17 + x,8 + y,0,146,14 );
	gfx.PutPixel( 18 + x,8 + y,0,146,14 );
	gfx.PutPixel( 20 + x,8 + y,0,146,14 );
	gfx.PutPixel( 21 + x,8 + y,0,146,14 );
	gfx.PutPixel( 25 + x,8 + y,0,146,14 );
	gfx.PutPixel( 26 + x,8 + y,0,146,14 );
	gfx.PutPixel( 27 + x,8 + y,0,146,14 );
	gfx.PutPixel( 28 + x,8 + y,0,146,14 );
	gfx.PutPixel( 32 + x,8 + y,0,146,14 );
	gfx.PutPixel( 33 + x,8 + y,0,146,14 );
	gfx.PutPixel( 37 + x,8 + y,0,146,14 );
	gfx.PutPixel( 38 + x,8 + y,0,146,14 );
	gfx.PutPixel( 41 + x,8 + y,0,146,14 );
	gfx.PutPixel( 42 + x,8 + y,0,146,14 );
	gfx.PutPixel( 43 + x,8 + y,0,146,14 );
	gfx.PutPixel( 44 + x,8 + y,0,146,14 );

}

void Game::DrawTie(int x, int y)
{
	gfx.PutPixel( 12 + x,0 + y,0,146,14 );
	gfx.PutPixel( 13 + x,0 + y,0,146,14 );
	gfx.PutPixel( 14 + x,0 + y,0,146,14 );
	gfx.PutPixel( 15 + x,0 + y,0,146,14 );
	gfx.PutPixel( 16 + x,0 + y,0,146,14 );
	gfx.PutPixel( 17 + x,0 + y,0,146,14 );
	gfx.PutPixel( 21 + x,0 + y,0,146,14 );
	gfx.PutPixel( 22 + x,0 + y,0,146,14 );
	gfx.PutPixel( 23 + x,0 + y,0,146,14 );
	gfx.PutPixel( 24 + x,0 + y,0,146,14 );
	gfx.PutPixel( 28 + x,0 + y,0,146,14 );
	gfx.PutPixel( 29 + x,0 + y,0,146,14 );
	gfx.PutPixel( 30 + x,0 + y,0,146,14 );
	gfx.PutPixel( 31 + x,0 + y,0,146,14 );
	gfx.PutPixel( 32 + x,0 + y,0,146,14 );
	gfx.PutPixel( 33 + x,0 + y,0,146,14 );
	gfx.PutPixel( 14 + x,1 + y,0,146,14 );
	gfx.PutPixel( 15 + x,1 + y,0,146,14 );
	gfx.PutPixel( 22 + x,1 + y,0,146,14 );
	gfx.PutPixel( 23 + x,1 + y,0,146,14 );
	gfx.PutPixel( 28 + x,1 + y,0,146,14 );
	gfx.PutPixel( 29 + x,1 + y,0,146,14 );
	gfx.PutPixel( 14 + x,2 + y,0,146,14 );
	gfx.PutPixel( 15 + x,2 + y,0,146,14 );
	gfx.PutPixel( 22 + x,2 + y,0,146,14 );
	gfx.PutPixel( 23 + x,2 + y,0,146,14 );
	gfx.PutPixel( 28 + x,2 + y,0,146,14 );
	gfx.PutPixel( 29 + x,2 + y,0,146,14 );
	gfx.PutPixel( 14 + x,3 + y,0,146,14 );
	gfx.PutPixel( 15 + x,3 + y,0,146,14 );
	gfx.PutPixel( 22 + x,3 + y,0,146,14 );
	gfx.PutPixel( 23 + x,3 + y,0,146,14 );
	gfx.PutPixel( 28 + x,3 + y,0,146,14 );
	gfx.PutPixel( 29 + x,3 + y,0,146,14 );
	gfx.PutPixel( 14 + x,4 + y,0,146,14 );
	gfx.PutPixel( 15 + x,4 + y,0,146,14 );
	gfx.PutPixel( 22 + x,4 + y,0,146,14 );
	gfx.PutPixel( 23 + x,4 + y,0,146,14 );
	gfx.PutPixel( 28 + x,4 + y,0,146,14 );
	gfx.PutPixel( 29 + x,4 + y,0,146,14 );
	gfx.PutPixel( 30 + x,4 + y,0,146,14 );
	gfx.PutPixel( 31 + x,4 + y,0,146,14 );
	gfx.PutPixel( 32 + x,4 + y,0,146,14 );
	gfx.PutPixel( 14 + x,5 + y,0,146,14 );
	gfx.PutPixel( 15 + x,5 + y,0,146,14 );
	gfx.PutPixel( 22 + x,5 + y,0,146,14 );
	gfx.PutPixel( 23 + x,5 + y,0,146,14 );
	gfx.PutPixel( 28 + x,5 + y,0,146,14 );
	gfx.PutPixel( 29 + x,5 + y,0,146,14 );
	gfx.PutPixel( 14 + x,6 + y,0,146,14 );
	gfx.PutPixel( 15 + x,6 + y,0,146,14 );
	gfx.PutPixel( 22 + x,6 + y,0,146,14 );
	gfx.PutPixel( 23 + x,6 + y,0,146,14 );
	gfx.PutPixel( 28 + x,6 + y,0,146,14 );
	gfx.PutPixel( 29 + x,6 + y,0,146,14 );
	gfx.PutPixel( 14 + x,7 + y,0,146,14 );
	gfx.PutPixel( 15 + x,7 + y,0,146,14 );
	gfx.PutPixel( 22 + x,7 + y,0,146,14 );
	gfx.PutPixel( 23 + x,7 + y,0,146,14 );
	gfx.PutPixel( 28 + x,7 + y,0,146,14 );
	gfx.PutPixel( 29 + x,7 + y,0,146,14 );
	gfx.PutPixel( 14 + x,8 + y,0,146,14 );
	gfx.PutPixel( 15 + x,8 + y,0,146,14 );
	gfx.PutPixel( 21 + x,8 + y,0,146,14 );
	gfx.PutPixel( 22 + x,8 + y,0,146,14 );
	gfx.PutPixel( 23 + x,8 + y,0,146,14 );
	gfx.PutPixel( 24 + x,8 + y,0,146,14 );
	gfx.PutPixel( 28 + x,8 + y,0,146,14 );
	gfx.PutPixel( 29 + x,8 + y,0,146,14 );
	gfx.PutPixel( 30 + x,8 + y,0,146,14 );
	gfx.PutPixel( 31 + x,8 + y,0,146,14 );
	gfx.PutPixel( 32 + x,8 + y,0,146,14 );
	gfx.PutPixel( 33 + x,8 + y,0,146,14 );

}

void Game::SetSquareState(int index, XOState state)
{
	switch(index)
	{
	case 0:
		s0 = state;
		break;
	case 1:
		s1 = state;
		break;
	case 2:
		s2 = state;
		break;
	case 3:
		s3 = state;
		break;
	case 4:
		s4 = state;
		break;
	case 5:
		s5 = state;
		break;
	case 6:
		s6 = state;
		break;
	case 7:
		s7 = state;
		break;
	case 8:
		s8 = state;
		break;
	default:
		break;
	}
}
Game::XOState Game::GetSquareState(int index)
{
	switch(index)
	{
	case 0:
		return s0;
	case 1:
		return s1;
	case 2:
		return s2;
	case 3:
		return s3;
	case 4:
		return s4;
	case 5:
		return s5;
	case 6:
		return s6;
	case 7:
		return s7;
	case 8:
		return s8;
	default:
		return EMPTY;
	}
}
void Game::SetSquareState(int ix, int iy, XOState state)
{
	int index = iy * 3 + ix;
	SetSquareState(index, state);
}
Game::XOState Game::GetSquareState(int ix, int iy)
{
	int index = iy * 3 + ix;
	return GetSquareState(index);
}

void Game::DoUserInput()
{
	if(!keysPressedLastFrame)
	{
		if (kbd.RightIsPressed())
		{
			keysPressedLastFrame = true;
			cursorX++;
			if (cursorX > 2)
			{
				cursorX = 2;
			}
		}
		if (kbd.LeftIsPressed())
		{
			keysPressedLastFrame = true;
			cursorX--;
			if (cursorX < 0)
			{
				cursorX = 0;
			}
		}
		if (kbd.DownIsPressed())
		{
			keysPressedLastFrame = true;
			cursorY++;
			if (cursorY > 2)
			{
				cursorY = 2;
			}
		}
		if (kbd.UpIsPressed())
		{
			keysPressedLastFrame = true;
			cursorY--;
			if (cursorY < 0)
			{
				cursorY = 0;
			}
		}
	}
	else if (!(kbd.UpIsPressed() ||
		kbd.DownIsPressed() ||
		kbd.LeftIsPressed() ||
		kbd.RightIsPressed()))
	{
		keysPressedLastFrame = false;
	}

	if (kbd.EnterIsPressed() && GetSquareState(cursorX, cursorY) == EMPTY)
	{
		SetSquareState(cursorX, cursorY, activePlayer);
		EndTurn();
	}
}
void Game::EndTurn()
{
	if (activePlayer == X)
	{
		activePlayer = O;
	}
	else if (activePlayer = O)
	{
		activePlayer = X;
	}
	nTurns += 1;
}
Game::XOState Game::CheckForVictory()
{
	if (s0 == s1 && s1 == s2 && s0 != EMPTY)
	{
		return s0;
	}
	else if (s3 == s4 && s4 == s5 && s3 != EMPTY)
	{
		return s3;
	}
	else if (s6 == s7 && s7 == s8 && s6 != EMPTY)
	{
		return s6;
	}
	else if (s0 == s3 && s3 == s6 && s0 != EMPTY)
	{
		return s0;
	}
	else if (s1 == s4 && s4 == s7 && s1 != EMPTY)
	{
		return s1;
	}
	else if (s2 == s5 && s5 == s8 && s2 != EMPTY)
	{
		return s2;
	}
	else if (s0 == s4 && s4 == s8 && s0 != EMPTY)
	{
		return s0;
	}
	else if (s6 == s4 && s4 == s2 && s6 != EMPTY)
	{
		return s6;
	}
	else
	{
		return EMPTY;
	}
}
void Game::DrawEndScreen(int x, int y, XOState state)
{
	DrawToilet(x, y);
	if (state == X)
	{
		DrawXWin(x + 18, y + 57);
	}
	else if (state == O)
	{
		DrawOWin(x + 18, y + 57);
	}
	else
	{
		DrawTie(x + 18, y + 57);
	}
}
void Game::AIGetNextMoveRand()
{
	do
	{
		AIMoveX = rand() % 3;
		AIMoveY = rand() % 3;
	} while (GetSquareState(AIMoveX, AIMoveY) != EMPTY);
}
Game::XOState Game::Opponent(XOState curPlayer)
{
	if (curPlayer == X) {
		return O;
	}
	else
	{
		return X;
	}
}
int Game::GetTwoInARow(XOState player)
{
	if (s0 == player && s1 == player && s2 == EMPTY)
	{
		return 2;
	}
	else if (s0 == player && s2 == player && s1 == EMPTY)
	{
		return 1;
	}
	else if (s1 == player && s2 == player && s0 == EMPTY)
	{
		return 0;
	}
	else if (s3 == player && s4 == player && s5 == EMPTY)
	{
		return 5;
	}
	else if (s3 == player && s5 == player && s4 == EMPTY)
	{
		return 4;
	}
	else if (s4 == player && s5 == player && s3 == EMPTY)
	{
		return 3;
	}
	else if (s6 == player && s7 == player && s8 == EMPTY)
	{
		return 8;
	}
	else if (s6 == player && s8 == player && s7 == EMPTY)
	{
		return 7;
	}
	else if (s7 == player && s8 == player && s6 == EMPTY)
	{
		return 6;
	}
	else if (s0 == player && s4 == player && s8 == EMPTY)
	{
		return 8;
	}
	else if (s0 == player && s8 == player && s4 == EMPTY)
	{
		return 4;
	}
	else if (s4 == player && s8 == player && s0 == EMPTY)
	{
		return 0;
	}
	else if (s2 == player && s4 == player && s6 == EMPTY)
	{
		return 6;
	}
	else if (s2 == player && s6 == player && s4 == EMPTY)
	{
		return 4;
	}
	else if (s4 == player && s6 == player && s2 == EMPTY)
	{
		return 2;
	}
	else {
		return -1;
	}
}
void Game::AIGetNextMoveSmart()
{
	int indexP = GetTwoInARow(activePlayer);
	if (indexP != -1)
	{
		AIMoveIndex = indexP;
	}
	else
	{
		int indexO = GetTwoInARow(Opponent(activePlayer));
		if (indexO != -1)
		{
			AIMoveIndex = indexO;
		}
		else
		{
			do
			{
			AIMoveIndex = rand() % 9;
			} while (GetSquareState(AIMoveIndex) != EMPTY);
		}
	}
}
void Game::DoAITurnRand()
{
	AIGetNextMoveRand();
	SetSquareState(AIMoveX, AIMoveY, activePlayer);
	EndTurn();
}
void Game::DoAITurnSmart()
{
	AIGetNextMoveSmart();

	DrawCursor(AIMoveIndex);
	SetSquareState(AIMoveIndex, activePlayer);
	EndTurn();
}
void Game::ComposeFrame()
{
	const int baseX = 250;
	const int baseY = 150;
	const int squareSize = 100;

	XOState victoryState = CheckForVictory();
	DrawGrid(baseX, baseY);

	if (victoryState == EMPTY && nTurns < 9)
	{
		if (activePlayer == X)
		{
			DoAITurnSmart();
		}
		else
		{
			DoUserInput();
			DrawCursor(baseX + cursorX * squareSize, baseY + cursorY * squareSize);
		}
		
	}
	else
	{
		DrawEndScreen(358, 495, victoryState);
	}
	for (int iy = 0; iy < 3; iy += 1)
	{
		for (int ix = 0; ix < 3; ix += 1)
		{
			if (GetSquareState(ix, iy) == X)
			{
				DrawX(baseX + ix * squareSize, baseY + iy * squareSize);
			}
			else if(GetSquareState(ix, iy) == O)
			{
				DrawO(baseX + ix * squareSize, baseY + iy * squareSize);
			}
		}
	}
}