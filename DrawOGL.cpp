//---------------------------------------------------------------------------
#pragma hdrstop
#include "DrawOGL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// OpenGL  OpenGL  OpenGL  OpenGL  OpenGL  OpenGL  OpenGL  OpenGL
//---------------------------------------------------------------------------
//double OffsetVaweGL   = -1.0	;
static HGLRC ghRC     = 0	;
static HDC   ghDC     = 0	;
static HWND  HandleGL = 0	;
#define		GRID     1
#define		WAVE	 2
#define		CNL_1	11
#define		CNL_2	12
#define		CNL_3	13
#define		CNL_4	14
#define		SHP_OGL 20
#define		CUR_OGL 30
//---------------------------------------------------------------------------
BOOL 	bSetupPixelFormat(HDC hdc)     	;
//---------------------------------------------------------------------------
GLvoid DrawCursorsGL(TDsoCursor* Cur[],int CntCur)
{uint32_t lstGL = CUR_OGL	;

 if(TDsoCursor::flChng){ TDsoCursor::flChng = false	;
   if(glIsList(lstGL)) glDeleteLists(lstGL,1)	;

   glNewList(lstGL,GL_COMPILE)	;{
//     glLineWidth(2)		;
     glLineStipple(4,0xAAAA)	;//1,0x3F07)	;
     glEnable(GL_LINE_STIPPLE)	;
     for(int is=0;is<CntCur;is++) Cur[is]->DrawGL()	;
     glDisable(GL_LINE_STIPPLE)	;
//     glLineWidth(1)		;
   } glEndList()  		;
 }
}
//---------------------------------------------------------------------------
GLvoid  DrawShapesGL(TShapeGL* shp[],int CntShp)
{uint32_t lstGL = SHP_OGL	;

 if(TShapeGL::flChng){ TShapeGL::flChng = false	;
   if(glIsList(lstGL)) glDeleteLists(lstGL,1)	;

   glNewList(lstGL,GL_COMPILE)	;{
     for(int is=0;is<CntShp;is++) shp[is]->DrawGL()	;
   }glEndList()			;
 }
}
//---------------------------------------------------------------------------
GLvoid  DrawWaveGL(USHORT nCh,TParamsDrawWave* prms)
{
 uint32_t lst = CNL_1+nCh	;
 if(glIsList(lst)) glDeleteLists(lst,1)	;

// кол-во отсчётов в ViewOGL
 double	nDisDataLen = prms->nDisDataLen	;
 double stpX = prms->StpOGL	;// шаг по горизонтали
 double stpY = 2.0 / 255	;// Шаг по вертикали
 double ofst = prms->Offset_H	;
// double shrn = prms->dbHorizontal;// растяжка по горизонтали

 if(!prms->pSrcData) return	;

 glNewList(lst,GL_COMPILE)	;{
   glLineWidth(1)		;
   glBegin(GL_LINE_STRIP) 	;{
     glColorT(prms->clrRGB)	;

     for(ULONG ix=0;ix<prms->nSrcDataLen;ix++){
       glVertex2f((ix * stpX + ofst),prms->pSrcData[ix] * stpY-1.0)	;
     }

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

 glEnable(GL_BLEND);
 glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // очищаем буфер кадра

 glDisable(GL_BLEND)		;

 glPushMatrix()			;
 //-------

 for(int nCh=0;nCh<4;nCh++)
   if(glIsList(CNL_1+nCh)) glCallList(CNL_1+nCh);
  //-------
 if(glIsList(SHP_OGL)) glCallList(SHP_OGL)     	;
 if(glIsList(CUR_OGL)) glCallList(CUR_OGL)     	;
 if(glIsList(GRID   )) glCallList(GRID)		;

// glDisable(GL_ALPHA_TEST)	;

 glDisable(GL_COLOR_MATERIAL)	;
 glEnable (GL_COLOR_MATERIAL)	;
 glPopMatrix()			;

 SwapBuffers(ghDC)		; // выводим всё на экран
}
//---------------------------------------------------------------------------
GLvoid InitializeGL(HWND handle,GLsizei width, GLsizei height,TColor _color)
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

  Trgb rgb(_color)			;
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
GLvoid  DrawGridGL(USHORT cntGrid_H,USHORT cntGrid_V,USHORT nBright,USHORT IsGrid)
{
 float lenT1 = 1.0f, lenT2 = 0.015f	;
 glNewList(GRID,GL_COMPILE)	;{
   glLineWidth(1)		;
   glLineStipple(1,0xAAAA)	;//1,0x3F07)	;
   glEnable(GL_LINE_STIPPLE)	;

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
   glDisable(GL_LINE_STIPPLE)	;
 }glEndList()	;
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

