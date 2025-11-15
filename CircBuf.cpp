

//Project Summary:


// My main hurdle with this project is the fact that it has been over a year
// since I have take a class using C++ or even C for that matter. Most of my
// time was spent relearning some of the basics and getting myself back up to
// speed with the language. 
// Another hurdle that was challenging were cases of wrapping around the buffer.
// It took a minute to figure out how to handle them in their own cases but towards
// the end of the project I started to get the hang of it and understand how it worked.





#include <iostream>
#include "CircBuf.h"
#include <string> 
#include <sstream>
using namespace std;
using std::string; 

CircBuf::CircBuf(size_t reserve)
{
    max_capacity = ((reserve + CHUNK - 1) / CHUNK) * CHUNK;
    current_size = 0;
    data_ptr = new int[CHUNK];
    tail = 0;
    head = 0;

}

void CircBuf::grow()
{

int new_capacity = max_capacity + CHUNK;
int* new_ptr = new int[new_capacity];

for(int i = 0; i < current_size; ++i){
    int old_index = (tail + i) % max_capacity;
    new_ptr[i] = data_ptr[old_index];
}

delete[] data_ptr;

data_ptr = new_ptr;
max_capacity = new_capacity;
tail = 0;
head = current_size;

}
 
CircBuf::~CircBuf()
{
    delete[] data_ptr;
};

size_t CircBuf::size()
{
    return current_size;
};

size_t CircBuf::capacity()
{
    return max_capacity;
}

void CircBuf::insert(char x)
{
    if (size() == capacity()) {
        grow();
    }

    data_ptr[head] = x;

    head = (head + 1) % max_capacity;

    current_size++;
}

void CircBuf::insert(const string& str)
{
    insert(str.c_str(), str.size());
}

void CircBuf::insert (const char* x, size_t sz)
{

    while (current_size + sz > max_capacity) {
        grow();
    }

    for (size_t i = 0; i < sz; ++i) {
        data_ptr[head] = x[i];
        head = (head + 1) % max_capacity; 
    }

    current_size += sz;
}

char CircBuf::get()
{
    if (current_size == 0){
        throw std::underflow_error("Buffer is empty.");
    }

    char value = static_cast<char>(data_ptr[tail]);

    tail = (tail + 1) % max_capacity;

    current_size--;

    // if (max_capacity - current_size >= CHUNK){
        
    //     shrink();
    // }

    return value;

}

string CircBuf::get(size_t x)
{

    if (current_size == 0){
        throw std::underflow_error("Buffer is empty.");
    }

    if (x > current_size) {
        x = current_size;
    }

    std::ostringstream strr;

    for (int i = 0; i < x; ++i){
        strr << get();
    }

    return strr.str();

}

string CircBuf::flush(){
    if (current_size == 0){
        throw std::underflow_error("Buffer is empty.");
    }

    std::ostringstream buff;

    buff << get(current_size);

    max_capacity = 0;

    return buff.str();
}

string CircBuf::examine()
{
    std::ostringstream buff;
    buff << "[";

    if (max_capacity == current_size){
        for (int i = 0; i < max_capacity; ++i){
            buff << static_cast<char>(data_ptr[i]);
        }
        buff << ']';
        return buff.str();
    }

    for (size_t i = 0; i < max_capacity; ++i) {
        if ((tail <= head && i >= tail && i < head) ||
            (tail > head && (i >= tail || i < head))) {
            buff << static_cast<char>(data_ptr[i]);
        } else {
            buff << "-";
        }

        // if (i != max_capacity - 1){
        //     buff << "-";
        // }

    }


    buff << "]";
   // std::cout << buff.str() << endl;
    return buff.str();
}

void CircBuf::shrink()
{
    if (max_capacity - current_size < CHUNK) {
        return;
    }

    size_t new_capacity = ((current_size + CHUNK - 1) / CHUNK) * CHUNK;

    if (new_capacity < current_size) {
        return; 
    }

   

    int* new_buffer = new int[new_capacity];

    for (size_t i = 0; i < current_size; ++i) {
        size_t old_index = (tail + i) % max_capacity;
        new_buffer[i] = data_ptr[old_index];     
    }

    delete[] data_ptr;
    data_ptr = nullptr;

    data_ptr = new_buffer;
    max_capacity = new_capacity;
    tail = 0;
    head = current_size;
}




