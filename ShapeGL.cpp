//---------------------------------------------------------------------------
#include	<vcl.h>
#pragma hdrstop
#include "ShapeGL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TShapeGL::TShapeGL(Classes::TComponent* AOwner,
				    TWinControl * _parent,
				    AnsiString    _name  ,
				    TColor	  _color,
				TShapeOrientation _ornt ,
				    int		  _ofst
				    ) : TShape(AOwner)
{
 Parent = _parent	; Name  = _name		;
 Offset = _ofst		; Color = _color	;
 Orientation  = _ornt	;
 cbSetHardLvl = 0	;

 if(Orientation == soVrt || Orientation == soVrtM){
   Left   = 0		; Top   = 10		; Height = 16 	;}
 else{Left = _ofst	; Top   = 0		; Width  = 16	;}


 TPanel* pnl = dynamic_cast<TPanel*>(Parent)	;

 Canvas->Pen->Color   = Color			;
 Canvas->Pen->Width   = 2	  		;
 Canvas->Brush->Style = bsClear			;

 if(pnl){
   if(Orientation == soVrt || Orientation == soVrtM){
	Width  = pnl->Width			;}
   else{Height = pnl->Height			;}

   Canvas->Font->Assign(pnl->Font)	       	;
   Canvas->Font->Color = Color	     		;
 }
}
//---------------------------------------------------------------------------
void __fastcall TShapeGL::Init(int _nCh, AnsiString _cap, UCHAR _lvl255)
{NCh     = _nCh	; Pos.Ornt = Orientation	;
 Caption = _cap	; Tag = _nCh + 1		;

 if(Orientation == soVrt || Orientation == soVrtM){
      Pos.iOfst = 0				;
      Pos.SetLvl255(_lvl255)		       	;
      Top  = Pos.iPos - Height/2		;}

 else{Pos.iOfst = Offset			;
      Pos.SetLvl100(_lvl255)		       	;
      Left = Pos.iPos - Width /2 		;}
}
//---------------------------------------------------------------------------
void __fastcall TShapeGL::OnResize(int HgtP,int WdtP)
{if(Orientation == soVrt || Orientation == soVrtM){
   Pos.HgtGL = HgtP	; Pos.WdtGL = WdtP	;
   Top = Pos.iPos - Height/2			;}
 else{ Pos.HgtGL = WdtP	; Pos.WdtGL = HgtP	;
   Left = Pos.iPos - Width/2			;}

 Pos.CalcRct()		;
}
//---------------------------------------------------------------------------
void __fastcall TShapeGL::OnMove(int X,int Y)
{
 if(Orientation == soVrt || Orientation == soVrtM){
   Y += Top	;
   Y = Min(Max(Y,0),Parent->Height)		;
   Top = Y - Height/2				;
   Pos.SetCursorPos(Y) 				;
   if(cbSetHardLvl) cbSetHardLvl(NCh,Pos.Lvl255);
//  m_Hard.SetLvl(shpM->NCh,shpM->Pos.Lvl255)	;
 }
 else{
   X += Left	;
   X = Min(Max(X,0),Parent->Width)		;
   Left = X - Width/2				;
   Pos.SetCursorPos(X)				;
   if(cbSetHardLvl) cbSetHardLvl(NCh,Pos.Lvl100);
 }
}
//---------------------------------------------------------------------------
void __fastcall TShapeGL::MouseWheel(int WheelDelta, TPoint &MousePos)
{

}
//---------------------------------------------------------------------------
void __fastcall TShapeGL::Paint(void)
{TPanel* pnl = dynamic_cast<TPanel*>(Parent)	; if(!pnl) return	;

 if(Orientation == soVrt || Orientation == soVrtM){
   Width = pnl->Width	;
   Canvas->Rectangle(1,1,Width,Height)		;
   Canvas->TextOut  (4,1,Caption)	       	;}
 else{ Height = pnl->Height			;
   Canvas->Rectangle(1,1,Width,Height)		;
   Canvas->TextOut  (4,1,Caption)	       	;
 }
}
//---------------------------------------------------------------------------
void __fastcall TShapeGL::DrawGL()
{float	X1 = Pos.dLft , X2 = Pos.dRgt , X3 = (X1+X2)/2.0	;
 float	Y1 = Pos.dTop , Y2 = Pos.dBot , Y3 = (Y1+Y2)/2.0	;

 if(Orientation == soVrt || Orientation == soVrtM){
   if(Orientation == soVrtM){X1 = -X1	; X2 = -X2		;}// зеркальное
   glBegin(GL_TRIANGLES);{
     glColorT(Color)	;
     glVertex2f(X1,Y1)	;
     glVertex2f(X1,Y2)	;
     glVertex2f(X2,Y3)	;
   } glEnd()		;
 }
 else{
   glBegin(GL_TRIANGLES);{
     glColorT(Color)	;
     glVertex2f(Y1,-X1)	;
     glVertex2f(Y2,-X1)	;
     glVertex2f(Y3,-X2)	;
   } glEnd()		;
 }
}
//---------------------------------------------------------------------------

