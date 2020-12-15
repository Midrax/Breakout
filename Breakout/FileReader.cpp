#include "pch.h"
#include "FileReader.h"

void FileReader::Initialize(string s, float H, float W)
{
    // Read file to generate level
    unsigned int tileCode;
    std::string line;
    std::ifstream fstream(s);
    std::vector<std::vector<unsigned int>> tileData;
    int n = 0;
    
    if (fstream)
    {
        while (std::getline(fstream, line)) // read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode) // read each word separated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
        {
            unsigned int height = tileData.size();
            unsigned int width = tileData[0].size();
            float unit_width = W / static_cast<float>(width);
            float unit_height = H / 2 / height;
            // initialize level tiles based on tileData		
            for (unsigned int i = 0; i < height; ++i)
            {
                for (unsigned int j = 0; j < width; ++j)
                {
                    /*
                    if (tileData[i][j] == 1)
                    {
                        block[n].setTexture(t1);
                        block[n].setColor(Color::Yellow);
                        block[n].setPosition(unit_width * j + unit_width / 4, unit_height * i + unit_height / 4);
                        n++;
                    }
                    else if (tileData[i][j] > 1)
                    {
                        block[n].setTexture(t1);
                        if (tileData[i][j] == 2)
                        {
                            block[n].setColor(Color(250, 150, 0));
                        }
                        else if (tileData[i][j] == 3)
                            block[n].setColor(Color::Red);
                        else if (tileData[i][j] == 4)
                            block[n].setColor(Color::Green);

                        block[n].setPosition(unit_width * j + unit_width / 4, unit_height * i + unit_height / 4);
                        n++;
                    }
                    */
                }
            }
        }

    }
}
