//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Chnl_frame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "rxPlacemnt"
#pragma resource "*.dfm"
static const char strVoltDiv[] = "20mV,50mV,100mV,200mV,500mV,1V,"
				 "2V  ,5V  ,10V  ,20V  ,50V  ,100V";
enum	{vd20mV,vd50mV,vd100mV,vd200mV,vd500mV,vd1V,
		    vd2V  ,vd5V  ,vd10V  ,vd20V  ,vd50V  ,vd100V}	;
enum	{adDC,adGnd,adAC}		; 				 
//---------------------------------------------------------------------------
__fastcall TFrmChnl::TFrmChnl(TComponent* Owner,TWinControl* parent,int ch,TOnChangeChnl _onChnge)
			:TFrame(Owner)
{IX = ch	;
 bOn->Caption = "CH" + String(ch)		;
 cbVoltDiv->Items->CommaText = strVoltDiv	;
 Hint 	= "CH_"+String(ch)  			;
 Name   = "FrmChnl" + String(ch)		;
 Parent = parent				;
 FOnChange = _onChnge				;

 FormStorage1->IniFileName = ChangeFileExt(ParamStr(0),".ini")	;
 FormStorage1->IniSection  = Name	;
 FormStorage1->RestoreFormPlacement()	;

 cbX10    ->Enabled = bOn  ->Checked  	;
 cbVoltDiv->Enabled = bOn  ->Checked  	;
 cbAC_DC  ->Enabled = bOn  ->Checked  	;
}
//---------------------------------------------------------------------------
void __fastcall TFrmChnl::BtnOnClick(TObject *Sender)
{TComboBox* cmbox = dynamic_cast<TComboBox*>(Sender)	;
 TCheckBox* chbox = dynamic_cast<TCheckBox*>(Sender)	;

 if((cmbox && cmbox->Enabled) ||
    (chbox && chbox->Enabled) || Sender == this){

   Prms.IX        = IX				;
   Prms.IxVoltDiv = cbVoltDiv->ItemIndex	;
   Prms.IxAcDc    = cbAC_DC  ->ItemIndex	;
   Prms.XX10   	  = cbX10    ->Checked		;
   Prms.OnOff 	  = bOn      ->Checked  	;

   cbX10    ->Enabled = bOn  ->Checked  	;
   cbVoltDiv->Enabled = bOn  ->Checked  	;
   cbAC_DC  ->Enabled = bOn  ->Checked  	;

   if(FOnChange) FOnChange(this)		;
 }
}
//---------------------------------------------------------------------------

