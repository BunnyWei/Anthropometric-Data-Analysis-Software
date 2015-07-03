/**************************************************************
** 文件名：
** Copyright (c) 2009 ********* MultiPower
** 创建人:xiejian 
** 日 期: 2009-07-30

** 修改人: 
** 日 期: 
** 修改描述：

** 描 述: 定义程序中openGl操作区域的相关操作

** 版本：1.0
****************************************************************/


#include <GL/glew.h>
#include <QtGui>

// widget capace di fare rendering di un Modello
#include <vcg/space/box3.h>
#include <wrap/gl/space.h>
#include "meshmodel.h"
#include "interfaces.h"
#include "glarea.h"
#include "mainwindow.h"

#include <wrap/gl/picking.h>
#include <wrap/qt/trackball.h>
using namespace std;
using namespace vcg;

GLArea::GLArea(QWidget *parent)
: QGLWidget(parent)
{
	showID = 1;
	animMode=AnimNone;
	iRenderer=0; //Shader support
	iEdit=0;
	currentEditor=0;
	suspendedEditor=false;
	lastModelEdited = 0;
	cfps=0;
	lastTime=0;
	hasToPick=false;
	hasToGetPickPos=false;
	hasToUpdateTexture=false;
	helpVisible=false;
	takeSnapTile=false;
	activeDefaultTrackball=true;
	infoAreaVisible = true;
	trackBallVisible = true;
	currentShader = NULL;
	lastFilterRef = NULL;
	//lastEditRef = NULL;
	currLogLevel = -1;
	setAttribute(Qt::WA_DeleteOnClose,true);
	fov = 60;
	clipRatioFar = 1;
	clipRatioNear = 1;
	nearPlane = .2f;
	farPlane = 5.f;
	pointSize = 2.0f;

	/*getting the meshlab MainWindow from parent, which is QWorkspace.
	*note as soon as the GLArea is added as Window to the QWorkspace the parent of GLArea is a QWidget,
	*which takes care about the window frame (its parent is the QWorkspace again).
	*/
	MainWindow* mainwindow = dynamic_cast<MainWindow*>(parent->parentWidget());
	//connecting the MainWindow Slots to GLArea signal (simple passthrough)
	if(mainwindow != NULL){
		connect(this,SIGNAL(updateMainWindowMenus()),mainwindow,SLOT(updateMenus()));
	}else{
		qDebug("The parent of the GLArea parent is not a pointer to the meshlab MainWindow.");
	}
}

void GLArea::initPreferences()
{
	QSettings settings;
	prefs.clear();
	prefs.addColor("BackgroundTop",    settings.value("BackgroundTop").value<QColor>(), "Top Background Color", "");
	prefs.addColor("BackgroundBottom", settings.value("BackgroundBottom").value<QColor>(), "Bottom Background Color", "");
}

GLArea::~GLArea()
{
	// warn any iRender plugin that we're deleting glarea
	//if (iRenderer)
	//	iRenderer->Finalize(currentShader, meshDoc, this);
}


/*
This member returns the information of the Mesh in terms of VC,VQ,FC,FQ,WT
where:
VC = VertColor,VQ = VertQuality,FC = FaceColor,FQ = FaceQuality,WT = WedgTexCoord
*/
QString GLArea::GetMeshInfoString()
{
	QString info;
	if(mm()->hasDataMask(MeshModel::MM_VERTQUALITY) ) {info.append("VQ ");}
	if(mm()->hasDataMask(MeshModel::MM_VERTCOLOR) ) {info.append("VC ");}
	if(mm()->hasDataMask(MeshModel::MM_VERTRADIUS) ) {info.append("VR ");}
	if(mm()->hasDataMask(MeshModel::MM_VERTCURV) ) {info.append("VK ");}
	if(mm()->hasDataMask(MeshModel::MM_VERTCURVDIR) ) {info.append("VD ");}
	if(mm()->hasDataMask(MeshModel::MM_FACECOLOR) ) {info.append("FC ");}
	if(mm()->hasDataMask(MeshModel::MM_FACEQUALITY) ) {info.append("FQ ");}
	if(mm()->hasDataMask(MeshModel::MM_WEDGTEXCOORD) ) {info.append("WT ");}
	if(mm()->hasDataMask(MeshModel::MM_CAMERA) ) {info.append("MC ");}

	return info;
}

QSize GLArea::minimumSizeHint() const {return QSize(400,300);}
QSize GLArea::sizeHint() const				{return QSize(400,300);}


void GLArea::initializeGL()
{
	glShadeModel(GL_SMOOTH);
	glPixelStorei(GL_PACK_ROW_LENGTH, 0);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	static float diffuseColor[]={1.0,1.0,1.0,1.0};
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,diffuseColor);
	trackball.center=Point3f(0, 0, 0);
	trackball.radius= 1;

	trackball_light.center=Point3f(0, 0, 0);
	trackball_light.radius= 1;
	GLenum err = glewInit();
	if (err != GLEW_OK ) {
		assert(0);
	}
}

//void GLArea::pasteTile()
//{
//	glPushAttrib(GL_ENABLE_BIT);
//	QImage tileBuffer=grabFrameBuffer(true).mirrored(false,true);
//
//	if (snapBuffer.isNull())
//		snapBuffer = QImage(tileBuffer.width() * ss.resolution, tileBuffer.height() * ss.resolution, tileBuffer.format());
//
//	uchar *snapPtr = snapBuffer.bits() + (tileBuffer.bytesPerLine() * tileCol) + ((totalCols * tileRow) * tileBuffer.numBytes());
//	uchar *tilePtr = tileBuffer.bits();
//
//	for (int y=0; y < tileBuffer.height(); y++)
//	{
//		memcpy((void*) snapPtr, (void*) tilePtr, tileBuffer.bytesPerLine());
//		snapPtr+=tileBuffer.bytesPerLine() * totalCols;
//		tilePtr+=tileBuffer.bytesPerLine();
//	}
//
//	tileCol++;
//
//	if (tileCol >= totalCols)
//	{
//		tileCol=0;
//		tileRow++;
//
//		if (tileRow >= totalRows)
//		{
//			QString outfile=QString("%1/%2%3.png")
//				.arg(ss.outdir)
//				.arg(ss.basename)
//				.arg(ss.counter++,2,10,QChar('0'));
//			bool ret = (snapBuffer.mirrored(false,true)).save(outfile,"PNG");
//			if (ret) log.Logf(GLLogStream::SYSTEM, "Snapshot saved to %s",outfile.toLocal8Bit().constData());
//			else log.Logf(GLLogStream::WARNING,"Error saving %s",outfile.toLocal8Bit().constData());
//
//			takeSnapTile=false;
//			snapBuffer=QImage();
//		}
//	}
//	update();
//	glPopAttrib();
//}



