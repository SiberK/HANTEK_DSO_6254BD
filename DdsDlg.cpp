//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DdsDlg.h"
//---------------------------------------------------------------------------
#include "DSO_frame.h"	// ÝÒÎ (#include "Hard.h") ÄÎËÆÍÎ ÁÛÒÜ ÍÈÆÅ ÂÑÅÕ rx*.h !!!!!
#include "ComWorL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "rxCurrEdit"
#pragma link "rxPlacemnt"
#pragma link "rxToolEdit"
#pragma resource "*.dfm"
TDdsDialog *DdsDialog;
//---------------------------------------------------------------------------
enum TModeDDS{ddsOff ,ddsSine,ddsSquare,ddsRamp,ddsTrapezia,
	      ddsArb ,ddsExponent,ddsAM_FM,ddsGause,ddsWhite};
enum TWaveType{wtSine,wtRamp,wtSquare,wtDC=4,wtNoise=8};
//---------------------------------------------------------------------------
void __fastcall	WhMouse(TCurrencyEdit* ed,TPoint &MPos,int Sgn, double mux)
{if(ed && ed->ClientRect.Contains(ed->ScreenToClient(MPos))){
   double Val = ed->Value * mux			;
   double Stp = (Sgn >= 0) ? (Val <   10.0 ?   1.0 :
			      Val <  100.0 ?  10.0 :  100.0) :
			     (Val <=  10.0 ?  -1.0 :
			      Val <= 100.0 ? -10.0 : -100.0) ;
   ed->Value = (Val + Stp)/mux			;}
}
//---------------------------------------------------------------------------
__fastcall TDdsDialog::TDdsDialog(TComponent* Owner): TForm(Owner)
{FormStorage1->IniFileName = ChangeFileExt(ParamStr(0),".ini")	;}
//---------------------------------------------------------------------------
void __fastcall TDdsDialog::FormStorage1RestorePlacement(TObject *Sender)
{DdsChange(this) ;}
//---------------------------------------------------------------------------
void __fastcall TDdsDialog::FormDestroy(TObject *Sender)
{DdsChange(this) ;}
//---------------------------------------------------------------------------
void __fastcall TDdsDialog::DdsChange(TObject *Sender)
{WORD 	devIx = FrmDSO ? FrmDSO->GetDevIx() : 0xFF	;
 if(devIx == 0xFF) return	;

 WORD	WaveNum			;
 WORD	PeriodNum		;
 float	Phase, Duty		;

 double Amp  = eAmpl->Value*1000;// mV
 double	Freq = eFrq->Value * (cbFrq->ItemIndex == 2 ? 1e6 :
			      cbFrq->ItemIndex == 1 ? 1e3 : 1	);
 short	Offset = eOffset->Value * 1000	;// mV
 if(Sender == this) cbDdsMode->ItemIndex = ddsOff	;

 int mode = cbDdsMode->ItemIndex		;
 switch(mode){
   case ddsSine:
	ddsSetCmd(devIx,0)			;
	ddsSDKSetFre(devIx,Freq)		;
	ddsSDKSetAmp(devIx, Amp)		;
	ddsSDKSetOffset(devIx, Offset)		;
	ddsSDKSetWaveType(devIx,wtSine)		;
	ddsSetOnOff(devIx,1)			; break	;
   case ddsSquare:
	ddsSetCmd(devIx,0)			;
	ddsSDKSetFre(devIx,Freq)		;
	ddsSDKSetAmp(devIx, Amp)		;
	ddsSDKSetOffset(devIx, Offset)		;
	ddsSDKSetWaveType(devIx,wtSquare)	;
	ddsSetOnOff(devIx,1)			; break	;

   default : ddsSetOnOff(devIx,0)	; break	;
 }
}
//---------------------------------------------------------------------------
void __fastcall TDdsDialog::FormMouseWheel(TObject *Sender, TShiftState Shift,
      int WheelDelta, TPoint &MousePos, bool &Handled)
{
 if(Visible){
   WhMouse(eFrq   ,MousePos,WheelDelta,1.0 )	;
   WhMouse(eAmpl  ,MousePos,WheelDelta,100.0)	;
   WhMouse(eOffset,MousePos,WheelDelta,10.0)	;}
}
//---------------------------------------------------------------------------


