# CMAKE TUTORIAL STEP4
> Lưu ý: hướng dẫn này sử dụng cmake 3.31 trên ubuntu jammy (22.04)

## In-Depth CMake Target Commands


Trong bước này, chúng ta sẽ xem xét tất cả các lệnh `target` có sẵn trong CMake.

Chúng ta có thể chia chúng thành ba nhóm: 
- các lệnh được khuyến nghị và thường được sử dụng phổ biến
- Các lệnh nâng cao, đòi hỏi người dùng phải cẩn trọng khi sử dụng
- Các lệnh nên tránh sử dụng trừ khi thực sự cần thiết

|Common/Recommended             |Advanced/Caution                   |Esoteric/Footguns                      |
|-------------------------------|-----------------------------------|---------------------------------------|
|target_compile_definitions()   |get_target_property()              |                                       |
|target_compile_features()      |set_target_properties()            |target_include_directories()           |
|target_link_libraries()        |target_compile_options()           |target_link_directories()              |
|target_sources()               |target_link_options()              |                                       |
|                               |target_precompile_headers()        |                                       |

`get_target_property() và set_target_properties()`
Các lệnh `get_target_property()` và `set_target_properties()` cho phép truy cập trực tiếp vào các thuộc tính của một đối tượng, bằng cách sử dụng tên của các thuộc tính đó. Chúng còn có thể được dùng để gán bất kỳ tên thuộc tính nào cho một đối tượng.


Ví dụ 1:

Cấu trúc:
```bash
.
├── CMakeLists.txt
├── CMakePresets.json
└── example.c
```
File `CMakeLists.txt`:
```cmake
cmake_minimum_required(VERSION 3.31)
project(Example_project)


add_library(Example)
target_sources(Example
    PRIVATE
        example.c
)

set_target_properties(Example
    PROPERTIES
        Key Value
)

get_target_property(KeyVar Example Key)

message("[Key] = ${KeyVar}")
```

config & build:
```bash
cmake -S . --preset=test
```
Kết quả:

```bash
[Key] = Value
-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /mnt/d/cmake/example/step4/example1/build
```

cmake-properties chia thành:
```
CMake Properties
│
├── Directory Properties
│   └── property của directory
│
├── Global Properties
│   └── property toàn CMake
│
├── Target Properties
│   └── property của executable/library
│
├── Test Properties
│   └── property của test
│
├── Source File Properties
│   └── property của source file
│
└── Install Properties
    └── property liên quan install
```

> Tham khảo https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#manual:cmake-properties(7)

`target_precompile_headers()`

Lệnh `target_precompile_headers()` nhận vào một danh sách các tệp header, tương tự như lệnh `target_sources()` . Sau đó, lệnh này tạo ra một tệp header đã được biên dịch trước từ các tệp đó. Tệp header này sẽ được áp dụng tự động cho tất cả các đơn vị dịch thuật trong `target`. Việc này giúp nâng cao hiệu suất quá trình biên dịch.

Ví dụ: 
```cpp
// main.cpp
#include <iostream>
#include <vector>
#include <string>
```
```cpp
// foo.cpp
#include <iostream>
#include <vector>
#include <string>
```
Mỗi lần compiler compile một .cpp, nó lại phải xử lý các file header.

Dùng `target_precompile_headers()`:
```cmake
add_executable(MyApp
    main.cpp
    foo.cpp
    bar.cpp
)
target_precompile_headers(MyApp
    PRIVATE
        <iostream>
        <vector>
        <string>
)
```

`target_compile_features()`

Lệnh target_compile_features() mô tả tiêu chuẩn ngôn ngữ tối thiểu cần được đáp ứng.

- Đã dùng chuẩn cao hơn (không làm gì):
```cmake
set(CMAKE_CXX_STANDARD 23)

target_compile_features(MyApp PRIVATE cxx_std_20)
```

- Compiler mặc định đã đáp ứng (không làm gì)

- Compiler chưa đáp ứng (CMake tự thêm flag)

```cmake
add_executable(MyApp main.cpp)
target_compile_features(MyApp PRIVATE cxx_std_20)
```
Lúc này CMake sẽ sinh lệnh compile kiểu:
```bash
g++ -std=c++20 main.cpp
```

`target_compile_definitions()`

Lệnh target_compile_definitions() dùng để mô tả các thông số cần được biên dịch thành các thuộc tính của đối tượng cần xây dựng. Đây là cơ chế phổ biến nhất để truyền thông tin về cấu hình quá trình biên dịch đến chính mã nguồn. Giống như tất cả các thuộc tính khác, các từ khóa liên quan đến phạm vi áp dụng của các thuộc tính này cũng được sử dụng như đã thảo luận trước đó.

