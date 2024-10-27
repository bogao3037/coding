/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

template <typename T>
class my_unique
{
public:
    // Constructor
    explicit my_unique(T *ptr = nullptr) : ptr_(ptr)
    {
        std::cout << "Constructor" << std::endl;
    }

    // Destructor
    ~my_unique()
    {
        if (ptr_)
        {
            delete ptr_;
        }
    }

    // Copy constructor and assignment operator deleted
    my_unique(const my_unique &) = delete;
    my_unique &operator=(const my_unique &) = delete;

    // Move constructor
    my_unique(my_unique &&other) noexcept : ptr_(other.ptr_)
    {
        std::cout << "Move constructor" << std::endl;
        other.ptr_ = nullptr;
    }

    // Move assignment operator
    my_unique &operator=(my_unique &&other) noexcept
    {
        std::cout << "assignment operator" << std::endl;
        if (this != &other)
        {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    // Move constructor for inheritance
    template <typename U>
    my_unique(my_unique<U> &&other)
    {
        std::cout << "U Move constructor" << std::endl;
        if ((void *)this != (void *)&other)
        {
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
    }

    // Move Assignment for inheritance
    template <typename U>
    my_unique &operator=(my_unique<U> &&other)
    {
        std::cout << "U assignment operator" << std::endl;
        if ((void *)this != (void *)&other)
        {
            delete ptr_;
            this->ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    // Member functions
    T *get() const noexcept
    {
        return ptr_;
    }

    T *release() noexcept
    {
        T *temp = ptr_;
        ptr_ = nullptr;
        return temp;
    }

    void reset(T *ptr = nullptr) noexcept
    {
        delete ptr_;
        ptr_ = ptr;
    }

    T &operator*() const noexcept
    {
        return *ptr_;
    }

    T *operator->() const noexcept
    {
        return ptr_;
    }

    explicit operator bool() const noexcept
    {
        return ptr_ != nullptr;
    }

    T *ptr_;
};

template <typename T, typename... ParamT>
my_unique<T> my_make_unique(ParamT &&...params)
{
    return my_unique<T>(new T(std::forward<ParamT>(params)...));
};

class Shape
{
public:
    Shape()
    {
        cout << "Shape" << endl;
    }
    virtual void draw() = 0;
    virtual ~Shape()
    {
        cout << "~Shape" << endl;
    };
};
class Circle : public Shape
{
public:
    Circle(int r) : rad(r) {

                    };
    void draw()
    {
        cout << "Circle rad:=" << rad << endl;
    };
    int rad;
    virtual ~Circle()
    {
        cout << "~Circle rad:=" << rad << endl;
    };
};

class Square : public Shape
{
public:
    Square(int s) : side(s) {

                    };
    void draw()
    {
        cout << "Square side:=" << side << endl;
    };
    int side;
    virtual ~Square()
    {
        cout << "Square Destructor side:=" << side << endl;
    };
};

int main()
{
    my_unique<Shape> x = my_make_unique<Circle>(10);
    x->draw();
    return 0;
}
