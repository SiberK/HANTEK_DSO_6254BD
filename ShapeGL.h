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
typedef void __fastcall (__closure *TcbSetHardLvl)(UCHAR ch,int lvl)	;
enum TShapeOrientation {soHrz,soVrt,soHrzM,soVrtM};
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
double	dMap(int imin,int imax,int ipos,double dmin,double dmax){
		   ipos = imin<imax? Min(Max(ipos,imin),imax):
				     Max(Min(ipos,imin),imax) 		;
	    return dmin + (dmax-dmin)*(ipos-imin)/(imax-imin)		;}
//---------------------------------------------------------------------------
double	dMapDbg(int imin,int imax,int ipos,double dmin,double dmax){
//		   ipos = imin<imax? Min(Max(ipos,imin),imax):
//				     Max(Min(ipos,imin),imax) 		;
	    return dmin + (dmax-dmin)*(ipos-imin)/(imax-imin)		;}
//---------------------------------------------------------------------------

struct TLvlPosition{
  short		HgtGL, WdtGL	 	;
  double	dLft,dRgt,dTop,dBot	;

  double	dPos		;
  short		iPos , iOfst	;
  short		Lvl100		;
  short		Lvl255		;
  short		Ornt		;

  void __fastcall SetPos(double _pos,bool fix=0)
  { dPos = _pos		; CalcRct(fix)		;}

//  void __fastcall SetFixPos(double _pos)
//  { dPos = _pos	; dLft = -1	;
//    if(!WdtGL || !HgtGL) 	        return 	;
//    double dWdt = WIDTH_LVL_MARK  * 2.0 / WdtGL	;
//    double dHgt = HEIGHT_LVL_MARK * 2.0 / HgtGL	;
//    dRgt = dLft + dWdt		;
//    dTop = dPos + dHgt/2	;
//    dBot = dPos - dHgt/2	;}

  // Установить позицию от курсора
  void __fastcall SetCursorPos(int _pos)
  {if(HgtGL != 0){
     if(Ornt == soVrt || Ornt == soVrtM){
	  dPos = dMap(iOfst,HgtGL,_pos,1.0,-1.0)	;}
     else dPos = dMap(0,HgtGL,_pos-iOfst,-1.0,1.0)	;
     CalcRct()			  		;}}

// Установить позицию от LVL255
  void __fastcall SetLvl255(uint8_t lvl)
  {dPos = dMap(0,255,lvl,-1.0,1.0) ; CalcRct()	;}

  void __fastcall SetLvl100(uint8_t lvl)
  {dPos = dMap(0,100,lvl,-1.0,1.0) ; CalcRct()	;}

  void __fastcall CalcRct(bool fix=0){
    if(!WdtGL || !HgtGL) 	        return 	;
    double dWdt = WIDTH_LVL_MARK  * 2.0 / WdtGL	;
    double dHgt = HEIGHT_LVL_MARK * 2.0 / HgtGL	;

    if(Ornt == soVrt || Ornt == soVrtM)
	 iPos = iMap(1.0,-1.0,dPos,0,HgtGL)	;
    else iPos = iMap(-1.0,1.0,dPos,0,HgtGL) + iOfst	;
    
    if(!fix){
      Lvl255 = iMap(-1.0,1.0,dPos,0,255)       	;
      Lvl100 = iMap(-1.0,1.0,dPos,0,100)       	;}

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
class TShapeGL : public TShape
{
 public:
 static bool 	flChng	;
 
 int		NCh	;
 AnsiString	Caption	;
 TLvlPosition	Pos	;
 TcbSetHardLvl	cbSetHardLvl	;

	__fastcall virtual TShapeGL(Classes::TComponent* AOwner,
				    TWinControl*  _parent,
				    AnsiString    _name  ,
				    TColor        _color ,
				TShapeOrientation _ornt = soVrt ,
				    int		  _ofst = 0)	;

 void __fastcall Init(int _nCh, AnsiString _cap, UCHAR _lvl255)	;
 void __fastcall OnResize(int HgtP,int WdtP,bool fix=0)		;
 void __fastcall OnMove(int X,int Y)	;
// void __fastcall MouseWheel(int WheelDelta, TPoint &MousePos)	;
 void __fastcall DrawGL()		;
 short __fastcall GetLvl(void)
 { return Orientation == soHrz ? Pos.Lvl100 : Pos.Lvl255	;}

 private:
 int		Offset		;
 TShapeOrientation Orientation	;
 protected:
	virtual void __fastcall Paint(void);
__published:
	__property OnDblClick ;
	
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
