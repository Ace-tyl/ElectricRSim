/*
 * 电磁学千题解 4.1.16 (2)
 */

#include <rsim.h>
using namespace std;

int s[] = {1, 1, 2, 3, 3, 4, 5};
int t[] = {2, 3, 4, 4, 5, 6, 6};
double w[] = {1, 1, 1, 1, 1, 1, 1};
vector<pair<int, double> > nei[7];

vector<pair<int, double> > get_neighbor(int now) { return nei[now]; }

int main() {
    for (int i = 0; i < 7; ++i) {
        nei[s[i]].push_back({t[i], w[i]});
        nei[t[i]].push_back({s[i], w[i]});
    }
    printf("Simulated R = %.15lf\n", rsim::calculate_resistance(1, 6, get_neighbor, true, 10));
    return 0;
}