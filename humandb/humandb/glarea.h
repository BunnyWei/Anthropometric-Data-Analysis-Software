/**************************************************************
** �ļ�����
** Copyright (c) 2009 ********* MultiPower
** ������:xiejian 
** �� ��: 2009-07-30

** �޸���: 
** �� ��: 
** �޸�������

** �� ��: ���������֧��OpenGL������

** �汾��1.0
****************************************************************/


#ifndef GLAREA_H
#define GLAREA_H
#include <GL/glew.h>
#include <QTimer>
#include <QGLWidget>
#include <QTime>
#include <QtGui>
#include <vcg/space/plane3.h>
#include <vcg/space/line3.h>
#include <vcg/math/matrix44.h>
#include <wrap/gl/math.h>
#include <wrap/gl/trimesh.h>
#include <wrap/gui/trackball.h>

#include "GLLogStream.h"
#include "meshmodel.h"
#include "interfaces.h"

#define SSHOT_BYTES_PER_PIXEL 4

enum LightingModel{LDOUBLE,LFANCY};



class GLLightSetting
{
public:

	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];

	GLfloat ambientFancyBack[4];
	GLfloat diffuseFancyBack[4];
	GLfloat specularFancyBack[4];

	GLfloat ambientFancyFront[4];
	GLfloat diffuseFancyFront[4];
	GLfloat specularFancyFront[4];

	GLLightSetting()
	{
		// defaults
		ambient[0] = 0.2f; ambient[1] = 0.2f; ambient[2] = 0.2f; ambient[3] = 1.0f;
		diffuse[0] = 0.8f; diffuse[1] = 0.8f; diffuse[2] = 0.8f; diffuse[3] = 1.0f;
		specular[0] = 1.0f; specular[1] = 1.0f; specular[2] = 1.0f; specular[3] = 1.0f;

		ambientFancyBack[0] = 0.0f;
		ambientFancyBack[1] = 0.0f;
		ambientFancyBack[2] = 0.0f;
		ambientFancyBack[3] = 1.0f;

		diffuseFancyBack[0] = 1.0f;
		diffuseFancyBack[1] = 0.7f;
		diffuseFancyBack[2] = 0.7f;
		diffuseFancyBack[3] = 1.0f;

		specularFancyBack[0] = 1.0f;
		specularFancyBack[1] = 1.0f;
		specularFancyBack[2] = 1.0f;
		specularFancyBack[3] = 1.0f;

		ambientFancyFront[0] = 0.0f;
		ambientFancyFront[1] = 0.0f;
		ambientFancyFront[2] = 0.0f;
		ambientFancyFront[3] = 1.0f;

		diffuseFancyFront[0] = 0.7f;
		diffuseFancyFront[1] = 0.7f;
		diffuseFancyFront[2] = 1.0f;
		diffuseFancyFront[3] = 1.0f;

		specularFancyFront[0] = 1.0f;
		specularFancyFront[1] = 1.0f;
		specularFancyFront[2] = 1.0f;
		specularFancyFront[3] = 1.0f;
	}
};

class ColorSetting
{
public:
	
	vcg::Color4b bColorBottom;
	vcg::Color4b bColorTop;
	vcg::Color4b lColor;

	ColorSetting()
	{
		bColorBottom=vcg::Color4b(64,64,128,1);	
		bColorTop=vcg::Color4b(0,0,0,1);
		lColor=vcg::Color4b(128,16,16,1);

    //bColorBottom=Color4b(192,192,192,1);	
		//bColorTop=Color4b(255,255,255,1);
		//lColor=Color4b(128,16,16,1);
	};
};

class MyPoint
{
public:
	vcg::Point3f point; 
	QString pointName;
	int type;
	int meshID;
};


class MeshModel;
class GLArea : public QGLWidget
{
	Q_OBJECT

public:
	GLArea(QWidget *parent = 0);
	~GLArea();

private:
public:
	std::vector<MyPoint *> itemPointVector;
	int meshID;
	int showID;//��ʶ��ʾ����
	MeshDocument meshDoc;
	MeshModel *mm(){return meshDoc.mm();}
 
	vcg::Trackball trackball;
	vcg::Trackball trackball_light;
	GLLogStream log;
	short currLogLevel;

