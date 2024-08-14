//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DSO_frame.h"
#include "ComWorL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "rxPlacemnt"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
#include	<GL\glu.h>
//#include	<Math.h>
#include	<StdIO.h>
#include	<IO.h>
//#include	<JPEG.hpp>
//---------------------------------------------------------------------------
struct TParamsDrawWave{
 HDC 	hDC		;// handle to dc
 RECT 	Rect		;// the rect for drawing
 COLORREF clrRGB	;// the color of the line
 USHORT nDisType	;// display type: Line or Dot
 short* pSrcData	;// the source data for drawing
 ULONG 	nSrcDataLen	;// the source data length
 ULONG 	nDisDataLen	;// the display data length for drawing
 ULONG 	nCenterData	;// half of the source data
 USHORT nDisLeverPos	;// the display position(Zero Level)
 double dbHorizontal	;// the horizontal factor of zoom out/in
 double dbVertical	;// the vertical factor of zoom out/in
 USHORT nYTFormat	;// Fomat: Normal or Scan
 ULONG 	nScanLen	;// the scan data length, only invalidate in scan mode
 
 USHORT CntGrid_H	;
 USHORT CntGrid_V	;
 double	SmplPerDiv	;
};
//---------------------------------------------------------------------------
extern GLvoid InitializeGL(HWND handle,GLsizei width, GLsizei height)	;
//extern GLvoid	DrawPxlArrayGL(GLsizei width, GLsizei height,TPxlArrayGL* PxlArr)			;
extern GLvoid DrawShapesGL(TShapeGL* shp[])				;
extern GLvoid DrawWaveGL(USHORT nCh,TParamsDrawWave* params)		;
extern GLvoid DrawGridGL(USHORT cntGrid_H,USHORT cntGrid_V,USHORT nBright,USHORT IsGrid);
extern GLvoid DrawSceneGL(GLsizei width, GLsizei height,TShapeGL* shp[])	;
extern GLvoid DestroyGL ()						;
//---------------------------------------------------------------------------

