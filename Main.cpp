//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include	<RxVerInf.hpp>
#include	<RxStrUtils.hpp>
#include "Main.h"
#include "DSO_frame.h"
#include "Chnl_frame.h"
#include "ComWorL.h"
#include "Hard.h"
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
static TFrmChnl*	ChnlFrm[4]		;				 
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner): TForm(Owner)
{FormStorage1->IniFileName = ChangeFileExt(ParamStr(0),".ini")	;
 cbTimeDiv->Items->CommaText = strTimeDiv	;
 cbSmplDiv->Items->CommaText = strSmplDiv	;}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{Exception* E = new Exception("Start "+StrVersion)	;
 LogException(__FILE__,__LINE__,*E) 	; delete E	;}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormStorage1RestorePlacement(TObject *Sender)
{
 try{
 FrmDSO = new TFrmDSO(this)	;
 FrmDSO->Parent = pDSO		;
 FrmDSO->Align  = alClient	;

 FrmDSO->Init(this)		;
 pcTool->ActivePage = tsDSO	;

 for(int ch=0;ch<4;ch++){
   ChnlFrm[ch] = new TFrmChnl(this,gbChnl,ch,ChnlOnChange);
   ChnlFrm[ch]->Align  = alBottom	;
   ChnlFrm[ch]->Align  = alTop		;
 }
 }DEF_CATCH
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{try{
   DDS_Change(this)		;
   FrmDSO->Destroy(this)	;
 } DEF_CATCH
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  for(int ch=0;ch<4;ch++) ChnlFrm[ch]->SaveProps()	;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::ChnlOnChange(TObject *Sender)
{TFrmChnl* Chnl = dynamic_cast<TFrmChnl*>(Sender)	;

 if(Chnl){
   FrmDSO->SetChnlParams(Chnl->GetParams())	;
 }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::timRefTimer(TObject *Sender)
{timRef->Enabled = false	;

 if(0xFF == FrmDSO->CollectData()){
   Application->MessageBox("No suitble device was found!","!!!",MB_OK);
 }
 else{
   FrmDSO->OnDraw(Sender)  	;
   timRef->Enabled = true  	;}
}
//---------------------------------------------------------------------------
enum TModeDDS{ddsOff ,ddsSine,ddsSquare,ddsRamp,ddsTrapezia,
	      ddsArb ,ddsExponent,ddsAM_FM,ddsGause,ddsWhite};
enum TWaveType{wtSine,wtRamp,wtSquare,wtDC=4,wtNoise=8};
//---------------------------------------------------------------------------
void __fastcall TForm1::DDS_Change(TObject *Sender)
{WORD 	devIx = FrmDSO ? FrmDSO->GetDevIx() : 0xFF	;
 if(devIx == 0xFF) return		;

 WORD	WaveNum		;
 WORD	PeriodNum	;
 float	Phase, Duty	;

 double Amp  = eAmpl->Value*1000      	;// mV
 double	Freq = eFrq->Value * (cbFrq->ItemIndex == 2 ? 1e6 :
			      cbFrq->ItemIndex == 1 ? 1e3 : 1	);
 short	Offset = eOffset->Value * 1000	;// mV

 int mode = Sender == this ? ddsOff : cbDdsMode->ItemIndex	;
 switch(mode){
   case ddsSine: ddsSetCmd(devIx,0)	;
	ddsSDKSetFre(devIx,Freq)	;
	ddsSDKSetAmp(devIx, Amp)	;
	ddsSDKSetOffset(devIx, Offset)	;
	ddsSDKSetWaveType(devIx,wtSine)	;
	ddsSetOnOff(devIx,1)		; break	;

   default : ddsSetOnOff(devIx,0)	; break	;
 }
}
//---------------------------------------------------------------------------
static void __fastcall	WhMouse(TCurrencyEdit* ed,TPoint &MPos,int Sgn, double mux)
{if(ed && ed->ClientRect.Contains(ed->ScreenToClient(MPos))){
   double Val = ed->Value * mux			;
   double Stp = Val <= 10.0 ? 1.0 : Val <= 100.0 ? 10.0 : 100.0	;
   if(Sgn < 0) Stp = -Stp			;
   ed->Value = (Val + Stp)/mux			;}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseWheel(TObject *Sender, TShiftState Shift,
      int WheelDelta, TPoint &MousePos, bool &Handled)
{if(pcTool->Visible){
   if(pcTool->ActivePage == tsDDS){
     WhMouse(eFrq   ,MousePos,WheelDelta,1.0 )	;
     WhMouse(eAmpl  ,MousePos,WheelDelta,100.0)	;
     WhMouse(eOffset,MousePos,WheelDelta,10.0)	;}
 }
}
//---------------------------------------------------------------------------




