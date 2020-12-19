#pragma once
#include "pch.h"

class Ball
{

public:
	void Initialize(ID3D11DeviceContext1* context);
	void Reset();
	void Render(Matrix view, Matrix proj);
	void Update(Keyboard::State kb, Vector3 paddleLocation, double dt);
	Color color;
	Vector3 location;
	Vector3 scale;
	Vector2 speed;
	bool hitWall = false;
	bool hitBrick = false;
	bool hitPaddle = false;
	bool startedMoving = false;
private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_sphere;
	Matrix m_world;
};