void GLArea::drawGradient()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1,1,-1,1,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_TRIANGLE_STRIP);
	glColor(cs.bColorTop);  	glVertex2f(-1, 1);
	glColor(cs.bColorBottom);	glVertex2f(-1,-1);
	glColor(cs.bColorTop);		glVertex2f( 1, 1);
	glColor(cs.bColorBottom);	glVertex2f( 1,-1);
	glEnd();

	glPopAttrib();
	glPopMatrix(); // restore modelview
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void GLArea::drawLight()
{
	// ============== LIGHT TRACKBALL ==============
	// Apply the trackball for the light direction
	glPushMatrix();
	trackball_light.GetView();
	trackball_light.Apply(!(isDefaultTrackBall()));

	static float lightPosF[]={0.0,0.0,1.0,0.0};
	glLightfv(GL_LIGHT0,GL_POSITION,lightPosF);
	static float lightPosB[]={0.0,0.0,-1.0,0.0};
	glLightfv(GL_LIGHT1,GL_POSITION,lightPosB);

	if (!(isDefaultTrackBall()))
	{
		glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
		glColor3f(1,1,0);
		glDisable(GL_LIGHTING);
		const unsigned int lineNum=3;
		glBegin(GL_LINES);
		for(unsigned int i=0;i<=lineNum;++i)
			for(unsigned int j=0;j<=lineNum;++j) {
				glVertex3f(-1.0f+i*2.0/lineNum,-1.0f+j*2.0/lineNum,-2);
				glVertex3f(-1.0f+i*2.0/lineNum,-1.0f+j*2.0/lineNum, 2);
			}
			glEnd();
			glPopAttrib();
	}
	glPopMatrix();

}

void GLArea::paintGL()
{
	QTime time;
	time.start();
	initTexture();
	glClearColor(1.0,1.0,1.0,0.0);	//vannini: alpha was 1.0
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setView();  // Set Modelview and Projection matrix
	drawGradient();  // draws the background
	drawLight();

	glPushMatrix();

	// Finally apply the Trackball for the model
	trackball.GetView();
	trackball.Apply(false);
	glPushMatrix();

	//glScale(d);
	//	glTranslate(-FullBBox.Center());
	setLightModel(); //响应不同的light的模式对应的不同绘制

	// Set proper colorMode
	if(rm.colorMode != GLW::CMNone)
	{
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	}
	else glColor(Color4b::LightGray);

	if(rm.backFaceCull) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);

	if(!meshDoc.busy)
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);

		if (iRenderer)
		{
			iRenderer->Render(currentShader, meshDoc, rm, this);
		}
		else 
		{
			if (1 == showID)
			{
				MeshModel * mp;
				int size = itemPointVector.size();
				if (0 == size)
				{
					mp = meshDoc.getMesh(0);
				}
				else
				{
					int temp = itemPointVector.at(0)->meshID;
					if (temp != 0)
						mp = meshDoc.getMesh(temp-1);
				}
				mp->Render(rm.drawMode,rm.colorMode,rm.textureMode);
				//foreach(MeshModel * mp, meshDoc.meshList)
				//{
				//	if(mp->visible)
				//	{
				//		//渲染模型
				//		mp->Render(rm.drawMode,rm.colorMode,rm.textureMode);
				//	}
				//}
			}//end if (1 == showID)
			else if (2 == showID)
			{
				MeshModel * mp = meshDoc.getMesh( meshDoc.size() - 1 );
				mp->Render(rm.drawMode,rm.colorMode,rm.textureMode);
			}
			else if (3 == showID)
			{
				//当没有找到模型时，什么也不显示
			}
			
		}	

		if (1 == showID)
			drawPickedPoint();
		if(iEdit) {
			iEdit->Decorate(*mm(),this);
		}

		// Draw the selection
		if(rm.selectedFaces)  mm()->RenderSelectedFaces();
		pair<QAction *,FilterParameterSet *> p;
		foreach(p , iDecoratorsList)
		{
			MeshDecorateInterface * decorInterface = qobject_cast<MeshDecorateInterface *>(p.first->parent());
			decorInterface->Decorate(p.first,*mm(),p.second,this,qFont);
		}

		glPopAttrib();
	} ///end if busy

	glPopMatrix(); // We restore the state to immediately after the trackball (and before the bbox scaling/translating)

	if(trackBallVisible && !takeSnapTile && !(iEdit && !suspendedEditor)) 
		trackball.DrawPostApply();

	// The picking of the surface position has to be done in object space, 
	// so after trackball transformation (and before the matrix associated to each mesh);		
	if(hasToPick && hasToGetPickPos)
	{
		Point3f pp;
		hasToPick=false;
		if(Pick<Point3f>(pointToPick[0],pointToPick[1],pp))
		{
			emit transmitSurfacePos(nameToGetPickPos, pp);
			hasToGetPickPos=false;
		}
	}
	glPopMatrix(); // We restore the state to immediately before the trackball

	// Double click move picked point to center
	// It has to be done in the before trackball space (we MOVE the trackball itself...)
	if(hasToPick && !hasToGetPickPos)
	{ 
		Point3f pp;
		hasToPick=false;
		if(Pick<Point3f>(pointToPick[0],pointToPick[1],pp))
		{
			trackball.Translate(-pp);
			trackball.Scale(1.25f);
			QCursor::setPos(mapToGlobal(QPoint(width()/2+2,height()/2+2)));
		}
	}

	// ...and take a snapshot
	//if (takeSnapTile) pasteTile(); 

	// Draw the log area background
	// on the bottom of the glArea
	if(infoAreaVisible)
	{
		displayInfo();
		updateFps(time.elapsed());
	}

	// Finally display HELP if requested
	if (isHelpVisible()) displayHelp();

	int error = glGetError();
	if(error) {
		log.Logf(GLLogStream::WARNING,"There are gl errors");
	}
}

