//---------------------------------------------------------------------------
#pragma hdrstop
#include "Hard.h"
#include "ComWorL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Hard.cpp: implementation of the CHard class.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static int BUF_LEN     = 0x1000	;//  4K
static int MAX_BUF_LEN = 0x4000	;// 16K

CHard::CHard()
{
  m_nLeverPos[CH1] = 127;//192;
  m_nLeverPos[CH2] = 127;//160;
  m_nLeverPos[CH3] = 127;//96;
  m_nLeverPos[CH4] = 127;//64;
  ULONG nCh = 0;
  m_nDeviceIndex = 0xFF;
  m_nDeviceNum = 0;
  for (nCh = 0; nCh < MAX_CH_NUM; nCh++){
    m_pSrcData[nCh] = new short[MAX_BUF_LEN]	;
  }
//  m_clrRGB[CH1] = RGB(255, 255,   0)	;
//  m_clrRGB[CH2] = RGB(  0, 255, 255)	;
//  m_clrRGB[CH3] = RGB(255,   0, 255)	;
//  m_clrRGB[CH4] = RGB(  0, 255,   0)	;
  m_clrRGB[CH1] = clBlue;//RGB(  0,  0, 255)	;
  m_clrRGB[CH2] = clRed;//RGB(255,  0,   0)	;
  m_clrRGB[CH3] = clGreen;//RGB(  0, 80,   0)	;
  m_clrRGB[CH4] = clPurple;//RGB(127,  0, 127)	;
  m_nTimeDIV    = 12			;//24;

  m_stControl.nCHSet 		= 0x0F		;//Все каналы открыты
  m_stControl.nTimeDIV 		= m_nTimeDIV	;//Factory Setup
  m_stControl.nTriggerSource 	= CH1		;//Канал 1 является триггерным каналом.

  m_stControl.nVTriggerPos	= m_nLeverPos[CH1];//Вертикальное положение триггера такое же, как у канала 1.
  m_stControl.nTriggerSlope 	= RISE		;//Режим запуска триггера по фронту: нарастающий фронт
  m_stControl.nBufferLen 	= BUF_LEN	;//Глубина сбора
  m_stControl.nReadDataLen 	= BUF_LEN	;//Длина чтения <= глубина сбора данных
  m_stControl.nLastAddress	= 0		;  //add by zhang
  m_stControl.nAlreadyReadLen 	= 0		;//Он действителен только при сканировании и прокрутке и используется для записи прочитанной длины.
  m_stControl.nALT 		= 0		;//Factory Setup

  m_nYTFormat = m_nTimeDIV > 23 ? YT_SCAN : YT_NORMAL;
  m_stControl.nHTriggerPos = m_nYTFormat == YT_SCAN ? 0 : 25;//Горизонтальное положение триггера (0-100)
 for (nCh = 0; nCh < MAX_CH_NUM; nCh++){
   RelayControl.bCHEnable  [nCh] = 1	;
   RelayControl.nCHVoltDIV [nCh] = 5	;
   RelayControl.nCHCoupling[nCh] = DC	;
   RelayControl.bCHBWLimit [nCh] = 0	;
 }
 RelayControl.nTrigSource      = CH1	;
 RelayControl.bTrigFilt        = 0	;
 RelayControl.nALT 	       = 0	;
 
 m_nTriggerMode  = EDGE	;
 m_nTriggerSlope = RISE	;
 m_nTriggerSweep = AUTO	;

 m_bCollect 	= TRUE	;
 m_nReadOK 	= 0	;
}
//---------------------------------------------------------------------------
void CHard::SetLvl(int nCh,USHORT lvl)
{
 m_nLeverPos[nCh] = lvl		;
 if(m_nDeviceIndex == 0xFF) return	;
 dsoHTSetCHPos(m_nDeviceIndex, RelayControl.nCHVoltDIV[nCh], m_nLeverPos[nCh], nCh, 4);
}
//---------------------------------------------------------------------------
void CHard::SetTrgT(int nCh,USHORT lvl)
{m_stControl.nHTriggerPos = lvl		;
 if(m_nDeviceIndex != 0xFF){
   dsoHTSetHTriggerLength(m_nDeviceIndex,&m_stControl,4)	;
 }
}
//---------------------------------------------------------------------------
void CHard::SetTrgV(int nCh,USHORT lvl)
{
 if(m_nDeviceIndex != 0xFF){
    dsoHTSetVTriggerLevel(m_nDeviceIndex, lvl, 4);
 }
}
//---------------------------------------------------------------------------
double CHard::SetTimeDiv(TTimeParams* timPrms)
{
 if(timPrms->nTimeDIV != -1)
   m_nTimeDIV = timPrms->nTimeDIV	;
 m_nYTFormat = m_nTimeDIV > 23 ? YT_SCAN : YT_NORMAL;

 m_stControl.nTimeDIV = m_nTimeDIV	;//Factory Setup

 double smplPerDiv = SamplingRate() * timPrms->TimeBase	;

 if(m_nDeviceIndex != 0xFF){
// Установить частоту дискретизации
   dsoHTSetSampleRate(m_nDeviceIndex, m_nYTFormat, &RelayControl, &m_stControl)	;
   for (int nCh = 0; nCh < MAX_CH_NUM; nCh++)
     dsoHTSetCHPos(m_nDeviceIndex, RelayControl.nCHVoltDIV[nCh], m_nLeverPos[nCh],nCh, 4);
//Установите переключатель каналов и уровень напряжения
   dsoHTSetCHAndTrigger(m_nDeviceIndex, &RelayControl, m_stControl.nTimeDIV)	;
// Установите коррекцию амплитуды, вызванную режимом канала
   dsoHTADCCHModGain(m_nDeviceIndex, 4)			;
 }

 return smplPerDiv	;}
