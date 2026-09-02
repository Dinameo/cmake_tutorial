# CMAKE TUTORIAL
> Lưu ý: hướng dẫn này sử dụng cmake 3.31 trên ubuntu jammy (22.04)
## Các loại generator thường sử dụng
Bảng các generator thường sử dụng:
|Single-Configuration|Multi-Configuration|
|:---:|:--:|
|Ninja|Ninja Multi-Config|
|Unix Makfiles|Visual Studio (All version)|
|FASTBuild|Xcode|


Khi sử dụng Single-Configuration, build type được lựa chọn dựa trên biến môi trường CMAKE_BUILD_TYPE. Ngoài ra cũng có thể cấu hình trực tiếp khi gọi thông qua cmake `-DCMAKE_BUILD_TYPE=<config>`

Khi sử dụng công cụ tạo Multi-Configuration, build configuration cần thiết sẽ được xác định vào lúc tạo ra sản phẩm, thông qua cơ chế riêng của hệ thống tạo cấu hình đó, hoặc bằng cách sử dụng tùy chọn cmake `--build --config .`



## Other basic
```bash 
cmake -S <dir>
```

Xác định thư mục gốc của dự án, nơi mà CMake sẽ tìm thấy dự án cần được xây dựng. Thư mục này chứa tệp tin gốc CMakeLists.txt

```bash
cmake -B <dir>
```

Xác định thư mục dùng để lưu các tệp liên quan đến quá trình xây dựng.

```bash
cmake --build <dir>
```
Chạy hệ thống xây dựng trong thư mục được chỉ định.

Đối với các công cụ hỗ trợ nhiều cấu hình khác nhau, người dùng có thể chọn cấu hình mong muốn bằng cách:

```bash
cmake --build <dir> --config <cfg>
```
Để chỉ định generator trực tiếp bằng cmake:
```bash
cmake -G <generator>
```

## Xây dựng dựng một dự án 

Nên tạo thư mục build và biên dịch từ đó

```bash
mkdir build
cd build
cmake ..
make
```
Có thể thay lệch make bằng
```bash
cmake --build .
```
Nó sẽ gọi make hoặc bất cứ công cự build nào đang dùng.

Với Cmake bản mới hơn nên sử dụng lệnh sau:
```bash
cmake -S . -B build
cmake --build build
```
- -S là vị trí chứa CMakeLists.txt
- -B là thư mục buid sẽ được tạo

## Chọn trình biên dịch
Phải được thực hiện trong lần đầu tiên ở một thư mục trống. Để chọn Clang:
```bash
# ~/package/build
CC=clang CCX=clang++ cmake ..
```
Hoặc export nó nếu sử dụng git bash
```bash
# ~/package/build
export CC=clang CXX=clang++ cmake..
```
## Lựa chọn generator

Có thể biên dịch bằng nhiều công cụ khác nhau (make thường là mặc định). Để xem tất cả công cụ mà cmake biết trên hệ thống hãy chạy:

```bash
# ~/package/build
cmake --help
```
Và có thể chọn một công cụ bằng -G"My tool" hoặc biến môi trường `CMAKE_GENERATOR`. Nên chọn công cụ trong lần gọi CMake đầu tiên (như chọn trình biên dịch).





## Getting started with cmake
Không phải mọi thư mục trong một dự án phần mềm đều cần có tệp CML. Tuy nhiên, rất nên đặt tệp CML tại thư mục gốc của dự án. Tệp CML này sẽ đóng vai trò là điểm khởi đầu cho quá trình cấu hình ban đầu của CMake. Trong tệp CML này, luôn cần phải có hai lệnh nhất định ở phần đầu hoặc gần đầu tệp.

```bash
cmake_minimum_required(VERSION 3.23)

project(MyProjectName)
```

`cmake_minimum_required()`: là công cụ đảm bảo tính tương thích mà CMake cung cấp cho nhà phát triển dự án. Nếu một phiên bản CMake mới hơn được sử dụng để xử lý tập tin CML chứa đoạn mã trên, thì CMake vẫn sẽ hoạt động giống hệt như khi sử dụng CMake 3.23.

`project()`: Lệnh này thông báo cho CMake rằng những nội dung được ghi sau đó chính là mô tả chi tiết về một dự án phần mềm cụ thể (khác với các script kiểu shell). 

CMake sẽ thực hiện nhiều kiểm tra khác nhau để đảm bảo rằng môi trường hiện tại phù hợp để xây dựng phần mềm.

