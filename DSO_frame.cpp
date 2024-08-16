//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include	<RxStrUtils.hpp>
#include "ComWorL.h"
#include "DdsDlg.h"
#include "DSO_frame.h"
#include "DrawOGL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "rxPlacemnt"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
//#include	<Math.h>
#include	<StdIO.h>
#include	<IO.h>
//#include	<JPEG.hpp>
//---------------------------------------------------------------------------

TFrmDSO *FrmDSO = 0	;
//TShape_M* spmLvl[4] = {0,0,0,0}	;
extern double OffsetVaweGL		;
//---------------------------------------------------------------------------
__fastcall TFrmDSO::TFrmDSO(TComponent* Owner,TNotifyEvent _onChnge): TFrame(Owner)
{String		nam			;
 FOnChange = _onChnge			;
 TColor		_color			;
 cbSendChnlParams = 0			;
 cbGetChnlParams = 0			;

 SmplPerDiv = 250			;
 CntGrid_H  = 10	; CntGrid_V = 8	;
 pLeft->Tag = 0x2060A0E0		;// для начального установа Lvl255!!!

 FormStorage1->IniFileName = ChangeFileExt(ParamStr(0),".ini")	;
 FormStorage1->IniSection  = Name     	;
 FormStorage1->RestoreFormPlacement() 	;

// pLeft->OnContextPopup = CntxtPopup		;

 for(int ch=0;ch<4;ch++){
   nam.printf("ShpL%ld",ch+1)		;
   _color = GetChColor(ch)		;
   shpLvl[ch] = new TShapeGL(this,pLeft,nam,_color)	;
   shpLvl[ch]->OnMouseMove  = FMouseMove		;
   shpLvl[ch]->cbSetHardLvl = SetHardLvlChnl		;
   shpLvl[ch]->OnMouseDown  = FrameMouseDown		;
   shpLvl[ch]->OnDblClick   = FDblClick			;

   nam.printf("LblCh%ld",ch+1)		;
   lblCh[ch] = new TLabel(this)		; lblCh[ch]->Name  = nam  	;
   lblCh[ch]->Parent = pBottom		; lblCh[ch]->Tag   = ch+1	;
   lblCh[ch]->Align  = alRight		; lblCh[ch]->Align = alLeft	;
   lblCh[ch]->AutoSize  = false		; lblCh[ch]->Width = 64		;
   lblCh[ch]->Alignment = taCenter 	; 
 }
 shpLvl[TRG_T] = new TShapeGL(this,pTop,"TrgT",clYellow,soHrz,0);//pLeft->Width)	;
 shpLvl[TRG_T]->OnMouseMove  = FMouseMove	;
 shpLvl[TRG_T]->cbSetHardLvl = SetHardLvlChnl	;

 shpLvl[TRG_V] = new TShapeGL(this,pRight,"TrgV",clGray,soVrtM,0)	;
 shpLvl[TRG_V]->OnMouseMove  = FMouseMove	;
 shpLvl[TRG_V]->cbSetHardLvl = SetHardLvlChnl	;
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::Destroy(TObject* Sender){ DestroyGL()	;}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::Init(TObject* Sender,uint32_t _lvlsPos)
{String	_cap				;
 UCHAR	lvl255				;
 UCHAR* LvlCh = (UCHAR*)&(pLeft->Tag) 	;// для сохр. в .ini файле

 try{
 for(int ch=0;ch<4;ch++){
   _cap = String(ch+1)			;
   lvl255 = LvlCh[ch]			;
   shpLvl[ch]->Init(ch,_cap,lvl255) 	;
   m_Hard.SetLvl(ch,lvl255)		;

   lblCh[ch]->Font->Color = GetChColor(ch)	;
 }

 shpLvl[TRG_T]->Init(TRG_T,"T",pTop  ->Tag)  	;
 shpLvl[TRG_V]->Init(TRG_V,"T",pRight->Tag) 	;

 InitializeGL(pView->Handle,pView->Width,pView->Height)	;
 }DEF_CATCH
}
//---------------------------------------------------------------------------
extern const char* strVoltDiv1 	;
extern const char* strVoltDiv10	;
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::SetChnlParams(TChnlParams* params)
{char	str[80]	;

 m_Hard.SetChnlParams(params)	;
 uint8_t ch = params->IX	;
 char	 cpl = params->IxAcDc	; cpl = !cpl ? '-' : cpl == 1 ? '~' : 'G'	;

 String   sns = params->XX10 ? strVoltDiv10 : strVoltDiv1	;
 TCharSet Dlm ; Dlm<<','<<' '	;
 sns = ExtractWord(params->IxVoltDiv+1,sns,Dlm)	;

 if(ch<4){
   sprintf(str,"%d %c %s",ch+1,cpl,sns.c_str())	;
   lblCh[ch]->Caption = str	;

 }
}
//---------------------------------------------------------------------------
USHORT __fastcall TFrmDSO::CollectData(void)
{
 return m_Hard.CollectData()	;
}
//---------------------------------------------------------------------------
//void __fastcall TFrmDSO::DrawShapes(void)
//{DrawShapesGL(shpLvl)		;
//}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::DrawWaves(void)
{
 TParamsDrawWave params	;
 params.nDisType      = 0				;// display type: Line or Dot
 params.nSrcDataLen   = m_Hard.m_stControl.nBufferLen	;// the source data length
 params.nDisDataLen   = m_Hard.m_stControl.nBufferLen	;// the display data length for drawing
 params.nCenterData   = params.nSrcDataLen / 2 		;// half of the source data
 params.dbHorizontal  = 1.0				;// the horizontal factor of zoom out/in
 params.dbVertical    = 1.0				;// the vertical factor of zoom out/in
 params.nYTFormat     = 0				;// Fomat: Normal or Scan
 params.nScanLen      = params.nSrcDataLen		;// the scan data length, only invalidate in scan mode

 params.CntGrid_H     = CntGrid_H			;
 params.CntGrid_V     = CntGrid_V			;
 params.SmplPerDiv    = SmplPerDiv			;

 int SmplPerDspl = CntGrid_H * SmplPerDiv		;// сколько смпл войдёт на экран?
 double     stpX = 2.0 / SmplPerDspl			;
 double	    lenX = stpX * m_Hard.m_stControl.nBufferLen ;// полная длина последовательности
 OffsetVaweGL    = shpLvl[4]->Pos.dPos - lenX*shpLvl[4]->Pos.Lvl100/100	;

 for(int ch=0;ch<MAX_CH_NUM;ch++){    //CH1/CH2/CH3/CH4
   params.clrRGB        = m_Hard.m_clrRGB[ch]		;// the color of the line
   params.pSrcData      = m_Hard.RelayControl.bCHEnable[ch] ?
			  m_Hard.m_pSrcData[ch] : 0	;// the source data for drawing
   params.nDisLeverPos  = m_Hard.m_nLeverPos[ch]	;// the display position(Zero Level)
   DrawWaveGL(ch,&params)				;//
 }
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::OnDraw(TObject *Sender)
{static bool  flGrid = false	;
 int CliWdt = pView->Width	;
 int CliHgt = pView->Height	;

 try{
   if(!flGrid){ flGrid = true			;
     DrawGridGL(CntGrid_H,CntGrid_V,200,1)	;}
   if(m_Hard.m_nDeviceIndex != 0xFF){
     DrawWaves()				;}

   DrawSceneGL(CliWdt,CliHgt,shpLvl)		;

 }DEF_CATCH
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::pViewResize(TObject *Sender)
{
 for(int ch=0;ch<CNT_SHP;ch++)
   shpLvl[ch]->OnResize(pView->Height,pView->Width)	;
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::FMouseMove(TObject *Sender,
			 TShiftState Shift, int X, int Y)
{TShapeGL* shpGL= dynamic_cast<TShapeGL*>(Sender)	;
 TPanel*   pan = shpGL ? dynamic_cast<TPanel*>(shpGL->Parent) : 0	;

 char str[100]	;
 if(Shift.Contains(ssLeft)){
   if(shpGL){
     shpGL->OnMove(X,Y)	    	;// обработка перемещения маркера
				 // из неё через cbSetHardLvl будет
				 // вызов процедуры SetHardLvlChnl
     short iLvl = shpGL->GetLvl();
     sprintf(str,"%3d (%6.2lf)",iLvl,shpGL->Pos.dPos);
     shpGL->Hint = str		;

//     if(shpGL->NCh == 4){	 // TrgT_
//
//     }
//     Application->ProcessMessages()		;
   }
 }
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::SetHardLvlChnl(UCHAR ch,int lvl)
{char str[80]	;
 UCHAR* LvlCh = (UCHAR*)&(pLeft->Tag) 	;// для сохр. в .ini файле
 UCHAR	CurCh = CH1		;

 switch(ch){
 case CH1 : case CH2 :
 case CH3 : case CH4 :
	m_Hard.SetLvl(ch,lvl)	;
	LvlCh[ch] = lvl		;// для сохр. в .ini файле
 break	;

 case TRG_T :
	m_Hard.SetTrgT(CurCh,lvl);// TODO
	pTop->Tag = lvl		;
 break	;

 case TRG_V :
	m_Hard.SetTrgV(CurCh,lvl);// TODO
	pRight->Tag = lvl	;
 break	;
 }
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::PanResize(TObject *Sender)
{
// if(spmLvl[0]){
//   spmLvl[0]->Width = spmLvl[0]->Parent->Width	;
//   spmLvl[0]->Height= 20		;
// }
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::BtnClick(TObject *Sender)
{TSpeedButton* btn = dynamic_cast<TSpeedButton*>(Sender)	;
 int tag = btn ? btn->Tag : 0	;

 switch(tag){
   case 13: if(!DdsDialog) DdsDialog = new TDdsDialog(this)	;
	    if( DdsDialog) DdsDialog->Visible = btn->Down	;
   break	;
 }
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::FrameMouseWheel(TObject *Sender, TShiftState Shift,
      int WheelDelta, TPoint &MousePos, bool &Handled)
{TChnlParams	params	;
 int		iix	;
 static double 	WhlPos = 0	;
 const  double  WhlSns = 1/5.0	;

 WhlPos += WheelDelta > 0 ? -WhlSns: WhlSns	;
 int iWhl = WhlPos	; if(iWhl) WhlPos = 0	;

 for(int ch=0;ch<CNT_SHP && iWhl;ch++){
   if(shpLvl[ch]->ClientRect.Contains(shpLvl[ch]->ScreenToClient(MousePos))){
     if(cbGetChnlParams && cbSendChnlParams && ch<4){
       cbGetChnlParams(shpLvl[ch]->NCh,&params) 	;
       iix = params.IxVoltDiv + iWhl		;
       iix = Min(Max(iix,0),11)			;
       params.IxVoltDiv = iix			;
       cbSendChnlParams(&params)		;
     }
   }
 }
}
//---------------------------------------------------------------------------

void __fastcall TFrmDSO::On1Click(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
//     sprintf(str,"Y=%ld, pos=%6.2lf, lvl255=%ld",
//		Y, shpGL->Pos.dPos,shpGL->Pos.Lvl255)	;
//     OutputDebugString(str)			;
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::FrameMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{TShapeGL* shp = dynamic_cast<TShapeGL*>(Sender)	;
 TPoint	   pnt	;
 if(shp){
   if(Shift.Contains(ssRight)){
     GetCursorPos(&pnt)	;
     pmChnl->Popup(pnt.x,pnt.y)	;
   }
 }
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::FDblClick(TObject *Sender)
{TChnlParams	params	;

 TShapeGL* shp = dynamic_cast<TShapeGL*>(Sender)	;
 if(shp && cbGetChnlParams && cbSendChnlParams){
   cbGetChnlParams(shp->NCh,&params) 	;
   params.OnOff ^= true			;
   cbSendChnlParams(&params)		;
 }
}
//---------------------------------------------------------------------------

