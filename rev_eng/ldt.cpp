

#pragma once

#include <iostream>
#include <boost/multi_array.hpp>

using namespace std;
const int div = 200;

boost::multi_array<float, 3> grid;
boost::multi_array<float, 3> g_scan;
grid.resize(boost::extents[div][div][div]);
g_scan.resize(boost::extents[div][div][div]);

auto f_y = [&](int xCoord, int zCoord, int yCoord, int ypos) {
    return SQ(yCoord - ypos) + SQ(grid[xCoord][ypos][zCoord]);
};

auto Sep_y = [&](int xCoord, int zCoord, int i, int u) {
    assert(u > i);
    return int((SQ(u) - SQ(i) + SQ(grid[xCoord][u][zCoord]) - SQ(grid[xCoord][i][zCoord])) / (2 * (u - i)));
};

void f()
{
    for (int x = 0u; x < div; x ++ ){
        std::vector<int> s(div), t(div);

        for (auto z = 0; z < div; z++)
        {
            auto q = 0;
            s[0] = t[0] = 0;

            for (auto u = 1; u < div; u++)
            {
                while ((q >= 0) && (f_y(x, z, t[q], s[q]) > f_y(x, z, t[q], u)))
                    q--;

                if (q < 0)
                {
                    q = 0;
                    s[0] = u;
                }
                else
                {
                    auto w = 1 + Sep_y(x, z, s[q], u);
                    if (w < div)
                    {
                        q++;
                        s[q] = u;
                        t[q] = w;
                    }
                }
            }

            for (int u = div - 1; u >= 0; u--)
            {
                auto point = f_y(x, z, u, s[q]);
                g_scan[x][u][z] = point;
                if (u == t[q])
                    q--;
            }
        }
    }

}

int main()
{
    for (int i = 0; i < 1)

}


