//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Chnl_frame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "rxPlacemnt"
#pragma resource "*.dfm"
const char* strVoltDiv1  = "2mV ,5mV  ,10mV ,20mV ,50mV ,0.1V ,"
			   "0.2V,0.5V ,1V   ,2V   ,5V   ,10V   ";
const char* strVoltDiv10 = "20mV,50mV ,0.1V ,0.2V ,0.5V ,1V   ,"
			   "2V  ,5V   ,10V  ,20V  ,50V  ,100V  ";
enum	{vd20mV,vd50mV,vd100mV,vd200mV,vd500mV,vd1V,
		    vd2V  ,vd5V  ,vd10V  ,vd20V  ,vd50V  ,vd100V}	;
enum	{adDC,adGnd,adAC}		;
//---------------------------------------------------------------------------
__fastcall TFrmChnl::TFrmChnl(TComponent* Owner,TWinControl* parent,
		int ch,TNotifyEvent _onChnge) : TFrame(Owner)
{IX = ch	;
 bOn->Caption = "CH"+ String(ch+1)		;
 Hint 	= "CH_"     + String(ch+1) 		;
 Name   = "FrmChnl" + String(ch)		;
 Parent = parent				;
 FOnChange = _onChnge				;

 cbX10->Checked = true				;
 bOn  ->Checked = false 			;
 cbVoltDiv->Items->CommaText = cbX10->Checked ? strVoltDiv10 : strVoltDiv1	;
 cbVoltDiv->ItemIndex = 5			;
 cbAC_DC  ->ItemIndex = 0			;

 FormStorage1->IniFileName = ChangeFileExt(ParamStr(0),".ini")	;
 FormStorage1->IniSection  = Name		;
 FormStorage1->RestoreFormPlacement()		;

 cbX10    ->Enabled = bOn->Checked  		;
 cbVoltDiv->Enabled = bOn->Checked  		;
 cbAC_DC  ->Enabled = bOn->Checked  		;
}
//---------------------------------------------------------------------------
void __fastcall TFrmChnl::FormStorage1RestorePlacement(TObject *Sender){ BtnOnClick(this)	;}
//---------------------------------------------------------------------------
void __fastcall TFrmChnl::BtnOnClick(TObject *Sender)
{TComboBox* cmbox = dynamic_cast<TComboBox*>(Sender)	;
 TCheckBox* chbox = dynamic_cast<TCheckBox*>(Sender)	;

 if(Sender == cbX10 || Sender == this){
   int ix = cbVoltDiv->ItemIndex		;
   cbVoltDiv->Items->CommaText = cbX10->Checked ? strVoltDiv10 : strVoltDiv1	;
   cbVoltDiv->ItemIndex	= ix			;
 }

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

   Hint = "ixVD = " + String(cbVoltDiv->ItemIndex)	;
 }
}
//---------------------------------------------------------------------------
TChnlParams* __fastcall TFrmChnl::GetParams(void)
{
 Prms.IX        = IX			;
 Prms.IxVoltDiv = cbVoltDiv->ItemIndex	;
 Prms.IxAcDc    = cbAC_DC  ->ItemIndex	;
 Prms.XX10   	= cbX10    ->Checked	;
 Prms.OnOff 	= bOn      ->Checked  	;
 return &Prms	;}
//---------------------------------------------------------------------------
void __fastcall TFrmChnl::SetParams(TChnlParams* prms)
{
 cbX10->Checked       = prms->XX10	;
 bOn  ->Checked	      = prms->OnOff	;
 cbVoltDiv->ItemIndex = prms->IxVoltDiv	;
 cbAC_DC  ->ItemIndex = prms->IxAcDc	;
 BtnOnClick(this)	;
}
//---------------------------------------------------------------------------

