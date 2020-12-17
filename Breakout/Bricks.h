#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct BrickData
{
    float x;
    float y;
    Color c;
    Matrix world;
};

class Bricks
{
public:
	void Initialize(string s, ID3D11DeviceContext1* context);
    void Reset();
    void Render(Matrix view, Matrix proj);
    void Update(Vector3 ballLocation);

    vector<BrickData>                       m_brickData;
private:
    std::unique_ptr<DirectX::GeometricPrimitive> m_brick;

    unsigned int height;
    unsigned int width;
    float levelWidth;
    float levelHeight;
};