//---------------------------------------------------------------------------
void CHard::Init()
{
 try{
 dsoInitHard(m_nDeviceIndex)		;//Инициализация оборудования
 dsoHTADCCHModGain(m_nDeviceIndex, 4)	;// Установите коррекцию амплитуды, вызванную режимом канала

// Установить частоту дискретизации
 dsoHTSetSampleRate(m_nDeviceIndex, m_nYTFormat, &RelayControl, &m_stControl)	;
//Установите переключатель каналов и уровень напряжения
 dsoHTSetCHAndTrigger(m_nDeviceIndex, &RelayControl, m_stControl.nTimeDIV)	;
//Установить источник триггера
 dsoHTSetRamAndTrigerControl(m_nDeviceIndex, m_stControl.nTimeDIV,
					     m_stControl.nCHSet  ,
					     m_stControl.nTriggerSource, 0)	;
 for (int nCh = 0; nCh < MAX_CH_NUM; nCh++){
   dsoHTSetCHPos(m_nDeviceIndex, RelayControl.nCHVoltDIV[nCh], m_nLeverPos[nCh], nCh, 4);
 }
 dsoHTSetVTriggerLevel(m_nDeviceIndex, m_nLeverPos[CH1], 4);

 switch (m_nTriggerMode) {//Настройки триггера
 case EDGE:
	  dsoHTSetTrigerMode(m_nDeviceIndex, m_nTriggerMode, m_stControl.nTriggerSlope, DC);
	  break;
	  /*
  case VIDEO:
	  {
	  double dbVolt=m_dbVoltDIV[RelayControl.nCHVoltDIV[m_nALTSelCH]];
	  short nPositive=nVideoPositive==POSITIVE?TRIGGER_VIDEO_POSITIVE:TRIGGER_VIDEO_NEGATIVE;
	  WORD nTriggerLevel=255-GetCHLeverPos(m_nALTSelCH)+short((256*nPositive)/(dbVolt*V_GRID_NUM)+0.5);
	  dsoHTSetTrigerMode(m_nDeviceIndex,m_nTriggerMode,m_stControl.nTriggerSlope,m_Trigger.m_nTriggerCouple);
	  dsoHTSetVideoTriger(m_nDeviceIndex,nVideoStandard,nVideoSyncSelect,nVideoHsyncNumOption,nVideoPositive,nTriggerLevel,GetLogicTriggerSource(m_nALTSelCH));
	  break;}
  case PULSE:
	  dsoHTSetTrigerMode(m_nDeviceIndex,m_nTriggerMode,m_stControl.nTriggerSlope,m_Trigger.m_nTriggerCouple);
	  dsoHTSetPulseTriger(m_nDeviceIndex,nPW,nPWCondition);
	  break;
  case FORCE:
	  dsoHTSetTrigerMode(m_nDeviceIndex,m_nTriggerMode,m_stControl.nTriggerSlope,m_Trigger.m_nTriggerCouple);
	  */
 default:
	  break;
 }
 }DEF_CATCH
}
//---------------------------------------------------------------------------
void CHard::SetChnlParams(TChnlParams* params)
{int nCh = params->IX	;

 RelayControl.bCHEnable  [nCh] = params->OnOff		;
 if(params->IxVoltDiv != -1)
   RelayControl.nCHVoltDIV [nCh] = params->IxVoltDiv	;
 if(params->IxAcDc != -1)
   RelayControl.nCHCoupling[nCh] = params->IxAcDc  	;

 if(m_nDeviceIndex != 0xFF){
   dsoHTSetCHPos(m_nDeviceIndex, RelayControl.nCHVoltDIV[nCh], m_nLeverPos[nCh],nCh, 4);
//Установите переключатель каналов и уровень напряжения
   dsoHTSetCHAndTrigger(m_nDeviceIndex, &RelayControl, m_stControl.nTimeDIV)	;
// Установите коррекцию амплитуды, вызванную режимом канала
   dsoHTADCCHModGain(m_nDeviceIndex, 4)			;
 }
}
//---------------------------------------------------------------------------
USHORT CHard::CollectData()
{
 if(m_nDeviceIndex == 0xFF){
   if(!FindeDev()){
     Application->MessageBox("No suitble device was found!","!!!",MB_OK);
     return m_nDeviceIndex 	;}
 }

 if(m_bStartNew) {
   WORD nStartControl=0	;
   nStartControl |= ((m_nTriggerSweep==AUTO)? 0x01:0)	;// add by zhang
   nStartControl |= ((m_nYTFormat== YT_ROLL)? 0x02:0)	;// add by zhang
   nStartControl |=   m_bCollect 	    ? 0   : 0x04;// add by zhang
   dsoHTStartCollectData(m_nDeviceIndex,nStartControl)	;
   m_stControl.nLastAddress    = 0			;// Скан действителен
   m_stControl.nAlreadyReadLen = 0			;// Скан действителен
//	dsoHTStartTrigger(m_nDeviceIndex);
//		m_nAutoTriggerCnt = 0;
   m_bStartNew = FALSE		;
 }

 short nState = dsoHTGetState(m_nDeviceIndex);
 if (YT_NORMAL == m_nYTFormat){
   if (nState & 0x02){
     if(ReadData())
       m_bStartNew = TRUE	;}
   else{
     m_bStartNew = FALSE	;}
 }
 else if (m_nYTFormat == YT_SCAN){		// Скан действителен
   if(((nState >> 8) & 0x0F) >= 3)		// Предварительная коллекция заполнена)
     ReadSCANData()				;
   if(m_stControl.nAlreadyReadLen >= DEF_READ_DATA_LEN){
     m_bStartNew = TRUE				;
   }
 }
 return m_nDeviceIndex 		;}