/*
这里就是模型区域中的状态信息的显示；
*/
void GLArea::displayInfo()
{
	// Enter in 2D screen Mode again
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1,1,-1,1,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	qFont.setStyleStrategy(QFont::NoAntialias);
	qFont.setFamily("Helvetica");
	qFont.setPixelSize(12);

	glBlendFunc(GL_ONE,GL_SRC_ALPHA);
	cs.lColor.V(3) = 128;	// set half alpha value
	glColor(cs.lColor);
	int lineNum =4;
	float lineSpacing = qFont.pixelSize()*1.5f;
	float barHeight = -1 + 2.0*(lineSpacing*(lineNum+.25))/float(curSiz.height());


	glBegin(GL_QUADS);
	glVertex2f(-1.f,barHeight);     glVertex2f(-1.f,-1.f);
	glVertex2f( 1.f,-1.f);          glVertex2f( 1.f,barHeight);
	glEnd();

	// First the LOG
	glColor4f(1,1,1,1);

	float middleCol=curSiz.width()*0.40;
	float rightCol=curSiz.width()*0.85;
	float startPos = curSiz.height()-(5+lineSpacing*(lineNum));

	renderText(10,startPos+ 1*lineSpacing,tr("模型信息"),qFont); //LOG MESSAGE
	glColor4f(1,1,0,1);
	renderText(10,startPos+ 3*lineSpacing,tr("按着ctrl键拖动鼠标移动模型"),qFont); //LOG MESSAGE
	log.glDraw(this,currLogLevel,3,lineSpacing,qFont);

	glColor4f(1,1,1,1);

	if(meshDoc.size()==1)
	{
		renderText(middleCol,startPos+ 1*lineSpacing,tr("点数: %1").arg(mm()->cm.vn),qFont); //Vertices
		renderText(middleCol,startPos+ 2*lineSpacing,tr("面数: %1").arg(mm()->cm.fn),qFont); //Faces
	}
	else
	{
		renderText(middleCol,startPos+ 1*lineSpacing,tr("<%1>").arg(QFileInfo(mm()->fileName.c_str()).fileName()),qFont);
		renderText(middleCol,startPos+ 2*lineSpacing,tr("点数: %1 (%2)").arg(mm()->cm.vn).arg(meshDoc.vn()),qFont);
		renderText(middleCol,startPos+ 3*lineSpacing,tr("面数: %1 (%2)").arg(mm()->cm.fn).arg(meshDoc.fn()),qFont);
	}
	if(rm.selectedFaces || mm()->cm.sfn>0)
		renderText(middleCol,startPos+ 4*lineSpacing,tr("Selected: %1").arg(mm()->cm.sfn),qFont);
	renderText(rightCol,startPos+ 4*lineSpacing,GetMeshInfoString(),qFont);

	if(fov>5) renderText(rightCol,startPos+1*lineSpacing,QString("FOV: ")+QString::number((int)fov,10),qFont);
	else renderText(rightCol,startPos+1*lineSpacing,QString("FOV: Ortho"),qFont);
	if ((cfps>0) && (cfps<500))
		renderText(rightCol,startPos+2*lineSpacing,QString("刷新率: %1").arg(cfps,7,'f',1),qFont); //FPS
	if ((clipRatioNear!=1) || (clipRatioFar!=1))
		renderText(rightCol,startPos+3*lineSpacing,QString("Clipping: N:%1 F:%2").arg(clipRatioNear,7,'f',1).arg(clipRatioFar,7,'f',1),qFont);


	// Closing 2D
	glPopAttrib();
	glPopMatrix(); // restore modelview
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}


void GLArea::resizeGL(int _width, int _height)
{
	glViewport(0,0, _width, _height);
	curSiz.setWidth(_width);
	curSiz.setHeight(_height);
}


void GLArea::displayHelp()
{
	glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT );
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_TRIANGLE_STRIP);
	glColor4f(.5f,.8f,1.f,.6f); glVertex2f(-1, 1);
	glColor4f(.0f,.0f,.0f,.0f); glVertex2f(-1,-1);
	glColor4f(.5f,.8f,1.f,.6f); glVertex2f(-.5f,1);
	glColor4f(.0f,.0f,.0f,.0f); glVertex2f(-.5f,-1);
	glEnd();


	float fontSpacingV = (curSiz.height()*.01f)+3;
	float hPosition = curSiz.width()*.1f;
	glColor(Color4b::White);
	//qFont.setBold(true);
	renderText(2+hPosition-(qFont.pointSize()*9),1.5*fontSpacingV,QString("MeshLab Quick Help"),qFont);qFont.setBold(false);
	renderText(2,3*fontSpacingV,QString("Drag:"),qFont);								renderText(hPosition,3*fontSpacingV,QString("Rotate"),qFont);
	renderText(2,4.5*fontSpacingV,QString("Ctrl-Drag:"),qFont);					renderText(hPosition,4.5*fontSpacingV,QString("Pan"),qFont);
	renderText(2,6*fontSpacingV,QString("Shift-Drag:"),qFont);					renderText(hPosition,6*fontSpacingV,QString("Zoom"),qFont);
	renderText(2,7.5*fontSpacingV,QString("Alt-Drag:"),qFont);					renderText(hPosition,7.5*fontSpacingV,QString("Z-Panning"),qFont);
	renderText(2,9*fontSpacingV,QString("Ctrl-Shift-Drag:"),qFont);			renderText(hPosition,9*fontSpacingV,QString("Rotate light"),qFont);
	renderText(2,10.5*fontSpacingV,QString("Wheel:"),qFont);						renderText(hPosition,10.5*fontSpacingV,QString("Zoom"),qFont);
	renderText(2,12*fontSpacingV,QString("Shift-Wheel:"),qFont);				renderText(hPosition,12*fontSpacingV,QString("Change perspective"),qFont);
	renderText(2,13.5*fontSpacingV,QString("Ctrl-Wheel:"),qFont);				renderText(hPosition,13.5*fontSpacingV,QString("Move far clipping plane"),qFont);
	renderText(2,15*fontSpacingV,QString("Ctrl-Shift-Wheel:"),qFont);		renderText(hPosition,15*fontSpacingV,QString("Move near clipping plane"),qFont);
	renderText(2,16.5*fontSpacingV,QString("Double Click:"),qFont);			renderText(hPosition,16.5*fontSpacingV,QString("Center on mouse"),qFont);
	renderText(2,18*fontSpacingV,QString("F1:"),qFont);									renderText(hPosition,18*fontSpacingV,QString("Toggle this help"),qFont);
	renderText(2,19.5*fontSpacingV,QString("Alt+enter:"),qFont);						renderText(hPosition,19.5*fontSpacingV,QString("Enter/Exit fullscreen mode"),qFont);
	glPopAttrib();
}


void GLArea::setCurrentlyActiveLayer(int meshId)
{
	//qDebug() << "setCurrent: " << meshId;

	//if we have an edit tool open, notify it that the current layer has changed
	if(iEdit)
	{
		assert(lastModelEdited);  //if there is an editor last model edited should always be set when start edit is called
		iEdit->LayerChanged(meshDoc, *lastModelEdited, this);

		//now update the last model edited
		//TODO this is not the best design....   iEdit should maybe keep track of the model on its own
		lastModelEdited = meshDoc.mm();
	}
}

