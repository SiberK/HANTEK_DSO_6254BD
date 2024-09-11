//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <RxStrUtils.hpp>
#include	<Math.hpp>
#include "Main.h"
#include "DrawOGL.h"
#include "ComWorL.h"
#include "DSO_frame.h"
#include "DdsDlg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma link "rxPlacemnt"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
//#include	<Math.h>
#include	<StdIO.h>
#include	<IO.h>
//#include	<JPEG.hpp>
//---------------------------------------------------------------------------
TFrmDSO *FrmDSO = 0	;
//TShape_M* spmLvl[4] = {0,0,0,0}	;
//extern double OffsetVaweGL		;
static 	TParamsDrawWave PrmsDW		;
static char* strHint1="Колёсиком мыши\n выбрать чувствительность\n канала по Y"	;
static char* strHint2="Колёсиком мыши\n выбрать развертку"	;

const TColor COLOR_V_CURSOR = clBlue	;
//---------------------------------------------------------------------------
__fastcall TFrmDSO::TFrmDSO(TComponent* Owner,TNotifyEvent _onChnge): TFrame(Owner)
{String		nam			;
 FOnChange = _onChnge			;
 TColor		_color			;
 cbSendChnlParams = 0			;
 cbGetChnlParams  = 0			;
 cbSendTimParams  = 0			;
 cbGetTimParams   = 0			;
 flDbg1 = flDbg2 = flDbg3 = flDbg4 = 0	;

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
   shpLvl[ch]->OnMouseDown  = FMouseDown		;
   shpLvl[ch]->OnDblClick   = FDblClick			;
   shpLvl[ch]->Hint = strHint1		;

   nam.printf("LblCh%ld",ch+1)		;
   lblCh[ch] = new TLabel(this)		; lblCh[ch]->Name  = nam  	;
   lblCh[ch]->Parent = pBottom		; lblCh[ch]->Tag   = ch+1	;
   lblCh[ch]->Align  = alRight		; lblCh[ch]->Align = alLeft	;
   lblCh[ch]->AutoSize  = false		; lblCh[ch]->Width = 64		;
   lblCh[ch]->Alignment = taCenter 	; lblCh[ch]->Hint  = strHint1	;
 }
 shpLvl[TRG_T] = new TShapeGL(this,pTop,"TrgT",clMaroon,soHrz,0);//pLeft->Width)	;
 shpLvl[TRG_T]->OnMouseMove  = FMouseMove	;
 shpLvl[TRG_T]->cbSetHardLvl = SetHardLvlChnl	;

 shpLvl[TRG_V] = new TShapeGL(this,pRight,"TrgV",clGray,soVrtM,0)	;
 shpLvl[TRG_V]->OnMouseMove  = FMouseMove	;
 shpLvl[TRG_V]->cbSetHardLvl = SetHardLvlChnl	;
 shpLvl[TRG_V]->OnMouseDown  = FMouseDown	;
 lblTrgT->Caption = ""				;
 lblTimDiv->Hint  = strHint2			;

 for(int ch=0;ch<4;ch++){
    nam.printf("LblDbg%ld",ch+1)		;
   lblDbg[ch] = new TLabel(this)	; lblDbg[ch]->Name  = nam  	;
   lblDbg[ch]->Parent = pBottom		; lblDbg[ch]->Caption = ""	;
   lblDbg[ch]->Align  = alRight		; lblDbg[ch]->Align = alLeft	;
   lblDbg[ch]->Alignment = taCenter 	; lblDbg[ch]->Hint  = strHint1	;
   lblDbg[ch]->Font->Size = 8		;
//   lblDbg[ch]->Font->Style >> fsBold	;
 }

 double _pos[] = {-0.8,-0.4,0.4,0.8,-0.5,0.5}	;
 for(int ix=0;ix<CNT_CUR;ix++){
   nam.printf("CursorDSO%ld",ix+1)		;
   _color = COLOR_V_CURSOR			;
   CursorDSO[ix] = new TDsoCursor(this,nam,_pos[ix],ix<4 ? coVrt : coHrz,_color);
 }
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
 m_Hard.FindeDev()			;

 shpLvl[TRG_T]->Init(TRG_T,"T",pTop  ->Tag)  	;
 shpLvl[TRG_V]->Init(TRG_V,"T",pRight->Tag) 	;

 InitializeGL(pView->Handle,pView->Width,pView->Height,Color)	;
 }DEF_CATCH

 try{
   m_Hard.SetTriggerMode (miMode  ->Tag)	;
   m_Hard.SetTriggerSweep(miSweep ->Tag)	;
   m_Hard.SetTriggerSrc  (miSource->Tag)	;
   m_Hard.SetTriggerSlope(miSlope ->Tag)	;
   CalcDrawWaves()	;
 }DEF_CATCH

 CalcDrawWaves()				;
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
 CalcDrawWaves()		;
 GetCursorInfo()		;
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
        sprintf(str,"%d%%",lvl)	;
