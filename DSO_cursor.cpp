//---------------------------------------------------------------------------
#pragma hdrstop
#include "DSO_cursor.h"
#include "ShapeGL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TDsoCursor* TDsoCursor::First  = 0	;
TDsoCursor* TDsoCursor::Last   = 0	;
int         TDsoCursor::Count  = 0	;
bool   	    TDsoCursor::flChng = false	;
double      TDsoCursor::ScaleX = 1.0 	;
double      TDsoCursor::ScaleY = 1.0 	;
const	double MinDist = 0.03		;
//---------------------------------------------------------------------------
  __fastcall TDsoCursor::TDsoCursor(TComponent* AOwner,
			     AnsiString    _name  ,
			     double	   _pos   ,
		       TCursorOrientation  _ornt ,
			     TColor        _color):TComponent(AOwner)
{
 Name   = _name		; Position = _pos	;
 Color  = _color 	; flSlct   = false	;
 flChng = true		; Orientation = _ornt	;

 Next = 0      	; Count++	;
 if(!First) First = this	;
 if(Last)   Last->Next = this	;
 Last = this	;
}
//---------------------------------------------------------------------------
int ComparePos(const void* pVal1,const void* pVal2)
{double val1 = *(double*)pVal1	;
 double val2 = *(double*)pVal2	;
 return val1 < val2 ? -1 : val1>val2 ? 1 : 0	;}
//---------------------------------------------------------------------------
String IntervalToStr(double val)
{String Str,SHz	;
 double Hz = val != 0.0 ? 1.0/val : 0.0				;

 if(val > 1)       Str = FormatFloat("0.00 S " ,val)		;
 else if(val>1e-3) Str = FormatFloat("0.00 mS ",val*1e3)	;
 else if(val>1e-6) Str = FormatFloat("0.00 uS ",val*1e6)	;
 else if(val>1e-9) Str = FormatFloat("0.00 nS ",val*1e9)	;
 else              Str = FormatFloat("0.00 nS ",val*1e9)	;

 if(Hz < 1e3)      SHz = FormatFloat("(0.00 Hz)" ,Hz)		;
 else if(Hz<1e6)   SHz = FormatFloat("(0.00 kHz)",Hz*1e-3)	;
 else if(Hz<1e9)   SHz = FormatFloat("(0.00 MHz)",Hz*1e-6)	;
 else 		   SHz = FormatFloat("(0.00 GHz)",Hz*1e-9)	;

 return (Str+SHz)	;}
//---------------------------------------------------------------------------
String  __fastcall TDsoCursor::GetInfoT(void)
{String Str = ""		;

 if(!Count) return Str		;
 int	ic = 0, cntInt=0	;

 double* pos = new double[Count];

 for(TDsoCursor* cur = First; cur;cur=cur->Next){
   if(cur->Orientation != coVrt) continue	;
   pos[ic++] = cur->Position			;}

 cntInt = ic-1					;// кол-во интервалов
 if(cntInt){
   qsort(pos,ic,sizeof(*pos),ComparePos)	;

   for(ic=0;ic<cntInt;ic++){
     pos[ic] = (pos[ic+1]-pos[ic])*ScaleX	;// интервалы (Sec)!!!
     if(ic) Str = Str + "   "			;
     Str = Str + IntervalToStr(pos[ic])		;
   }
 }

 delete[] pos				;
 return Str				;}
//---------------------------------------------------------------------------
void __fastcall TDsoCursor::CalcScale(int cntDivH,int cntDivV,double timDiv,double vltDiv)
{
 ScaleX = cntDivH*timDiv/2.0	;
 ScaleY = cntDivV*vltDiv/2.0   	;
}
//---------------------------------------------------------------------------
bool __fastcall TDsoCursor::OnSelect(double dX,double dY)
{bool rslt = false		;
 double dP = Orientation == coVrt ? dX : dY	;

 if(fabs(dP-Position) < MinDist){ flChng = flSlct = rslt = true	;
   Position = dP		;}
 else flSlct = false		;

return rslt			;}
//---------------------------------------------------------------------------
bool __fastcall TDsoCursor::OnMove(double dX,double dY)
{bool rslt = false		;
 double dP = Orientation == coVrt ? dX : dY	;

 if(flSlct){ flChng = rslt = true	;
   Position = dP		;}

return rslt			;}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TDsoCursor::DrawGL()
{
 glBegin(GL_LINES)		;{
   glColorT(Color)		;
   if(Orientation == coVrt){
     glVertex2f(Position,-1.0)	;
     glVertex2f(Position, 1.0)	;}
   else{
     glVertex2f(-1.0,Position)	;
     glVertex2f( 1.0,Position)	;
   }
 } glEnd()			;
}
//---------------------------------------------------------------------------