void GLArea::setCurrentEditAction(QAction *editAction)
{
	assert(editAction);
	currentEditor = editAction;

	iEdit = actionToMeshEditMap.value(currentEditor);
	qDebug("################# iEdit added###############");
	assert(iEdit);
	lastModelEdited = meshDoc.mm();
	if (!iEdit->StartEdit(meshDoc, this))
	{
		//iEdit->EndEdit(*(meshDoc.mm()), this);
		endEdit();
	}
	else
		log.Logf(GLLogStream::SYSTEM,"Started Mode %s", qPrintable(currentEditor->text()));
}


void GLArea::closeEvent(QCloseEvent *event)
{
	bool close = true;
	if(isWindowModified())
	{
		QMessageBox::StandardButton ret=QMessageBox::question(
			this,  tr("MeshLab"), tr("File '%1' modified.\n\nClose without saving?").arg(getFileName()),
			QMessageBox::Yes|QMessageBox::No,
			QMessageBox::No);
		if(ret==QMessageBox::No)
		{
			close = false;	// don't close please!
			event->ignore();
			return;
		}
	}
	if(getCurrentEditAction()) endEdit();
	event->accept();
}

void GLArea::keyReleaseEvent ( QKeyEvent * e )
{
	e->ignore();
	if(iEdit && !suspendedEditor)  iEdit->keyReleaseEvent(e,*mm(),this);
	else{
		if(e->key()==Qt::Key_Control) trackball.ButtonUp(QT2VCG(Qt::NoButton, Qt::ControlModifier ) );
		if(e->key()==Qt::Key_Shift) trackball.ButtonUp(QT2VCG(Qt::NoButton, Qt::ShiftModifier ) );
		if(e->key()==Qt::Key_Alt) trackball.ButtonUp(QT2VCG(Qt::NoButton, Qt::AltModifier ) );
	}
}

void GLArea::keyPressEvent ( QKeyEvent * e )
{
	e->ignore();
	if(iEdit && !suspendedEditor)  iEdit->keyPressEvent(e,*mm(),this);
	else{
		if(e->key()==Qt::Key_Control) trackball.ButtonDown(QT2VCG(Qt::NoButton, Qt::ControlModifier ) );
		if(e->key()==Qt::Key_Shift) trackball.ButtonDown(QT2VCG(Qt::NoButton, Qt::ShiftModifier ) );
		if(e->key()==Qt::Key_Alt) trackball.ButtonDown(QT2VCG(Qt::NoButton, Qt::AltModifier ) );
	}
}

// 鼠标按下事件
void GLArea::mousePressEvent(QMouseEvent*e)
{
	e->accept();
	setFocus();

	// 如果有激活的插件，且不处于not editing状态，如果不是鼠标中键按下的，则把这个事件传递给插件，即调用插件的mousePressEvent方法
	if( (iEdit && !suspendedEditor) && !(e->buttons() & Qt::MidButton) )
		iEdit->mousePressEvent(e,*mm(),this);
	else {
		// Ctrl + Shift + 左键，禁用默认的trackball, 激活发光的trackball
		if ((e->modifiers() & Qt::ShiftModifier) && (e->modifiers() & Qt::ControlModifier) && (e->button()==Qt::LeftButton) )
			activeDefaultTrackball=false;
		else activeDefaultTrackball=true;

		if (isDefaultTrackBall())
		{
			// Ctrl + 左键，只移动模型
			if(QApplication::keyboardModifiers () & Qt::Key_Control) 
				trackball.ButtonDown(QT2VCG(Qt::NoButton, Qt::ControlModifier));
			else 
				trackball.ButtonUp(QT2VCG(Qt::NoButton, Qt::ControlModifier ));
			// Shift + 左键，放大和缩小模型
			if(QApplication::keyboardModifiers () & Qt::Key_Shift) 
				trackball.ButtonDown(QT2VCG(Qt::NoButton, Qt::ShiftModifier ));
			else 
				trackball.ButtonUp(QT2VCG(Qt::NoButton, Qt::ShiftModifier ));
			// Alt + 左键，暂时不知道干嘛
			if(QApplication::keyboardModifiers () & Qt::Key_Alt) 
				trackball.ButtonDown(QT2VCG(Qt::NoButton, Qt::AltModifier ) );
			else 
				trackball.ButtonUp(QT2VCG(Qt::NoButton, Qt::AltModifier ) );
			trackball.MouseDown(e->x(),height()-e->y(), QT2VCG(e->button(), e->modifiers() ) );
		}
		// 只有鼠标左键
		else trackball_light.MouseDown(e->x(),height()-e->y(), QT2VCG(e->button(), Qt::NoModifier ) );
	}
	update();
}


//鼠标移动事件
void GLArea::mouseMoveEvent(QMouseEvent*e)
{
	if( (iEdit && !suspendedEditor) && !(e->buttons() & Qt::MidButton) )
		iEdit->mouseMoveEvent(e,*mm(),this);
	else {
		if (isDefaultTrackBall())
		{
			trackball.MouseMove(e->x(),height()-e->y());	/* 默认的trackball跟着鼠标移动 */
			setCursorTrack(trackball.current_mode);	/* 设置光标的形状 */
		}
		else trackball_light.MouseMove(e->x(),height()-e->y());	/* 当Ctrl + Shift + 左键一起按时，发光的trackball_light跟着鼠标移动 */
		update();
	}
}
// When mouse is released we set the correct mouse cursor
// 鼠标释放事件
void GLArea::mouseReleaseEvent(QMouseEvent*e)
{
	//clearFocus();
	activeDefaultTrackball=true;	/* 鼠标一释放，就激活默认的trackball */
	if( (iEdit && !suspendedEditor) && (e->button() != Qt::MidButton) )
		iEdit->mouseReleaseEvent(e,*mm(),this);
	else {
		if (isDefaultTrackBall()) trackball.MouseUp(e->x(),height()-e->y(), QT2VCG(e->button(), e->modifiers() ) );
		else trackball_light.MouseUp(e->x(),height()-e->y(), QT2VCG(e->button(),e->modifiers()) );
		setCursorTrack(trackball.current_mode);	/* 改变鼠标的形状 */
	}

	update();
}

//Processing of tablet events, interesting only for painting plugins
void GLArea::tabletEvent(QTabletEvent*e)
{
	if(iEdit && !suspendedEditor) iEdit->tabletEvent(e,*mm(),this);
	else e->ignore();
}

