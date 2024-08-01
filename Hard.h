//---------------------------------------------------------------------------
#ifndef HardH
#define HardH
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Hard.h: interface for the CHard class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

class CHard
{
public:
	CHard();
	virtual ~CHard();
//Attributes
public:
  USHORT       	m_nDeviceIndex;
  USHORT       	m_nDeviceNum;
  //USHORT 	m_nComType;//0:USB; 1:LAN
  short*       	m_pSrcData[MAX_CH_NUM];//��ȡ�����ݼ�ȥ���ƽ��λ��(-255 ~ 255)
  //USHORT 	m_nCalLevel[CAL_LEVEL_LEN];//Cal Level
  USHORT       	m_nTimeDIV;
  USHORT       	m_nYTFormat;
  BOOL 		m_bCollect;
  CONTROLDATA 	m_stControl;
  RELAYCONTROL 	RelayControl;
  USHORT       	m_nTriggerMode;
  USHORT       	m_nTriggerSweep;
  USHORT       	m_nTriggerSlope;
  USHORT       	m_nLeverPos[MAX_CH_NUM];
  COLORREF 	m_clrRGB[MAX_CH_NUM];
	//WORD pAmpLevel[AMPCALI_Len];

	int m_nReadOK;//���ζ������Ƿ���ȷ,0,����ȷ����0����ȷ��
//Operations
public:
	bool FindeDev();
	void Init();
	void ReadData();
	void ReadSCANData();
	void SourceToDisplay(USHORT* pData,ULONG nDataLen,USHORT nCH,int nOffset=0);

};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif

