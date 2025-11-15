# Circular Buffer Implementation

A dynamic circular buffer (ring buffer) implementation in C++ with automatic resizing capabilities. This project demonstrates memory management, data structure design, and efficient buffer operations.

## Features

- **Dynamic Resizing**: Automatically grows when full, shrinks when significantly underutilized
- **Efficient Operations**: O(1) insertions and retrievals with circular wrapping
- **Memory Management**: Proper allocation/deallocation with dynamic memory handling
- **Multiple Insert Methods**: Support for single characters, C-strings, and std::strings
- **Flexible Retrieval**: Get single characters or multiple characters at once

## Technical Implementation

### Key Concepts
- **Circular Logic**: Uses modulo arithmetic to wrap around buffer boundaries
- **Head/Tail Pointers**: Tracks insertion and removal positions
- **Chunked Growth**: Grows in fixed chunks (8 elements) for efficiency
- **Automatic Shrinking**: Reduces memory footprint when buffer is underutilized

### Time Complexity
- Insert (single): O(1) amortized
- Insert (multiple): O(n) where n is number of elements
- Get: O(1)
- Grow/Shrink: O(n) where n is current buffer size

### Space Complexity
- O(capacity) where capacity grows in chunks of 8

## Usage

```cpp
#include "CircBuf.h"

// Create buffer with initial capacity
CircBuf buffer(16);

// Insert data
buffer.insert('A');
buffer.insert("Hello");
buffer.insert(std::string("World"));

// Retrieve data
char c = buffer.get();              // Get single character
std::string str = buffer.get(5);    // Get 5 characters
std::string all = buffer.flush();   // Get all and clear buffer

// Check status
size_t size = buffer.size();
size_t cap = buffer.capacity();
```

## Building and Running

```bash
# Compile
g++ -std=c++11 -o circbuf_test CircBuf.cpp main.cpp

# Run
./circbuf_test
```

## Challenges Overcome

1. **Wrapping Logic**: Implementing correct behavior when head/tail wrap around buffer boundaries
2. **Memory Management**: Ensuring proper cleanup and avoiding memory leaks during resize operations
3. **Efficient Growth**: Balancing between memory usage and reallocation frequency
4. **Edge Cases**: Handling empty buffer, full buffer, and single-element scenarios

## What I Learned

- Deep understanding of circular buffer data structures
- Manual memory management in C++ (new/delete, avoiding leaks)
- Modulo arithmetic for circular indexing
- Trade-offs between memory efficiency and performance

## Future Enhancements

- Template implementation for generic types (not just char)
- Thread-safety with mutex locks
- Iterator support for STL compatibility
- Configurable chunk size

## Technologies Used

- **Language**: C++
- **Concepts**: Data Structures, Memory Management, Object-Oriented Design
- **Tools**: g++, Make

## Author

Ethan Kidd - [GitHub Profile](https://github.com/kiddethan071)

## License

This project is available for educational purposes.
