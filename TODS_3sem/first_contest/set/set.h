#include <vector>
#include <algorithm>

class Set {
 public:
    Set() {
        data.resize(0);
    }
    explicit Set(const std::vector<int64_t>& v) {
        data.assign(v.begin(), v.end());
        auto it = std::unique(data.begin(), data.end());

        data.resize(std::distance(data.begin(), it));

        std::sort(data.begin(), data.end());
    }
    Set Union(const Set& other) const {
        std::vector<int64_t> resulted_set;

        std::set_union(data.begin(), data.end(),
                       other.data.begin(), other.data.end(),
                       std::back_inserter(resulted_set));
        return Set(resulted_set);
    }
    Set Intersection(const Set& other) const {
        std::vector<int64_t> intersection_of_sets;

        std::set_intersection(data.begin(), data.end(),
                              other.data.begin(), other.data.end(),
                              std::back_inserter(intersection_of_sets));

        return Set(intersection_of_sets);
    }

    Set Difference(const Set& other) const {
        std::vector<int64_t> difference_of_sets;

        std::set_difference(data.begin(), data.end(),
                            other.data.begin(), other.data.end(),
                            std::back_inserter(difference_of_sets));

        return Set(difference_of_sets);
    }

    Set SymmetricDifference(const Set& other) const {
        std::vector<int64_t> sym_difference_of_sets;

        std::set_symmetric_difference(data.begin(), data.end(),
                                      other.data.begin(), other.data.end(),
                                      std::back_inserter \
                                      (sym_difference_of_sets));

        return Set(sym_difference_of_sets);
    }

    bool Contains(int64_t num) {
        auto it = std::find(data.begin(), data.end(), num);
        if (it != data.end()) {
            return true;
        } else {
            return false;
        }
    }

    void Add(int64_t num) {
        if (!Contains(num)) {
            data.push_back(num);
            std::sort(data.begin(), data.end());
        }
    }

    void Remove(int64_t num) {
        std::vector<int64_t>::iterator it;
        do {
            it = std::find(data.begin(), data.end(), num);
            if (it != data.end()) {
                data.erase(it);
            }
        } while (it != data.end());
        std::sort(data.begin(), data.end());
    }

    std::vector<int64_t> Data() const {
        return data;
    }

 private:
    std::vector<int64_t> data;
};
