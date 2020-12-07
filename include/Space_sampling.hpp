#ifndef SPACE_SAMPLING_H
#define SPACE_SAMPLING_H

#include "Utilities.hpp"
#include <vector>

using std::vector;

void poisson_sphere_sampling(const Point3 &origin, const Vec3 &size, double min_dist, vector<Point3> &result)
{
    const int max_nb_try = 10;
    int max_x = floor(size.x() / min_dist);
    int max_y = floor(size.y() / min_dist);
    int max_z = floor(size.z() / min_dist);

    vector<vector<vector<Vec3>>> positions(max_x, vector<vector<Vec3>>(max_y, vector<Vec3>(max_z)));
    for (int i = 0; i < max_x; i++)
    {
        for (int j = 0; j < max_y; j++)
        {
            for (int k = 0; k < max_z; k++)
            {

                bool ok = false;
                Vec3 temp;
                for (int t = 0; t < max_nb_try && !ok; t++)
                {
                    ok = true;
                    temp = Vec3::random(0, min_dist) + min_dist * Vec3(i, j, k);
                    if (i > 0)
                        for (int b = std::max(j - 1, 0); b >= 0 && b < max_y && b <= j + 1; b++)
                            for (int c = std::max(k - 1, 0); c < max_z && c <= k + 1; c++)
                                if ((positions[i - 1][b][c] - temp).length() < min_dist)
                                    ok = false;
                    if (j > 0)
                        for (int c = k - 1; c >= 0 && c < max_z && c <= k + 1; c++)
                            if ((positions[i][j - 1][c] - temp).length() < 2 * min_dist)
                                ok = false;
                    if (k > 0 && (positions[i][j][k - 1] - temp).length() < 2 * min_dist)
                        ok = false;
                }
                positions[i][j][k] = temp;
                result.push_back(temp + origin);
            }
        }
    }
}

#endif // !SPACE_SAMPLING_H