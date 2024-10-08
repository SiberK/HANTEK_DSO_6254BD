﻿//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <RxVerInf.hpp>
#include <RxStrUtils.hpp>
#include "Main.h"

#include "ComWorL.h"
#include "DdsDlg.h"
#include "DSO_frame.h"	// ЭТО (#include "Hard.h") ДОЛЖНО БЫТЬ НИЖЕ ВСЕХ rx*.h !!!!!
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "rxPlacemnt"
#pragma link "rxCurrEdit"
#pragma link "rxToolEdit"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
static const char strTimeDiv[] = "2nS,5nS,10nS,20nS,50nS,100nS,200nS,500nS,1uS,"
				 "2uS,5uS,10uS,20uS,50uS,100uS,200uS,500uS,1mS,"
				 "2mS,5mS,10mS,20mS,50mS,100mS,200mS,500mS,1S,"
				 "2S ,5S ,10S ,20S ,50S ,100S ,200S ,500S ,1000S";

static const char strSmplDiv[] = "50 ,100,200";
static const char strSmplRat[] = "1G/sec   ,0.5G/sec,250M/sec ,"
				 "125M/sec ,50M/sec ,25M/sec  ,"
				 "12.5M/sec,5M/sec  ,2.5M/sec ,"
				 "1.25M/sec,0.5M/sec,250K/sec ,"
				 "125K/sec ,50K/sec ,25K/sec  ,"
				 "12.5K/sec,5K/sec  ,2.5K/sec ,"
				 "1.25K/sec,0.5K/sec,250/sec  ,"
				 "125/sec  ,50/sec  ,25/sec   ,"
				 "12.5/sec ,5/sec   ,2.5/sec  ,"
				 "1.25/sec ,0.5/sec ,0.25/sec "  ;
