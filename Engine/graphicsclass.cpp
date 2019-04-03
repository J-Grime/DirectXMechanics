////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_Input = 0;
	m_D3D = 0;
	m_Timer = 0;
	m_ShaderManager = 0;
	m_Light = 0;
	m_Position = 0;
	m_Camera = 0;
	m_Model1 = 0;
	m_Model2 = 0;
	m_Model3 = 0;

	m_Model4 = 0;

	//Xu. 14/03/19 
	m_Model5 = 0;
	m_TextureShader1 = 0;
	//m_LightShader = 0;
	//m_Light = 0;
	m_Text = 0;
	m_Bitmap = 0;

}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;
	XMMATRIX baseViewMatrix;

	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation of the viewer.
	m_Position->SetPosition(0.0f, 0.0f, -10.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	// Set the initial position of the camera.
	//m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(64.0f);

	// Create the model object.
	m_Model1 = new ModelClass;
	if(!m_Model1)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model1->Initialize(m_D3D->GetDevice(), "../Engine/data/new-ninjaHead.txt", L"../Engine/data/marble.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the first model object.", L"Error", MB_OK);
		return false;
	}

	// Create the second model object.
	m_Model2 = new ModelClass;
	if(!m_Model2)
	{
		return false;
	}

	// Initialize the second model object.
	result = m_Model2->Initialize(m_D3D->GetDevice(), "../Engine/data/new-ninjaHead.txt", L"../Engine/data/metal.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the second model object.", L"Error", MB_OK);
		return false;
	}

	// Create the third bump model object for models with normal maps and related vectors.
	m_Model3 = new BumpModelClass;
	if(!m_Model3)
	{
		return false;
	}

	// Initialize the bump model object.
	result = m_Model3->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/stone.dds", 
								  L"../Engine/data/normal.dds");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the third model object.", L"Error", MB_OK);
		return false;
	}

	// Create the fourth fire model object.
	m_Model4 = new FireModelClass;
	if (!m_Model4)
	{
		return false;
	}

	result = m_Model4->Initialize(m_D3D->GetDevice(), "../Engine/data/new-ninjaHead.txt", L"../Engine/data/fire01.dds", //square or cube
		L"../Engine/data/noise01.dds", L"../Engine/data/alpha01.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fourth model object.", L"Error", MB_OK);
		return false;
	}

	//Xu.
	// Create the model object.
	m_Model5 = new ModelClass;
	if (!m_Model5)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model5->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/blue.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	
	// Create the texture shader object.
	m_TextureShader1 = new TextureShaderClass;
	if (!m_TextureShader1)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader1->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	/*
	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);

	//*/

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}
	//*
	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix); //Xu. need a base view matrix
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

		// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../Engine/data/mouse.dds", 32, 32);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize that the user has not clicked on the screen to try an intersection test yet.
	m_beginCheck = false;
	//*/


	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	if (m_TextureShader1)
	{
		m_TextureShader1->Shutdown();
		delete m_TextureShader1;
		m_TextureShader1 = 0;
	}

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the model object.
	if (m_Model5)
	{
		m_Model5->Shutdown();
		delete m_Model5;
		m_Model5 = 0;
	}

	// Release the model objects.
	if(m_Model1)
	{
		m_Model1->Shutdown();
		delete m_Model1;
		m_Model1 = 0;
	}

	if(m_Model2)
	{
		m_Model2->Shutdown();
		delete m_Model2;
		m_Model2 = 0;
	}

	if(m_Model3)
	{
		m_Model3->Shutdown();
		delete m_Model3;
		m_Model3 = 0;
	}

	if (m_Model4)
	{
		m_Model4->Shutdown();
		delete m_Model4;
		m_Model4 = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


<<<<<<< HEAD
bool GraphicsClass::Frame()
{
	bool result;

=======
bool GraphicsClass::Frame(int mouseX, int mouseY)
{
	bool result;


	// Set the location of the mouse.
	result = m_Text->SetMousePosition(mouseX, mouseY, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	return true;
>>>>>>> cd5eacbc5b9d5c1225f731d62979680b86a0860e
	// Update the system stats.
	m_Timer->Frame();

	// Read the user input.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleMovementInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}

	// Render the graphics.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::HandleMovementInput(float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsUpPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsDownPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	//Xu.
	bool result;
	int mouseX, mouseY;
	// Do the input frame processing.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the left mouse button has been pressed.
	if (m_Input->IsLeftMouseButtonDown() == true)
	{
		// If they have clicked on the screen with the mouse then perform an intersection test.
		if (m_beginCheck == false)
		{
			m_beginCheck = true;
			m_Input->GetMouseLocation(mouseX, mouseY);
			TestIntersection(mouseX, mouseY);
		}
	}

	// Check if the left mouse button has been released.
	if (m_Input->IsLeftMouseButtonDown() == false)
	{
		m_beginCheck = false;
	}

	return true;
}

bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix, orthoMatrix;
	bool result;

	//Variables for the fire 
	XMFLOAT3 scrollSpeeds, scales;
	XMFLOAT2 distortion1, distortion2, distortion3;
	float distortionScale, distortionBias;
	static float frameTime = 0.0f;


	// Increment the frame time counter.
	frameTime += 0.01f;
	if (frameTime > 1000.0f)
	{
		frameTime = 0.0f;
	}

	// Set the three scrolling speeds for the three different noise textures.
	scrollSpeeds = XMFLOAT3(1.3f, 2.1f, 2.3f);

	// Set the three scales which will be used to create the three different noise octave textures.
	scales = XMFLOAT3(1.0f, 2.0f, 3.0f);

	// Set the three different x and y distortion factors for the three different noise textures.
	distortion1 = XMFLOAT2(0.1f, 0.2f);
	distortion2 = XMFLOAT2(0.1f, 0.3f);
	distortion3 = XMFLOAT2(0.1f, 0.1f);

	// The the scale and bias of the texture coordinate sampling perturbation.
	distortionScale = 0.8f;
	distortionBias = 0.5f;

	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.0005f * m_Timer->GetTime();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.03f, 0.03f, 0.03f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationZ(rotation * 3.0f));
	translateMatrix = XMMatrixTranslation(-3.5f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	/*
	// Setup the rotation and translation of the first model.
	worldMatrix = XMMatrixRotationZ(rotation * 3.0f);
	translateMatrix = XMMatrixTranslation(- 3.5f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);
	//*/

	// Render the first model using the texture shader.
	m_Model1->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
												  m_Model1->GetTexture());
	if(!result)
	{
		return false;
	}

	// Setup the rotation and translation of the second model.
	m_D3D->GetWorldMatrix(worldMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.03f, 0.03f, 0.03f));
	
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation));

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, -2.0f, 0.0f));

	// Render the second model using the light shader.
	m_Model2->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
									   m_Model2->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
									   m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	// Setup the rotation and translation of the third model.
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixRotationX(rotation / 3.0f);
	translateMatrix = XMMatrixTranslation(3.5f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the third model using the bump map shader.
	m_Model3->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Model3->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
												  m_Model3->GetColorTexture(), m_Model3->GetNormalMapTexture(), m_Light->GetDirection(), 
												  m_Light->GetDiffuseColor());
	if(!result)
	{
		return false;
	}

