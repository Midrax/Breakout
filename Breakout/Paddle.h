#pragma once
#include "pch.h"
#include "Ball.h"

class Paddle
{

public:
	void Initialize(ID3D11DeviceContext1* context);
	void Reset();
	void Render(Matrix view, Matrix proj);
	void Update(Keyboard::State k, Ball &ball);
	Vector3 location;
private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_paddle;
	Matrix m_world;
};

