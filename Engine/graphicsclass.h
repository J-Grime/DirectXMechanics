////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "d3dclass.h"
#include "timerclass.h"
#include "shadermanagerclass.h"
#include "positionclass.h"
#include "cameraclass.h"
#include "lightclass.h"
#include "modelclass.h"
#include "bumpmodelclass.h"
#include "firemodelclass.h"

//Xu. 
#include "fontclass.h"
#include "fontshaderclass.h"
#include "textclass.h"
#include "bitmapclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
<<<<<<< HEAD
	bool Frame();
=======
	bool Frame(int, int);
>>>>>>> cd5eacbc5b9d5c1225f731d62979680b86a0860e

private:
	//bool Render(float);
	//Xu
	void TestIntersection(int, int);
	bool RaySphereIntersect(XMVECTOR, XMVECTOR, float);

	bool HandleMovementInput(float);
	bool Render();

private:
	InputClass* m_Input;
	D3DClass* m_D3D;
	TimerClass* m_Timer;
	ShaderManagerClass* m_ShaderManager;
	PositionClass* m_Position;
	CameraClass* m_Camera;
	LightClass* m_Light;
	ModelClass* m_Model1;
	ModelClass* m_Model2;
	BumpModelClass* m_Model3;

	FireModelClass* m_Model4;

	//Sphere Model
	ModelClass* m_Model5;
    TextureShaderClass* m_TextureShader1;
//	LightShaderClass* m_LightShader;
//	LightClass* m_Light;

	TextClass* m_Text;
	BitmapClass* m_Bitmap;
	bool m_beginCheck;
	int m_screenWidth, m_screenHeight;

};

#endif