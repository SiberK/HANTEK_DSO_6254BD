//---------------------------------------------------------------------------
#pragma hdrstop
#include "DSO_cursor.h"
#include "ShapeGL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
bool TDsoCursor::flChng = false	;
const	double MinDist = 0.03	;
//---------------------------------------------------------------------------
  __fastcall TDsoCursor::TDsoCursor(TComponent* AOwner,
			     AnsiString    _name  ,
			     double	   _pos   ,
			     TColor        _color):TComponent(AOwner)
{
 Name   = _name		; Position = _pos	;
 Color  = _color 	; flSlct   = false	;
 flChng = true		;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool __fastcall TDsoCursor::OnSelect(double dX)
{bool rslt = false		;

 if(fabs(dX-Position) < MinDist){ flChng = flSlct = rslt = true	;
   Position = dX		;}
 else flSlct = false		;

return rslt			;}
//---------------------------------------------------------------------------
bool __fastcall TDsoCursor::OnMove(double dX)
{bool rslt = false		;

// if(fabs(dX-Position) < MinDist){ flChng = rslt = true	;
//   Position = dX		;}
 if(flSlct){ flChng = rslt = true	;
   Position = dX		;}

return rslt			;}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TDsoCursor::DrawGL()
{
 glBegin(GL_LINES)		;{
   glColorT(Color)		;
   glVertex2f(Position,-1.0)	;
   glVertex2f(Position, 1.0)	;
 } glEnd()			;
}
//---------------------------------------------------------------------------
