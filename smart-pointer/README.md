### Definition

**Smart pointers** automatically manage the lifetime of resources.

+ According to RAII idiom (Resource Acquisition Is Initialization)
+ C++ answer to garbage collection
+ Automatic memory management with **reference counting**

### History

+ C++98

    + `std::auto_ptr`

+ C++11

    + `std::unique_ptr`
    + `std::shared_ptr`
    + `std::weak_ptr`

### Details

#### `std::unique_ptr`

+ Replacement of `std::auto_ptr`

+ Does not support copy semantic

    +   Here `foo()` actually returns `std::move(ret)`.

        ```
        std::unique_ptr<int> foo() {
            std::unique_ptr<int> ret(new int(4));
            return ret;
        }
        ```

+ **No overhead in space and time** compared to the raw pointers

#### `std::shared_ptr`

+ Has a **reference** to the resource and the **reference counter**

+ Has **some overhead in time and space** compared to raw pointers

#### `std::weak_ptr`

+ Owns no resource

+ Borrows the resource from an `std::shared_ptr` but can not access it

+ Does not change the reference counter -> **helps to break cycles of** `std::shared_ptr`、

+ 当对象不对另外一个对象拥有**所有权**的时候，尽量用 `std::weak_ptr` 来访问。比如，`company` 这个 class 拥有 `staff` 的 `shared_ptr`，但是 `staff` 的 class 中也希望可以访问 `company` 的时候，则可以用 `std::weak_ptr` （因为员工并不拥有公司的所有权）。

### Concurrency

+ The reference counter inside `std::shared_ptr` is thread-safe. But the control on the resource is **NOT thread-safe**.

+ Solution: `std::atomic<std::shared_ptr<T>>` or `std::atomic_shared_ptr`