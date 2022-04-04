#include <string>
#include <map>
#include <utility>
class Object {
 public:
    virtual std::string ToString() const = 0;
    virtual ~Object() {}
};

class ObjectCreator : public Object {
 public:
    explicit ObjectCreator(std::string object_id) : object_id_(object_id) {}
    std::string ToString() const override {
        return object_id_;
    }
 private:
    std::string object_id_;
};

Object* new_apple() {
    return new ObjectCreator("apple!");
}

Object* new_list() {
    return new ObjectCreator("list");
}

Object* new_yet() {
    return new ObjectCreator("yet another identifier");
}

class Factory {
 public:
    Factory() {
        objects_creators.insert(std::make_pair("apple!", new_apple));
        objects_creators.insert(std::make_pair("list", new_list));
        objects_creators.insert(std::make_pair \
                                ("yet another identifier", new_yet));
    }

    Object* Create(const std::string& object_id) {
        auto obj_creator = objects_creators.find(object_id);
        if (obj_creator != objects_creators.end()) {
            return obj_creator->second();
        } else {
            return 0;
        }
    }

    void Register(const std::string& object_id, \
                    std::function<Object*()> creator) {
        if (objects_creators.find(object_id) == objects_creators.end()) {
            objects_creators.insert(std::make_pair(object_id, creator));
        } else {
            return;
        }
    }

 private:
    std::map<std::string, std::function<Object*()>> objects_creators;
};
