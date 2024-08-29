//---------------------------------------------------------------------------
#ifndef DSO_frameH
#define DSO_frameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <rxPlacemnt.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>

#include "Hard.h"
#include "ShapeGL.h"

#include <Menus.hpp>			// ›“Œ ƒŒÀ∆ÕŒ ¡€“‹ Õ»∆≈ ¬—≈’ rx*.h !!!!!
#include "DSO_cursor.h"
#define		CNT_SHP		6       // 4 shapes chnl + 2 shapes triggers
#define		CNT_CUR		6
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TcbSendChnlParams)(TChnlParams*)	;
typedef void __fastcall (__closure *TcbGetChnlParams )(uint8_t,TChnlParams*)	;
typedef void __fastcall (__closure *TcbSendTimParams )(TTimeParams*)	;
typedef void __fastcall (__closure *TcbGetTimParams  )(uint8_t,TTimeParams*)	;
typedef void __fastcall (__closure *TcbChngTimDiv    )(int chng)	;

enum  TTrgMode	{tmEdge=11,tmPulse,tmVideo,tmCAN,tmLIN,tmUART,tmSPI,tmI2C,tmALT};
enum  TTrgSweep {tsAUTO=21,tsNORMAL,tsSINGLE};
enum  TTrgSrc   {srcCH1=31,srcCH2,srcCH3,srcCH4};
enum  TTrgSlope {slRising=41,slFalling};
//---------------------------------------------------------------------------
class TFrmDSO : public TFrame
{
__published:	// IDE-managed Components
	TScrollBox *pView;
	TLabel *Label1;
	TLabel *Label2;
	TPanel *pLeft;
	TPanel *pTop2;
	TPanel *pRight;
	TPanel *pBottom2;
	TFormStorage *FormStorage1;
	TPanel *pTop;
	TSpeedButton *bStretch;
	TSpeedButton *bFixTrgT;
	TSpeedButton *btn3;
	TSpeedButton *btn4;
	TPanel *pBottom;
	TPopupMenu *pmChnl;
	TMenuItem *On1;
	TMenuItem *VDiv1;
	TMenuItem *N20mV1;
	TMenuItem *N50mV1;
	TMenuItem *Couple1;
	TMenuItem *DC1;
	TMenuItem *AC1;
	TMenuItem *GND1;
	TLabel *lblTimDiv;
	TShape *shpView;
	TLabel *lblTrgT;
	TPopupMenu *popTrgV;
	TMenuItem *miMode;
	TMenuItem *miEdge;
	TMenuItem *miPulse;
	TMenuItem *miVideo;
	TMenuItem *miCAN;
	TMenuItem *miLin;
	TMenuItem *miUART;
	TMenuItem *miSPI;
	TMenuItem *miI2C;
	TMenuItem *miALT;
	TMenuItem *miSweep;
	TMenuItem *miAUTO;
	TMenuItem *miNORMAL;
	TMenuItem *miSINGLE;
	TMenuItem *miSource;
	TMenuItem *miCH1;
	TMenuItem *miCH2;
	TMenuItem *miCH3;
	TMenuItem *miCH4;
	TMenuItem *miSlope;
	TMenuItem *miRising;
	TMenuItem *miFalling;
	void __fastcall FMouseMove(TObject *Sender,TShiftState Shift,int X,int Y);
	void __fastcall FResize(TObject *Sender);
	void __fastcall BtnClick(TObject *Sender);
	void __fastcall FMouseWheel(TObject *Sender, TShiftState Shift,
          int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall FMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall FDblClick(TObject *Sender);
	void __fastcall popTrgClick(TObject *Sender);
	void __fastcall FMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
//	uint32_t        LvlsPos		;
	CHard		m_Hard		;
	TRect		Rect		;
	TNotifyEvent 	FOnChange	;
	double		SmplPerDiv	;
	USHORT 		CntGrid_H	;
	USHORT		CntGrid_V	;

	TShapeGL* 	shpLvl[CNT_SHP]		;// shapes chnl + shapes triggers
	TLabel*		lblCh[4]		;
	TLabel*		lblDbg[4]		;
	TDsoCursor*	CursorDSO[CNT_CUR]	;

 void __fastcall CalcDrawWaves(void)		;
 void __fastcall DrawWaves   (void)    		;
 void __fastcall DrawShapes  (void)    		;
 void __fastcall DrawWaveInYT(USHORT nCH)	;
 void __fastcall SetHardLvlChnl(UCHAR ch,int lvl);
 void __fastcall ShowShpView(bool Fix_TrgT=false) 	;
 void __fastcall GetCursorInfo(void)		;


public:		// User declarations

 TcbSendChnlParams cbSendChnlParams		;
 TcbGetChnlParams  cbGetChnlParams		;
 TcbSendTimParams  cbSendTimParams		;
 TcbGetTimParams   cbGetTimParams		;
 TcbChngTimDiv	   cbChngTimDiv			;

	__fastcall TFrmDSO(TComponent* Owner,TNotifyEvent _onChnge)	;

 void   __fastcall Init(TObject* Sender,uint32_t _lvlsPos)		;

 void   __fastcall SetChnlParams(TChnlParams* params)	;
 void   __fastcall SetTimeDiv(TTimeParams* timPrms, String StrTimDiv)	;
 
 String __fastcall GetSmplRate  (void)			;
 String __fastcall GetTimDiv    (void)			;
 String __fastcall GetSmplPerDiv(void)			;
 String __fastcall GetTimClct   (void)			;
 size_t __fastcall CountSamples(){ return m_Hard.BufferLen()	;}

 void   __fastcall Destroy(TObject* Sender)		;
 USHORT __fastcall CollectData (void)			;
 void   __fastcall OnDraw(TObject *Sender)		;

 uint16_t __fastcall GetDevIx(){ return m_Hard.m_nDeviceIndex	;}
 TColor   __fastcall GetChColor(uint8_t ch){return ch<4 ? TColor(m_Hard.m_clrRGB[ch]) : clGray	;}

// uint8_t  __fastcall LoadLvl255(uint8_t nCh)
// { UCHAR* lvl = (UCHAR*)&(pLeft->Tag) ; return nCh < 4 ? lvl[nCh] : 127	;}
// void     __fastcall SaveLvl255(UCHAR nCh,UCHAR val)
// { UCHAR* lvl = (UCHAR*)&(pLeft->Tag) ; lvl[nCh] = val	;}
 void   __fastcall SaveProps(void){ FormStorage1->SaveFormPlacement()	;}
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmDSO *FrmDSO;
//---------------------------------------------------------------------------
#endif
