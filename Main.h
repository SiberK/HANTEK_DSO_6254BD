//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>

#include "rxPlacemnt.hpp"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSpeedButton *bInit;
	TStatusBar *StatBar1;
	TSpeedButton *SpeedButton1;
	TPanel *pDSO;
	TFormStorage *FormStorage1;
	TTimer *timRef;
	void __fastcall timRefTimer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);

private:	// User declarations
 void   __fastcall wrStatBar(int i,String val)
   { if(i<StatBar1->Panels->Count)StatBar1->Panels->Items[i]->Text = val	;}
 String	__fastcall rdStatBar(int i)
   { return (i<StatBar1->Panels->Count)? StatBar1->Panels->Items[i]->Text : String("")	;}

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

 __property String  StatMsg[int i] = {read=rdStatBar,write=wrStatBar	};
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
