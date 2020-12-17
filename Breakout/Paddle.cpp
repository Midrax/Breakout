#include "pch.h"
#include "Paddle.h"
#include "Constants.h"

void Paddle::Initialize(ID3D11DeviceContext1* context)
{
	location = Vector3(0.f, -2.15f, 0.f);
	m_paddle = GeometricPrimitive::CreateCube(context);
	m_world = Matrix::Identity;
	m_world = m_world.CreateScale(PADDLE_SIZE);
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
		location.x -= 0.1f;

	if (kb.Right || kb.D)
		location.x += 0.1f;
	
	if (location.x - PADDLE_SIZE.x/2 < LEFT_EDGE + EDGE_SIZE/2)
	{
		location.x = LEFT_EDGE + EDGE_SIZE / 2 + PADDLE_SIZE.x / 2;
	}
	if (location.x + PADDLE_SIZE.x / 2 > RIGHT_EDGE - EDGE_SIZE / 2)
	{
		location.x = RIGHT_EDGE - EDGE_SIZE / 2 - PADDLE_SIZE.x / 2;
	}
	m_world.Translation(location);
}
