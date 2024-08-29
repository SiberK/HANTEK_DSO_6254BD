//---------------------------------------------------------------------------
#ifndef DSO_cursorH
#define DSO_cursorH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>

#include <GL\glu.h>
#include <Math.hpp>
#include <Math.h>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
enum TCursorOrientation {coHrz,coVrt}	;
//---------------------------------------------------------------------------
class TDsoCursor : public TComponent
{
private:
 static TDsoCursor*	First	;
 static TDsoCursor*	Last	;
 static int	Count		;
 static double	ScaleX, ScaleY	;

 TDsoCursor*	Next		;
 TColor		Color		;
 double 	Position	;
 bool		flSlct		;
 TCursorOrientation Orientation	;

protected:

public:
static bool	flChng	;

       __fastcall TDsoCursor(TComponent* AOwner,
			     AnsiString  _name ,
			     double	 _pos  ,
		     TCursorOrientation  _ornt ,
			     TColor      _color);
 void __fastcall DrawGL() 	;
 bool __fastcall OnSelect(double dX,double dY)	;
 bool __fastcall OnMove  (double dX,double dY)	;
// static void __fastcall SetScale(double sX,double sY){ ScaleX = sX	; ScaleY = sY	;}
 static void   __fastcall CalcScale(int cntDivH,int cntDivV,double timDiv,double vltDiv);
 static double __fastcall GetScaleX(void){ return ScaleX	;}
 static double __fastcall GetScaleY(void){ return ScaleY	;}
 static String __fastcall GetInfoT(void)	;
 static String __fastcall GetInfoV(void)	;
 __published:

};
//---------------------------------------------------------------------------
extern String IntervalToStr(double val)		;
extern String IntervalToStr2(double val)	;
extern String VoltToStr(double val)		;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#endif