//---------------------------------------------------------------------------
bool CHard::FindeDev()
{bool rzlt = false		;
 for (m_nDeviceIndex = 0; m_nDeviceIndex < 32; m_nDeviceIndex++){
   if (dsoHTDeviceConnect(m_nDeviceIndex)){
     Init()	; rzlt = true	; break		;}
 }
 if(!rzlt) m_nDeviceIndex = 0xFF;
 return rzlt			;
}
//---------------------------------------------------------------------------
#ifndef OLOLO
int CHard::ReadData()
{
  int nCh = 0;
  for (nCh = 0; nCh < MAX_CH_NUM; nCh++) {
    memset(m_pSrcData[nCh], 0, m_stControl.nReadDataLen * sizeof(USHORT));//
  }

//Фактическое значение напряжения j-й точки каждого канала
// nCh = (pReadData[nCh][j]-m_nLeverPos[nCh])*8*значение напряжения/255
  try{
  m_nReadOK = dsoHTGetData(m_nDeviceIndex, (USHORT*)m_pSrcData[CH1], (USHORT*)m_pSrcData[CH2],
					   (USHORT*)m_pSrcData[CH3], (USHORT*)m_pSrcData[CH4], &m_stControl);
  }DEF_CATCH

  for (nCh = 0; nCh < MAX_CH_NUM; nCh++){
    if(RelayControl.nCHCoupling[nCh] == GND)
      for(size_t ix=0;ix<m_stControl.nReadDataLen;ix++)
        m_pSrcData[nCh][ix] = m_nLeverPos[nCh]		;//
  }
//  if(m_nReadOK == 1){
//    for (nCh = 0; nCh < MAX_CH_NUM; nCh++){
//      if(RelayControl.bCHEnable[nCh] && pReadData[nCh])
//	SourceToDisplay(pReadData[nCh], m_stControl.nReadDataLen, nCh);// Для удобства отображения
//    }
//  }

 return m_nReadOK	;}
