#include <iostream>
#include <unordered_map>
#include <vector>

class containter {
    std::unordered_map<int,int> map_;
    std::vector<int> vec_;
public:
    bool insert(int val) {
        if (map_.count(val)){
            return false;
        }
        map_[val] = vec_.size();
        vec_.emplace_back(val);
    }

    bool remove(int val) {
        if (!map_.count(val)) return false;
        int index = map_.at(val);
        vec_[index] = vec_.back();
        map_[vec_.back()] = index;
        vec_.pop_back();
        map_.erase(val);
        
    }   

    int getRandom() {
        return vec_[rand()%vec_.size()];
    }
};


int main() {

    return 0;
}