//


// Draw the fire
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Setup the rotation and translation of the 4th model.
	m_D3D->GetWorldMatrix(worldMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.03f, 0.03f, 0.03f));// (1.0f, 1.0f, 1.0f));
	//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 2.0f, -1.0f));


	// Turn on alpha blending for the fire transparency.
	m_D3D->TurnOnAlphaBlending();

	// Put the square model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model4->Render(m_D3D->GetDeviceContext());

	// Render the square model using the fire shader.
	result = m_ShaderManager->RenderFireShader(m_D3D->GetDeviceContext(), m_Model4->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model4->GetTexture1(), m_Model4->GetTexture2(), m_Model4->GetTexture3(), frameTime, scrollSpeeds,
		scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending.
	m_D3D->TurnOffAlphaBlending();

	//Xu. 14/03/2019
	// Translate to the location of the sphere.
	// Setup the rotation and translation of the third model.
	int mouseX, mouseY;

	m_D3D->GetWorldMatrix(worldMatrix);
	translateMatrix = XMMatrixTranslation(-5.0f, 1.0f, 5.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the model using the light shader.
	m_Model5->Render(m_D3D->GetDeviceContext());

	// Render the sphere model using the fire shader.
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model5->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model5->GetTexture());
	if (!result)
	{
		return false;
	}


	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Turn on alpha blending.
	m_D3D->EnableAlphaBlending();

	// Get the location of the mouse from the input object,
	m_Input->GetMouseLocation(mouseX, mouseY);

	// Render the mouse cursor with the texture shader.
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), mouseX, mouseY);  if (!result) { return false; }
	//Xu.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn of alpha blending.
	m_D3D->DisableAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();
	// Present the rendered scene to the screen.
	m_D3D->EndScene();


	return true;
}

