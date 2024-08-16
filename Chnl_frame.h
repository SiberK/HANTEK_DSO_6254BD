//---------------------------------------------------------------------------
#ifndef Chnl_frameH
#define Chnl_frameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "rxPlacemnt.hpp"

#include "StdAfx.h"
//---------------------------------------------------------------------------
class TFrmChnl : public TFrame
{
__published:	// IDE-managed Components
	TCheckBox *bOn;
	TComboBox *cbVoltDiv;
	TPanel *Panel1;
	TFormStorage *FormStorage1;
	TCheckBox *cbX10;
	TComboBox *cbAC_DC;
	void __fastcall BtnOnClick(TObject *Sender);
	void __fastcall FormStorage1RestorePlacement(TObject *Sender);
private:	// User declarations
 TNotifyEvent	FOnChange	;
 int 		IX		;
 TChnlParams    Prms		;
public:		// User declarations
	__fastcall TFrmChnl(TComponent* Owner,TWinControl* parent,int ch,TNotifyEvent _onChnge);

 void   __fastcall SaveProps(void){ FormStorage1->SaveFormPlacement()	;}
 uint16_t __fastcall GetLvlPos(void){ return Min(Max(cbVoltDiv->Tag,0),255)	;}
 void     __fastcall SetLvlPos(uint16_t lvl){ cbVoltDiv->Tag = lvl	;}
 TChnlParams* __fastcall GetParams(void)	;//{ return &Prms	;}
 void __fastcall SetParams(TChnlParams* prms)	;
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmChnl *FrmChnl;
//---------------------------------------------------------------------------
#endif
