#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <functional>
#include <utility>

bool operator>(const GameObject& a, const GameObject& b) {
    return a.id > b.id;
}

template<class Tp, template<class> class Compare>
class DereferenceCompare {
    Compare<Tp> comp;

 public:
    bool operator()(const Tp* const a, const Tp* const b) const {
        return comp(*a, *b);
    }
};

class GameDatabase {
 public:
    GameDatabase() = default;

    void Insert(ObjectId id, string name, size_t x, size_t y) {
        GameObject object {id, name, x, y};
        if (data_by_id.find(id) != data_by_id.end()) {
            Remove(id);
        }

        data_by_id.insert({id, object});
        auto obj_ref = &data_by_id.at(id);
        data_by_position[{x, y}].insert(obj_ref);
        data_by_name[name].insert(obj_ref);
    }

    void Remove(ObjectId id) {
        if (data_by_id.find(id) != data_by_id.end()) {
            GameObject *object_to_del = &data_by_id.find(id)->second;

            data_by_id.erase(data_by_id.find(id));
            (data_by_name.find({object_to_del->name}))\
                                ->second.erase(object_to_del);
            (data_by_position.find({object_to_del->x, object_to_del->y}))\
                                ->second.erase(object_to_del);
        }
    }

    vector<GameObject> DataByName(string name) const {
        vector <GameObject> result;
        auto it = data_by_name.find(name);
        if (it == data_by_name.end()) {
            return result;
        }
        for (auto obj : it->second) {
            result.push_back(*obj);
        }
        return result;
    }

    vector<GameObject> DataByPosition(size_t x, size_t y) const {
        vector <GameObject> result;
        auto it = data_by_position.find({x, y});
        if (it == data_by_position.end()) {
            return result;
        }
        for (auto obj : it->second) {
            result.push_back(*obj);
        }
        return result;
    }

    vector<GameObject> Data() const {
        vector <GameObject> result;
        for (auto obj : data_by_id) {
            result.push_back(obj.second);
        }
        return result;
    }

 private:
    std::map<ObjectId, GameObject, std::greater<ObjectId>> data_by_id;
    std::map<std::pair<size_t, size_t>, \
        std::set<GameObject*, \
            DereferenceCompare<GameObject, std::greater>>> data_by_position;
    std::unordered_map<string, \
        std::set<GameObject*, \
            DereferenceCompare<GameObject, std::greater>>> data_by_name;
};
