### Definition

+ “Lambda” means nameless

+ **Definition of "lambda expression":** an expression that returns a function object

### Types of Functions

+ Function Pointer
  
    ```
    void (*myProcess)(int)
    myProcess = std::exit;

    myProcess(42);
    ```

+ Overloaded Operator & Function Call Operator

    + **Function call operator** `operator()`
  
        ```
        void operator()()
        bool operator()(int value)
        double operator()(double d1, double d2)
        ```

    + Other operators are called **overloaded operators**

        ```
        bool opeartor==(const T &value)
        bool opeartor>(const T &value)
        ```

+ Function Object
  
    + **Function object data type:** class or structure with a **function call operator** method
    
    + **Function object:** an instance of a function object data type. It is a *callable object*.

        ```
        class Printer {
            void operator()(std::string str);
        }

        Printer printer;

        printer("hello"); // ok
        printer.operator()("hello"); // also ok
        ```

+ `std::function`

    + A container, holds a single **function pointer** or a **function object**

### Lambda Function

```
[capture clause] (parameter list) -> return type { body }
```

**Capture Clause**

+ by value

  + capture is by const value
  + `x` will be **copied into** the function object
  + original variable does not need to stay alive
  + **capture occurs when the lambda expression is evaluated**
  + **if any captured value will be modified in the body,** `lambda` **must be declared**

    ```
    auto myLamb = [x] () mutable { return ++ x; };
    ```

+ by reference

  + ensure captured **lvalue** references remain alive for the entire lifetime of the closure

    ```
    auto myLamb = [&x] () { return ++x; };
    ```

+ C++14: generalized capture

    + by value

        ```
        [varA = 10]
        [varB = x]
        ```

    + by reference

        ```
        [&varC = y]
        // y must be declared in the local scope
        ```

    + by move

        ```
        [varD = std::move(z)]
        // move occurs when the lambda expression is evaluated
        ```

+ capture all variables **in the body of the expression**

    + by value

        ```
        auto myLamb = [=] () { return x + m_data; }
        ```

    + by reference

        ```
        auto myLamb = [&] () { return x + m_data; }
        ```

**Parameter List**

+ C++11

    +  default parameters were not permitted

+ C++14

    + parameters can have a data type of `auto`
    + default parameters are supported

        ```
        auto myLamb = [ ] (const std::string &data, uint max = 20)
            { return data.substr(0, max); };
        ```

**Return Type**

+ C++11

    + Multiple return -> must specify the return type

+ C++14

    + Multiple returns must deduce to the same type **OR** it must be specified

**Examples**

+ Capture `std::unique_ptr` in a lambda expression

    + capturing a move-only type means **the closure (the lambda expression) is move-only** -> `myLamb` can only be moved, which is not copyable

        ```
        std::unique_ptr<Widget> myPtr = std::make_unique<Widget>();

        auto myLamb = [ capturedPtr = std::move(myPtr) ] ( )
        { return capturedPtr->computeSize(); };
        ```