//
// Created by Maksym Pasichnyk on 26.04.2023.
//

module;

#include <atomic>
#include <memory>
#include <utility>

export module cpp_script:gc;

template<typename T>
class ManagedShared;

class ManagedObject {
public:
    explicit ManagedObject() : strong_references_(1) {}
    virtual ~ManagedObject() {}

    void retain() {
        strong_references_.fetch_add(1, std::memory_order_relaxed);
    }

    void release() {
        if (strong_references_.fetch_sub(1, std::memory_order_release) == 1) {
            std::atomic_thread_fence(std::memory_order_acquire);
            delete this;
        }
    }

private:
    std::atomic_uint64_t strong_references_;
};

template<typename T>
class ManagedShared {
public:
    explicit ManagedShared() : object_(nullptr) {}
    explicit ManagedShared(T* other) : object_(other) {}

    ManagedShared(const ManagedShared<T>& other) : object_(other.get()) {
        if (object_) {
            object_->ManagedObject::retain();
        }
    }

    template<typename U>
    ManagedShared(const ManagedShared<U>& other) : object_(other.get()) {
        if (object_) {
            object_->ManagedObject::retain();
        }
    }

    ManagedShared(ManagedShared<T>&& other) noexcept : object_(other.get()) {
        other.detach();
    }

    template<typename U>
    ManagedShared(ManagedShared<U>&& other) noexcept : object_(other.get()) {
        other.detach();
    }

    ~ManagedShared() {
        if (object_) {
            object_->ManagedObject::release();
        }
    }

public:
    constexpr auto get() const noexcept -> T* {
        return object_;
    }

    constexpr void detach() noexcept {
        object_ = nullptr;
    }

public:
    auto operator=(const ManagedShared<T>& other) -> ManagedShared<T>& {
        if (object_ != other.get()) {
            if (object_ != nullptr) {
                object_->ManagedObject::release();
            }
            object_ = other.get();
            if (object_ != nullptr) {
                object_->ManagedObject::retain();
            }
        }
        return *this;
    }

    template<typename U>
    auto operator=(const ManagedShared<U>& other) -> ManagedShared<T>& {
        if (object_ != other.get()) {
            if (object_ != nullptr) {
                object_->ManagedObject::release();
            }
            object_ = other.get();
            if (object_ != nullptr) {
                object_->ManagedObject::retain();
            }
        }
        return *this;
    }

    auto operator=(ManagedShared<T>&& other) -> ManagedShared<T>& {
        if (object_ != other.get()) {
            if (object_) {
                object_->ManagedObject::release();
            }
            object_ = other.get();
            other.detach();
        }
        return *this;
    }

    template<typename U>
    auto operator=(ManagedShared<U>&& other) -> ManagedShared<T>& {
        if (object_ != other.get()) {
            if (object_) {
                object_->ManagedObject::release();
            }
            object_ = other.get();
            other.detach();
        }
        return *this;
    }

    constexpr explicit operator bool() const noexcept {
        return object_ != nullptr;
    }

    constexpr auto operator->() const noexcept -> T* {
        return object_;
    }

    constexpr auto operator*() const noexcept -> T& {
        return *object_;
    }

    auto operator<=>(const ManagedShared<T>& other) const = default;

private:
    T* object_;
};

template<typename T>
ManagedShared(T*) -> ManagedShared<T>;

template<typename T>
ManagedShared(ManagedShared<T>) -> ManagedShared<T>;