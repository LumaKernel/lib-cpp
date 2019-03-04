// @ memory_pool
// @snippet memory_pool

// memory_pool {{{
#include <memory>
#include <vector>
template < int POOL_SIZE >
struct memory_pool {
  template < class T >
  struct core {
  public:
    using value_type = T;
    using size_type = size_t;
    using pointer = value_type *;
    using const_pointer = const value_type *;

  private:
    pointer start;
    std::shared_ptr< std::vector< pointer > > ptr;
    std::shared_ptr< size_type > idx;

  public:
    core() {
      ptr = std::shared_ptr< std::vector< pointer > >(
          new std::vector< pointer >(POOL_SIZE));
      idx = std::shared_ptr< size_type >(new size_type);
      start = static_cast< pointer >(malloc(sizeof(value_type) * POOL_SIZE));
      clear();
    }
    core(const core &a) noexcept {
      start = a.start;
      ptr = a.ptr;
      idx = a.idx;
    }
    ~core() {
      if(ptr.use_count() == 1) free(start);
    }
    void clear() {
      *idx = 0;
      iota(ptr->begin(), ptr->end(), start);
    }
    pointer allocate(size_type n) {
      if(n != 1) throw std::bad_alloc();
      if(rest() == 0) throw std::bad_alloc();
      return (*ptr)[(*idx)++];
    }
    void deallocate(pointer p, size_type) noexcept {
      if(p) (*ptr)[--*idx] = p;
    }
    size_type max_size() const { return 1; }
    size_type rest() const { return POOL_SIZE - *idx; }
    bool operator==(const core &a) const noexcept { return start == a.start; }
    bool operator!=(const core &a) const noexcept { return !(*this == a); }
  };
};
// }}}

// @new
// @ memory_pool_no_deallocate
// @snippet memory_pool_no_deallocate
// @alias no_deallocate_memory_pool
// @alias pool_no_deallocate

// memory_pool_no_deallocate {{{
#include <memory>
#include <vector>
#include <iostream>
template < int POOL_SIZE >
struct memory_pool_no_deallocate {
  template < class T >
  struct core {
  public:
    using value_type = T;
    using size_type = size_t;
    using pointer = value_type *;
    using const_pointer = const value_type *;

  private:
    pointer start, head;
    size_type *use_cnt;

  public:
    core() {
      start = static_cast< pointer >(std::malloc(sizeof(value_type) * POOL_SIZE));
      use_cnt = new size_type(1);
      clear();
    }
    core(const core &a) noexcept {
      start = a.start;
      head = a.head;
      use_cnt = a.use_cnt;
      ++*use_cnt;
    }
    ~core() {
      --*use_cnt;
      if(*use_cnt) {
        delete use_cnt;
        free(start);
      }
    }
    void clear() { head = start; }
    pointer allocate(size_type n) {
      if(n != 1) throw std::bad_alloc();
      if(rest() == 0) throw std::bad_alloc();
      return head++;
    }
    void deallocate(pointer, size_type) noexcept {
      std::cerr << "do not use deallocate" << std::endl;
      std::abort();
    }
    size_type max_size() const { return 1; }
    size_type rest() const { return POOL_SIZE - (head - start); }
    bool operator==(const core &a) const noexcept { return start == a.start; }
    bool operator!=(const core &a) const noexcept { return !(*this == a); }
  };
};
// }}}

// @new
// @ memory_block
// @snippet memory_block

// memory_block {{{
#include <memory>
#include <vector>
template < size_t BLOCK_SIZE >
struct memory_block {
  template < class T >
  struct core {
  public:
    using value_type = T;
    using size_type = size_t;
    using pointer = value_type *;
    using const_pointer = const value_type *;

  private:
    std::shared_ptr< std::vector< pointer > > starts;
    std::shared_ptr< std::vector< pointer > > ptr;
    std::shared_ptr< size_type > idx;

