/****************************************************************************************** 
 *	Chili DirectX Framework Version 11.12.17											  *	
 *	D3DGraphics.cpp																		  *
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
#include "D3DGraphics.h"
#include <stdlib.h>
#include <math.h>

D3DGraphics::D3DGraphics( HWND hWnd )
{
	pDirect3D = Direct3DCreate9( D3D_SDK_VERSION );

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp,sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

    pDirect3D->CreateDevice( D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,&d3dpp,&pDevice );
}

D3DGraphics::~D3DGraphics()
{
	if( pDevice )
	{
		pDevice->Release();
		pDevice = NULL;
	}
	if( pDirect3D )
	{
		pDirect3D->Release();
		pDirect3D = NULL;
	}
}

void D3DGraphics::PutPixel( int x,int y,int r,int g,int b )
{
	IDirect3DSurface9* pBackBuffer = NULL;
	D3DLOCKED_RECT rect;

	pDevice->GetBackBuffer( 0,0,D3DBACKBUFFER_TYPE_MONO,&pBackBuffer );
	pBackBuffer->LockRect( &rect,NULL,NULL );
	((D3DCOLOR*)rect.pBits)[ x + (rect.Pitch >> 2) * y ] = D3DCOLOR_XRGB( r,g,b );
	pBackBuffer->UnlockRect();
	pBackBuffer->Release();
}

void D3DGraphics::BeginFrame()
{
	pDevice->Clear( 0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0),0.0f,0 );
}

void D3DGraphics::EndFrame()
{
	pDevice->Present( NULL,NULL,NULL,NULL );
}

void D3DGraphics::DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b)
{
	int dx, dy;
	dx = x2 - x1;
	dy = y2 - y1;
	

	if (abs(dy) > abs(dx))
	{
		if (y1 > y2)
		{
			int temp = y2;
			y2 = y1;
			y1 = temp;
			temp = x2;
			x2 = x1;
			x1 = temp;
		}
		float m = float(dx) / float(dy);
		float bValue = x1 - m*y1;
		for (int y = y1; y <= y2; y++)
		{
			int x = m*y + bValue + 0.5f;
			PutPixel(x, y, r, g, b);
		}
	}
	else
	{
		if (x1 > x2)
		{
			int temp = y2;
			y2 = y1;
			y1 = temp;
			temp = x2;
			x2 = x1;
			x1 = temp;
		}
		float m = (float)dy/ (float)dx;
		float bValue = y1 - m*x1;
		for (int x = x1; x <= x2; x++)
		{
			int y = m * x + bValue + 0.5f;
			PutPixel(x, y, r, g, b);
		}
	}
}

void D3DGraphics::DrawCircle(int cx, int cy, int rad, int r, int g, int b)
{
	float radSqr = rad * rad;
	int x0 = 0.7071068f * rad + 0.5f;
	for (int x = 0; x <= x0; x++)
	{
		int y = sqrt(radSqr - (x * x)) + 0.5f;
		PutPixel(cx + x, cy + y, r, g, b);
		PutPixel(cx + y, cy + x, r, g, b);
		PutPixel(cx - x, cy + y, r, g, b);
		PutPixel(cx - y, cy + x, r, g, b);
		PutPixel(cx + x, cy - y, r, g, b);
		PutPixel(cx + y, cy - x, r, g, b);
		PutPixel(cx - x, cy - y, r, g, b);
		PutPixel(cx - y, cy - x, r, g, b);
	}
}