//	lblTrgT->Caption = lvl	;
	shpLvl[TRG_T]->Hint = str	;
	CalcDrawWaves()		;
 break	;

 case TRG_V :
	m_Hard.SetTrgV(CurCh,lvl);// TODO
	pRight->Tag = lvl	;
 break	;
 }
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::CalcDrawWaves(void)
{char	str[80]	;
 double	Tprc = shpLvl[TRG_T]->Pos.Lvl100/100.0		;// 0.0 ... 1.0  % положение T относительно полной длины последовательности
 SmplPerDiv  = m_Hard.SmplPerDiv()			;
 int IX_LEN  = m_Hard.m_nCHMod == 1 ? 4 : m_Hard.m_nCHMod == 2 ? 2 : 1	;

 PrmsDW.nDisType      = 0				;// display type: Line or Dot
 PrmsDW.nSrcDataLen   = m_Hard.m_stControl.nBufferLen	;// the source data length

 // PrmsDW.nDisDataLen   = m_Hard.m_stControl.nBufferLen	;// the display data length for drawing
 PrmsDW.nCenterData   = PrmsDW.nSrcDataLen / 2 		;// half of the source data
 PrmsDW.dbHorizontal  = bStretch->Down ?
				1.0 / TIME_STRETH : 1.0	;// the horizontal factor of zoom out/in
 PrmsDW.dbVertical    = 1.0				;// the vertical factor of zoom out/in
 PrmsDW.nYTFormat     = 0				;// Fomat: Normal or Scan
 PrmsDW.nScanLen      = PrmsDW.nSrcDataLen		;// the scan data length, only invalidate in scan mode

 PrmsDW.CntGrid_H     = CntGrid_H			;
 PrmsDW.CntGrid_V     = CntGrid_V			;
 PrmsDW.SmplPerDiv    = SmplPerDiv			;// отсчётов на деление  с учётом растяжки(масштаба)
 // the display data length for drawing
 PrmsDW.nDisDataLen   = PrmsDW.SmplPerDiv * CntGrid_H 	;// сколько отсчётов войдёт на экран? с учётом растяжки(масштаба)
 PrmsDW.StpOGL	      = 2.0/PrmsDW.nDisDataLen		;// шаг отображения отсчётов в OGL (-1.0 .. 1.0)

// длительность набираемой последовательности отсчётов (мСек)
 PrmsDW.dLenWave      = PrmsDW.nSrcDataLen * PrmsDW.StpOGL*IX_LEN		;
// кол-во массивов в которых размазаны данные выборки одного канала
 PrmsDW.CHMode = m_Hard.m_nCHMod			;// в одноканальном режиме - в 4-х массивах!!!
							 // в двухканальном - в двух массивах,

// !!! (SC_OGL) - система координат контекста OGL !!! (причём видимая часть контекста -1.0 ... 1.0)!!!
 if(!bFixTrgT->Down){
   PrmsDW.Offset_H = Tprc*(2.0-PrmsDW.StpOGL*PrmsDW.nSrcDataLen*IX_LEN) -1.0	;}
 else{
   int    iMin = 0, iMax = pTop->Width - shpView->Width		;
   int    iPos = shpView->Left					;
   double dMin = -1.0,dPos, dMax = 1.0 - PrmsDW.dLenWave	;

   dPos = flDbg3 ? dMapDbg(iMin,iMax,iPos,dMin,dMax) :
		   dMapDbg(iMin,iMax,iPos,dMin,dMax)		;
   PrmsDW.Offset_H = dPos					;
// рассчёт положения отметки TrgT
   dPos = PrmsDW.Offset_H + Tprc * PrmsDW.dLenWave		;

   shpLvl[TRG_T]->Pos.SetPos(dPos,bFixTrgT->Down)		;
   shpLvl[TRG_T]->OnResize(pView->Height,pView->Width,bFixTrgT->Down)		;

   sprintf(str,"ipos=%ld,ofst=%6.3lf,tpos=%6.3lf",iPos,PrmsDW.Offset_H,dPos);
   pTop->Hint = str	;
 }
 double timDiv = m_Hard.GetTimDiv()	;
 double vltDiv = m_Hard.GetVltDiv()	;
 TDsoCursor::CalcScale(CntGrid_H,CntGrid_V,timDiv,vltDiv)	;
 ShowShpView(bFixTrgT->Down) 		;
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::ShowShpView(bool Fix_TrgT)	// показать область видимости
{
 int IX_LEN  = m_Hard.m_nCHMod == 1 ? 4 : m_Hard.m_nCHMod == 2 ? 2 : 1	;
 if(PrmsDW.dLenWave > 1.0 && PrmsDW.nSrcDataLen > 0){
   double scale1 = double(PrmsDW.nDisDataLen) / (PrmsDW.nSrcDataLen * IX_LEN)	;
   double scale2 = (-1.0 - PrmsDW.Offset_H)/2.0	;
   shpView->Width = pTop->Width * scale1+0.5	;
   if(!Fix_TrgT)
     shpView->Left  = shpView->Width * scale2	;
 }
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::DrawWaves(void)
{bool	ChEnbl			;
 int 	wch = 0, cntCh = 1	;
 PrmsDW.pSrcData[0] = m_Hard.m_pSrcData[0] 		;
 PrmsDW.pSrcData[1] = m_Hard.m_pSrcData[1] 		;
 PrmsDW.pSrcData[2] = m_Hard.m_pSrcData[2] 		;
 PrmsDW.pSrcData[3] = m_Hard.m_pSrcData[3] 		;
 PrmsDW.flDbg1      = m_Hard.flDbg1 = flDbg1   		;
 PrmsDW.flDbg2      = m_Hard.flDbg2 = flDbg2   		;
 PrmsDW.flDbg3      = m_Hard.flDbg3 = flDbg3   		;
 PrmsDW.flDbg4      = m_Hard.flDbg4 = flDbg4   		;

// кол-во массивов в которых размазаны данные выборки одного канала
 PrmsDW.CHMode = m_Hard.m_nCHMod			;// в одноканальном режиме - в 4-х массивах!!!
							 // в двухканальном - в двух массивах,

 for(int ch=0;ch<MAX_CH_NUM && wch<MAX_CH_NUM;ch++){    //CH1/CH2/CH3/CH4
   PrmsDW.ChEnbl = m_Hard.RelayControl.bCHEnable[ch]   	;
   PrmsDW.nCh           = ch				;
   PrmsDW.nDisLeverPos  = m_Hard.m_nLeverPos[ch]	;// the display position(Zero Level)
   PrmsDW.clrRGB        = m_Hard.m_clrRGB[ch]		;// the color of the line
   if(!PrmsDW.ChEnbl) continue				;

// в режиме nTimeDiv < 8 ( SamplingRate > 0.5GSa), когда работ. каналов = 2
// выборки в pSrcData 0 и 2 !!!!
//   if(PrmsDW.CntArr == 4)     { PrmsDW.IxArr = 0 	;// 1 канал 1GHz
//				wch = 4			;}// это чтоб вышли из цикла for
//   else if(PrmsDW.CntArr == 2){ PrmsDW.IxArr = wch	; // 2 канала 0.5GHz
//				wch+=2			;}
//   else{                        PrmsDW.IxArr = ch	;}// обычный режим
//
   if(PrmsDW.CHMode == 1){ PrmsDW.IxArr = 0	; wch = 0	;}
   if(PrmsDW.CHMode == 2){ PrmsDW.IxArr = wch	; wch += 2	;}
   if(PrmsDW.CHMode == 4){ PrmsDW.IxArr = ch	; wch = ch	;}
//   DrawWaveGL(&PrmsDW)
   if(PrmsDW.CHMode <= 2 && flDbg1) DrawWaveGL_D(&PrmsDW)	;
   else DrawWaveGL_M(&PrmsDW)	;//
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
     DrawWaves()	 			;}

   DrawCursorsGL(CursorDSO,CNT_CUR)	;
   DrawShapesGL (shpLvl ,CNT_SHP)	;
   DrawSceneGL  (CliWdt ,CliHgt, btn4->Down )	;
 }DEF_CATCH
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::FResize(TObject *Sender)
{
 for(int ch=0;ch<CNT_SHP;ch++)
   shpLvl[ch]->OnResize(pView->Height,pView->Width)	;
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::SetTimeDiv(TTimeParams* timPrms, String StrTimDiv)
{bool chk = m_Hard.SetTimeDiv(timPrms)			;
 if(bStretch->Down && !chk) bStretch->Down = false	;
 
 CalcDrawWaves()		;
 GetCursorInfo()      		;
 lblTimDiv->Caption = StrTimDiv	;}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::FMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{TShapeGL* shp = dynamic_cast<TShapeGL*>(Sender)	;
 TScrollBox* box = dynamic_cast<TScrollBox*>(Sender)	;
 TPoint	   pnt	;

 if(shp){
   if(shp->NCh == TRG_V){
     if(Shift.Contains(ssRight)){
       GetCursorPos(&pnt)			;
       popTrgV->Popup(pnt.x,pnt.y)		;}
   }
 }
 else if(box){
     double    _posX = dMap(0,box->Width ,X,-1.0, 1.0)	;
     double    _posY = dMap(0,box->Height,Y, 1.0,-1.0)	;

     for(int ic=0;ic<CNT_CUR;ic++){
       if(CursorDSO[ic]->OnSelect(_posX,_posY)) break	;
     }
 }
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::FMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
 TScrollBox* box = dynamic_cast<TScrollBox*>(Sender)	;
 if(box){
     for(int ic=0;ic<CNT_CUR;ic++){
       if(CursorDSO[ic]->OnSelect(-8,-8)) break		;
     }
 }
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::FMouseMove(TObject *Sender,
			 TShiftState Shift, int X, int Y)
{int ic = 0	;
 TShapeGL* shpGL= dynamic_cast<TShapeGL*>(Sender)	;
 TShape*   shp  = shpGL ? 0 : dynamic_cast<TShape*>(Sender) 	;
 TScrollBox* box = dynamic_cast<TScrollBox*>(Sender)	;

 char str[100]	;
 if(Shift.Contains(ssLeft)){
   if(shpGL && !(shpGL->NCh == TRG_T && bFixTrgT->Down)){
     shpGL->OnMove(X,Y)	    	;// обработка перемещения маркера
				 // из неё через cbSetHardLvl будет
				 // вызов процедуры SetHardLvlChnl
   }
   else if(shp == shpView && bFixTrgT->Down){
     X += shp->Left				;
     if(!flDbg3)
       X = Min(Max(X,shp->Width/2 ),shp->Parent->Width-shp->Width/2 )	;
     shp->Left = X - shp->Width/2 	 	;
     CalcDrawWaves()	;
     sprintf(str,"%ld  %ld", X, shp->Left)	;
//     pTop->Caption = str	;
   }
   else if(box){
     double    _posX = dMap(0,box->Width,X,-1.0,1.0)	;
     double    _posY = dMap(0,box->Height,Y, 1.0,-1.0)	;

     for(ic=0;ic<CNT_CUR;ic++){
       if(CursorDSO[ic]->OnMove(_posX,_posY)) break  	;}
     if(ic<CNT_CUR) GetCursorInfo()		;
   }
 }
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::GetCursorInfo(void)
{WORD	nCHState = m_Hard.m_nCHMod		;
 if(Form1){

   Form1->StatMsg[0] = TDsoCursor::GetInfoT()	;
   Form1->StatMsg[1] = TDsoCursor::GetInfoV()	;
   double 	insNum = dsoSFGetInsertNum(m_Hard.m_nTimeDiv,0,m_Hard.m_nCHMod)	;
   uint32_t	smplRate = dsoSFGetSampleRate(m_Hard.m_nTimeDiv,0,nCHState,1)		;
   Form1->StatMsg[3] = FormatFloat("0.0##",insNum) + FormatFloat(":::0.##",smplRate)	;
 }
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::FMouseWheel(TObject *Sender, TShiftState Shift,
      int WheelDelta, TPoint &MousePos, bool &Handled)
{TChnlParams	params		;
 int		iix,flUpDn=0		;
// static double 	WhlPos = 0	;
// const  double  WhlSns = 1/4.0	;
 bool 		bCtrl = Shift.Contains(ssCtrl) 	;// ??????
 bool 		bShft = Shift.Contains(ssShift)	;// ??????
 uint8_t	nCh = 0xFF	;

 WheelAccumulator += WheelDelta	;
 if(abs(WheelAccumulator) > WHEEL_DELTA*4){
   flUpDn = (WheelAccumulator > 0) ? 1 : -1	;
   WheelAccumulator = 0			   	;
 }
 if(flUpDn){
   if(lblTimDiv->ClientRect.Contains(lblTimDiv->ScreenToClient(MousePos))){
     if(cbChngTimDiv) cbChngTimDiv(flUpDn)	;
     nCh = 9 		;
     CalcDrawWaves()	;
   }

   for(int ch=0;ch<CNT_SHP && nCh > 10;ch++){
     if(shpLvl[ch]->ClientRect.Contains(shpLvl[ch]->ScreenToClient(MousePos)))
       nCh = shpLvl[ch]->Tag-1			;
     else if(ch<4 && lblCh[ch]->ClientRect.Contains(lblCh[ch]->ScreenToClient(MousePos)))
       nCh = lblCh[ch]->Tag-1			;
   }

   if(nCh < 4){
     if(cbGetChnlParams && cbSendChnlParams && nCh<4){
       cbGetChnlParams(nCh,&params)		;
       if(!bCtrl){
	 iix = params.IxVoltDiv + flUpDn   	;
	 iix = Min(Max(iix,0),11)	   	;
	 params.IxVoltDiv = iix			;
       }
       cbSendChnlParams(&params)	   	;
     }
   }
   Application->ProcessMessages()		;
 }
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::BtnClick(TObject *Sender)
{TSpeedButton* btn = dynamic_cast<TSpeedButton*>(Sender)	;
 int tag = btn ? btn->Tag : 0	;
 pTop->Hint = ""		;
 bool	rzlt = false		;

 switch(tag){
   case 14:
   break	;

   case 13: if(!DdsDialog) DdsDialog = new TDdsDialog(this)	;
	    if( DdsDialog) DdsDialog->Visible = btn->Down	;
   break	;

   case 12:		// растяжка!!!
	    rzlt = m_Hard.SetStrth(bStretch->Down)		;
	    if(!rzlt && bStretch->Down) bStretch->Down = false	;
	    CalcDrawWaves()	;
	    if(Form1) Form1->DisplaySampleRate()	;
   break	;
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
void __fastcall TFrmDSO::popTrgClick(TObject *Sender)
{TMenuItem* mi = dynamic_cast<TMenuItem*>(Sender)	;
 int tag = mi ? mi->Tag : 0	;
 if(mi) mi->Checked = true	;

 switch(tag){
   case tmEdge : case tmPulse : case tmVideo : case tmCAN:
   case tmLIN  : case tmUART  : case tmSPI   : case tmI2C: case tmALT:
	miMode->Tag = tag - tmEdge  		;
	m_Hard.SetTriggerMode(miMode->Tag)	; break	;

   case tsAUTO : case tsNORMAL : case tsSINGLE :
	miSweep->Tag = tag - tsAUTO  		;
	m_Hard.SetTriggerSweep(miSweep->Tag)	; break	;

   case srcCH1 : case srcCH2 : case srcCH3 : case srcCH4 :
	miSource->Tag = tag - srcCH1		;
	m_Hard.SetTriggerSrc(miSource->Tag)	;
	CalcDrawWaves()				;
	GetCursorInfo()				; break	;

   case slRising : case slFalling :
	miSlope->Tag = tag - slRising		;
	m_Hard.SetTriggerSlope(miSlope->Tag )	; break	;
 }
}
//---------------------------------------------------------------------------
String __fastcall TFrmDSO::GetSmplPerDiv(void)
{return FormatFloat("0.## Sa/Div",m_Hard.SmplPerDiv())	;}
//---------------------------------------------------------------------------
size_t __fastcall TFrmDSO::CountSamples (void)
{int IX_LEN  = m_Hard.m_nCHMod == 1 ? 4 : m_Hard.m_nCHMod == 2 ? 2 : 1	;
 return m_Hard.BufferLen() * IX_LEN	;}
//---------------------------------------------------------------------------
String __fastcall TFrmDSO::GetTimClct   (void)
{double val = CountSamples()/m_Hard.SamplingRate()	;
 return IntervalToStr(val)				;}
//---------------------------------------------------------------------------
String __fastcall TFrmDSO::GetTimDiv(void)
{double val = m_Hard.GetTimDiv()		;
 String str = val<1e-6 ? FormatFloat("#nS",val*1e9) :
	      val<1e-3 ? FormatFloat("#uS",val*1e6) :
	      val<1    ? FormatFloat("#mS",val*1e3) :
			 FormatFloat("#S" ,val) 	;
 return str	;}
//---------------------------------------------------------------------------
String __fastcall TFrmDSO::GetSmplRate(void)
{double val = m_Hard.SamplingRate()		;
 String str = val > 250e6 ? FormatFloat("0.# GSa",val/1e9) :
	      val > 250e3 ? FormatFloat("0.# MSa",val/1e6) :
	      val > 250   ? FormatFloat("0.# kSa",val/1e3) :
			    FormatFloat("0.# Sa" ,val)		;
 return str	;}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::Dbg1(void)
{
 double insNum = dsoSFGetInsertNum(m_Hard.m_nTimeDiv,0,m_Hard.m_nCHMod)	;
 ShowMessage(FormatFloat("0.00E+00",insNum))	;

}
//---------------------------------------------------------------------------
//     sprintf(str,"Y=%ld, pos=%6.2lf, lvl255=%ld",
//		Y, shpGL->Pos.dPos,shpGL->Pos.Lvl255)	;
//     OutputDebugString(str)			;
//---------------------------------------------------------------------------

// double	srm = smplRate/(smplRate > 250.0e6 ? 1.0e9 :
//			smplRate > 250.0e3 ? 1.0e6 :
//			smplRate > 250.0   ? 1.0e3 : 1.0);
// String strPp = smplRate > 250.0e6 ? "GSa" :
//		smplRate > 250.0e3 ? "MSa" :
//		smplRate > 250.0   ? "KSa" : "Sa"	;
// String strSrm = FormatFloat("0.##",srm)		;