Ví dụ 3:

Cấu trúc: 
```bash
.
├── CMakeLists.txt
└── main.cpp
```

File `CMakeLists.txt`:
```cmake
cmake_minimum_required(VERSION 3.31)
project(Example3)



add_executable(MyApp)
target_sources(MyApp
    PRIVATE
        main.cpp
)

target_compile_definitions(MyApp
    PRIVATE
        DEBUG
        VER="1.0"
)
```

File `main.cpp`:
```cpp
#include <iostream>
using namespace std;
int main() {
    #ifndef DEBUG
    cout << "Che do binh thuong" << endl;
    #else
    cout << "Che do debug" << endl;
    #ifdef VER
    cout << "Version: " << VER << endl;
    #endif
    #endif   
}
```
`target_compile_options() và target_link_options()`

Đôi khi bạn muốn tự chỉ định option cụ thể cho compiler hoặc linker

- `target_compile_options()`: Dùng để thêm option cho compiler khi biên dịch source.
- `target_link_options()`: Dùng để thêm option cho linker khi tạo executable/library.

Ví dụ 4:

File `main.cpp`:
```cpp
#include <iostream>

using namespace std;
int main() {
    int x;
    return 0;
}
```
File `CMakeLists.txt`:
```cmake
cmake_minimum_required(VERSION 3.31)
project(Example4)

add_executable(MyApp)
target_sources(MyApp
    PRIVATE
        main.cpp
)
set(WARNING "ON")
if(WARNING STREQUAL "ON")
target_compile_options(MyApp
    PRIVATE
        -Wall
)
endif()
```

build bình thường:
```bash
cmake -S . -B build
cmake --build build
```

output:
```bash
...
[100%] Built target MyApp
```

đưa `WARNING` về `OFF`:
```bash
cmake -S . -B build -DWARNING=OFF
cmake --build build
```
output:
```bash
/mnt/d/cmake/example/step4/example4/main.cpp: In function ‘int main()’:
/mnt/d/cmake/example/step4/example4/main.cpp:5:9: warning: unused variable ‘x’ [-Wunused-variable]
    5 |     int x;
      |         ^
[100%] Linking CXX executable MyApp
[100%] Built target MyApp
```
> -Wall là một compiler option của GCC/Clang, dùng để bật một nhóm cảnh báo (warning) khi biên dịch

Để đảm bảo rằng dự án của chúng ta tương thích với nhiều loại trình biên dịch khác nhau, chúng ta chỉ nên chuyển các tùy chọn tương thích cho trình biên dịch mà thôi.

Chúng ta có thể thực hiện điều này bằng cách kiểm tra biến CMAKE_<LANG>_COMPILER_FRONTEND_VARIANT. Biến này cho biết kiểu các `` mà trình biên dịch hỗ trợ.

Ví dụ:
```cmake
message("${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}")
```
output:
```bash
GNU
```
`target_include_directories() và target_link_directories()`

- `target_include_directories()`: Dùng để chỉ cho compiler biết nơi tìm header (.h, .hpp). CMake sẽ thêm đường dẫn include vào quá trình compile
- `target_link_directories()`: Dùng để chỉ cho linker biết nơi tìm library. CMake sẽ thêm đường dẫn lib vào quá trình link, tương ứng

```txt
Bài tập 1. Project có cấu trúc sau:
project/
├── CMakeLists.txt
├── src/
│   └── main.cpp
└── third_party/
    ├── include/
    │   └── math.h
    └── lib/
        └── libmath.a
Bạn được cung cấp sẵn: third_party/lib/libmath.a

Bạn không có source code của math và cũng không có CMakeLists.txt của thư viện này.
```

File `CMakeLists.txt`:
```cmake
cmake_minimum_required(VERSION 3.31)

project(MyProject)

add_executable(MyApp)
target_sources(MyApp
    PRIVATE
        src/main.cpp
)

target_include_directories(MyApp
    PRIVATE
        third_party/include
)
target_link_directories(MyApp
    PRIVATE
        third_party/lib
)
target_link_libraries(MyApp
    PRIVATE
        math
)
```

Nếu không dùng cmake:
```bash
g++ -Ithird_party/include -c src/main.cpp -o main.o
g++ main.o -Lthird_party/lib -lmath -o MyApp
```