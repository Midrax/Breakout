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
                        b.color = Colors::Yellow;
                        b.location = Vector3(j * blockWidth - width * blockWidth / 2 + blockWidth / 2, 
                            i * blockHeight + (height + 2 )* blockHeight / 2, 0);
                        b.scale = Vector3(blockWidth - blockWidth / 4, blockHeight - blockHeight / 4, 0.2f);
                        brickData.push_back(b);
                    }
                    if (tileData[i][j] == 'O')
                    {
                        BrickData b;
                        b.color = Colors::Orange;
                        b.location = Vector3(j * blockWidth - width * blockWidth / 2 + blockWidth / 2,
                            i * blockHeight + (height + 2 )* blockHeight / 2, 0);
                        b.scale = Vector3(blockWidth - blockWidth / 4, blockHeight - blockHeight / 4, 0.2f);
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
        auto b = m_brickData[i];
        m_world = Matrix::Identity.CreateScale(b.scale);
        m_world.Translation(b.location);
        m_brick->Draw(m_world, view, proj, b.color);
    }
}

void Bricks::Update(Ball &ball)
{
    // A = TOP LEFT, B = TOP RIGHT, C = BOTTOM LEFT;
    Vector2 ballA = Vector2(ball.location.x - ball.scale.x / 2, ball.location.y + ball.scale.y / 2);
    Vector2 ballB = Vector2(ball.location.x + ball.scale.x / 2, ball.location.y + ball.scale.y / 2);
    Vector2 ballC = Vector2(ball.location.x - ball.scale.x / 2, ball.location.y - ball.scale.y / 2);

    bool hasHit = false;
    for (int i = 0; i < m_brickData.size(); i++)
    {
        if (!hasHit)
        {
            Vector2 brickA = Vector2(m_brickData[i].location.x - m_brickData[i].scale.x / 2, m_brickData[i].location.y + m_brickData[i].scale.y / 2);
            Vector2 brickB = Vector2(m_brickData[i].location.x + m_brickData[i].scale.x / 2, m_brickData[i].location.y + m_brickData[i].scale.y / 2);
            Vector2 brickC = Vector2(m_brickData[i].location.x - m_brickData[i].scale.x / 2, m_brickData[i].location.y - m_brickData[i].scale.y / 2);

            if (ballA.y >= brickC.y && ballC.y <= brickA.y &&
                ballB.x >= brickA.x && ballA.x <= brickB.x
                )
            {
                if (m_brickData[i].color.ToVector3() == Colors::Orange.v)
                {
                    m_brickData[i].color = Colors::Yellow;
                }
                else
                {
                    m_brickData[i].location.y = -500;
                }
                if (ball.location.y > brickC.y && ball.location.y < brickA.y && (ball.location.x >= m_brickData[i].location.x || ball.location.x <= m_brickData[i].location.x))
                {
                    ball.speed.x *= -1;
                }
                else
                    ball.speed.y *= -1;
                hasHit = true;

            }
        }
    }
    ball.hitBrick = hasHit;
}