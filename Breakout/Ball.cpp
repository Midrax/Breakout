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
	scale = BALL_SIZE;
	m_world = m_world.CreateScale(scale);
	location = Vector3(0.f, -1.75f, 0);
	m_world.Translation(location);

	speed = Vector2(-2.f, -2.f);
}

void Ball::Reset()
{
	m_sphere.reset();
}

void Ball::Render(Matrix view, Matrix proj)
{
	m_sphere->Draw(m_world, view, proj, Colors::Silver);
}

void Ball::Update(Keyboard::State kb, Vector3 paddleLocation, double dt)
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
		(location.y - scale.y / 2 <= paddleLocation.y + PADDLE_SIZE.y / 2 && !(location.y + scale.y / 2 <= paddleLocation.y - PADDLE_SIZE.y / 2)) 
		&& (location.x + scale.x / 2 >= paddleLocation.x - PADDLE_SIZE.x/2 && location.x - scale.x / 2 <= paddleLocation.x + PADDLE_SIZE.x / 2)
		)
	{
		hitPaddle = true;
		speed.y = -speed.y;
		float xDiff = location.x - paddleLocation.x;
		if (xDiff >= 0)
			speed.x = clamp(xDiff, 1.5f, 3.f);
		if (xDiff < 0)
			speed.x = clamp(xDiff, -3.f, -1.5f);
	}
	else 
	{
		hitPaddle = false;
	}

	// The Ball has hit a Wall
	if ((location.x - scale.x / 2 < LEFT_EDGE + EDGE_SIZE / 2) || (location.x + scale.x / 2 > RIGHT_EDGE - EDGE_SIZE / 2))
	{
		hitWall = true;
		speed.x = -speed.x;
	}
	else if (location.y + scale.y / 2 > TOP_EDGE - EDGE_SIZE / 2)
	{
		hitWall = true;
		speed.y = -speed.y;
	}
	else
	{
		hitWall = false;
	}

	// The ball is moving
	if (startedMoving)
	{
		location.y += speed.y * dt;
		location.x += speed.x * dt;
	}

	m_world.Translation(location);
}
