//---------------------------------------------------------------------------
#ifndef ShapeGLH
#define ShapeGLH

#include <ExtCtrls.hpp>
#include <GL\glu.h>
#include <Math.hpp>
//---------------------------------------------------------------------------
const int WIDTH_LVL_MARK  = 8	;
const int HEIGHT_LVL_MARK = 10	;
//---------------------------------------------------------------------------
#pragma pack(push,1)
struct TRgbPxl {
 static TColor clTransparence	;
 uint8_t	r,g,b,a	;
	TRgbPxl(GLbyte _r=0,GLbyte _g=0,GLbyte _b=0){ Set(_r,_g,_b)	;}
	TRgbPxl(TColor clr){ Set(clr)	;}

 void	Set(GLbyte _r,GLbyte _g,GLbyte _b){r=_r ; g=_g ; b=_b	; a = 0	;}
 void	Set(TColor clr){*(TColor*)this = clr	; if(clr != clTransparence) a = 0xFF	;}
};
#pragma pack(pop)
//---------------------------------------------------------------------------
int	iMap(double dmin,double dmax,double dpos,int imin,int imax){
		   dpos = dmin<dmax? Min(Max(dpos,dmin),dmax):
				     Max(Min(dpos,dmin),dmax) 		;
	    return imin + (imax-imin)*(dpos-dmin)/(dmax-dmin)+0.5	;}
//---------------------------------------------------------------------------
double	dMap(int dmin,int dmax,int dpos,double imin,double imax){
		   dpos = dmin<dmax? Min(Max(dpos,dmin),dmax):
				     Max(Min(dpos,dmin),dmax) 		;
	    return imin + (imax-imin)*(dpos-dmin)/(dmax-dmin)		;}
//---------------------------------------------------------------------------

struct TLvlPosition{
  int		HgtGL, WdtGL	 	;
//  TRect		Rect			;
  double	dLft,dRgt,dTop,dBot	;

  double	dPos	;
  int		iPos	;
  int		Lvl255	;

  void __fastcall SetPos(double _pos)
  { dPos = _pos		; CalcRct()		;}

  // Установить позицию от курсора
  void __fastcall SetCursorPos(int _pos)
  {if(HgtGL != 0){
     dPos   = dMap(0,HgtGL,_pos,1.0,-1.0)	;
     Lvl255 = iMap(-1.0,1.0,dPos,0,255)		;
     CalcRct()			  		;}}

// Установить позицию от LVL255
  void __fastcall SetLvl255(uint8_t lvl)
  {dPos = dMap(0,255,lvl,-1.0,1.0) ; CalcRct()	;}

  void __fastcall CalcRct(void){
    if(!WdtGL || !HgtGL) 	        return 	;
    double dWdt = WIDTH_LVL_MARK  * 2.0 / WdtGL	;
    double dHgt = HEIGHT_LVL_MARK * 2.0 / HgtGL	;

    iPos = iMap(1.0,-1.0,dPos,0,HgtGL)		;

    dLft = -1	; dRgt = dLft + dWdt		;
    dTop = dPos + dHgt/2	;
    dBot = dPos - dHgt/2	;
  }
};
//---------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
enum TShapeOrientation {soHrz,soVrt};
//---------------------------------------------------------------------------
class TShape_M : public TShape
{
 public:
 int		NCh	;
 AnsiString	Caption	;
 TLvlPosition	Pos	;

	__fastcall virtual TShape_M(Classes::TComponent* AOwner,
				    TWinControl*  _parent,
				    AnsiString    _name  ,
				    TColor        _color ,
				TShapeOrientation _ornt = soVrt ,
				    int		  _ofst = 0)	;

 void __fastcall Init(int _nCh, AnsiString _cap, UCHAR _lvl255)	;
 void __fastcall OnResize(int HgtP,int WdtP)			;
 void __fastcall DrawGL()	;

 private:
 int		Offset		;
 TShapeOrientation Orientation	;
 protected:
	virtual void __fastcall Paint(void);
};
//---------------------------------------------------------------------------
#pragma pack(push,1)
struct Trgb{
  uint8_t	r,g,b,a	;
  Trgb(TColor color) {Set(color)	;}

  void  Set(TColor color){*(TColor*)this= color	;}
  float rf()		{ return r/255.0	;}
  float gf()		{ return g/255.0	;}
  float bf()		{ return b/255.0	;}

  void  glColor(TColor color){ Set(color)	; glColor3ub(r,g,b)	;}
  void  glColor(void){ glColor3ub(r,g,b)	;}
};
#pragma pack(pop)
//---------------------------------------------------------------------------
void glColorT(TColor clr)  {Trgb rgb(clr)	        ; rgb.glColor()	;}
void glColorT(COLORREF clr){Trgb rgb(*(TColor*)&clr)	; rgb.glColor()	;}
//---------------------------------------------------------------------------
#endif
