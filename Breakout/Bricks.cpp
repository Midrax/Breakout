#include "pch.h"
#include "Bricks.h"
#include "Constants.h"

void Bricks::Initialize(string s, ID3D11DeviceContext1* context)
{
    m_brick = GeometricPrimitive::CreateCube(context);

    levelWidth = std::abs(RIGHT_EDGE - LEFT_EDGE);
    levelHeight = std::abs(TOP_EDGE*2);
    // Read file to generate level
    char tileCode;
    std::string line;
    std::ifstream fstream(s);
    std::vector<std::vector<char>> tileData;
    std::vector<BrickData> brickData;
    int n = 0;
    
    if (fstream)
    {
        while (std::getline(fstream, line)) // read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<char> row;
            while (sstream >> tileCode) // read each word separated by spaces
                row.push_back(tileCode);
            tileData.insert(tileData.begin(), row);
        }
        if (tileData.size() > 0)
        {
            height = tileData.size();
            width = tileData[0].size();
            float blockWidth = (levelWidth / width);
            float blockHeight = (levelHeight / 2 / width);
            for (unsigned int i = 0; i < height; ++i)
            {
                for (unsigned int j = 0; j < width; ++j)
                {
                    if (tileData[i][j] == 'Y')
                    {
                        BrickData b;
                        b.y = i * blockHeight + height * blockHeight / 2 + blockHeight/2;
                        b.x = j * blockWidth - width * blockWidth/2 + blockWidth / 2;
                        b.c = Colors::Yellow;
                        b.world = Matrix::Identity.CreateScale(blockWidth - blockWidth / 4, 0.2f, 0.2f);
                        brickData.push_back(b);
                    }
                    if (tileData[i][j] == 'O')
                    {
                        BrickData b;
                        b.y = i * blockHeight + height * blockHeight / 2 + blockHeight / 2;
                        b.x = j * blockWidth - width * blockWidth / 2 + blockWidth / 2;
                        b.c = Colors::Orange;
                        b.world = Matrix::Identity.CreateScale(blockWidth-blockWidth/4, 0.2f, 0.2f);
                        brickData.push_back(b);
                    }
                    n++;
                }
            }
        }

    }
    m_brickData = brickData;
}

void Bricks::Reset()
{
    m_brick.reset();
}

void Bricks::Render(Matrix view, Matrix proj)
{
    for (int i = 0; i < m_brickData.size(); i++)
    {
        m_brickData[i].world.Translation(Vector3(m_brickData[i].x, m_brickData[i].y, 0.f));

        m_brick->Draw(m_brickData[i].world, view, proj, m_brickData[i].c);
    }
}

void Bricks::Update(Vector3 ballLocation)
{
}
