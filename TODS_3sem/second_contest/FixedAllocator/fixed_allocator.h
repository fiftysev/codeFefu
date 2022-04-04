#pragma once
#include <vector>

template <typename Tp>
class FixedAllocator {
 public:
    explicit FixedAllocator(std::uint64_t page_size) :
        page_allocator_(page_size),
        page_size_(page_size) {}
    Tp* Allocate() {
        Tp * memory_block;

        if (memory_pool.empty()) {
            memory_block = static_cast<Tp *>(page_allocator_.Allocate());
            for (size_t i = 0; i < page_size_; i++) {
                memory_block = 0;
                memory_pool.push_back(memory_block);
            }
        }

        memory_block = *(memory_pool.end() - 1);
        memory_pool.pop_back();
        return memory_block;
    }

    void Deallocate(Tp* p) {
        memory_pool.push_back(p);
    }

    const PageAllocator& InnerAllocator() const noexcept {
     return page_allocator_;
    }

 private:
    PageAllocator page_allocator_;
    uint64_t page_size_;
    std::vector<Tp *> memory_pool;
};
