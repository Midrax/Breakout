#include "pch.h"
#include "Edges.h"

void Edges::Initialize(ID3D11DeviceContext1* context)
{
	m_edge = GeometricPrimitive::CreateCube(context);
	m_right_world = Matrix::Identity;
	m_right_world = m_right_world.CreateScale(EDGE_SIZE, 6.f, 0.2f);
	m_right_world.Translation(Vector3(LEFT_EDGE, 0.f, 0));

	m_left_world = Matrix::Identity;
	m_left_world = m_left_world.CreateScale(EDGE_SIZE, 6.f, 0.2f);
	m_left_world.Translation(Vector3(RIGHT_EDGE, 0.f, 0));

	m_top_world = Matrix::Identity;
	m_top_world = m_left_world.CreateScale(8.f, EDGE_SIZE, 0.2f);
	m_top_world.Translation(Vector3(0.f, TOP_EDGE-EDGE_SIZE/2, 0));

	
}

void Edges::Reset()
{
	m_edge.reset();
}

void Edges::Render(Matrix view, Matrix proj)
{
	m_edge->Draw(m_right_world, view, proj, Colors::White);
	m_edge->Draw(m_left_world, view, proj, Colors::White);
	m_edge->Draw(m_top_world, view, proj, Colors::White);
}