  public:
    core() {
      starts = std::shared_ptr< std::vector< pointer > >(new std::vector< pointer >);
      ptr = std::shared_ptr< std::vector< pointer > >(new std::vector< pointer >);
      idx = std::shared_ptr< size_type >(new size_type);
      clear();
    }
    core(const core &a) noexcept {
      starts = a.starts;
      ptr = a.ptr;
      idx = a.idx;
    }
    ~core() {
      if(ptr.use_count() == 1)
        for(auto start : *starts) free(start);
    }
    void expand() {
      starts->push_back(static_cast< pointer >(malloc(sizeof(value_type) * BLOCK_SIZE)));
      ptr->resize(ptr->size() + BLOCK_SIZE);
      iota(ptr->end() - BLOCK_SIZE, ptr->end(), starts->back());
    }
    void clear() {
      *idx = 0;
      for(size_type i = 0; i < starts->size(); i++)
        iota(ptr->begin() + i * BLOCK_SIZE, ptr->begin() + i * BLOCK_SIZE + BLOCK_SIZE,
             (*starts)[i]);
    }
    pointer allocate(size_type n) {
      if(n != 1) throw std::bad_alloc();
      if(rest() == 0) expand();
      return (*ptr)[(*idx)++];
    }
    void deallocate(pointer p, size_type) noexcept {
      if(p) (*ptr)[--*idx] = p;
    }
    size_type max_size() const { return 1; }
    bool operator==(const core &a) const noexcept { return idx == a.idx; }
    bool operator!=(const core &a) const noexcept { return !(*this == a); }

  private:
    int rest() const { return ptr->size() - *idx; }
  };
};
// }}}

// @new
// @ memory_block_no_deallocate
// @snippet memory_block_no_deallocate
// @alias no_deallocate_memory_block
// @alias block_no_deallocate

// memory_block_no_deallocate {{{
#include <memory>
#include <vector>
#include <iostream>
template < size_t BLOCK_SIZE >
struct memory_block_no_deallocate {
  static_assert(BLOCK_SIZE > 0, "BLOCK_SIZE must be positive");
  template < class T >
  struct core {
  public:
    using value_type = T;
    using size_type = size_t;
    using pointer = value_type *;
    using const_pointer = const value_type *;

  private:
    std::shared_ptr< std::vector< pointer > > starts;
    std::shared_ptr< size_type > idx;
    std::shared_ptr< size_type > block_id;

  public:
    core() {
      starts = std::shared_ptr< std::vector< pointer > >(new std::vector< pointer >);
      idx = std::shared_ptr< size_type >(new size_type);
      block_id = std::shared_ptr< size_type >(new size_type);
      clear();
    }
    core(const core &a) noexcept {
      starts = a.starts;
      idx = a.idx;
      block_id = a.block_id;
    }
    ~core() {
      if(idx.use_count() == 1)
        for(auto start : *starts) free(start);
    }
    void expand() {
      *idx = 0;
      starts->push_back(static_cast< pointer >(malloc(sizeof(value_type) * BLOCK_SIZE)));
      *block_id = starts->size() - 1;
    }
    void clear() {
      *idx = 0;
      *block_id = 0;
    }
    pointer allocate(size_type n) {
      if(n != 1) throw std::bad_alloc();
      if(rest() == 0) expand();
      if(*idx == BLOCK_SIZE) *idx = 0, (*block_id)++;
      return (*starts)[*block_id] + (*idx)++;
    }
    void deallocate(pointer, size_type) noexcept {
      std::cerr << "do not use deallocate" << std::endl;
      std::abort();
    }
    size_type max_size() const { return 1; }
    bool operator==(const core &a) const noexcept { return idx == a.idx; }
    bool operator!=(const core &a) const noexcept { return !(*this == a); }

  private:
    size_type rest() const {
      return starts->size() * BLOCK_SIZE - *idx - *block_id * BLOCK_SIZE;
    }
  };
};
// }}}