void GraphicsClass::TestIntersection(int mouseX, int mouseY)
{
	float pointX, pointY;
	XMMATRIX projectionMatrix, viewMatrix, inverseViewMatrix, worldMatrix, translateMatrix, inverseWorldMatrix;
	XMVECTOR direction, origin, rayOrigin, rayDirection;
	bool intersect, result;

	//Xu.
	direction = XMVectorSet(0.0f, 0.0f, 0.0, 0.0);
	origin = XMVectorSet(0.0f, 0.0f, 0.0, 0.0);
	rayOrigin = XMVectorSet(0.0f, 0.0f, 0.0, 0.0);
	rayDirection = XMVectorSet(0.0f, 0.0f, 0.0, 0.0);

	// Move the mouse cursor coordinates into the -1 to +1 range.
	pointX = ((2.0f * (float)mouseX) / (float)m_screenWidth) - 1.0f;
	pointY = (((2.0f * (float)mouseY) / (float)m_screenHeight) - 1.0f) * -1.0f;


	// Adjust the points using the projection matrix to account for the aspect ratio of the viewport.
	m_D3D->GetProjectionMatrix(projectionMatrix);

	//Xu.
	XMFLOAT4X4 fProjectionMatrix;
	XMStoreFloat4x4(&fProjectionMatrix, projectionMatrix);

	//pointX = pointX / projectionMatrix._11;
	//pointY = pointY / projectionMatrix._22;
	pointX = pointX / fProjectionMatrix._11;
	pointY = pointY / fProjectionMatrix._22;

	/*
	XMMATRIX mtxView;
	XMFLOAT4X4 fView;
	XMStoreFloat4x4(&fView, mtxView);
	float fView_11 = fView._11;
	*/

	// Get the inverse of the view matrix.
	m_Camera->GetViewMatrix(viewMatrix);
	inverseViewMatrix = XMMatrixInverse(NULL, viewMatrix);

	//Xu
	XMFLOAT3 fDirection;// = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 fOrigin;// = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 fRayOrigin;// = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 fRayDirection;// = XMFLOAT3(0.0f, 0.0f, 0.0f);

	XMStoreFloat3(&fDirection, direction);
	XMStoreFloat3(&fOrigin, origin);
	XMStoreFloat3(&fRayOrigin, rayOrigin);
	XMStoreFloat3(&fRayDirection, rayDirection);

	XMFLOAT4X4 fInverseViewMatrix;
	XMStoreFloat4x4(&fInverseViewMatrix, inverseViewMatrix);

	// Calculate the direction of the picking ray in view space.
	fDirection.x = (pointX * fInverseViewMatrix._11) + (pointY * fInverseViewMatrix._21) + fInverseViewMatrix._31;
	fDirection.y = (pointX * fInverseViewMatrix._12) + (pointY * fInverseViewMatrix._22) + fInverseViewMatrix._32;
	fDirection.z = (pointX * fInverseViewMatrix._13) + (pointY * fInverseViewMatrix._23) + fInverseViewMatrix._33;

	// Get the origin of the picking ray which is the position of the camera.
	fOrigin = m_Camera->GetPosition();

	//*** Xu, need reassemble above values to XMVECTOR and pass to below. 18/03/2019
	/*


	You don't access the vector's members directly, you have to copy the vector to a XMFLOAT4 first:

	XMVECTOR v2 = XMVectorSet(1.0, 1.0, 1.0, 1.0);
	XMFLOAT4 v2F;    //the float where we copy the v2 vector members
	XMStoreFloat4(&v2F, v2);   //the function used to copy

	now you can access and manipulate the v2F members simply like so:

	v2F.x = 4.5f;

	when you are done, just copy back the v2F to v2:

	v2 = XMLoadFloat4(&v2F);
	
	*/

	// Get the world matrix and translate to the location of the sphere.
	m_D3D->GetWorldMatrix(worldMatrix);
	translateMatrix = XMMatrixTranslation(-5.0f, 1.0f, 5.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Now get the inverse of the translated world matrix.
	//D3DXMatrixInverse(&inverseWorldMatrix, NULL, &worldMatrix);
	inverseWorldMatrix = XMMatrixInverse(NULL, worldMatrix);

	/*
	XMMATRIXV = mCam.View();
	XMMATRIXinvView = XMMatrixInverse(&XMMatrixDeterminant(V),V);
	XMMATRIXW = XMLoadFloat4x4(&mMeshWorld);

	XMMATRIXinvWorld = XMMatrixInverse(&XMMatrixDeterminant(W),W);
	XMMATRIXtoLocal = XMMatrixMultiply(invView,invWorld);

	rayOrigin = XMVector3TransformCoord(rayOrigin,toLocal);
	rayDir = XMVector3TransformNormal(rayDir,toLocal);

	rayDir = XMVector3Normalize(rayDir);
	//*/

	// Now transform the ray origin and the ray direction from view space to world space.
	//D3DXVec3TransformCoord(&rayOrigin, &origin, &inverseWorldMatrix);
	rayOrigin = XMVector3TransformCoord(XMLoadFloat3(&fOrigin), inverseWorldMatrix);
	
	//D3DXVec3TransformNormal(&rayDirection, &direction, &inverseWorldMatrix);
	rayDirection = XMVector3TransformNormal(XMLoadFloat3(&fDirection), inverseWorldMatrix);

	// Normalize the ray direction.
	rayDirection = XMVector3Normalize(rayDirection);

	// Now perform the ray-sphere intersection test.
	intersect = RaySphereIntersect(rayOrigin, rayDirection, 1.0f);

	if (intersect == true)
	{
		// If it does intersect then set the intersection to "yes" in the text string that is displayed to the screen.
		result = m_Text->SetIntersection(true, m_D3D->GetDeviceContext());
	}
	else
	{
		// If not then set the intersection to "No".
		result = m_Text->SetIntersection(false, m_D3D->GetDeviceContext());
	}

	return;
}


bool GraphicsClass::RaySphereIntersect(XMVECTOR rayOrigin, XMVECTOR rayDirection, float radius)
{
	float a, b, c, discriminant;
	XMFLOAT4  fRayOrigin, fRayDirection;    
	
	XMStoreFloat4(&fRayOrigin, rayOrigin);   
	XMStoreFloat4(&fRayDirection, rayDirection);

	// Calculate the a, b, and c coefficients.
	a = (fRayDirection.x * fRayDirection.x) + (fRayDirection.y * fRayDirection.y) + (fRayDirection.z * fRayDirection.z);
	b = ((fRayDirection.x * fRayOrigin.x) + (fRayDirection.y * fRayOrigin.y) + (fRayDirection.z * fRayOrigin.z)) * 2.0f;
	c = ((fRayOrigin.x * fRayOrigin.x) + (fRayOrigin.y * fRayOrigin.y) + (fRayOrigin.z * fRayOrigin.z)) - (radius * radius);

	// Find the discriminant.
	discriminant = (b * b) - (4 * a * c);

	// if discriminant is negative the picking ray missed the sphere, otherwise it intersected the sphere.
	if (discriminant < 0.0f)
	{
		return false;
	}

	return true;
}