//---------------------------------------------------------------------------
static int FL_CHECK_RUN = 0	;
//---------------------------------------------------------------------------
static int CheckRepeatRun()
{HANDLE hMutex = CreateMutex( NULL, true, "ScopeMutex" );
 int rzlt = 0	;
 if( GetLastError() == ERROR_ALREADY_EXISTS ){
   rzlt = 1	;
   ShowMessage( "Запускаете программу 2-ой раз !!!" );
   CloseHandle( hMutex )			;
   Application->Terminate()			;}

 return rzlt	;}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner): TForm(Owner)
{FL_CHECK_RUN = CheckRepeatRun()		;
 if(FL_CHECK_RUN) return			;
 
 FormStorage1->IniFileName   = ChangeFileExt(ParamStr(0),".ini")	;
 cbTimeDiv->Items->CommaText = strTimeDiv	;
 cbTimeDiv->ItemIndex        = 17		;
 cbSmplDiv->Items->CommaText = strSmplDiv	;
 cbSmplDiv->ItemIndex        = 1		;
// pDSO->Tag = 0x2060A0E0	;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{Exception* E = new Exception("Start "+StrVersion)	;
 LogException(__FILE__,__LINE__,*E) 	; delete E	;}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormStorage1RestorePlacement(TObject *Sender)
{
 if(FL_CHECK_RUN) return		;

 try{
 FrmDSO = new TFrmDSO(this,ChnlOnChange);
 FrmDSO->Parent = pDSO			;
 FrmDSO->Align  = alClient		;

 FrmDSO->Init(this,pDSO->Tag)		;// здесь инит LvlsPos!!!

 for(int ch=0;ch<4;ch++){
   ChnlFrm[ch] = new TFrmChnl(this,gbChnl,ch,ChnlOnChange);
   ChnlFrm[ch]->Align  = alBottom	;
   ChnlFrm[ch]->Align  = alTop		;}

 FrmDSO->cbGetChnlParams = GetChnlParams	;
 FrmDSO->cbSendChnlParams= SendChnlParams	;
 FrmDSO->cbChngTimDiv    = ChngTimDiv		;

 TimeDivChange(cbTimeDiv)		;
 timRefTimer(this)	;
 }DEF_CATCH
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{try{
//   DDS_Change(this)		;
   if(FrmDSO) FrmDSO->Destroy(this)	;
 } DEF_CATCH
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
 if(FrmDSO) FrmDSO->SaveProps()			;
 for(int ch=0;ch<4;ch++)
    if(ChnlFrm[ch]) ChnlFrm[ch]->SaveProps()	;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimeDivChange(TObject *Sender)
{TComboBox* cmbox = dynamic_cast<TComboBox*>(Sender)	;
 TCheckBox* chbox = dynamic_cast<TCheckBox*>(Sender)	;
 int	tag = cmbox ? cmbox->Tag : chbox ? chbox->Tag : 0	;
 String	Str, strPp			;

 if(!tag || !FrmDSO) return		;

 size_t ixTB  = cbTimeDiv->ItemIndex 	;
 if(ixTB >= SIZE_TBL_TIM_DIV) ixTB = 17	;

 TTimeParams	timPrms	;
 timPrms.nTrigSource = cbSrcTrg->ItemIndex		;
 timPrms.nTimeDiv    = ixTB				;
// timPrms.TimeBase    = tblTimDiv[ixTB]			;
 timPrms.nHTriggerPos	;
 timPrms.nHTriggerPos	;
 timPrms.nVTriggerPos	;
 timPrms.nTriggerSlope	;

 switch(tag){
   case 121 :	// cbTimeDiv
   case 122 :	// cbSmplDiv
	FrmDSO->SetTimeDiv(&timPrms,cbTimeDiv->Text)	;
	DisplaySampleRate()      			;
   break	;

   case 131 :	// Trg_Src
   break	;
   case 132 :	// Trg_Edge
   break	;
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DisplaySampleRate()
{
 String	Str						;
 String	smplRate = FrmDSO->GetSmplRate()		;
 String timDiv   = FrmDSO->GetTimDiv()			;
 String timClct  = FrmDSO->GetTimClct()			;
 String smplPerDiv=FrmDSO->GetSmplPerDiv()		;
 size_t cntSmpls = FrmDSO->CountSamples()		;
 char	chCHMode = FrmDSO->GetCHMode()			;
	chCHMode = chCHMode == 4 ? 'Q' : chCHMode == 2 ? 'D' : 'S'	;
// smplRate != 0 ? cntSmpls / smplRate : 0	;
// String	smplPerDiv = smplRate * timeBase		;// отсчётов на 1 деление
// double	srm = smplRate/(smplRate > 250.0e6 ? 1.0e9 :
//			smplRate > 250.0e3 ? 1.0e6 :
//			smplRate > 250.0   ? 1.0e3 : 1.0);
// String strPp = smplRate > 250.0e6 ? "GSa" :
//		smplRate > 250.0e3 ? "MSa" :
//		smplRate > 250.0   ? "KSa" : "Sa"	;
// String strSrm = FormatFloat("0.##",srm)		;
//
// Str.printf("%s %s (%3.0lf Sa/Div) %ld (%s)",
//		strSrm,strPp.c_str(), smplPerDiv,
//		cntSmpls, IntervalToStr(timCollect))	;
 Str.printf("%s (%s) %ld (%s)%c",
	    smplRate,smplPerDiv, cntSmpls, timClct,chCHMode)	;
 StatMsg[2] = Str	;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChnlOnChange(TObject *Sender)
{TFrmChnl* Chnl = dynamic_cast<TFrmChnl*>(Sender)	;
 TFrmDSO * Dso  = dynamic_cast<TFrmDSO* >(Sender)	;

 if(Chnl){
   FrmDSO->SetChnlParams(Chnl->GetParams())		;
 }
// if(Dso){
//   pDSO->Tag = Dso->Tag		;// здесь инит LvlsPos!!!
// }
 DisplaySampleRate()		;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::timRefTimer(TObject *Sender)
{uint8_t 	rzlt = 0 	;
 timRef->Enabled = false	;
 if(!FrmDSO) return		;

 if(!bPause->Down) rzlt = FrmDSO->CollectData()	;

 if(rzlt == 0xFF){
   Application->MessageBox("No suitble device was found!","!!!",MB_OK);
 }
 else{
   FrmDSO->OnDraw(Sender)  	;
   timRef->Enabled = true  	;}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::eTimRefChange(TObject *Sender)
{timRef->Enabled  = false		;
 timRef->Interval = eTimRef->Value	;
 timRef->Enabled  = true		;}
//---------------------------------------------------------------------------
void __fastcall TForm1::PanDblClick(TObject *Sender)
{if(pTool->Visible){ pTool->Hide()	; panSwtch->Caption = ">"	;}
 else{               pTool->Show() 	; panSwtch->Caption = "<"	;}}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChngTimDiv(int chng)
{int ix = cbTimeDiv->ItemIndex + chng		;
 cbTimeDiv->ItemIndex = Min(Max(ix,0),cbTimeDiv->Items->Count-1)	;
 TimeDivChange(cbTimeDiv)		;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SendChnlParams(TChnlParams* params)
{uint8_t ch = params->IX		;
 if(ch<4) ChnlFrm[ch]->SetParams(params);}
//---------------------------------------------------------------------------
void __fastcall TForm1::GetChnlParams(uint8_t ch,TChnlParams* params)
{*params = *ChnlFrm[ch]->GetParams()	;}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseWheel(TObject *Sender, TShiftState Shift,
      int WheelDelta, TPoint &MousePos, bool &Handled)
{//if(Shift.Contains(ssCtrl))
   FrmDSO->FMouseWheel(Sender,Shift,WheelDelta,MousePos,Handled)	;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FBtnClick(TObject *Sender)
{
 TSpeedButton* btn = dynamic_cast<TSpeedButton*>(Sender)	;
 int tag = btn ? btn->Tag : 0	;

 switch(tag){
   case 101 : timRefTimer(this)	; break	;// bPause
   case 102 : if(FrmDSO) FrmDSO->flDbg1 = btn->Down	; break	;// bDbg1
   case 103 : if(FrmDSO) FrmDSO->flDbg2 = btn->Down	; break	;// bDbg2
   case 104 : if(FrmDSO) FrmDSO->flDbg3 = btn->Down	; break	;// bDbg3
   case 105 : if(FrmDSO) FrmDSO->flDbg4 = btn->Down	; break	;// bDbg4   
 }
}
//---------------------------------------------------------------------------

