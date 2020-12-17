#include "pch.h"
#include "Ball.h"
#include "Constants.h"
#include "Paddle.h"

float clamp(float n, float lower, float upper)
{
	n = (n > lower) * n + !(n > lower) * lower;
	return (n < upper) * n + !(n < upper) * upper;
}


void Ball::Initialize(ID3D11DeviceContext1* context)
{
	m_sphere = GeometricPrimitive::CreateSphere(context);
	m_world = Matrix::Identity;
	m_world = m_world.CreateScale(BALL_SIZE);
	location = Vector3(0.f, -1.75f, 0);
	m_world.Translation(location);

	movingOffset = Vector2(-0.05f, -0.05f);
}

void Ball::Reset()
{
	m_sphere.reset();
}

void Ball::Render(Matrix view, Matrix proj)
{
	m_sphere->Draw(m_world, view, proj, Colors::Silver);
}

void Ball::Update(Keyboard::State kb, Vector3 paddleLocation)
{
	if (!startedMoving)
	{
		if (kb.Space)
		{
			startedMoving = true;
		}
	}

	// The Ball is above the Paddle, and it has hit the Paddle 
	if (
		(location.y <= paddleLocation.y + PADDLE_SIZE.y / 2 && !(location.y <= paddleLocation.y - PADDLE_SIZE.y / 2)) 
		&& (location.x > paddleLocation.x - PADDLE_SIZE.x/2 && location.x < paddleLocation.x + PADDLE_SIZE.x / 2)
		)
	{
		hitPaddle = true;
		movingOffset.y = -movingOffset.y;
		float xDiff = location.x - paddleLocation.x;
		if (xDiff != 0)
			movingOffset.x = clamp(location.x - paddleLocation.x, -0.075f, 0.075f);
	}
	else 
	{
		hitPaddle = false;
	}

	// The Ball has hit a Wall
	if ((location.x - BALL_SIZE.x / 2 < LEFT_EDGE + EDGE_SIZE / 2) || (location.x + BALL_SIZE.x / 2 > RIGHT_EDGE - EDGE_SIZE / 2))
	{
		hitWall = true;
		movingOffset.x = -movingOffset.x;
	}
	else if (location.y + BALL_SIZE.y / 2 > TOP_EDGE - EDGE_SIZE / 2)
	{
		hitWall = true;
		movingOffset.y = -movingOffset.y;
	}
	else
	{
		hitWall = false;
	}

	// The ball is moving
	if (startedMoving)
	{
		location.y += movingOffset.y;
		location.x += movingOffset.x;
	}

	m_world.Translation(location);
}