Bao gồm việc kiểm tra sự hiện diện của các công cụ biên dịch và các công cụ cần thiết khác để xây dựng phần mềm; đồng thời xác định các thông số như kiểu truyền dữ liệu giữa máy chủ và máy đích.

> Mặc dù CMake hỗ trợ cả các lệnh viết bằng chữ hoa, chữ thường và kết hợp cả hai, nhưng các lệnh viết bằng chữ thường được ưu tiên sử dụng.

## Building an Executable
Lệnh này dùng để tạo ra một `target` trong quá trình xây dựng phần mềm. Trong thuật ngữ của CMake, `target` chính là tên mà lập trình viên đặt cho tập hợp các thuộc tính liên quan đến một thành phần cụ thể của phần mềm.

Một số ví dụ về các thông tin mà `target` cần được theo dõi bao gồm:
- Các loại tệp tin liên quan đến công cụ/ứng dụng (tệp thực thi, thư viện, tập hợp các tệp định nghĩa, v.v.)
- Source files 
- Include directories
- Output name of exec or lib
- Dependencies
- Compiler and linker flags

Việc sử dụng lệnh add_executable() rất đơn giản: chỉ cần chỉ định tên mà chúng ta muốn dùng để gọi `target` đó.

Ví dụ:
```bash
add_executable(MyProgram)
```
Bây giờ khi chúng ta đã xác định được tên của `target` cần xử lý, chúng ta có thể bắt đầu liên kết các thuộc tính với `target` đó. Các tệp nguồn mà chúng ta muốn sử dụng để xây dựng và liên kết với `target` đó cũng được coi là những thuộc tính của `target` đó. Lệnh chính để thực hiện việc này là `target_sources()` , trong đó tên của `target` được đưa vào làm đối số, kèm theo một hoặc nhiều tập hợp tệp tin.

Ví dụ:
```bash
target_sources(MyProgram
  PRIVATE
    main.cxx
)
```

Trong CMake, các đường dẫn thường là đường dẫn tuyệt đối, hoặc là đường dẫn tương đối so với vị trí của tệp tin `CMAKE_CURRENT_SOURCE_DIR`
Trong đó:
- PRIVATE: là một từ khóa biểu thị phạm vi áp dụng của các tệp tin đó

Thông thường, không có gì phụ thuộc vào các tệp thực thi. 

Các chương trình và thư viện khác không cần phải liên kết với các tệp thực thi này, cũng không cần kế thừa các thông tin liên quan đến chúng. 

Vì vậy, phạm vi áp dụng phù hợp ở đây là `PRIVATE` . Điều này giúp CMake hiểu rằng thuộc tính này chỉ thuộc về `MyProgram` mà thôi, và không thể được kế thừa.

```text
Bài tập: Tạo một project C/C++ sử dụng CMake để build chương trình calculator thành một executable. 

Chương trình nhận 2 số nguyên từ command line thông qua argc và argv, sau đó tính và in ra tổng của hai số.
```

Cấu trúc thư mục:
```bash
.
├── CMakeLists.txt
└── main.c
```

File `CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.22)
project(calculator_app)
add_executable(calculator)
target_sources(calculator
    PRIVATE
        main.c
)
```
> Tham khảo code tại [example/step1/caculator_simple_bt1](example/step1/caculator_simple_bt1)

## Build a library
Cách thức hoạt động của lệnh này giống hệt lệnh `add_executable()` , nhưng được áp dụng riêng cho việc tạo thư viện.

Ví dụ:
```cmake
add_library(MyLib)
```

Để mô tả một tập hợp các tệp tin tiêu đề, chúng ta sẽ sử dụng cách ký hiệu `FILE_SET`

Ví dụ:

```cmake
target_sources(MyLib
    PRIVATE
        lib_implementation.c
    PUBLIC
        FILE_SET myHeaders
        TYPE HEADERS
        BASE_DIRS
            include
        FILES
            include/library_header.
)
```
Trong đó:
- `FILE_SET` \<name\>: Đây là một "handle" mà ta có thể sử dụng để mô tả tập hợp dữ liệu này trong các bối cảnh khác nhau.
- `TYPE` \<type\>: chính là loại tệp mà chúng ta đang đề cập
- `BASE_DIRS`: đây chính là những vị trí mà các trình biên dịch sẽ sử dụng để tìm kiếm các tệp tin header.
- `FILES`: là danh sách các tệp tin, tương tự như danh sách các nguồn mã nguồn được đề cập trước đó.

