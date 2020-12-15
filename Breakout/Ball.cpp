#include "pch.h"
#include "Ball.h"

void Ball::Initialize(ID3D11DeviceContext1* context)
{
	m_sphere = GeometricPrimitive::CreateSphere(context);
	m_world = Matrix::Identity;
	m_world = m_world.CreateScale(0.15f, 0.15f, 0.15f);
	m_world.Translation(Vector3(0.f, -1.75f, 0));
}

void Ball::Reset()
{
	m_sphere.reset();
}

void Ball::Render(Matrix view, Matrix proj)
{
	m_sphere->Draw(m_world, view, proj, Colors::Silver);
}

void Ball::Update()
{
}