// 鼠标滚轮事件
void GLArea::wheelEvent(QWheelEvent*e)
{
	const int WHEEL_STEP = 120;
	float notch = e->delta()/ float(WHEEL_STEP);
	switch(e->modifiers())
	{
	case Qt::ShiftModifier + Qt::ControlModifier:	/* Ctrl + Shift + 滚轮 */
		clipRatioFar  *= powf(1.2f, notch); break;	
	case Qt::ControlModifier:						/* Ctrl + 滚轮 */
		clipRatioNear *= powf(1.2f, notch); break;
	case Qt::AltModifier:							/* Alt + 滚轮 */
		pointSize = math::Clamp(pointSize*powf(1.2f, notch),0.01f,150.0f);
		foreach(MeshModel * mp, meshDoc.meshList)
			mp->glw.SetHintParamf(GLW::HNPPointSize,pointSize);
		break;
	case Qt::ShiftModifier:							/* Shift +　滚轮　*/
		fov = math::Clamp(fov*powf(1.2f,notch),5.0f,90.0f); break;
	default:
		trackball.MouseWheel( e->delta()/ float(WHEEL_STEP));	/* 只有滚轮，放大和缩小trackball */
		break;
	}
	updateGL();
}

// 鼠标双击事件
void GLArea::mouseDoubleClickEvent ( QMouseEvent * e )
{
	hasToPick=true;
	pointToPick=Point2i(e->x(),height()-e->y());
	updateGL();
}

void GLArea::setCursorTrack(vcg::TrackMode *tm)
{
	//static QMap<QString,QCursor> curMap;
	if(curMap.isEmpty())
	{
		curMap[QString("")]=QCursor(Qt::ArrowCursor);
		curMap["SphereMode"]=QCursor(QPixmap(":/images/cursors/plain_trackball.png"),1,1);
		curMap["PanMode"]=QCursor(QPixmap(":/images/cursors/plain_pan.png"),1,1);
		curMap["ScaleMode"]=QCursor(QPixmap(":/images/cursors/plain_zoom.png"),1,1);
	}
	if(tm) setCursor(curMap[tm->Name()]);
	else setCursor(curMap[""]);

}

void GLArea::setDrawMode(vcg::GLW::DrawMode mode)
{
	rm.drawMode = mode;
	updateGL();
}


void GLArea::setColorMode(vcg::GLW::ColorMode mode)
{
	rm.colorMode = mode;
	updateGL();
}
void GLArea::updateTexture()
{
	hasToUpdateTexture = true;
}

// Texture loading done during the first paint.
void GLArea::initTexture()
{
	if(hasToUpdateTexture)
	{
		mm()->glw.TMId.clear();
		qDebug("Beware: deleting the texutres could lead to problems for shared textures.");
		hasToUpdateTexture = false;
	}

	if(!mm()->cm.textures.empty() && mm()->glw.TMId.empty()){
		glEnable(GL_TEXTURE_2D);
		GLint MaxTextureSize;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE,&MaxTextureSize);

		for(unsigned int i =0; i< mm()->cm.textures.size();++i){
			QImage img, imgScaled, imgGL;

			const char* str_TMP = mm()->cm.textures[i].c_str();
			bool res = img.load(mm()->cm.textures[i].c_str());
			// image has to be scaled to a 2^n size. We choose the first 2^N <= picture size.
			int bestW=pow(2.0,floor(::log(double(img.width() ))/::log(2.0)));
			int bestH=pow(2.0,floor(::log(double(img.height()))/::log(2.0)));
			while(bestW>MaxTextureSize) bestW /=2;
			while(bestH>MaxTextureSize) bestH /=2;

			log.Log(GLLogStream::SYSTEM,"Loading textures");
			log.Logf(GLLogStream::SYSTEM,"	Texture[ %3i ] =  '%s' ( %6i x %6i ) -> ( %6i x %6i )",	i,mm()->cm.textures[i].c_str(), img.width(), img.height(),bestW,bestH);
			imgScaled=img.scaled(bestW,bestH,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
			imgGL=convertToGLFormat(imgScaled);
			mm()->glw.TMId.push_back(0);
			glGenTextures( 1, (GLuint*)&(mm()->glw.TMId.back()) );
			glBindTexture( GL_TEXTURE_2D, mm()->glw.TMId.back() );
			glTexImage2D( GL_TEXTURE_2D, 0, 3, imgGL.width(), imgGL.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imgGL.bits() );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imgGL.width(), imgGL.height(), GL_RGBA, GL_UNSIGNED_BYTE, imgGL.bits() );

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			qDebug("      	will be loaded as GL texture id %i  ( %i x %i )",mm()->glw.TMId.back() ,imgGL.width(), imgGL.height());
		}
	}
	glDisable(GL_TEXTURE_2D);
}

void GLArea::setTextureMode(vcg::GLW::TextureMode mode)
{
	rm.textureMode = mode;
	updateGL();
}

void GLArea::setLight(bool state)
{
	rm.lighting = state;
	updateGL();
}

void GLArea::setLightMode(bool state,LightingModel lmode)
{
	switch(lmode)
	{
	case LDOUBLE:		rm.doubleSideLighting = state;	break;
	case LFANCY:		rm.fancyLighting = state; break;
	}
	updateGL();
}

void GLArea::setBackFaceCulling(bool enabled)
{
	rm.backFaceCull = enabled;
	updateGL();
}

void GLArea::setSelectionRendering(bool enabled)
{
	rm.selectedFaces = enabled;
	updateGL();
}

void GLArea::setLightModel()
{
	glDisable(GL_LIGHTING);
	if (rm.lighting)
	{
		glEnable(GL_LIGHTING);

		if (rm.doubleSideLighting)
			glEnable(GL_LIGHT1);
		else
			glDisable(GL_LIGHT1);

		if(rm.fancyLighting)
		{
			glLightfv(GL_LIGHT0, GL_AMBIENT, ls.ambientFancyFront);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, ls.diffuseFancyFront);
			glLightfv(GL_LIGHT0, GL_SPECULAR, ls.specularFancyFront);

			glLightfv(GL_LIGHT1, GL_AMBIENT, ls.ambientFancyBack);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, ls.diffuseFancyBack);
			glLightfv(GL_LIGHT1, GL_SPECULAR, ls.specularFancyBack);
		}
		else
		{
			glLightfv(GL_LIGHT0, GL_AMBIENT, ls.ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, ls.diffuse);
			glLightfv(GL_LIGHT0, GL_SPECULAR, ls.specular);

			glLightfv(GL_LIGHT1, GL_AMBIENT, ls.ambient);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, ls.diffuse);
			glLightfv(GL_LIGHT1, GL_SPECULAR, ls.specular);
		}
	}
}


void GLArea::setCustomSetting(const ColorSetting & s)
{
	cs.bColorBottom = s.bColorBottom;
	cs.bColorTop = s.bColorTop;
	cs.lColor = s.lColor;
}

//void GLArea::setSnapshotSetting(const SnapshotSetting & s)
//{
//	ss=s;
//}

void GLArea::setView()
{
	GLfloat fAspect = (GLfloat)curSiz.width()/ curSiz.height();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// This parameter is the one that controls:
	// HOW LARGE IS THE TRACKBALL ICON ON THE SCREEN.
	float viewRatio = 1.75f;
	float cameraDist = viewRatio / tanf(vcg::math::ToRad(fov*.5f));

	nearPlane = cameraDist - 2.f*clipRatioNear;
	farPlane =  cameraDist + 10.f*clipRatioFar;
	if(nearPlane<=cameraDist*.1f) nearPlane=cameraDist*.1f;

	if (!takeSnapTile)	
	{
		if(fov==5)	glOrtho( -viewRatio*fAspect, viewRatio*fAspect, -viewRatio, viewRatio, cameraDist - 2.f*clipRatioNear, cameraDist+2.f*clipRatioFar);
		else    		gluPerspective(fov, fAspect, nearPlane, farPlane);
	}	 
	else	setTiledView(fov, viewRatio, fAspect, nearPlane, farPlane, cameraDist);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, cameraDist,0, 0, 0, 0, 1, 0);
}

void GLArea::setTiledView(GLdouble fovY, float viewRatio, float fAspect, GLdouble zNear, GLdouble zFar,  float cameraDist)
{
	if(fovY<=5)
	{
		GLdouble fLeft   = -viewRatio*fAspect;
		GLdouble fRight  =  viewRatio*fAspect;
		GLdouble fBottom = -viewRatio;
		GLdouble fTop    =  viewRatio;

		GLdouble tDimX = fabs(fRight-fLeft) / totalCols;
		GLdouble tDimY = fabs(fTop-fBottom) / totalRows;


		glOrtho(fLeft   + tDimX * tileCol, fLeft   + tDimX * (tileCol+1),     /* left, right */
			fBottom + tDimY * tileRow, fBottom + tDimY * (tileRow+1),     /* bottom, top */
			cameraDist - 2.f*clipRatioNear, cameraDist+2.f*clipRatioFar);
	}
	else
	{
		GLdouble fTop    = zNear * tan(math::ToRad(fovY/2.0));
		GLdouble fRight  = fTop * fAspect;
		GLdouble fBottom = -fTop;
		GLdouble fLeft   = -fRight;

		// tile Dimension
		GLdouble tDimX = fabs(fRight-fLeft) / totalCols;
		GLdouble tDimY = fabs(fTop-fBottom) / totalRows;

		glFrustum(fLeft   + tDimX * tileCol, fLeft   + tDimX * (tileCol+1), 
			fBottom + tDimY * tileRow, fBottom + tDimY * (tileRow+1), zNear, zFar);
	}
}

void GLArea::updateFps(float deltaTime)
{
	static float fpsVector[10];
	static int j=0;
	float averageFps=0;
	if (deltaTime>0) {
		fpsVector[j]=deltaTime;
		j=(j+1) % 10;
	}
	for (int i=0;i<10;i++) averageFps+=fpsVector[i];
	cfps=1000.0f/(averageFps/10);
	lastTime=deltaTime;
}

void GLArea::resetTrackBall()
{
	trackball.Reset();
	float newScale= 3.0f/meshDoc.bbox().Diag();
	trackball.track.sca = newScale;
	trackball.track.tra =  -meshDoc.bbox().Center();
	updateGL();
}

void GLArea::hideEvent(QHideEvent * /*event*/)
{
	trackball.current_button=0;
}

void GLArea::sendViewPos(QString name) 
{
	Point3f pos=  trackball.track.InverseMatrix() *Inverse(trackball.camera.model) *Point3f(0,0,0);
	emit transmitViewPos(name, pos);
}

void GLArea::sendSurfacePos(QString name) 
{
	nameToGetPickPos = name;
	hasToGetPickPos=true;
}

void GLArea::sendViewDir(QString name) 
{
	Point3f dir= getViewDir();
	emit transmitViewDir(name,dir);
}

void GLArea::sendCameraPos(QString name) 
{
	Point3f pos=meshDoc.mm()->cm.shot.GetViewPoint();
	emit transmitViewDir(name, pos);
}


Point3f GLArea::getViewDir()
{
	vcg::Matrix44f rotM; 
	trackball.track.rot.ToMatrix(rotM); 
	vcg::Invert(rotM);
	return rotM*vcg::Point3f(0,0,1);
}


void GLArea::drawPickedPoint()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	
	// enable color tracking
	glEnable(GL_COLOR_MATERIAL);
	
	//draw the things that we always want to show, like the names 
	glDepthFunc(GL_ALWAYS);
	glDisable(GL_DEPTH_TEST); 
	glDepthMask(GL_FALSE);
	
	//set point attributes
	glPointSize(6.0);
	
	glColor(Color4b::Blue);
	
	int size = itemPointVector.size();
	int type = 0;
	//type = 1 :直线距离
	//type = 2 :垂直距离
	//type = 3 :水平X距离
	//type = 4 :水平Z距离
	//type = 5 :曲线距离
	//type = 6 :环形距离

	for (int i = 0; i < size; i++) {
		Point3f p = itemPointVector[i]->point;

		QString name = itemPointVector[i]->pointName;
		//renderText(p[0], p[1], p[2], name);//显示点的名字
		glColor(Color4b::Red);
		glBegin(GL_POINTS);
		if (2 == size)
		{
			int typeID = itemPointVector.at(0)->type;
			//if (1 == typeID)
				glVertex(p);//显示点
		}			
		glEnd();
	}
	if (2 == size)
	{
		type = itemPointVector.at(0)->type;

		switch (type)
		{
			case 1 : drawLineDistance(); break;
				//
			case 2 : drawVerticalDistance(); break;//
			case 3 : drawXHorizontalDistance(); break;
			case 4 : drawZHorizontalDistance(); break;
			default : break;
		}
		
	}
	else if (size > 2)
	{
		
		type = itemPointVector.at(0)->type;

		switch (type)
		{
			case 5 : drawCurveDistance(size); break;
			case 6 : drawLoopDistance(size); break;
			default : break;
		}
	}	
	//now draw the things that we want drawn if they are not ocluded 
	//we can see in bright red
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST); 
	glDepthMask(GL_TRUE);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glMatrixMode(GL_MODELVIEW);
	
	glDisable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);
	
	glPopAttrib();
	update();
}

void GLArea::drawLineDistance()
{//直线距离
	glColor(Color4b::Green);
	glLineWidth(2.0);
	glEnable(GL_LINE_STIPPLE); //可以虚线
	glLineStipple (1, 0x0F0F);
	glBegin(GL_LINES);
		glVertex3f(itemPointVector[0]->point.X(), itemPointVector[0]->point.Y(), itemPointVector[0]->point.Z());
		glVertex3f(itemPointVector[1]->point.X(), itemPointVector[1]->point.Y(), itemPointVector[1]->point.Z());
    glEnd();
}
void GLArea::drawVerticalDistance()
{//垂直距离
	Point3f pointStart;
	Point3f pointEnd;
	pointStart.X() = pointEnd.X() = (itemPointVector[0]->point.X() + itemPointVector[1]->point.X())/2;
	pointStart.Z() = pointEnd.Z() = (itemPointVector[0]->point.Z() + itemPointVector[1]->point.Z())/2;
	pointStart.Y() = itemPointVector[0]->point.Y();
	pointEnd.Y() = itemPointVector[1]->point.Y();
	//修改后的************************************************************
	glColor(Color4b::Black);
	Point3f pointStartre;
	//Point3f pointEndre;
    pointStartre.X() = (itemPointVector[0]->point.X());
	pointStartre.Y() = (itemPointVector[1]->point.Y());
	pointStartre.Z() = (itemPointVector[0]->point.Z());
   /*  pointEndre.X() = (itemPointVector[0]->point.X());
	pointEndre.Y() = (itemPointVector[1]->point.Y());
	pointEndre.Z() = (itemPointVector[0]->point.Z());*/
	//画出纠正后的点
	//glColor(Color4b::Red);
	//glBegin(GL_POINTS);
	//	glVertex(pointStart);//显示起点
	//	glVertex(pointEnd);//显示终点
	//glEnd();
    glBegin(GL_POINTS);
	glVertex(pointStartre);//显示起点
	//glVertex(pointEndre);//显示终点
	glEnd();
	const float offset = 200;
	glColor(Color4b::Green);
	/*glLineWidth(1.0);
	glBegin(GL_LINES);
		glVertex3f(pointStart.X(), pointStart.Y(), pointStart.Z());
		glVertex3f(pointStart.X() + offset, pointStart.Y(), pointStart.Z());
    glEnd();
	glLineWidth(1.0);
	glBegin(GL_LINES);
		glVertex3f(pointEnd.X(), pointEnd.Y(), pointEnd.Z());
		glVertex3f(pointEnd.X() + offset, pointEnd.Y(), pointEnd.Z());
    glEnd();*/
//***************************************************************************************
	
glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex3f(itemPointVector[0]->point.X(),itemPointVector[0]->point.Y(),itemPointVector[0]->point.Z());
		glVertex3f(itemPointVector[0]->point.X() + offset,itemPointVector[0]->point.Y(),itemPointVector[0]->point.Z());
    glEnd();
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex3f(itemPointVector[0]->point.X() + offset,itemPointVector[0]->point.Y(),itemPointVector[0]->point.Z());
		glVertex3f(itemPointVector[0]->point.X() + offset,itemPointVector[1]->point.Y(),itemPointVector[0]->point.Z());
    glEnd();
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex3f(itemPointVector[0]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[0]->point.Z());
		glVertex3f(itemPointVector[0]->point.X() + offset,itemPointVector[1]->point.Y(),itemPointVector[0]->point.Z());
    glEnd();
	glLineWidth(2.0);
	glEnable(GL_LINE_STIPPLE); //可以虚线
	glLineStipple (1, 0x0F0F);
	glBegin(GL_LINES);
		glVertex3f(itemPointVector[1]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[1]->point.Z());
		glVertex3f(itemPointVector[0]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[0]->point.Z());
    glEnd();
	glEnable(GL_LINE_STIPPLE); //可以虚线
	glLineStipple (1, 0x0F0F);
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex3f(itemPointVector[0]->point.X(),itemPointVector[0]->point.Y(),itemPointVector[0]->point.Z());
		glVertex3f(pointStartre.X(),pointStartre.Y(),pointStartre.Z());
    glEnd();
	/*glLineWidth(3.0);
	glBegin(GL_LINES);
		glVertex3f(pointStart.X() + offset, pointStart.Y(), pointStart.Z());
		glVertex3f(pointEnd.X() + offset, pointEnd.Y(), pointEnd.Z());
    glEnd();*/
}
void GLArea::drawXHorizontalDistance()
{//水平距离drawCurveDistance
	Point3f pointStart;
	Point3f pointEnd;
	pointStart.Y() = pointEnd.Y() = (itemPointVector[0]->point.Y() + itemPointVector[1]->point.Y())/2;
	pointStart.Z() = pointEnd.Z() = (itemPointVector[0]->point.Z() + itemPointVector[1]->point.Z())/2;
	pointStart.X() = itemPointVector[0]->point.X();
	pointEnd.X() = itemPointVector[1]->point.X();

	//画出纠正后的点
	//glColor(Color4b::Red);
	//glBegin(GL_POINTS);
	//	glVertex(pointStart);//显示起点
	//	glVertex(pointEnd);//显示终点
	//glEnd();

	const float offset = 200;
	glColor(Color4b::Green);
	/*glLineWidth(1.0);
	glBegin(GL_LINES);
		glVertex3f(pointStart.X(), pointStart.Y(), pointStart.Z());
		glVertex3f(pointStart.X(), pointStart.Y(), pointStart.Z() + offset);
    glEnd();
	glLineWidth(1.0);
	glBegin(GL_LINES);
		glVertex3f(pointEnd.X(), pointEnd.Y(), pointEnd.Z());
		glVertex3f(pointEnd.X(), pointEnd.Y(), pointEnd.Z() + offset);
    glEnd();
	glLineWidth(3.0);
	glBegin(GL_LINES);
		glVertex3f(pointStart.X(), pointStart.Y(), pointStart.Z() + offset);
		glVertex3f(pointEnd.X(), pointEnd.Y(), pointEnd.Z() + offset);

    glEnd();*/
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex3f(itemPointVector[1]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[1]->point.Z());
		glVertex3f(itemPointVector[0]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[1]->point.Z());
    glEnd();
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex3f(itemPointVector[1]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[1]->point.Z());
		glVertex3f(itemPointVector[1]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[1]->point.Z() + offset);
    glEnd();
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex3f(itemPointVector[1]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[1]->point.Z() + offset);
		glVertex3f(itemPointVector[0]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[1]->point.Z() + offset);
    glEnd();
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex3f(itemPointVector[0]->point.X(),itemPointVector[0]->point.Y(),itemPointVector[0]->point.Z());
		glVertex3f(itemPointVector[0]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[1]->point.Z());
    glEnd();
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex3f(itemPointVector[0]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[1]->point.Z());
		glVertex3f(itemPointVector[0]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[1]->point.Z() + offset);
    glEnd();
}

void GLArea::drawZHorizontalDistance()
{//水平距离drawCurveDistance
	Point3f pointStart;
	Point3f pointEnd;
	pointStart.X() = pointEnd.X() = (itemPointVector[0]->point.X() + itemPointVector[1]->point.X())/2;
	pointStart.Y() = pointEnd.Y() = (itemPointVector[0]->point.Y() + itemPointVector[1]->point.Y())/2;
	pointStart.Z() = itemPointVector[0]->point.Z();
	pointEnd.Z() = itemPointVector[1]->point.Z();

	//画出纠正后的点
	//glColor(Color4b::Red);
	//glBegin(GL_POINTS);
	//	glVertex(pointStart);//显示起点
	//	glVertex(pointEnd);//显示终点
	//glEnd();

	const float offset = 300;
	glColor(Color4b::Green);
	/*glLineWidth(1.0);
	glBegin(GL_LINES);
		glVertex3f(pointStart.X(), pointStart.Y(), pointStart.Z());
		glVertex3f(pointStart.X() + offset, pointStart.Y(), pointStart.Z());
    glEnd();
	glLineWidth(1.0);
	glBegin(GL_LINES);
		glVertex3f(pointEnd.X(), pointEnd.Y(), pointEnd.Z());
		glVertex3f(pointEnd.X() + offset, pointEnd.Y(), pointEnd.Z());
    glEnd();
	glLineWidth(1.0);*/
	//******************************************************************************************
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex3f(itemPointVector[1]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[1]->point.Z());
		glVertex3f(itemPointVector[1]->point.X() + offset,itemPointVector[1]->point.Y(),itemPointVector[1]->point.Z());
    glEnd();
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex3f(itemPointVector[0]->point.X() + offset,itemPointVector[1]->point.Y(),itemPointVector[0]->point.Z());
		glVertex3f(itemPointVector[1]->point.X() + offset,itemPointVector[1]->point.Y(),itemPointVector[1]->point.Z());
    glEnd();
    glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex3f(itemPointVector[0]->point.X() + offset,itemPointVector[1]->point.Y(),itemPointVector[0]->point.Z());
		glVertex3f(itemPointVector[0]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[0]->point.Z());
    glEnd();
	
	glEnable(GL_LINE_STIPPLE); //可以虚线
	glLineStipple (1, 0x0F0F);
	glBegin(GL_LINES);
		glVertex3f(itemPointVector[0]->point.X(),itemPointVector[0]->point.Y(),itemPointVector[0]->point.Z());
		glVertex3f(itemPointVector[0]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[0]->point.Z());
    glEnd();
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex3f(itemPointVector[1]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[1]->point.Z());
		glVertex3f(itemPointVector[0]->point.X(),itemPointVector[1]->point.Y(),itemPointVector[0]->point.Z());
    glEnd();
	
	
	/*glLineWidth(3.0);
	glBegin(GL_LINES);
		glVertex3f(pointStart.X() + offset, pointStart.Y(), pointStart.Z());
		glVertex3f(pointEnd.X() + offset, pointEnd.Y(), pointEnd.Z());
    glEnd();*/
}
void GLArea::drawCurveDistance(int size)
{//曲线距离
#if 0
	GLfloat *glPoint = new GLfloat[size * 3];
	for (int i = 0; i < size; i++) 
	{
		glPoint[3*i] = (itemPointVector[i]->point.X());
		glPoint[3*i+1] = (itemPointVector[i]->point.Y());
		glPoint[3*i+2] = (itemPointVector[i]->point.Z());

	}
	glColor(Color4b::Green);//设置颜色
		//使用bezier曲线拟合

	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, size, glPoint);
	glEnable(GL_MAP1_VERTEX_3);
	glShadeModel(GL_FLAT);
	glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= 30; i++)
		{
			glEvalCoord1f((GLfloat) i/30.0);
		}
	glEnd();

	delete [] glPoint;
#endif

#if 0
	//使用NURBS曲线拟合
	GLUnurbsObj *theNurb = gluNewNurbsRenderer();//创建NURBS对象theNurb
	gluNurbsProperty(theNurb,GLU_SAMPLING_TOLERANCE,10);  
	//GLfloat knots[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	//GLfloat *knots = new GLfloat[size + 4];
	for (int i = 0; i < size+4; i++)
		knots[i] = i + 1;
	gluBeginCurve(theNurb);
	gluNurbsCurve(theNurb, size+4, knots, 3, glPoint, 4, GL_MAP1_VERTEX_3);
	gluEndCurve(theNurb);
#endif
#if 1
	glColor(Color4b::Green);
	glLineWidth(3.0);
	for (int i = 0; i < size; i++)
	{
		if (i != size-1)
		{
			glBegin(GL_LINES);
			glVertex3f(itemPointVector[i]->point.X(), itemPointVector[i]->point.Y(), itemPointVector[i]->point.Z());
			glVertex3f(itemPointVector[i+1]->point.X(), itemPointVector[i+1]->point.Y(), itemPointVector[i+1]->point.Z());
			glEnd();
		}
	}

#endif
}

void GLArea::drawLoopDistance(int size)
{
	glColor(Color4b::Green);
	glLineWidth(3.0);
	for (int i = 0; i < size; i++)
	{
		if (i != size-1)
		{
			glBegin(GL_LINES);
			glVertex3f(itemPointVector[i]->point.X(), itemPointVector[i]->point.Y(), itemPointVector[i]->point.Z());
			glVertex3f(itemPointVector[i+1]->point.X(), itemPointVector[i+1]->point.Y(), itemPointVector[i+1]->point.Z());
			glEnd();
		}
		else
		{
			glBegin(GL_LINES);
			glVertex3f(itemPointVector[size-1]->point.X(), itemPointVector[size-1]->point.Y(), itemPointVector[size-1]->point.Z());
			glVertex3f(itemPointVector[0]->point.X(), itemPointVector[0]->point.Y(), itemPointVector[0]->point.Z());
			glEnd();
		}
	}
}
