
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;


bool has(vector<vector<int>>& ret, vector<int>& t) {
    for(int i = 0; i < ret.size(); ++i) {
        if (std::equal(t.begin(), t.end(), ret[i].begin()))
            return true;
    }
    return false;
}


void find(vector<vector<int>>& ret, vector<int>& t, int pos, int s, vector<int>& nums, int start) {
    if (pos == 3 && s == 0) {
        if (!has(ret, t))
            ret.push_back(t);
        return;
    }
    for(int i = start; i < nums.size(); ++i) {
        s += nums[i];
        t[pos] = nums[i];
        if (s <= 0)
            find(ret, t, pos + 1, s, nums, i + 1);
        else
            break;
        s -= nums[i];
    }
}


vector<vector<int>> threeSum(vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    vector<vector<int>> ret;
    vector<int> tmp(3, 0);
    int s = 0;
    find(ret, tmp, 0, s, nums, 0);
    return ret;
}

int main(int argc, char const *argv[])
{
    std::vector<int> v = {-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6};
    threeSum(v);
    return 0;
}