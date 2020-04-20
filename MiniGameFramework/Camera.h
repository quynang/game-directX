#pragma on
#include <vector>
#include <string>
#include <iostream>
#include "Utils.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "debug.h"
using namespace std;

class Camera {
public:
	Camera();
	Camera(D3DXVECTOR2 position, int camWith, int camHeight);
	~Camera();
	float getWidth();
	float getHeight();
	D3DXVECTOR2 getPostion();
	void setPostion(float x, float y);
	RECT getBound();
private:
	D3DXVECTOR2 position;
	int camWidth;
	int camHeight;
};