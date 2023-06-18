/*
 * 电磁学与电动力学 习题 4.6
 * 标准答案：(sqrt(21)-2)/sqrt(21)
 */

#include <rsim.h>
using namespace std;

vector<pair<pair<int, int>, double> > get_neighbor_lrinf(pair<int, int> now) {
    auto [x, y] = now;
    vector<pair<pair<int, int>, double> > res = {{{x - 1, y}, 1}, {{x + 1, y}, 1}};
    if (y < 1) res.push_back({{x, y + 1}, 1});
    if (y > -1) res.push_back({{x, y - 1}, 1});
    return res;
}

int main() {
    printf("Simulated R = %.15lf\n", rsim::calculate_resistance({0, 0}, {1, 0}, get_neighbor_lrinf, true, 60));
    return 0;
}