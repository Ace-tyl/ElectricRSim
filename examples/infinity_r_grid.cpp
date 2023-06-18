/*
 * 计算无限大电阻网格的等效电阻
 * 设每条边上的电阻为 1，标准答案应为 1/2
 * 构图方法：用 (x, y) 表示当前节点的坐标，(x, y) 与 (x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1) 之间各有一条权值为 1 的边
 */

#include <rsim.h>
using namespace std;

vector<pair<pair<int, int>, double> > get_neighbor_infinity(pair<int, int> now) {
    auto [x, y] = now;
    return {{{x - 1, y}, 1}, {{x + 1, y}, 1}, {{x, y - 1}, 1}, {{x, y + 1}, 1}};
}

int main() {
    printf("Simulated R = %.15lf\n", rsim::calculate_resistance({0, 0}, {1, 0}, get_neighbor_infinity, true, 60));
    return 0;
}