	QSize curSiz;
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	//QFont getFont() {return qFont;}

	QAction *getLastAppliedFilter()							{return lastFilterRef;}
	void		setLastAppliedFilter(QAction *qa)		{lastFilterRef = qa;}

	QString getFileName()							{return QString(mm()->fileName.c_str());}
	void		setFileName(QString name)	
    {
    mm()->fileName = qPrintable(name); 
		setWindowTitle(QFileInfo(name).fileName()+tr("[*]"));
		//layerDialog->setWindowTitle("Layer Dialog for "+QFileInfo(name).fileName());			
	  
    //ss.basename=QFileInfo(getFileName()).baseName().append("Snap");
	}

	short		getLogLevel()												{return currLogLevel;}
	void		setLogLevel(short lvl)	{currLogLevel = lvl;}
	
	RenderMode &  getCurrentRenderMode()		{return rm;}
	const ColorSetting& getCustomSetting()		const {return cs;}
	GLLightSetting getLightSettings(){return ls;}
	void setLightSettings(GLLightSetting glls){ls = glls;}
	//const SnapshotSetting& getSnapshotSetting()	{/*ss.dx=vpWidth; ss.dy=vpHeight;*/ return ss;}
	void updateFps(float deltaTime);
	
	void showTrackBall(bool b)		{trackBallVisible = b; updateGL();}
	bool isHelpVisible()      {return helpVisible;}  
	bool isTrackBallVisible()		{return trackBallVisible;}
	bool isDefaultTrackBall()   {return activeDefaultTrackball;}

	void toggleHelpVisible()      {helpVisible = !helpVisible; update();}  
	void setBackFaceCulling(bool enabled);
	void setCustomSetting(const ColorSetting & s);
	void setLight(bool state);
	void setLightMode(bool state,LightingModel lmode);
	void saveSnapshot();
	void setLightModel();
	void setView();
	void resetTrackBall();
	std::list<std::pair<QAction *,FilterParameterSet *> > iDecoratorsList;

	void drawPickedPoint();
	void drawLineDistance();
	void drawVerticalDistance();
	void drawXHorizontalDistance();
	void drawZHorizontalDistance();
	void drawCurveDistance(int size);
	void drawLoopDistance(int size);

	void setRenderer(MeshRenderInterface *rend, QAction *shader){	iRenderer = rend; currentShader = shader;}
	MeshRenderInterface * getRenderer() { return iRenderer; }

  // Edit Mode management
	// In the glArea we can have a active Editor that can toggled into a ''suspendeed'' state 
	// in which the mouse event are redirected back to the GLArea to drive the camera trackball
	// The decorate function of the current active editor is still called.
  // EndEdit is called only when you press again the same button or when you change editor.
	  
public slots:
	void updateTexture(); // slot for forcing the texture reload. 
		
	//slots for changing the draw rendering and texturing mode
	void setDrawMode(vcg::GLW::DrawMode mode); 
	void setColorMode(vcg::GLW::ColorMode mode);
	void setTextureMode(vcg::GLW::TextureMode mode);
	
	void endEdit(){	
		if(iEdit && currentEditor) 
		{
			iEdit->EndEdit(*mm(),this);
		}

		iEdit= 0; 
		currentEditor=0; 
		setCursorTrack(0); 
		
		update(); 
		emit updateMainWindowMenus();
	} 

	void setSelectionRendering(bool enabled);

	void suspendEditToggle()
	{	
		if(currentEditor==0) return;
		static QCursor qc;
		if(suspendedEditor) {
						suspendedEditor=false; 
						setCursor(qc); 
		}	else {
						suspendedEditor=true;
						qc=cursor(); 
						setCursorTrack(0); 						
		}
	}
  
signals:
	void updateMainWindowMenus(); //updates the menus of the meshlab MainWindow

  
public slots:

	// Called when we change layer, notifies the edit tool if one is open
	void setCurrentlyActiveLayer(int meshId);
	
public:
	
	//call when the editor changes
	void setCurrentEditAction(QAction *editAction);
	
	//get the currently active edit action
	QAction * getCurrentEditAction() { return currentEditor; }
	
