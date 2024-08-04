//---------------------------------------------------------------------------

#ifndef DSO_frameH
#define DSO_frameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "StdAfx.h"
#include "Hard.h"
//---------------------------------------------------------------------------
class TFrmDSO : public TFrame
{
__published:	// IDE-managed Components
	TScrollBox *pView;
private:	// User declarations
	CHard	m_Hard		;
	TRect	Rect		;

 void __fastcall DrawWaves   (void)    	;	
 void __fastcall DrawWaveInYT(USHORT nCH)	;

public:		// User declarations
	__fastcall TFrmDSO(TComponent* Owner)	;

 void  __fastcall Init(TObject* Sender)		;
 void  __fastcall SetChnlParams(TChnlParams* params)
			{ m_Hard.SetChnlParams(params)	;}
 void  __fastcall Destroy(TObject* Sender)	;
 USHORT __fastcall CollectData (void)		;
 void  __fastcall OnDraw(TObject *Sender)	;

 uint16_t __fastcall GetDevIx(){ return m_Hard.m_nDeviceIndex	;}
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmDSO *FrmDSO;
//---------------------------------------------------------------------------
#endif
