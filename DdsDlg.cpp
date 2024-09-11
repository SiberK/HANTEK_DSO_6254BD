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
enum TWaveType{wtSine,wtRamp,wtSquare,wtTrape,wtDC,wtExp,wtAM,wtStorage,wtGause,wtWhite,wtARB};
//#define WAVE_SINE		0
//#define WAVE_RAMP		1
//#define WAVE_SQUARE		2
//#define WAVE_TRAPE		3
//#define WAVE_DC		4
//#define WAVE_EXP		5
//#define WAVE_AM		6
//#define WAVE_STORAGE		7
//#define WAVE_GAUSE		8
//#define WAVE_WHITE		9
//#define WAVE_ARB		10	//ÓÃ»§×Ô¶¨Òå²¨ÐÎ
//---------------------------------------------------------------------------
void __fastcall	WhMouse(TCurrencyEdit* ed,TPoint &MPos,int Sgn, double mux)
{if(ed && ed->ClientRect.Contains(ed->ScreenToClient(MPos)) && ed->Enabled){
   double Val = ed->Value * mux			;
   double Stp = (Sgn >= 0) ? (Val <   10.0 ?   1.0 :
			      Val <  100.0 ?  10.0 :  100.0) :
			     (Val <=  10.0 ?  -1.0 :
			      Val <= 100.0 ? -10.0 : -100.0) ;
   ed->Value = (Val + Stp)/mux			;}
}
//---------------------------------------------------------------------------
__fastcall TDdsDialog::TDdsDialog(TComponent* Owner): TForm(Owner)
{FormStorage1->IniFileName = ChangeFileExt(ParamStr(0),".ini")	;
 pAMFM->Hide()	; pPhase->Hide()	; pRise->Hide()		;
 Height = 330	;}
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

 bool	isGause = false		;
 WORD	WaveNum			;
 WORD	PeriodNum		;
 float	Phase = ePhase->Value	;
 float  Duty  = eDuty ->Value 	;
 float  Rise  = eRise ->Value	;
 float  High  = eHigh ->Value	;
 float  Fall  = eFall ->Value	;
 double Amp  = eAmpl->Value*1000;// mV
 double	Freq = eFrq->Value * (cbFrq->ItemIndex == 2 ? 1e6 :
			      cbFrq->ItemIndex == 1 ? 1e3 : 1	);
 short	Offset = eOffset->Value * 1000	;// mV
 double AMDepth= eAMDepth->Value	;
 double FMDev  = eFMDev->Value * 1000	;
 double	CWFreq = eCWFrq->Value * (cbCWFrq->ItemIndex == 2 ? 1e6 :
				  cbCWFrq->ItemIndex == 1 ? 1e3 : 1	);
 bool	isFM   = cbFM->Checked		;

 if(Sender == this) cbDdsMode->ItemIndex = ddsOff	;
// ePhase->Enabled = false	;
// eDuty ->Enabled = false	;
// eRise ->Enabled = false	;
// eHigh ->Enabled = false	;
// eFall ->Enabled = false	;
 pAMFM->Hide()	; pRise->Hide()	; pPhase->Hide();

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
	pPhase->Show()	;
	ePhase->Enabled = true			;
	eDuty ->Enabled = true			;
	ddsSetCmd(devIx,0)			;
	ddsSDKSetFre      (devIx,Freq)		;
	ddsSDKSetAmp      (devIx,Amp)		;
	ddsSDKSetOffset   (devIx,Offset)  	;
	ddsSDKSetWaveType (devIx,wtSquare)	;
	ddsSDKSetWaveDuty (devIx,Duty    )	;
	ddsSDKSetWavePhase(devIx,Phase   )	;
	ddsSetOnOff(devIx,1)			; break	;

   case ddsRamp :
	pPhase->Show()	;
	ePhase->Enabled = true			;
	eDuty ->Enabled = true			;
	ddsSetCmd(devIx,0)			;
	ddsSDKSetFre      (devIx,Freq  )	;
	ddsSDKSetAmp      (devIx,Amp   )	;
	ddsSDKSetOffset   (devIx,Offset)  	;
	ddsSDKSetWavePhase(devIx,Phase )	;
	ddsSDKSetWaveType (devIx,wtRamp)	;
	ddsSetOnOff(devIx,1)			; break	;

   case ddsTrapezia:
	pRise ->Show()	;
	pPhase->Show()	;
	ePhase->Enabled = true			;
	eDuty ->Enabled = true			;
	ddsSetCmd(devIx,0)			;
	ddsSDKSetFre      (devIx,Freq  )	;
	ddsSDKSetAmp      (devIx,Amp   )	;
	ddsSDKSetOffset   (devIx,Offset)  	;
	ddsSDKSetWavePhase(devIx,Phase )	;
	ddsSDKSetWaveDuty (devIx,Duty  )	;
	ddsSDKSetWaveType (devIx,wtTrape)	;
	ddsSetOnOff(devIx,1)			; break	;

   case ddsExponent:
	ePhase->Enabled = true			;
//	eDuty ->Enabled = true			;
	ddsSetCmd(devIx,0)			;
	ddsSDKSetFre      (devIx,Freq  )	;
	ddsSDKSetAmp      (devIx,Amp   )	;
	ddsSDKSetOffset   (devIx,Offset)  	;
	ddsSDKSetWavePhase(devIx,Phase )	;
//	ddsSDKSetWaveDuty (devIx,Duty  )	;
	ddsSDKSetWaveType (devIx,wtExp )	;
	ddsSetOnOff(devIx,1)			; break	;

   case ddsGause: isGause = true		;
   case ddsWhite:
	ddsSetCmd(devIx,0)			;
	ddsSDKSetFre      (devIx,Freq)		;
	ddsSDKSetAmp      (devIx,Amp)		;
	ddsSDKSetOffset   (devIx,Offset)  	;
	ddsSDKSetWaveType (devIx,isGause ? wtGause:wtWhite)	;
	ddsSetOnOff(devIx,1)			; break	;

   case ddsAM_FM:
   	pAMFM->Show()	;
	ePhase->Enabled = true			;
	eDuty ->Enabled = true			;
	ddsSetCmd(devIx,0)			;
	ddsSDKSetFre      (devIx,Freq  )	;
	ddsSDKSetAmp      (devIx,Amp   )	;
	ddsSDKSetOffset   (devIx,Offset)  	;
	ddsSetAMFMFreq	  (devIx,Freq  )	;
//	ddsSetFAOC	  (devIx,CWFreq,1000,
//			   0,0,
//			   AMDepth,FMDev)	;
	ddsSetFAOC	  (devIx,1000,1,
			   0,10000,0.5,500)		;

//DLL_API WORD  WINAPI ddsSetFAOC(WORD DeviceIndex, double dFre,WORD nAmpVolt,
//				  SHORT nOffsetVolt,ULONG nPeriodNum,
//				  float fAMDepth,double dbFMMAXOffset);
//DLL_API ULONG WINAPI ddsSetSweep(WORD DeviceIndex, WORD nControl);
//DLL_API ULONG WINAPI ddsSetAMFMFreq(WORD DeviceIndex,double dbFre);
	ddsSDKSetWaveType (devIx,wtAM  )  	;
	ddsSetOnOff(devIx,1)			; break	;

   case ddsArb:
   default : ddsSetOnOff(devIx,0)	; break	;
 }
}
//wtSine,wtRamp,wtSquare,wtTrape,wtDC,wtExp,wtAM,etStorage,wtGause,wtWhite,wtARB
//---------------------------------------------------------------------------
void __fastcall TDdsDialog::FormMouseWheel(TObject *Sender, TShiftState Shift,
      int WheelDelta, TPoint &MousePos, bool &Handled)
{
 if(Visible){
   WhMouse(eFrq   ,MousePos,WheelDelta,1.0 )	;
   WhMouse(eAmpl  ,MousePos,WheelDelta,100.0)	;
   WhMouse(eOffset,MousePos,WheelDelta,10.0)	;
   WhMouse(ePhase ,MousePos,WheelDelta,100.0)	;
   WhMouse(eDuty  ,MousePos,WheelDelta,100.0)	;
   WhMouse(eRise  ,MousePos,WheelDelta,100.0)	;
   WhMouse(eHigh  ,MousePos,WheelDelta,100.0)	;
   WhMouse(eFall  ,MousePos,WheelDelta,100.0)	;
   WhMouse(eCWFrq ,MousePos,WheelDelta,1.0 )	;
   WhMouse(eAMDepth,MousePos,WheelDelta,100.0)	;
   WhMouse(eFMDev ,MousePos,WheelDelta,1.0)	;
 }
}
//---------------------------------------------------------------------------

