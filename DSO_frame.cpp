//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DSO_frame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
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
};
//---------------------------------------------------------------------------
extern GLvoid InitializeGL(HWND handle,GLsizei width, GLsizei height)	;
//extern GLvoid	DrawPxlArrayGL(GLsizei width, GLsizei height,TPxlArrayGL* PxlArr)			;
extern GLvoid DrawWaveGL(USHORT nCH,TParamsDrawWave* params)	;
extern GLvoid DrawGridGL(USHORT nHoriGridNum,USHORT nVertGridNum,USHORT nBright,USHORT IsGrid);
extern GLvoid DrawSceneGL(GLsizei width, GLsizei height)		;
extern GLvoid DestroyGL ()						;
//---------------------------------------------------------------------------



TFrmDSO *FrmDSO = 0	;
//---------------------------------------------------------------------------
__fastcall TFrmDSO::TFrmDSO(TComponent* Owner): TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::Init(TObject* Sender)
{InitializeGL(pView->Handle,pView->Width,pView->Height)	;}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::Destroy(TObject* Sender){DestroyGL()	;}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::CollectData(void)
{short	nState = 0	;
 String Str		;

 if(m_Hard.m_nDeviceIndex == 0xFF){
   if(!m_Hard.FindeDev()){
     Application->MessageBox("No suitble device was found!","!!!",MB_OK);
     return;
   }
   else{
     Str.printf("verFPGA %lX",dsoGetFPGAVersion(m_Hard.m_nDeviceIndex));
//     StatMsg[0] = Str	;
   }
 }

  if(m_bStartNew) {
    WORD nStartControl=0;
    nStartControl|=((m_Hard.m_nTriggerSweep==AUTO)?0x01:0);//add by zhang
    nStartControl|=((m_Hard.m_nYTFormat== YT_ROLL)?0x02:0);//add by zhang
    nStartControl|=m_Hard.m_bCollect?0:0x04;//add by zhang
    dsoHTStartCollectData(m_Hard.m_nDeviceIndex,nStartControl);
    m_Hard.m_stControl.nLastAddress = 0;  //扫描有效 Скан действителен
    m_Hard.m_stControl.nAlreadyReadLen = 0;//扫描有效 Скан действителен
//	dsoHTStartTrigger(m_Hard.m_nDeviceIndex);
//		m_nAutoTriggerCnt = 0;
    m_bStartNew = FALSE		;
  }

  nState = dsoHTGetState(m_Hard.m_nDeviceIndex);
  if (YT_NORMAL == m_Hard.m_nYTFormat){
    if (nState & 0x02){
      m_Hard.ReadData()		;
      m_bStartNew = TRUE	;
    }
    else{
      m_bStartNew = FALSE	;
    }
  }
  else if (m_Hard.m_nYTFormat == YT_SCAN)//扫描有效 Скан действителен
  {
    if(((nState >> 8) & 0x0F) >= 3)//预采集满 Предварительная коллекция заполнена)
      m_Hard.ReadSCANData()	;
    if(m_Hard.m_stControl.nAlreadyReadLen >= DEF_READ_DATA_LEN){
      m_bStartNew = TRUE	;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::DrawWave(HDC hdc,TRect Rect)
{
 for(int i=0;i<MAX_CH_NUM;i++)    //CH1/CH2/CH3/CH4
   DrawWaveInYT(hdc,Rect,i)	;
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::DrawWaveInYT(HDC hdc,TRect Rect,USHORT nCH)
{
//  short*  pData        = m_Hard.m_pSrcData[nCH]		;//源数据 		   источник данных
//  ULONG   nDisDataLen  = 2500				;//网格内要画的数据长度 Длина данных, отображаемых в сетке
//  ULONG   nSrcDataLen  = BUF_4K_LEN			;//源数据的长度         Длина исходных данных
//  USHORT  nDisLeverPos = m_Hard.m_nLeverPos[nCH]	;//零电平的显示位置     Положение отображения нулевого уровня
//  ULONG   nCenterData  = BUF_4K_LEN / 2			;//
//  COLORREF  clrRGB     = m_Hard.m_clrRGB[nCH]		;//颜色                 цвет
//  USHORT  nHTriggerPos = m_Hard.m_stControl.nHTriggerPos;//水平触发点位置       Горизонтальное расположение триггерной точки
//  USHORT  nYTFormat    = 0				;
//  USHORT  nDisType     = 0				;//显示类型，点或线       Тип отображения, точка или линия
//  double  dbVertical   = 1.0				;//
//  double  dbHorizontal = 1.0				;

  TParamsDrawWave        params	;
//  params.hDC	       = 			;// handle to dc
//  params.Rect	       = 			;// the rect for drawing
  params.clrRGB        = m_Hard.m_clrRGB[nCH]	;// the color of the line
  params.nDisType      = 0			;// display type: Line or Dot
  params.pSrcData      = m_Hard.m_pSrcData[nCH]	;// the source data for drawing
  params.nSrcDataLen   = BUF_4K_LEN		;// the source data length
  params.nDisDataLen   = 2500			;// the display data length for drawing
  params.nCenterData   = BUF_4K_LEN / 2		;// half of the source data
  params.nDisLeverPos  = m_Hard.m_nLeverPos[nCH];// the display position(Zero Level)
  params.dbHorizontal  = 1.0			;// the horizontal factor of zoom out/in
  params.dbVertical    = 1.0			;// the vertical factor of zoom out/in
  params.nYTFormat     = 0			;// Fomat: Normal or Scan
  params.nScanLen      = BUF_4K_LEN		;// the scan data length, only invalidate in scan mode

  DrawWaveGL(nCH,&params)			;//
}
//---------------------------------------------------------------------------
void __fastcall TFrmDSO::OnDraw(TObject *Sender)
{
 HDC 	hdc  = GetDC(pView->Handle)	;
 TRect	Rect = pView->ClientRect	;

 static bool  flGrid = false		;
 if(!flGrid){ flGrid = true		;
   DrawGridGL(12,8,200,1)		;}

 if(m_Hard.m_nDeviceIndex!=0xFF){
   DrawWave(hdc,Rect)			;}

 DrawSceneGL(Rect.Width(),Rect.Height());
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#pragma pack(push,1)
struct Trgb{
  uint8_t	r,g,b,a	;
  Trgb(TColor color) {Set(color)	;}

  void  Set(TColor color){*(TColor*)this= color	;}
  float rf()		{ return r/255.0	;}
  float gf()		{ return g/255.0	;}
  float bf()		{ return b/255.0	;}
  void  glColor(TColor color){ Set(color)	; glColor3ub(r,g,b)	;}
  void  glColor(void){ glColor3ub(r,g,b)	;}
};
#pragma pack(pop)
//---------------------------------------------------------------------------
void glColorT(TColor clr){Trgb rgb(clr)	; rgb.glColor()	;}
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
//---------------------------------------------------------------------------
BOOL 	bSetupPixelFormat(HDC hdc)     	;
//---------------------------------------------------------------------------
GLvoid  DrawWaveGL(USHORT nCH,TParamsDrawWave* prms)
{
 uint32_t lst = CNL_1+nCH	;
 if(glIsList(lst)) glDeleteLists(lst,1)	;

 double stpX = 2.0 / prms->nDisDataLen	;
 double stpY = 1.0 / 255	;

 glNewList(lst,GL_COMPILE);{
   glLineWidth(1)		;
   glBegin(GL_LINE_STRIP) 	;{
     glColorT(prms->clrRGB)	;
     
     for(ULONG ix=0;ix<prms->nSrcDataLen;ix++){
       glVertex2f(ix * stpX-1.0,prms->pSrcData[ix] * stpY)	;
     }

   } glEnd()	;
 }glEndList()	;
}
//---------------------------------------------------------------------------
GLvoid  DrawGridGL(USHORT nHoriGridNum,USHORT nVertGridNum,USHORT nBright,USHORT IsGrid)
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

     for(float ix=-1.0;ix<1.0f;ix+=2.0f/nHoriGridNum){
       glVertex2f( ix,-lenT1)	; glVertex2f( ix, lenT1) ;}

     for(float ix=-1.0;ix<1.0f;ix+=0.4f/nHoriGridNum){
       glVertex2f( ix,-lenT2)	; glVertex2f( ix, lenT2) ;}

     lenT2 = lenT2 * nVertGridNum / nHoriGridNum	;
     for(float ix=-1.0;ix<1.0f;ix+=2.0f/nVertGridNum){
       glVertex2f(-lenT1, ix)	; glVertex2f( lenT1, ix) ;}

     for(float ix=-1.0;ix<1.0f;ix+=0.4f/nVertGridNum){
       glVertex2f(-lenT2, ix)	; glVertex2f( lenT2, ix) ;}

   } glEnd()	;
 }glEndList()	;
}
//---------------------------------------------------------------------------
GLvoid	DrawSceneGL(GLsizei width, GLsizei height)
{if(!ghDC || !ghRC) return	;

 glViewport( 0, 0,width,height)	;// устанавливаем область вывода
 glMatrixMode( GL_PROJECTION ) 	;// устанавливаем режим матрицы видового преобразования
 glLoadIdentity()	      	;// заменяем текущую матрицу видового преобразования
 glMatrixMode( GL_MODELVIEW ) 	;

 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // очищаем буфер кадра

 glPushMatrix()			;
 //-------
 
 glCallList(GRID)		;

 for(int nCH=0;nCH<4;nCH++){
   if(glIsList(CNL_1+nCH))
     glCallList(CNL_1+nCH)	;
 }
 
 //-------
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
  glClearColor(rgb.rf(),rgb.gf(),rgb.bf(),0.0)	;// Set the clear color
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