//---------------------------------------------------------------------------
#else
void CHard::ReadData()
{
  int nCh = 0;
  USHORT* pReadData[MAX_CH_NUM]	;
  for (nCh = 0; nCh < MAX_CH_NUM; nCh++) {
    pReadData[nCh] = new USHORT[m_stControl.nReadDataLen];
    memset(pReadData[nCh], 0, m_stControl.nReadDataLen * sizeof(USHORT));//
  }

//Фактическое значение напряжения j-й точки каждого канала
// nCh = (pReadData[nCh][j]-m_nLeverPos[nCh])*8*значение напряжения/255
  try{
  m_nReadOK = dsoHTGetData(m_nDeviceIndex, pReadData[CH1], pReadData[CH2],
					   pReadData[CH3], pReadData[CH4], &m_stControl);
  }DEF_CATCH

  if(m_nReadOK == 1){
    for (nCh = 0; nCh < MAX_CH_NUM; nCh++){
      if(RelayControl.bCHEnable[nCh] && pReadData[nCh])
	SourceToDisplay(pReadData[nCh], m_stControl.nReadDataLen, nCh);// Для удобства отображения
    }
  }

  for (nCh = 0; nCh < MAX_CH_NUM; nCh++){
    if(!pReadData[nCh]) continue	;
    delete[] pReadData[nCh]	;
  }
}
#endif
//---------------------------------------------------------------------------
void CHard::ReadSCANData()
{
 int nCh = 0;
 USHORT* pReadData[MAX_CH_NUM];
 for (nCh = 0; nCh < MAX_CH_NUM; nCh++){
   pReadData[nCh] = new USHORT[m_stControl.nReadDataLen];
   memset(pReadData[nCh], 0, m_stControl.nReadDataLen * sizeof(USHORT));//
 }
 m_nReadOK = dsoHTGetScanData(m_nDeviceIndex, pReadData[CH1], pReadData[CH2], pReadData[CH3], pReadData[CH4], &m_stControl);//每通道i第j个点的实际电压值=(pReadData[nCh][j]-m_nLeverPos[nCh])*8*电压值/255

 int nLastSCANLen = m_stControl.nAlreadyReadLen	;
 int nCurSCANLen  = m_stControl.nAlreadyReadLen	;
 int nCurReadLen  = nCurSCANLen - nLastSCANLen	;
//	CString str;
//	AnsiString str;
//	str.Format(_T("Длина, полученная SCan на этот раз, равна %d\t. Общая длина теперь равна %d\n"), nCurReadLen, nCurSCANLen);
//	OutputDebugString(str);
 if (m_nReadOK &&nCurSCANLen > nLastSCANLen){
   for (nCh = 0; nCh < MAX_CH_NUM; nCh++){
     SourceToDisplay(pReadData[nCh], nCurReadLen, nCh, nLastSCANLen);// Для удобства отображения
   }
 }

 for (nCh = 0; nCh < MAX_CH_NUM; nCh++){
   delete pReadData[nCh]			;}
}
//---------------------------------------------------------------------------
void CHard::SourceToDisplay(USHORT* pData, ULONG nDataLen, USHORT nCH, int nOffset)
{
 for (ULONG i = 0; i < nDataLen; i++){
   m_pSrcData[nCH][i + nOffset] = pData[i];// - (MAX_DATA - m_nLeverPos[nCH]);
 }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
double CHard::SamplingRate()
{static double tblSmplRate[] = {1.0e9,1.0e9,1.0e9,1.0e9 ,1.0e9, 1.0e9, 1.0e9,0.5e9,250e6,
				125e6, 50e6, 25e6,12.5e6,  5e6, 2.5e6,1.25e6,500e3,250e3,
				125e3, 50e3, 25e3,12.5e3,  5e3, 2.5e3,1.25e3,500.0,250.0,
				125.0, 50.0, 25.0,12.5  ,  5.0, 2.5  ,1.25  ,0.5  ,0.25};
 USHORT cntChn = CntChnlW()	;
 double rate   = m_nTimeDIV < sizeof(tblSmplRate) ? tblSmplRate[m_nTimeDIV] : 0.0	;
// на высоких частотах SampleRate меньше задаваемого !!!! (зависит от кол-ва вкл. каналов)
 if(m_nTimeDIV < 7) rate = cntChn > 2 ? rate/4 : cntChn > 1 ? rate/2 : rate	;
 if(m_nTimeDIV== 7) rate = cntChn > 2 ? rate/2 : rate	;

 return rate	;
}
//---------------------------------------------------------------------------
int CHard::CntChnlW()	// кол-во включенных каналов
{int cnt = 0	;
 for(int nCh=0;nCh<4;nCh++) if(RelayControl.bCHEnable[nCh]) cnt++	;
 return cnt	;}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
