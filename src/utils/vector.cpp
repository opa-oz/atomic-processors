#pragma once

#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

namespace Utils
{
    namespace Vector
    {

        template <typename T>
        void unique(vector<T> &v)
        {
            std::sort(v.begin(), v.end());

            v.resize(std::distance(v.begin(), std::unique(v.begin(), v.begin() + 12)));
        }
    }
}