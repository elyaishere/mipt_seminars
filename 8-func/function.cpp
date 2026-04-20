#include <functional>
#include <memory>

bool fooo(int, char *) {}

int main() {
  std::function<bool(int, char *)> f = [](int, char *) { return true; };

  // struct base
  // {
  //     base() = default;
  //     virtual ~base() { }
  //     virtual base* clone() = 0;
  //     virtual bool operator()(int, char*) = 0;
  //     virtual void destroy() = 0;
  //     virtual void destroy_deallocate() = 0;
  // };

  // template<typename F>
  // struct func : base
  // {
  //     F __func_;

  //     func(F const& t) : __func_(t) {}
  //     func(F&& t) : __func_(std::move(t)) {}

  //     base* clone() override { return new func(__func_); }

  //     bool operator()(int a, char* b) override {
  //         return std::invoke_r<bool>(__func_, a, b);
  //     }

  //     void destroy() override { __func_.~F(); }
  //     void destroy_deallocate() override { delete this; }
  // };

  // struct function
  // {
  //     // storage for small callables
  //     typename aligned_storage<3 * sizeof(void*)>::type __buf_;

  //     base * __f_;

  //     template<typename F>
  //     function(F&& f) {
  //         using _Fun = __func<F>;

  //         if constexpr (sizeof(_Fun) <= sizeof(__buf_)) {
  //             __f_ = ::new (std::addressof(__buf_)) _Fun(std::move(f));
  //         }
  //         else {
  //             __f_ = new _Fun(std::move(f));
  //         }
  //     }

  //     function(const function& other) : __f_(other.__f_ ? other.__f_->clone()
  //     : nullptr) { }

  //     function(function&& other) {
  //         if (other.__f_ == nullptr)
  //             __f_ = nullptr;
  //         else if ((void*)other.__f_ == &other.__buf_) {
  //             other.__f_->clone(__buf_);
  //         } else {
  //             __f_     = other.__f_;
  //             __f.__f_ = nullptr;
  //         }
  //     }

  //     ~function() {
  //         if ((void*)__f_ == &__buf_)
  //             __f_->destroy();
  //         else if (__f_)
  //             __f_->destroy_deallocate();
  //     }

  //     bool operator()(int a, char* b) {
  //         if (__f_ == nullptr)
  //             std::__throw_bad_function_call();

  //         return (*__f_)(a, b);
  //     }
  // };
}