	//get the currently active mesh editor
	MeshEditInterface * getCurrentMeshEditor() { return iEdit; }
	
	//see if this glAarea has a MESHEditInterface for this action
	bool editorExistsForAction(QAction *editAction){ return actionToMeshEditMap.contains(editAction); }
	
	//add a MeshEditInterface for the given action
	void addMeshEditor(QAction *editAction, MeshEditInterface *editor){ actionToMeshEditMap.insert(editAction, editor); }

	MeshEditInterface* getMeshEditor(QAction *editAction) {return actionToMeshEditMap.value(editAction);}
	
	void closeEvent(QCloseEvent *event);
	float lastRenderingTime() { return lastTime;}
	void drawGradient();
	void drawLight();
	float getFov() { return fov; }
	
// the following pairs of slot/signal implements a very simple message passing mechanism.
// a widget that has a pointer to the glarea call the sendViewDir() slot and 
// setup a connect to recive the transmitViewDir signal that actually contains the point3f.
// This mechanism is used to get the view direction/position and picking point on surface in the filter parameter dialog.
// See the Point3fWidget code.
signals :
		void transmitViewDir(QString name, vcg::Point3f dir);
		void transmitViewPos(QString name, vcg::Point3f dir);
		void transmitSurfacePos(QString name,vcg::Point3f dir);
		void transmitCameraPos(QString name,vcg::Point3f dir);
public slots:
		void sendViewPos(QString name);
		void sendSurfacePos(QString name);
		void sendViewDir(QString name);
		void sendCameraPos(QString name);


public:
	vcg::Point3f getViewDir(); 
	bool	infoAreaVisible;		// Draws the lower info area ?
	bool  suspendedEditor;
protected:

	FilterParameterSet prefs;
	void initPreferences();
	void initializeGL();
	void initTexture();
	void displayInfo();
	void displayHelp();

	QString GetMeshInfoString();
	void paintGL();
	void resizeGL(int width, int height);
	void keyReleaseEvent ( QKeyEvent * e ); 
	void keyPressEvent ( QKeyEvent * e ); 
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent ( QMouseEvent * event ) ;
	void wheelEvent(QWheelEvent*e);
	void tabletEvent(QTabletEvent *e);
	bool drawSelection;

	void hideEvent(QHideEvent * event);

private:
	QMap<QString,QCursor> curMap;
	void pasteTile();
	void setTiledView(GLdouble fovY, float viewRatio, float fAspect, GLdouble zNear, GLdouble zFar, float cameraDist);
    
	bool  helpVisible;				// Help on screen	
	bool	trackBallVisible;		// Draws the trackball ?
	bool  activeDefaultTrackball; // keep track on active trackball
	bool	hasToUpdateTexture;			// has to reload textures at the next redraw
	bool  hasToPick;							// has to pick during the next redraw.
	bool hasToGetPickPos;							// if we are waiting for a double click for getting a surface position that has to be sent back using signal/slots (for parameters)
	QString nameToGetPickPos;         // the name of the parameter that has asked for the point on the surface 
	
	vcg::Point2i pointToPick;

	//shader support
	MeshRenderInterface *iRenderer;
	QAction *currentShader;
	QAction *lastFilterRef; // reference to last filter applied
	QFont	qFont;			//font settings

	// Editing support
	MeshEditInterface *iEdit;
	QAction *currentEditor;
	QAction *suspendedEditRef; // reference to last Editing Mode Used 
	QMap<QAction*, MeshEditInterface*> actionToMeshEditMap;

	//the last model that start edit was called with
	MeshModel *lastModelEdited;
	
public:
	RenderMode rm;
	ColorSetting cs;
	GLLightSetting ls;
	// view setting variables
	float fov;
	float clipRatioFar;
	float clipRatioNear;
	float nearPlane;
	float farPlane;
  float pointSize;
private:
	float cfps;
	float lastTime;
	
	//SnapshotSetting ss;
	QImage snapBuffer;
	bool takeSnapTile;
  
	enum AnimMode { AnimNone, AnimSpin, AnimInterp};
	AnimMode animMode; 
	int tileCol, tileRow, totalCols, totalRows;
	void setCursorTrack(vcg::TrackMode *tm);

};


#endif