TFrmDSO *FrmDSO = 0	;
//TShape_M* spmLvl[4] = {0,0,0,0}	;
//---------------------------------------------------------------------------
__fastcall TFrmDSO::TFrmDSO(TComponent* Owner,TNotifyEvent _onChnge): TFrame(Owner)
{String		nam			;
 FOnChange = _onChnge			;
 TColor		_color			;

 SmplPerDiv = 250			;
 CntGrid_H  = 10	; CntGrid_V = 8	;
 pLeft->Tag = 0x2060A0E0		;// для начального установа Lvl255!!!

 FormStorage1->IniFileName = ChangeFileExt(ParamStr(0),".ini")	;
 FormStorage1->IniSection  = Name     	;
 FormStorage1->RestoreFormPlacement() 	;

 for(int ch=0;ch<4;ch++){
   nam.printf("ShpL%ld",ch+1)		;
   _color = TColor(m_Hard.m_clrRGB[ch])	;
   shpLvl[ch] = new TShapeGL(this,pLeft,nam,_color)	;
   shpLvl[ch]->OnMouseMove  = FMouseMove		;
   shpLvl[ch]->cbSetHardLvl = SetHardLvlChnl		;
 }
 shpLvl[TRG_T] = new TShapeGL(this,pTop,"TrgT",clYellow,soHrz,pLeft->Width)	;
 shpLvl[TRG_T]->OnMouseMove  = FMouseMove	;
 shpLvl[TRG_T]->cbSetHardLvl = SetHardLvlChnl	;

 shpLvl[TRG_V] = new TShapeGL(this,pRight,"TrgV",clGray,soVrtM,0)	;
 shpLvl[TRG_V]->OnMouseMove  = FMouseMove	;
 shpLvl[TRG_V]->cbSetHardLvl = SetHardLvlChnl	;
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::Init(TObject* Sender,uint32_t _lvlsPos)
{String	_cap				;
 UCHAR	lvl255				;
 UCHAR* LvlCh = (UCHAR*)&(pLeft->Tag) 	;// для сохр. в .ini файле

 try{
 for(int nCh=0;nCh<4;nCh++){
   _cap = String(nCh+1)			;
   lvl255 = LvlCh[nCh]			;
   shpLvl[nCh]->Init(nCh,_cap,lvl255) 	;
   m_Hard.SetLvl(nCh,lvl255)		;
 }

 shpLvl[TRG_T]->Init(TRG_T,"T",pTop  ->Tag)  	;
 shpLvl[TRG_V]->Init(TRG_V,"T",pRight->Tag) 	;

 InitializeGL(pView->Handle,pView->Width,pView->Height)	;
 }DEF_CATCH
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::Destroy(TObject* Sender){
 DestroyGL()	;
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
 for(int nCh=0;nCh<MAX_CH_NUM;nCh++){    //CH1/CH2/CH3/CH4
   params.clrRGB        = m_Hard.m_clrRGB[nCh]		;// the color of the line
   params.nDisType      = 0				;// display type: Line or Dot
   params.pSrcData      = m_Hard.RelayControl.bCHEnable[nCh] ?
			    m_Hard.m_pSrcData[nCh] : 0	;// the source data for drawing
   params.nSrcDataLen   = m_Hard.m_stControl.nBufferLen ;// the source data length
   params.nDisDataLen   = m_Hard.m_stControl.nBufferLen	;// the display data length for drawing
   params.nCenterData   = params.nSrcDataLen / 2 	;// half of the source data
   params.nDisLeverPos  = m_Hard.m_nLeverPos[nCh]	;// the display position(Zero Level)
   params.dbHorizontal  = 1.0				;// the horizontal factor of zoom out/in
   params.dbVertical    = 1.0				;// the vertical factor of zoom out/in
   params.nYTFormat     = 0				;// Fomat: Normal or Scan
   params.nScanLen      = params.nSrcDataLen		;// the scan data length, only invalidate in scan mode

   params.CntGrid_H	= CntGrid_H			;
   params.CntGrid_V	= CntGrid_V			;
   params.SmplPerDiv    = SmplPerDiv			;
   DrawWaveGL(nCh,&params)				;//
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
 for(int nCh=0;nCh<CNT_SHP;nCh++)
   shpLvl[nCh]->OnResize(pView->Height,pView->Width)	;
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::FMouseMove(TObject *Sender,
			 TShiftState Shift, int X, int Y)
{TShapeGL* shpM= dynamic_cast<TShapeGL*>(Sender)	;
 TPanel*   pan = shpM ? dynamic_cast<TPanel*>(shpM->Parent) : 0	;
 
 char str[100]	;
 if(Shift.Contains(ssLeft)){
   if(shpM){
     shpM->OnMove(X,Y)	    	;// обработка перемещения маркера
				 // из неё через cbSetHardLvl будет
				 // вызов процедуры SetHardLvlChnl
     short iLvl = shpM->GetLvl()	;
     sprintf(str,"%3d (%6.2lf)",iLvl,shpM->Pos.dPos);
     shpM->Hint = str	;

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
//	pTop->Caption = lvl	;
 break	;

 case TRG_V :
	m_Hard.SetTrgV(CurCh,lvl);// TODO
	pRight->Tag = lvl	;
//	pRight->Caption = lvl	;
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
//     sprintf(str,"Y=%ld, pos=%6.2lf, lvl255=%ld",
//		Y, shpM->Pos.dPos,shpM->Pos.Lvl255)	;
//     OutputDebugString(str)			;
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------
// OpenGL  OpenGL  OpenGL  OpenGL  OpenGL  OpenGL  OpenGL  OpenGL
//---------------------------------------------------------------------------
static HGLRC ghRC = 0		;
static HDC   ghDC = 0		;
static HWND  HandleGL = 0	;
#define		GRID     1
#define		WAVE	 2
#define		CNL_1	11
#define		CNL_2	12
#define		CNL_3	13
#define		CNL_4	14
#define		LVL_1	21
#define		LVL_2	21
#define		LVL_3	21
#define		LVL_4	21
//---------------------------------------------------------------------------
BOOL 	bSetupPixelFormat(HDC hdc)     	;
//---------------------------------------------------------------------------
//GLvoid  DrawShapesGL(TShape_M* shp[])
//{uint32_t lstGL				;
//
// for(int nCh=0;nCh<MAX_CH_NUM;nCh++){
//   lstGL = LVL_1+nCh				;
//   if(glIsList(lstGL)) glDeleteLists(lstGL,1)	;
//
//   glNewList(lstGL,GL_COMPILE);{
////     glLineWidth(2)				;
////     glBegin(GL_LINE_LOOP) 			;{
////       glColorT(shp[nCh].Color)			;
////       glVertex2f(shp[nCh].dLft,shp[nCh].dTop)	;
////       glVertex2f(shp[nCh].dRgt,shp[nCh].dTop)	;
////       glVertex2f(shp[nCh].dRgt,shp[nCh].dBot)	;
////       glVertex2f(shp[nCh].dLft,shp[nCh].dBot)	;
////     } glEnd()	;
//     shp[nCh]->DrawGL()	;
//   }glEndList()	;
// }
//}
//---------------------------------------------------------------------------
GLvoid  DrawWaveGL(USHORT nCh,TParamsDrawWave* prms)
{
 uint32_t lst = CNL_1+nCh	;
 if(glIsList(lst)) glDeleteLists(lst,1)	;

// расчитаем шаг по горизонтали
// исходные данные: кол-во делений по горизонтали  (CntGrid_H),
//		    число  отсчётов на деление	 (SmplPerDiv),
 double stpX = 2.0 / (double(prms->CntGrid_H) * prms->SmplPerDiv)	;

 double stpY = 2.0 / 255	;// Шаг по горизонтали

 if(!prms->pSrcData) return	;

 glNewList(lst,GL_COMPILE);{
   glLineWidth(1)		;
   glBegin(GL_LINE_STRIP) 	;{
     glColorT(prms->clrRGB)	;

     for(ULONG ix=0;ix<prms->nSrcDataLen;ix++){
       glVertex2f(ix * stpX-1.0,prms->pSrcData[ix] * stpY-1.0)	;
     }

   } glEnd()	;
 }glEndList()	;
}
//---------------------------------------------------------------------------
GLvoid  DrawGridGL(USHORT cntGrid_H,USHORT cntGrid_V,USHORT nBright,USHORT IsGrid)
{
 float lenT1 = 1.0f, lenT2 = 0.015f	;
 glNewList(GRID,GL_COMPILE)	;{
   glLineWidth(1)		;
   glBegin(GL_LINES)		;{
     glColorT(clGray)		;//	glColor3ub(50,90,40)	;
     glVertex2f(-1.0f, 0.0f)	;
     glVertex2f( 1.0f, 0.0f)	;
     glVertex2f( 0.0f, 1.0f)	;
     glVertex2f( 0.0f,-1.0f)	;

     for(float ix=-1.0;ix<1.0f;ix+=2.0f/cntGrid_H){
       glVertex2f( ix,-lenT1)	; glVertex2f( ix, lenT1) ;}

     for(float ix=-1.0;ix<1.0f;ix+=0.4f/cntGrid_H){
       glVertex2f( ix,-lenT2)	; glVertex2f( ix, lenT2) ;}

     lenT2 = lenT2 * cntGrid_V / cntGrid_H	;
     for(float ix=-1.0;ix<1.0f;ix+=2.0f/cntGrid_V){
       glVertex2f(-lenT1, ix)	; glVertex2f( lenT1, ix) ;}

     for(float ix=-1.0;ix<1.0f;ix+=0.4f/cntGrid_V){
       glVertex2f(-lenT2, ix)	; glVertex2f( lenT2, ix) ;}

   } glEnd()	;
 }glEndList()	;
}
//---------------------------------------------------------------------------
GLvoid	DrawSceneGL(GLsizei width, GLsizei height,TShapeGL* shp[])
{if(!ghDC || !ghRC) return	;

 glViewport( 0, 0,width,height)	;// устанавливаем область вывода
 glMatrixMode( GL_PROJECTION ) 	;// устанавливаем режим матрицы видового преобразования
 glLoadIdentity()	      	;// заменяем текущую матрицу видового преобразования
 glMatrixMode( GL_MODELVIEW ) 	;

 glEnable(GL_BLEND);
 glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // очищаем буфер кадра

 glDisable(GL_BLEND)		;

 glPushMatrix()			;
 //-------


 for(int nCh=0;nCh<4;nCh++){
   if(glIsList(CNL_1+nCh))
     glCallList(CNL_1+nCh)	;
 }
 for(int nShp=0;nShp<CNT_SHP;nShp++){
//   if(glIsList(LVL_1+nCh))
//     glCallList(LVL_1+nCh)	;
   shp[nShp]->DrawGL()		;
 }
 //-------
 if(glIsList(GRID))
   glCallList(GRID)		;

// glDisable(GL_ALPHA_TEST)	;

 glDisable(GL_COLOR_MATERIAL)	;
 glEnable (GL_COLOR_MATERIAL)	;
 glPopMatrix()			;

 SwapBuffers(ghDC)		; // выводим всё на экран
}
//---------------------------------------------------------------------------
GLvoid InitializeGL(HWND handle,GLsizei width, GLsizei height)
{
  GLfloat     maxObjectSize, aspect;
  GLdouble    near_plane;

  HandleGL = handle	;
  ghDC  = GetDC(handle)	;

  if(bSetupPixelFormat(ghDC)){
    ghRC = wglCreateContext(ghDC)		;
    wglMakeCurrent(ghDC, ghRC)			;}
  else{ DestroyGL()	; return		;}

//    glClearIndex( (GLfloat)BLACK_INDEX);

  glClearDepth( 1.0 );

//    glEnable(GL_DEPTH_TEST);

  glMatrixMode( GL_PROJECTION );
  aspect = (GLfloat) width / height;
  gluPerspective( 45.0, aspect, 1.0, 10.0 );
  glMatrixMode( GL_MODELVIEW );

  GLfloat specular   [] = { 1.0, 1.0, 1.0, 1.0};
  GLfloat diffuse    [] = { 1.0, 1.0, 1.0, 1.0};
  GLfloat emission   [] = { 0.1, 0.1, 0.1, 1.0 };
  GLfloat ambient    [] = { 0.8, 0.8, 0.8, 1.0 };
  GLfloat shininess  [] = { 100.0 };
  GLfloat specularM  [] = { 1.0, 1.0, 1.0, 1.0};
  GLfloat diffuseM   [] = { 0.8, 0.8, 0.8, 1.0};
  GLfloat ambientM   [] = { 0.2, 0.2, 0.2, 1.0 };
  GLfloat shininessM [] = { 50.0 };
  GLfloat emissionM  [] = { 0.1, 0.1, 0.1, 1.0 };
  GLfloat position   [] = { 2.0, 2.0, 2.0, 0.0 };
  GLfloat position1  [] = { -1.0, 1.0, 1.0, 0.0 };

  Trgb rgb(clMoneyGreen)			;
  glClearColor(rgb.rf(),rgb.gf(),rgb.bf(),1)	;// Set the clear color
//  glClearColor(0.7, 0.7, 0.7, 0.0);

  // Set the shading model
//  glShadeModel(GL_SMOOTH);
  glShadeModel(GL_FLAT);

//  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);

  // Set the polygon mode to fill
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glPolygonMode(GL_FRONT, GL_FILL);

  // Enable depth testing for hidden line removal
  glEnable(GL_DEPTH_TEST);

  // Define material properties of specular color and degree of
  // shininess.  Since this is only done once in this particular
  // example, it applies to all objects.  Material properties can
  // be set for individual objects, individual faces of the objects,
  // individual vertices of the faces, etc...
//  glMaterialfv(GL_FRONT, GL_SPECULAR , specularM);
//  glMaterialfv(GL_FRONT, GL_SHININESS, shininessM);
//  glMaterialfv(GL_FRONT, GL_EMISSION , emissionM);

  // Set the GL_AMBIENT_AND_DIFFUSE color state variable to be the
  // one referred to by all following calls to glColor
//  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);

  // Create a Directional Light Source
//  glLightfv(GL_LIGHT0,GL_POSITION, position);
//  glLightfv(GL_LIGHT0,GL_DIFFUSE , diffuse);
//  glLightfv(GL_LIGHT0,GL_SPECULAR, specular);
//	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
//	glBlendFunc(GL_SRC_ALPHA,GL_SRC_ALPHA);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glPixelStorei(GL_UNPACK_ALIGNMENT,2)	;
//	glEnable(GL_BLEND);

  near_plane = 3.0;
  maxObjectSize = 3.0F;
//  CreateObjects();
}
//---------------------------------------------------------------------------
GLvoid DestroyGL(void)
{
 if(ghRC){
   wglMakeCurrent(ghDC,0)		;
   wglDeleteContext(ghRC)		;}

 if(ghDC) ReleaseDC(HandleGL, ghDC)	;
 ghDC = 0	; ghRC = 0		; HandleGL = 0	;}
//---------------------------------------------------------------------------
BOOL bSetupPixelFormat(HDC hdc)
{
 PIXELFORMATDESCRIPTOR pfd, *ppfd;
 int pixelformat;

 ppfd = &pfd;

 ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR)	;
 ppfd->nVersion   = 1				;
 ppfd->dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
 ppfd->dwLayerMask= PFD_MAIN_PLANE		;
 ppfd->iPixelType = PFD_TYPE_RGBA		;//COLORINDEX;
 ppfd->cColorBits = 8	;
 ppfd->cDepthBits = 16	;

 ppfd->cAccumBits = 0	;
 ppfd->cStencilBits = 0	;

 if((pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0 ){
   MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK)	; return FALSE	;}

 if(SetPixelFormat(hdc,pixelformat,ppfd) == FALSE){
   MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK)	; return FALSE	;}
 return TRUE;
}
//-----------------------------------------------------------------------------


