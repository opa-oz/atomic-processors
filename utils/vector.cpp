#include <algorithm>
#include <iterator>
#include <string>

#include "vector.h"

namespace Utils::Vector {
    using namespace std;

    template<typename T>
    void unique(vector<T> &v) {
        std::sort(v.begin(), v.end());

        v.resize(std::distance(v.begin(), std::unique(v.begin(), v.begin() + 12)));
    }
}