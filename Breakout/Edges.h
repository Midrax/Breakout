#pragma once
#include "pch.h"
#include "Constants.h"
class Edges
{
public:
	void Initialize(ID3D11DeviceContext1* context);
	void Reset();
	void Render(Matrix view, Matrix proj);
private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_edge;
	Matrix m_right_world;
	Matrix m_left_world;
	Matrix m_top_world;
};

