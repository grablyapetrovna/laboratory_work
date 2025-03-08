#include <iostream>
#include "shared-ptr.cpp"

int main() {
    SharedPtr<int> ptr1(new int(42));
    std::cout << "ptr1 use count: " << ptr1.use_count() << "\n"; 

    {
        SharedPtr<int> ptr2 = ptr1;
        std::cout << "ptr1 use count: " << ptr1.use_count() << "\n"; 
        std::cout << "ptr2 use count: " << ptr2.use_count() << "\n"; 
    } 

    std::cout << "ptr1 use count: " << ptr1.use_count() << "\n"; 

    return 0;
}
