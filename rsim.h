#ifndef RSIM
#define RSIM

// 代码实现中需要用到的库，如 vector, set, map
#include <vector>
#include <set>
#include <map>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>

namespace rsim {

using namespace std;

mt19937 Rand(chrono::steady_clock::now().time_since_epoch().count()); // 定义一个随机数生成器
const time_t CPS = 1000000;

// 获取当前的系统时间，以便对随机化过程进行限时
time_t inline get_current_time() {
    return chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

/*
 * 使用随机化算法迭代计算电阻的函数
 * @param u 起始点
 * @param v 终止点
 * @param get_neigh 给定一个点、获取这个点所有相邻的点的函数
 * @param progress_bar 是否输出进度条，默认为 false
 * @param simu_timeout 算法时间限制，单位 s，默认为 10
 * @param steps_limit 单次游走步数限制，默认为 100000
 * @param num_threads 线程数，默认为 256
 */
template<typename node_t>
double calculate_resistance(node_t u, node_t v, vector<pair<node_t, double> > get_neigh(node_t), bool progress_bar = false, double simu_timeout = 10, int steps_limit = 100000, int num_threads = 256) {
    // 进行单次随机游走的函数
    auto get_route = [&] (vector<pair<node_t, double> >* route) {
        node_t cur = u;
        set<node_t> passed; passed.insert(cur);
        int steps = 0;
        while (cur != v) {
            auto neighbors = get_neigh(cur); // 获取当前节点的所有相邻点
            auto [nxt, R] = neighbors[Rand() % neighbors.size()]; // 随机选取一个相邻点
            if (passed.count(nxt)) {
                // 如果出现环，则删除掉这个环
                while (route->size() && route->back().first != nxt) {
                    passed.erase(route->back().first);
                    route->pop_back();
                }
            }
            else {
                // 将这条边加入路径中
                route->emplace_back(nxt, R);
                passed.insert(nxt);
            }
            ++steps;
            if (steps > steps_limit) break;
            cur = nxt;
        }
    };

    time_t begin_t = get_current_time(), last_flush_t = 0;
    map<pair<node_t, node_t>, double> current;
    double result = 0;
    int simu_times = 0;
    while (get_current_time() - begin_t < simu_timeout * CPS) {
        if (progress_bar && get_current_time() - last_flush_t > 0.1 * CPS) {
            // 输出一个进度条
            printf("\rSimu Times: %d (%.2lf / %.2lf s)", simu_times, 1. * (get_current_time() - begin_t) / CPS, simu_timeout);
            fflush(stdout);
            last_flush_t = get_current_time();
        }
        simu_times += num_threads;
        vector<pair<node_t, double> > route[num_threads];
        for (int i = 0; i < num_threads; ++i) route[i].reserve(steps_limit); // 对路径数组预分配空间
        thread threads[num_threads]; // 使用多线程对随机化过程进行加速
        for (int i = 0; i < num_threads; ++i) {
            threads[i] = thread(get_route, route + i);
        }
        for (int i = 0; i < num_threads; ++i) threads[i].join(); // 等待所有线程结束
        for (int i = 0; i < num_threads; ++i) {
            // 对路径进行更新，该部分无法并行
            if (route[i].back().first != v) continue;
            double r_sum = 0, v_sum = 0;
            node_t pre = u;
            for (auto [cur, R] : route[i]) {
                // 计算路径上的电阻之和与原先的电压
                r_sum += R;
                auto edge = minmax(pre, cur);
                v_sum += current[edge] * R * (pre < cur ? 1 : -1);
                pre = cur;
            }
            pre = u;
            double new_current = (1 - v_sum) / r_sum; // 计算增加电流 I' = (U - U_0) / R_0
            result += new_current;
            for (auto [cur, R] : route[i]) {
                // 更新路径上的电流值
                auto edge = minmax(pre, cur);
                current[edge] += new_current * (pre < cur ? 1 : -1);
                pre = cur;
            }
        }
    }
    if (progress_bar) printf("\rSimu Times: %d (%.2lf / %.2lf s)\n", simu_times, (1. * get_current_time() - begin_t) / CPS, simu_timeout);
    return 1 / result;
}

}

#endif
