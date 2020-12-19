#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Ball.h"

using namespace std;

class BrickData
{
public:
    Color color;
    Vector3 location;
    Vector3 scale;
};

class Bricks
{
public:
	void Initialize(string s, ID3D11DeviceContext1* context);
    void Reset();
    void Render(Matrix view, Matrix proj);
    void Update(Ball &ball);

    vector<BrickData>                       m_brickData;
private:
    std::unique_ptr<DirectX::GeometricPrimitive> m_brick;

    unsigned int height;
    unsigned int width;
    float levelWidth;
    float levelHeight;
    Matrix m_world;
};

