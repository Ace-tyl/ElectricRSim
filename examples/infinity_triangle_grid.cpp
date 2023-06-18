/*
 * 计算无限大正三角形电阻网格的等效电阻
 * 设每条边上的电阻为 1，标准答案应为 1/3
 */

#include <rsim.h>
using namespace std;

vector<pair<pair<int, int>, double> > get_neighbor_infinity_triangle(pair<int, int> now) {
    auto [x, y] = now;
    return {{{x - 2, y}, 1}, {{x + 2, y}, 1}, {{x - 1, y - 1}, 1}, {{x + 1, y - 1}, 1}, {{x - 1, y + 1}, 1}, {{x + 1, y + 1}, 1}};
}

int main() {
    printf("Simulated R = %.15lf\n", rsim::calculate_resistance({0, 0}, {2, 0}, get_neighbor_infinity_triangle, true, 60));
    return 0;
}