//---------------------------------------------------------------------------
#ifndef DSO_frameH
#define DSO_frameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "rxPlacemnt.hpp"

#include "ShapeGL.h"

#include "Hard.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFrmDSO : public TFrame
{
__published:	// IDE-managed Components
	TScrollBox *pView;
	TLabel *Label1;
	TLabel *Label2;
	TPanel *pLeft;
	TPanel *pTop;
	TPanel *pRight;
	TPanel *pBottom;
	void __fastcall FMouseMove(TObject *Sender,TShiftState Shift,int X,int Y);
	void __fastcall pViewResize(TObject *Sender);
	void __fastcall PanResize(TObject *Sender);
private:	// User declarations
//	uint32_t        LvlsPos		;
	CHard		m_Hard		;
	TRect		Rect		;
	TNotifyEvent 	FOnChange	;
	double		SmplPerDiv	;
	USHORT 		CntGrid_H	;
	USHORT		CntGrid_V	;


	TShape_M* 	shpLvl[4]	;

 void   __fastcall DrawWaves   (void)    	;
 void   __fastcall DrawShapes  (void)    	;
 void   __fastcall DrawWaveInYT(USHORT nCH)	;

public:		// User declarations
	__fastcall TFrmDSO(TComponent* Owner,TNotifyEvent _onChnge)	;

 void   __fastcall Init(TObject* Sender,uint32_t _lvlsPos)		;

 void   __fastcall SetChnlParams(TChnlParams* params)
			{ m_Hard.SetChnlParams(params)	;}
 void   __fastcall SetTimeDiv(TTimeParams* timPrms)
			{ SmplPerDiv = m_Hard.SetTimeDiv(timPrms)	;}
 double __fastcall  SamplingRate()
			{ return m_Hard.SamplingRate()	;}
 size_t __fastcall CountSamples(){ return m_Hard.BufferLen()	;}			

 void   __fastcall Destroy(TObject* Sender)		;
 USHORT __fastcall CollectData (void)			;
 void   __fastcall OnDraw(TObject *Sender)		;

 uint16_t __fastcall GetDevIx(){ return m_Hard.m_nDeviceIndex	;}

 uint8_t  __fastcall LoadLvl255(uint8_t nCh)
 { UCHAR* lvl = (UCHAR*)&Tag ; return nCh < 4 ? lvl[nCh] : 127	;}
 void     __fastcall SaveLvl255(UCHAR nCh,UCHAR val)
 { UCHAR* lvl = (UCHAR*)&Tag ; lvl[nCh] = val	;}
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmDSO *FrmDSO;
//---------------------------------------------------------------------------
#endif
