#include <cassert>
#include <chrono>
#include <execution>
#include <functional>
#include <iostream>
#include <new>
#include <numeric>
#include <thread>
#include <vector>

constexpr auto cacheline = std::hardware_destructive_interference_size;

struct time_guard {
  using clock = std::chrono::steady_clock;

  time_guard() : start(clock::now()) {}
  ~time_guard() {
    using std::chrono::microseconds;
    std::cout << "elapsed "
              << std::chrono::duration_cast<microseconds>(clock::now() - start)
              << std::endl;
  }

  clock::time_point start;
};

template <typename T> struct aligned {
  alignas(cacheline) T val;

  aligned() = default;
  aligned(T val) : val(val) {}
  aligned &operator+=(const aligned &other) {
    val += other.val;
    return *this;
  }
  aligned operator+(T other_val) const { return val + other_val; }
  aligned operator+(const aligned &other) const { return val + other.val; }
  operator T() const { return val; }
};

template <typename T> aligned<T> operator+(T val, const aligned<T> &other) {
  return other + val;
}

template <typename Iterator, typename T> struct AccumulateBlock {
  void operator()(Iterator first, Iterator last, T &result) const {
    // result = std::accumulate(first, last, result);
    while (first != last) {
      result += *first;
      ++first;
    }
  }
};

template <typename Iterator, typename T>
T Accumulate(Iterator first, Iterator last, T init) {
  const auto length = std::distance(first, last);
  if (!length)
    return init;
  const auto min_work_per_thread = 50000uz;
  const auto max_threads =
      (length + min_work_per_thread - 1) / min_work_per_thread;

  const auto hardware_threads = std::thread::hardware_concurrency();
  const auto num_threads =
      std::min(hardware_threads != 0 ? hardware_threads : 2uz, max_threads);
  const auto block_size = (length + num_threads - 1) / num_threads;

  // std::vector<aligned<T>> results(num_threads);
  std::vector<T> results(num_threads);
  std::vector<std::thread> threads;
  Iterator block_start = first;
  for (auto i = 0uz; block_start < last; ++i) {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);
    block_end = block_end > last ? last : block_end;
    threads.emplace_back(
        [
            // block = AccumulateBlock<Iterator, aligned<T>>()
            block = AccumulateBlock<Iterator, T>(), &dst = results[i],
            block_start,
            block_end] mutable { block(block_start, block_end, dst); });
    block_start = block_end;
  }

  for (auto &entry : threads)
    entry.join();
  return std::accumulate(results.begin(), results.end(), init);
}

int main() {
  using clock = std::chrono::steady_clock;
  using std::chrono::microseconds;

  std::vector<size_t> numbers(100000000);
  std::iota(numbers.begin(), numbers.end(), 0uz);
  size_t my, std_;
  {
    time_guard t;
    my = Accumulate(numbers.begin(), numbers.end(), 0uz);
  }
  {
    time_guard t;
    std_ = std::accumulate(numbers.begin(), numbers.end(), 0uz);
  }
  assert(my == std_);
}
