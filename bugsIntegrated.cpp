#include <bits/stdc++.h>
#include <cmath>
using namespace std;

int get_max_chips(int n, int m, int k, vector<tuple<int, int>> bad_chip)
{
    vector<unordered_map<int, int>> DP;
    for (int i{0}; i < m; ++i)
    {
        vector<int> proj = get_row_proj(n, m, k, bad_chip, i);
        for (int s{0}; s <= compress(proj); ++s)
        {
            DP[i][s] = max(get_value(i, s), DP[i][s]);
        }
    }

    return 2;
}

vector<int> get_row_proj(int n, int m, int k, vector<tuple<int, int>> bad_chip, int col)
{
    vector<int> proj(n);
    unordered_map<int, vector<tuple<int, int>>> dict;
    for (auto chip : bad_chip)
    {
        if ((get<1>(chip) <= col) || (get<1>(chip) >= max(col - 2, 0)))
        {
            dict[get<0>(chip)].push_back(chip);
        }
    }
    for (int row{0}; row <= n; ++row)
    {
        auto it = dict.find(row);
        proj[row] = (it != dict.end()) ? (col - get<1>(*max_element(it->second.begin(), it->second.end()))) : min(col, 3);
    }

    return proj;
}

vector<int> decompress(int val)
{
    vector<int> decompressed;
    while (val >= 4)
    {
        int dig = val % 4;
        val /= 4;
        decompressed.push_back(dig);
    }
    decompressed.push_back(val);
    reverse(decompressed.begin(), decompressed.end());
    return decompressed;
}

int compress(vector<int> compressed)
{
    int res = 0, dig = 0;
    for (int i{0}; i < compressed.size(); ++i)
    {
        dig = compressed[i] * pow(4, i);
        res += dig;
    }
    return res;
}

int get_value(vector<vector<int>> DP, int i, int s)
{
    if (i == 0)
    {
        return 0;
    }
    return DP[i][s];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n, m, k;
    cin >> t;
    cin >> n >> m >> k;

    vector<tuple<int, int>> bad_chip(k);
    for (int i = 0; i < k; ++i)
    {
        cin >> get<0>(bad_chip[i]);
        cin >> get<1>(bad_chip[i]);
    }

    return get_max_chips(n, m, k, bad_chip);
}