Một cách viết ngắn gọn hơn:
```cmake
target_sources(MyLib
    PRIVATE
        lib_implementation.c
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            include
        FILES
            include/library_header.
)
```
Lúc này `HEADERS` vừa là `FILE_SET` vừa là `TYPE`

## Linking Together Libraries and Executables
Để kết hợp thư viện của mình với các tệp thực thi, húng ta cần sử dụng một lệnh mới, đó là `target_link_libraries()`. Về cơ bản, lệnh này dùng để mô tả mối quan hệ giữa các tệp thực thi với nhau.

Ví dụ:
```cmake
target_link_libraries(MyProgram
  PRIVATE
    MyLibrary
)
```

### Scope keyword
Có ba từ khóa chính: `PRIVATE`, `INTERFACE` và `PUBLIC`:

- `PRIVATE`: chỉ được sử dụng bởi chính `target` sở hữu nó. Các `target` khác khi liên kết với target này sẽ **không được nhận** những thuộc tính `PRIVATE`.

- `INTERFACE`: không được sử dụng bởi chính `target` sở hữu nó, mà chỉ được cung cấp cho các `target` liên kết với nó. Thường dùng cho **header-only library** hoặc các thuộc tính mà chỉ target sử dụng library cần.

- `PUBLIC`: được sử dụng bởi cả chính `target` sở hữu nó **và** các `target liên kết với nó`. Nói cách khác, thuộc tính `PUBLIC` vừa áp dụng cho target hiện tại, vừa được truyền cho các target sử dụng nó.

> Lưu ý: Không có `BASE_DIR` mặc định là thư mực nguồn hiện 
```txt
Bài tập: Cải tiến bài tập Calculator trước đó bằng cách tách phần khai báo hàm và phần cài đặt thành header và source file. Sử dụng FILE_SET HEADERS để khai báo header public cho target.
```

Cấu trúc dự án:
```bash
.
├── CMakeLists.txt
├── include
│   └── math.h
└── src
    ├── main.c
    └── math.c
```

File `CMakeLists.txt`:
```cmake
cmake_minimum_required(VERSION 3.31)
project(calculator_app)

add_library(math)
target_sources(math
    PRIVATE
        src/math.c
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            include
        FILES
            include/math.h
)

add_executable(calculator)
target_sources(calculator
    PRIVATE
        src/main.c
)
target_link_libraries(calculator
    PRIVATE
        math
)
```
> Tham khảo code tại [example/step1/caculator_simple_bt2](example/step1/caculator_simple_bt2)

## Subdirectories
Lệnh `add_subdirectory()` cho phép chúng ta kết hợp các tệp CML nằm trong các thư mục con của dự án.

Ví dụ:
```cmake
add_subdirectory(SubdirectoryName)
```
Khi một thư mục con được xử lý bởi CMake, tất cả các đường dẫn tương đối được ghi trong tệp CML của thư mục con đó đều được tính từ vị trí của thư mục con đó, chứ không phải từ tệp CML ở cấp độ cao nhất.

```txt
Bài tập: Cải tiến bài tập Calculator hiện tại bằng cách tách cấu hình của calculator và math thành các CMakeLists.txt riêng trong các thư mục con.
```

File `math/CMakeLits.txt`:
```cmake
add_library(math)
target_sources(math
    PRIVATE
        math.c
    PUBLIC
        FILE_SET HEADERS
        FILES
            math.h
)
```

File `calculator/CMakeLits.txt`:
```cmake
add_executable(calculator)
target_sources(calculator
    PRIVATE
    main.c
)
target_link_libraries(calculator
    PRIVATE
        math
)
```

File `CMakeLists.txt`:
```cmake
cmake_minimum_required(VERSION 3.31)
project(calculator_app)

add_subdirectory(math)
add_subdirectory(calculator)
```
> Tham khảo code tại [example/step1/caculator_simple_bt3](example/step1/caculator_simple_bt3)


Do việc tái tổ chức này, chúng ta cần phải dọn dẹp thư mục chứa các tệp cài đặt ban đầu trước khi tiến hành quá trình cài đặt lại. Nếu không làm như vậy, thư mục chứa các tệp cài đặt mới (`target`) sẽ xung đột với tệp thực thi đã được tạo trước đó (`target`). Chúng ta có thể thực hiện việc này bằng cách sử dụng tùy chọn `--clean-first`


