#include "pch.h"
#include "Paddle.h"

void Paddle::Initialize(ID3D11DeviceContext1* context)
{
	m_paddle = GeometricPrimitive::CreateCube(context);
	m_world = Matrix::Identity;
	m_world = m_world.CreateScale(0.15f, 0.15f, 0.15f);
	m_world.Translation(Vector3(0.f, -2.f, 0));
	Vector3 move = Vector3::Zero;
}

void Paddle::Reset()
{
	m_paddle.reset();
}

void Paddle::Render(Matrix view, Matrix proj)
{
	m_paddle->Draw(m_world, view, proj, Colors::Beige);
}

void Paddle::Update(Keyboard::State kb)
{

	if (kb.Left || kb.A)
		move.x -= 0.1f;

	if (kb.Right || kb.D)
		move.x += 0.1f;
	m_world.Translation(move);
}
