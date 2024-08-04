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
#include <Menus.hpp>
#include "rxCurrEdit.hpp"
#include "rxToolEdit.hpp"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *StatBar1;
	TPanel *pDSO;
	TFormStorage *FormStorage1;
	TTimer *timRef;
	TPageControl *pcTool;
	TTabSheet *tsDSO;
	TTabSheet *tsDDS;
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Edit1;
	TMenuItem *Save1;
	TComboBox *cbDdsMode;
	TLabel *Label1;
	TCurrencyEdit *eFrq;
	TComboBox *cbFrq;
	TLabel *Label2;
	TCurrencyEdit *eAmpl;
	TLabel *Label3;
	TCurrencyEdit *eOffset;
	TGroupBox *GroupBox1;
	TGroupBox *gbChnl;
	TComboBox *cbTimeDiv;
	TComboBox *cbSmplDiv;
	TGroupBox *gbTrgr;
	TComboBox *cbEdge;
	TComboBox *cbSrcTrg;
	void __fastcall timRefTimer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall DDS_Change(TObject *Sender);
	void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift,
	  int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall FormStorage1RestorePlacement(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

private:	// User declarations
	String		StrVersion	;

 void   __fastcall wrStatBar(int i,String val)
   { if(i<StatBar1->Panels->Count)StatBar1->Panels->Items[i]->Text = val	;}
 String	__fastcall rdStatBar(int i)
   { return (i<StatBar1->Panels->Count)? StatBar1->Panels->Items[i]->Text : String("")	;}
 void __fastcall ChnlOnChange(TObject *Sender);

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

 __property String  StatMsg[int i] = {read=rdStatBar,write=wrStatBar	};
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
