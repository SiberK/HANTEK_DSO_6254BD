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
typedef	void __fastcall (__closure *TOnChangeChnl)(TObject*)	;
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
private:	// User declarations
 TOnChangeChnl	FOnChange	;
 int 		IX		;
 TChnlParams    Prms		;
public:		// User declarations
	__fastcall TFrmChnl(TComponent* Owner,TWinControl* parent,int ch,TOnChangeChnl _onChnge);

 void   __fastcall SaveProps(void){ FormStorage1->SaveFormPlacement()	;}
 TChnlParams* __fastcall GetParams(void){ return &Prms	;}
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmChnl *FrmChnl;
//---------------------------------------------------------------------------
#endif
