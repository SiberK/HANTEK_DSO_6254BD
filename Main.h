﻿//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Mask.hpp>

#include "rxPlacemnt.hpp"
#include <Menus.hpp>
#include "rxCurrEdit.hpp"
#include "rxToolEdit.hpp"
#include "Chnl_frame.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *StatBar1;
	TPanel *pDSO;
	TFormStorage *FormStorage1;
	TTimer *timRef;
	TGroupBox *GroupBox1;
	TGroupBox *gbChnl;
	TComboBox *cbTimeDiv;
	TComboBox *cbSmplDiv;
	TGroupBox *gbTrgr;
	TComboBox *cbEdge;
	TComboBox *cbSrcTrg;
	TGroupBox *GroupBox2;
	TCurrencyEdit *eTimRef;
	TPanel *panSwtch;
	TPanel *pTool;
	TPanel *Panel1;
	TSpeedButton *bPause;
	TSpeedButton *bDbg1;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	void __fastcall timRefTimer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormStorage1RestorePlacement(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall TimeDivChange(TObject *Sender);
	void __fastcall eTimRefChange(TObject *Sender);
	void __fastcall PanDblClick(TObject *Sender);
	void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift,
          int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall FBtnClick(TObject *Sender);

private:	// User declarations
	String		StrVersion	;
	double		SmplPerDiv	;
	TFrmChnl*	ChnlFrm[4]	;

 void   __fastcall wrStatBar(int i,String val)
   { if(i<StatBar1->Panels->Count)StatBar1->Panels->Items[i]->Text = val	;}
 String	__fastcall rdStatBar(int i)
   { return (i<StatBar1->Panels->Count)? StatBar1->Panels->Items[i]->Text : String("")	;}
 void __fastcall ChnlOnChange(TObject *Sender)		;

 void __fastcall SendChnlParams(TChnlParams* params)	;
 void __fastcall GetChnlParams(uint8_t ch,TChnlParams* params)	;
 void __fastcall ChngTimDiv(int chng)			;

 public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

 void __fastcall DisplaySampleRate()			;
 __property String  StatMsg[int i] = {read=rdStatBar,write=wrStatBar	};
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
