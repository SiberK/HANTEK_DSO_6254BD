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
//---------------------------------------------------------------------------
class TDsoCursor : public TComponent
{
private:
 TColor	Color		;
 double Position	;
 bool	flSlct		;


protected:

public:
static bool	flChng	;

       __fastcall TDsoCursor(TComponent* AOwner,
			     AnsiString  _name ,
			     double	 _pos  ,
			     TColor      _color);
 void __fastcall DrawGL() 	;
 bool __fastcall OnSelect(double dX)	;
 bool __fastcall OnMove  (double dX)	;
__published:

};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#endif
