/*
 * 电磁学千题解 4.1.25
 * 采用坐标的方式对节点进行编号
 * 标准答案：
 * 邻：7/12
 * 间：3/4
 * 对：5/6
 */

#include <rsim.h>
using namespace std;

vector<pair<tuple<int, int, int>, double> > get_neighbor(tuple<int, int, int> now) {
    auto [x, y, z] = now;
    return {{{x ^ 1, y, z}, 1}, {{x, y ^ 1, z}, 1}, {{x, y, z ^ 1}, 1}};
}

int main() {
    printf("1-Simulated R = %.15lf\n", rsim::calculate_resistance({0, 0, 0}, {1, 0, 0}, get_neighbor, true, 10)); // 邻
    printf("2-Simulated R = %.15lf\n", rsim::calculate_resistance({0, 0, 0}, {1, 1, 0}, get_neighbor, true, 10)); // 间
    printf("3-Simulated R = %.15lf\n", rsim::calculate_resistance({0, 0, 0}, {1, 1, 1}, get_neighbor, true, 10)); // 对
    return 0;
}