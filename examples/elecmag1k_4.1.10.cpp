/*
 * 电磁学千题解 4.1.10
 */

#include <rsim.h>
using namespace std;

int s[] = {1, 2, 3, 3, 4, 5, 5, 6, 7};
int t[] = {3, 4, 4, 5, 6, 6, 7, 8, 8};
double w[] = {2, 2, 6, 4, 4, 6, 4, 4, 4};
vector<pair<int, double> > nei[9];

vector<pair<int, double> > get_neighbor(int now) { return nei[now]; }

int main() {
    for (int i = 0; i < 9; ++i) {
        nei[s[i]].push_back({t[i], w[i]});
        nei[t[i]].push_back({s[i], w[i]});
    }
    printf("Simulated R = %.15lf\n", rsim::calculate_resistance(1, 2, get_neighbor, true, 10));
    return 0;
}