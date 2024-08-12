//---------------------------------------------------------------------------
#include	<vcl.h>
#pragma hdrstop
#include "ShapeGL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TShape_M::TShape_M(Classes::TComponent* AOwner,
				    TWinControl * _parent,
				    AnsiString    _name  ,
				    TColor	  _color,
				TShapeOrientation _ornt ,
				    int		  _ofst
				    ) : TShape(AOwner)
{
 Left   = 0		; Top    = 10		;
 Height = 16		; Color = _color	;
 Parent = _parent	; Name  = _name		;
 Orientation = _ornt	;
 Offset = _ofst		;

 TPanel* pnl = dynamic_cast<TPanel*>(Parent)	;

 Canvas->Pen->Color   = Color			;
 Canvas->Pen->Width   = 2	  		;
 Canvas->Brush->Style = bsClear			;
 
 if(pnl){
   if(Orientation == soVrt)
	Width  = pnl->Width			;
   else Height = pnl->Height			;

   Canvas->Font->Assign(pnl->Font)	       	;
   Canvas->Font->Color = Color	     		;
 }
}
//---------------------------------------------------------------------------
void __fastcall TShape_M::Init(int _nCh, AnsiString _cap, UCHAR _lvl255)
{Pos.SetLvl255(_lvl255)				;
 NCh = _nCh		; Caption = _cap	;
 Top = Pos.iPos - Height/2			;}
//---------------------------------------------------------------------------
void __fastcall TShape_M::OnResize(int HgtP,int WdtP)
{Pos.HgtGL = HgtP	; Pos.WdtGL = WdtP	;

 Pos.CalcRct()		;
 
 Top = Pos.iPos - Height/2			;}
//---------------------------------------------------------------------------
void __fastcall TShape_M::Paint(void)
{TPanel* pnl = dynamic_cast<TPanel*>(Parent)	;
 if(pnl){   Width = pnl->Width			;}

 Canvas->Rectangle(1,1,Width,Height)		;
 Canvas->TextOut(4,1,Caption)			;
}
//---------------------------------------------------------------------------
void __fastcall TShape_M::DrawGL()
{float	X1 = Pos.dLft , X2 = Pos.dRgt		;
 float	Y1 = Pos.dTop , Y2 = Pos.dBot , Y3 = (Y1+Y2)/2.0	;

 glBegin(GL_TRIANGLES);{
   glColorT(Color)	;
   glVertex2f(X1,Y1)	;
   glVertex2f(X1,Y2)	;
   glVertex2f(X2,Y3)	;
 } glEnd()		;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
TColor TRgbPxl::clTransparence = clWhite	;
//---------------------------------------------------------------------------
//void __fastcall TShapeGL::Init(int _nCh, double _pos,TColor _clr,TFont* font)
//{int ix,iy,x,y	;
// NCh   = _nCh	;
// Color = _clr	; Pos.SetPos(_pos)	;
// size_t	cntPxls  = HEIGHT_LVL_MARK * WIDTH_LVL_MARK	;
// size_t	sizePxls = cntPxls * sizeof(TRgbPxl)		;
//
//// Bmp = new Windows::TBitmap	;
// Graphics::TBitmap* Bmp = new Graphics::TBitmap	;
// Bmp->PixelFormat = pf32bit   	;
// Bmp->Width  = WIDTH_LVL_MARK	;
// Bmp->Height = HEIGHT_LVL_MARK	;
//
// TCanvas* Canvas = Bmp->Canvas	;
// Canvas->Pen->Color = _clr	;
// Canvas->Pen->Width = 2		;
// Canvas->Brush->Style = bsClear	;
//
// Canvas->Rectangle(1,1,Bmp->Width,Bmp->Height)	;
//
// Canvas->Font->Assign(font)		;
// Canvas->Font->Color = _clr		;
// Canvas->TextOut(4,2,String(_nCh))	;
//
// Pixels = new TRgbPxl[cntPxls]		;
//
//// GetBitmapBits(Bmp->Handle,sizePxls,(LPVOID)Pixels);
//
// for(y=0;y<HEIGHT_LVL_MARK;y++){
//   for(x=0;x<WIDTH_LVL_MARK;x++){
//     ix = x + y*WIDTH_LVL_MARK			;
//     iy = HEIGHT_LVL_MARK-1-y  			;
//     Pixels[ix].Set(Bmp->Canvas->Pixels[x][iy])	;
//   }}
//
// delete Bmp	;
//}
////-----------------------------------------------------------------------------
//void __fastcall TShapeGL::DrawGL(){
//  if(Pixels){
//    glEnable(GL_ALPHA_TEST)		;
//    glAlphaFunc(GL_GEQUAL, 0.5f)	;
//    glRasterPos2f(Pos.dLft,Pos.dBot)	;
//    glDrawPixels(WIDTH_LVL_MARK,HEIGHT_LVL_MARK,GL_RGBA,GL_UNSIGNED_BYTE,Pixels)	;
//    glDisable(GL_ALPHA_TEST)		;
//  }
//}
////-----------------------------------------------------------------------------

