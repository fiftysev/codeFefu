#pragma once

#include <memory>
#include "Test.hpp"

namespace smart_pointer {
// `exception` class definition

class exception : std::exception {
        using base_class = std::exception;
        using base_class::base_class;
};

template<
            typename T,
            typename Allocator
    >class SmartPointer {
        // don't remove this macro
        ENABLE_CLASS_TESTS;

     public:
        using value_type = T;

        explicit SmartPointer(value_type* ptr = nullptr) :
                core((ptr == nullptr ? nullptr : new Core(ptr))) {}

        SmartPointer(const SmartPointer &another_ptr) :
                core((another_ptr.core == nullptr ?\
                        nullptr : another_ptr.core)) {
            if (this->core != nullptr) {
                this->core->count_of_refs++;
            }
        }

        SmartPointer(SmartPointer &&another_ptr) {
            this->core = another_ptr.core;
            another_ptr.core = nullptr;
        }

        SmartPointer &operator=(const SmartPointer &another_ptr) {
            this->~SmartPointer();
            this->core = another_ptr.core;
            if (this->core != nullptr) {
                this->core->count_of_refs++;
            }
            return *this;
        }

        SmartPointer &operator=(SmartPointer &&another_ptr) {
            this->~SmartPointer();
            this->core = another_ptr.core;
            another_ptr.core = nullptr;
            return *this;
        }
        //
        SmartPointer &operator=(value_type *ptr) {
            this->~SmartPointer();
            ptr == nullptr ? this->core = nullptr : this->core = new Core(ptr);
            return *this;
        }

        ~SmartPointer() {
            if (this->core != nullptr) {
                if (this->core->count_of_refs <= 1) {
                    delete this->core;
                } else {
                    this->core->count_of_refs--;
                }
            }
        }

        // return reference to the object of class/type T
        // if SmartPointer contains nullptr throw `SmartPointer::exception`
        value_type &operator*() {
            if (this->core == nullptr || this->core->pointer == nullptr) {
                throw smart_pointer::exception();
            } else {
                return *(this->core->pointer);
            }
        }

        const value_type &operator*() const {
            if (this->core == nullptr || this->core->pointer == nullptr) {
                throw smart_pointer::exception();
            } else {
                return *(this->core->pointer);
            }
        }

        // return pointer to the object of class/type T
        value_type *operator->() const {
            return this->get();
        }

        value_type *get() const {
            return this->core == nullptr ? nullptr : this->core->pointer;
        }

        // if pointer == nullptr => return false
        operator bool() const {
            return !(this->core == nullptr || this->core->pointer == nullptr);
        }

        // if pointers points to the same address or both null => true
        template<typename U, typename AnotherAllocator>
        bool operator==(const SmartPointer<U, \
        AnotherAllocator> &another_obj) const {
            return static_cast<void *>(this->get()) == \
                static_cast<void *>(another_obj.get());
        }

        // if pointers points to the same address or both null => false
        template<typename U, typename AnotherAllocator>
        bool operator!=(const SmartPointer<U, \
                                AnotherAllocator> &another_obj) const {
            return static_cast<void *>(this->get()) != \
                        static_cast<void *>(another_obj.get());
        }

        // if smart pointer contains non-nullptr => return count owners
        // if smart pointer contains nullptr => return 0
        std::size_t count_owners() const {
            return this->core == nullptr ? 0 : this->core->count_of_refs;
        }

     private:
        class Core {
         public:
            explicit Core(value_type* ptr) : pointer(ptr), count_of_refs(1) {}
            ~Core() {
                if (pointer != nullptr) {
                    delete pointer;
                }
            }
            value_type* pointer;
            size_t count_of_refs;
        };
        Core *core;
    };
}  // namespace smart_pointer
