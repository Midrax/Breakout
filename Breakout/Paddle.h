#pragma once
#include "pch.h"

class Paddle
{

public:
	void Initialize(ID3D11DeviceContext1* context);
	void Reset();
	void Render(Matrix view, Matrix proj);
	void Update(Keyboard::State k);
	Matrix m_world;
private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_paddle;
	Vector3 move;
};

