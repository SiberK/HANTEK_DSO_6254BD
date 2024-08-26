//---------------------------------------------------------------------------
#ifndef DrawOGLH
#define DrawOGLH
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include	<GL\glu.h>
#include	"DSO_frame.h"
//---------------------------------------------------------------------------
struct TParamsDrawWave{
 HDC 	hDC		;// handle to dc
 RECT 	Rect		;// the rect for drawing
 COLORREF clrRGB	;// the color of the line
 USHORT nDisType	;// display type: Line or Dot
 short* pSrcData	;// the source data for drawing
 ULONG 	nSrcDataLen	;// the source data length
 ULONG 	nDisDataLen	;// the display data length for drawing
 ULONG 	nCenterData	;// half of the source data
 USHORT nDisLeverPos	;// the display position(Zero Level)
 double dbHorizontal	;// the horizontal factor of zoom out/in
 double dbVertical	;// the vertical factor of zoom out/in
 USHORT nYTFormat	;// Fomat: Normal or Scan
 ULONG 	nScanLen	;// the scan data length, only invalidate in scan mode

 USHORT CntGrid_H	;
 USHORT CntGrid_V	;
 double	SmplPerDiv	;
 double StpOGL		;//
 double Offset_H	;
 double dLenWave	;
 double dPercentX	;
};
//---------------------------------------------------------------------------
extern GLvoid InitializeGL(HWND handle,GLsizei width, GLsizei height,TColor _color)	;
//extern GLvoid	DrawPxlArrayGL(GLsizei width, GLsizei height,TPxlArrayGL* PxlArr)			;
extern GLvoid DrawCursorsGL(TDsoCursor* Cur[],int CntCur)		;
extern GLvoid DrawShapesGL (TShapeGL*   shp[],int CntShp) 	       	;
extern GLvoid DrawWaveGL(USHORT nCh,TParamsDrawWave* params)		;
extern GLvoid DrawGridGL(USHORT cntGrid_H,USHORT cntGrid_V,USHORT nBright,USHORT IsGrid);
extern GLvoid DrawSceneGL(GLsizei width, GLsizei height)		;
extern GLvoid DestroyGL ()						;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif
