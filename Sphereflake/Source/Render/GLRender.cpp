#include "StdAfx.h"

#include "Scene.h"
#include "Camera.h"
#include "GLRender.h"

using namespace Render;

///////////////////////////////////////////////////////////////////////
/// FreeGLUT is C-style API, add some globals for keeping data ////////
GLRendererData	gData;

bool	gMouseMoving;
int		gMouseButton;
int		gMouseStartX;
int		gMouseStartY;
bool	gMemoryCleaning;

CGLRenderer::CGLRenderer()
	: fInit(false)
{
}

CGLRenderer::~CGLRenderer()
{
}

void CGLRenderer::Init(const GLRendererData& data)
{
	if (fInit)
	{
		///@note Already initialized.
		return;
	}

	gData = data;

	///@note Initialize the globals.
	gMouseMoving = false;
	gMouseStartX = 0;
	gMouseStartY = 0;
	gMouseButton = -1;
	gMemoryCleaning = false;

	fInit = true;
}

void CGLRenderer::Render()
{
	if (!fInit)
	{
		return;
	}

	///@note Init with the command input data.
	glutInit(&gData.fArgc, gData.fArgv);

	///@note Show glut window.
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(gData.fStartX, gData.fStartY);
	glutInitWindowSize(gData.fWidth, gData.fHeight);
	glutCreateWindow("DrawPad");

	///@note Register glut callbacks.
	glutDisplayFunc(CGLRenderer::DrawScene);
	glutReshapeFunc(CGLRenderer::OnWindowsReshape);
	glutMouseFunc(CGLRenderer::OnMouseClick);
	glutMotionFunc(CGLRenderer::OnMouseMove);
	glutKeyboardFunc(CGLRenderer::OnKeyboardClick);

	///@note Use depth buffering.
	glEnable(GL_DEPTH_TEST);

	///@note Enable lighting.
	if (gData.fEnableLighting)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		///@note Set lighting position.
		GLfloat lightPos[] = {gData.fLightPosition[0]
							, gData.fLightPosition[1]
							, gData.fLightPosition[2]
							, gData.fLightType}; 
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	}

	///@note We are ready, let the event loop begin.
	glutMainLoop();
}

void CGLRenderer::DrawScene()
{
	///@note Clear color and depth buffers.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	///@note Reset transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	///@note Set the camera.
	CCamera& cam = CCamera::GetInstance();

	const CPoint3D center = cam.GetCameraFocus();
	gluLookAt(	center.x, center.y, cam.GetZoom(),
				center.x, center.y, center.z,
				0.0, 1.0, 0.0 );

	///@note Rotate current matrix representing the camera rotations.
	glRotated(cam.GetYaw(), 1.0, 0.0, 0.0);
	glRotated(cam.GetPitch(), 0.0, 1.0, 0.0);

	///@note Enable memory cleaning when:
	/// 1. It is enabled in the init values.
	/// 2. Shapes count is bigger than the init critical count.
	gMemoryCleaning = gData.fMemoryCleaning 
					&& Scene::GetInstance().GetShapesCount() >= gData.fCriticalObjectsCount;

	///@note Draw each shape from the scene.
	Scene::GetInstance().ForEachShape(CGLRenderer::DrawShape);

	glutSwapBuffers();
}

void CGLRenderer::OnMouseClick(int button, int state, int x, int y)
{
#define	GLUT_WHEEL_UP	0x0003
#define GLUT_WHEEL_DOWN	0x0004

	switch (button)
	{
		case GLUT_MIDDLE_BUTTON:
		case GLUT_LEFT_BUTTON:
		{
			if (state == GLUT_DOWN)
			{
				gMouseStartX = x;
				gMouseStartY = y;

				gMouseMoving = true;
			}
			else if (state == GLUT_UP)
			{
				gMouseMoving = false;
			}
			break;
		}

		case GLUT_WHEEL_UP:
		case GLUT_WHEEL_DOWN:
		{
			///@note Zoom the camera. The wheel is moved.
			CCamera::GetInstance().Zoom(button == GLUT_WHEEL_UP, kZoomFactor);

			///@note Redraw the scene.
			glutPostRedisplay();
			break;
		}
	}

	gMouseButton = button;
}

void CGLRenderer::OnMouseMove(int x, int y)
{
	if (gMouseMoving)
	{
		if ( gMouseButton == GLUT_LEFT_BUTTON )
		{
			///@note Rotate the camera.
			CCamera::GetInstance().Rotate(CPoint2D(gMouseStartX, gMouseStartY), CPoint2D(x, y));
		}
		else
		{
			///@note Calculate factors for making the ratio:
			/// (mouse movement)/(camera movement) == 1/1.
			///@todo Think of better way to because the ratio now is not consistent.
			double xFactor = kMoveFactor * gData.fWidth;
			double yFactor = kMoveFactor * gData.fHeight;

			///@note Move the center position of the camera.
			CCamera::GetInstance().Move(CPoint2D(gMouseStartX, gMouseStartY)
									  , CPoint2D(x, y)
									  , xFactor
									  , yFactor );
		}

		///@note Redraw the scene.
		glutPostRedisplay();

		///@note Save the coords for the next mouse event.
		gMouseStartX = x;
		gMouseStartY = y;
	}
}

void CGLRenderer::OnKeyboardClick(unsigned char key, int x, int y)
{
	switch(key)
	{
		case kEscape:
		{
			exit(0);
			break;
		}
	}
}

void CGLRenderer::OnWindowsReshape(int width, int height)
{
	///@note Save new width and height in the data.
	gData.fWidth = width;
	gData.fHeight = height;

	///@note Prevent a divide by zero, when window is too short.
	if (height == 0)
	{
		height = 1;
	}

	///@note Now calculate the new ratio.
	double ratio = (double)width / height;

	///@note Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	///@note Reset Matrix
	glLoadIdentity();

	///@note Set the viewport to be the entire window
	glViewport(0, 0, width, height);

	///@note Set the correct perspective.
	gluPerspective(gData.fViewAngle, ratio, gData.fNearZ, gData.fFarZ);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void CGLRenderer::DrawShape(IShapePtr pShape)
{
	if (!pShape)
	{
		return;
	}

	///@note First draw the object geometry.
	if (gMemoryCleaning)
	{
		pShape->Draw();
	}

	///@note Get the transform matrix.
	const Math::CMatrix m = pShape->GetMatrix();
	
	///@note Convert the CMatrix to a matrix understandable by GL.
	GLdouble glMat[16] = 
	{
		m.fMat[0][0], m.fMat[0][1], m.fMat[0][2], 0.0,
		m.fMat[1][0], m.fMat[1][1], m.fMat[1][2], 0.0,
		m.fMat[2][0], m.fMat[2][1], m.fMat[2][2], 0.0,
		m.fMat[3][0], m.fMat[3][1], m.fMat[3][2], 1.0,
	};

	///@note Push the current matrix. We do not want to modify it.
	/// And multiply the new with our object's matrix.
	glPushMatrix();
	glMultMatrixd(glMat);

	///@note Get attribues(color)
	Primitive::CRGBAColor col = pShape->GetColor();
	
	///@note Convert CRGBAColor to color understandable by GL.
	GLfloat color[] = 
	{ (float)col.GetRed() / 255.0f
	, (float)col.GetGreen() / 255.0f
	, (float)col.GetBlue() / 255.0f
	, col.A() };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	
	///@note Get the geometry.
	const Math::CPoint3D* points = pShape->GetPoints();
	const Math::CPoint3D* normals = pShape->GetNormals();
	const Primitive::TVertIndex* indices = pShape->GetIndices();
	
	///@note Enable the vertex and normals array. 
	glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

	///@note Pass the pointers to the arrays.
	glVertexPointer(3, GL_DOUBLE, 0, points);
	glNormalPointer(GL_DOUBLE, 0, normals);

	///@note Map the faces types from the enum to GL constant.
	GLenum faceType;

	switch(pShape->GetFaceType())
	{
		case EFace::Triangle: faceType = GL_TRIANGLES; break;
		case EFace::Quad: faceType = GL_QUADS; break;
	}

	///@note Finally draw the elements.
	glDrawElements(faceType, pShape->GetIndicesCount(), GL_UNSIGNED_INT, indices);

	///@note Delete our shape's matrix from the stack.
	glPopMatrix();

	///@note We have drawn the shape. Clean its memory.
	if (gMemoryCleaning)
	{
		pShape->Clean();
	}
}