# CMAKE TUTORIAL STEP3
> Lưu ý: hướng dẫn này sử dụng cmake 3.31 trên ubuntu jammy (22.04)

## Configuration and Cache Variables
Các dự án được xây dựng bằng CMake thường có những biến cấu hình riêng biệt.

CMake cung cấp nhiều cách khác nhau để người dùng hoặc tiến trình thực thi có thể truyền các thông số cấu hình này. Tuy nhiên, cách đơn giản và hiệu quả nhất chính là sử dụng các flag -D.

## Background

Nếu chúng ta có một dự án CMake dùng để phát triển phần mềm nén dữ liệu, và phần mềm này hỗ trợ nhiều thuật toán nén khác nhau, Chúng ta nên để người tạo ra bản cài đặt của dự án quyết định xem nên sử dụng thuật toán nào.

Ví dụ 1:
```cmake
if(COMPRESSION_SOFTWARE_USE_ZLIB)
    message("I will use Zlib!")
    # ...
endif()
if(COMPRESSION_SOFTWARE_USE_ZSTD)
  message("I will use Zstd!")
  # ...
endif()
```
Kết quả:
```bash
$ cmake -DCOMPRESSION_SOFTWARE_USE_ZLIB=ON -P CMakeLists.txt 
I will use Zlib!
```


Chúng ta cần đặt các giá trị mặc định hợp lý cho các tùy chọn cấu hình này, đồng thời cần có cách để giải thích mục đích của từng tùy chọn. Chức năng này được thực hiện bởi lệnh `option()`.

```cmake
option(COMPRESSION_SOFTWARE_USE_ZLIB "Support Zlib compression" ON)
option(COMPRESSION_SOFTWARE_USE_ZSTD "Support Zstd compression" ON)
```


Các tên biến được tạo ra bởi các cờ -D và option() không phải là các biến thông thường, mà là các biến được lưu trong bộ nhớ đệm.

Các biến này có thể được truy cập từ mọi nơi trong chương trình. Giá trị của chúng rất khó thay đổi sau khi được thiết lập lần đầu. 

Nếu một biến được thiết lập một lần, giá trị đó sẽ được giữ nguyên cho đến khi có cờ -D nào đó thay đổi giá trị đó.


Mặc dù các biến trong bộ nhớ đệm thường không thể được thay đổi, chúng vẫn có thể bị “che khuất” bởi các biến thông thường. 

Ví dụ 2:
```cmake
set(VERSION "3.31" CACHE STRING "A cache variable")
set(VERSION "3.32")

message(${VERSION})
unset(VERSION)
message(${VERSION})
```

Kết quả:
```bash
3.32
3.31
```

> Lưu ý: Chế độ Script chỉ những tham số được đánh dấu bằng -D và nằm trước tham số -P trong lệnh mới được xử lý và có thể được sử dụng trong script đang chạy.


**Bài tập 1:**

Trong project Tutorial, có hai thành phần chính:

`MathFunctions`: thư viện tính toán.
`Tutorial`: chương trình executable sử dụng thư viện MathFunctions.

Giả sử người dùng chỉ muốn sử dụng thư viện `MathFunctions` và không muốn build chương trình `Tutorial`. Vì vậy, cần tạo một `option` để người dùng có thể bật/tắt việc build `Tutorial`.

Yêu cầu
- Tạo một option có tên `TUTORIAL_BUILD_UTILITIES` Option này dùng để quyết định có cấu hình và build executable `Tutorial` hay không.
- Giá trị mặc định ON. Nghĩa là mặc định project vẫn build Tutorial.
- Khi người dùng cấu hình:

```cmake
cmake -B build -DTUTORIAL_BUILD_UTILITIES=OFF
```
thì project không được tạo executable `Tutorial`, chỉ build phần `MathFunctions`.

Cấu trúc:
```bash
.
├── CMakeLists.txt
├── inc
│   └── MathFunctions.h
└── src
    ├── MathFunctions.c
    └── Tutorial.c
```

File `CMakeList.txt`:
```cmake
cmake_minimum_required(VERSION 3.31)
project(tutorial_project)


option(TUTORIAL_BUILD_UTILITIES "Lua cho build tutoral" ON)

add_library(MathFunctions)
target_sources(MathFunctions
    PRIVATE
        src/MathFunctions.c
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            inc
        FILES
            inc/MathFunctions.h
)

if(TUTORIAL_BUILD_UTILITIES )
    add_executable(Tutorial)
    target_sources(Tutorial
        PRIVATE
            src/Tutorial.c
    )
    target_link_libraries(
        Tutorial
        PRIVATE
            MathFunctions
    )
    message("Build tutorial")
else()
    message("Khong build tutorial")
endif()
```
> Tham khảo `example/step3/exercise1`

configure & generate và build
```bash
# mặc định ON
cmake -S . -B build
# hoặc OFF
cmake -S . -B build -DTUTORIAL_BUILD_UTILITIES=OFF
cmake --build build
```

Kiểm tra thử file `CMakeCache.txt` sẽ tìm thấy đoạn sau:
```cmake
//Lua chon build tutoral
TUTORIAL_BUILD_UTILITIES:BOOL=
```

Chúng ta có thể thay đổi giá trị từ OFF thành ON , sau đó chạy lại quy trình xây dựng. Như vậy, chúng ta sẽ có tập tin thực thi Tutorial.

## CMakePresets.json
Việc quản lý các giá trị cấu hình này có thể trở nên khá phức tạp nếu không được xử lý đúng cách. Trong các hệ thống CI, việc ghi lại các giá trị cấu hình này là điều cần thiết.

Hầu hết các môi trường phát triển tích hợp cũng có cơ chế riêng để kiểm soát cấu hình của CMake. Giải pháp có sẵn trong CMake, được gọi là `CMake Presets`.

Các thiết lập sẵn của CMake được lưu trữ trong hai loại tệp tin tiêu chuẩn: 
- `CMakePresets.json`: là một phần của dự án và cần được theo dõi trong hệ thống quản lý nguồn mã nguồn
- `CMakeUserPresets.json`: dùng để thiết lập cho người dùng cục bộ, và không nên được theo dõi trong hệ thống quản lý nguồn mã nguồn.

Ví dụ:
```json
{
    "version": 4,
    "configurePresets": [
        {
            "name": "example-preset",
            "cacheVariables": {
                "EXAMPLE_FOO": "Bar",
                "EXAMPLE_QUX": "Baz"
            }
        }
    ] 
}
```
Thay vì:
```bash
cmake -B build -DEXAMPLE_FOO=Bar -DEXAMPLE_QUX=Baz
```

Sử dụng các giá trị đặt sẵn:
```cmake
cmake -B build --preset example-preset
```

CMake sẽ tìm các tệp có tên `CMakePresets.json` và `CMakeUserPresets.json`, tải nội dung cấu hình được lưu trong các tệp đó vào hệ thống.

> Bắt đầu từ CMake 4.4, CMake cũng có thể tải các thiết lập sẵn từ bất kỳ tệp tin nào được chỉ định bằng ký hiệu `cmake --presets-file`

Các thiết lập sẵn cũng hỗ trợ việc sử dụng các macro và biến nhất định. những biến này có thể được mở rộng ngay bên trong các thiết lập sẵn đó. 

Ví dụ sau sử dụng macro `sourceDir` để xác định thư mục lưu trữ kết quả xây dựng dự án, đồng thời bỏ qua thông số -B khi cấu hình dự án.

```json
{
    "name": "example-preset",
    "binaryDir": "${sourceDir}/build"
}
```

Cấu trúc cơ bản của một preset trong CMakePresets.json:
```json
{
    "version": 4, // Preset format version
    "configurePresets": [
        {
            "name": "name-of-preset",
            // ...
        }
    ]
}
```

Cách sử dụng preset:
```bash
cmake --list-presets # Liệt kê các preset
cmake --preset <name-of-preset> # configure
```

Các Preset macro:
|Macro|Ý nghĩa|
|---|---|
|${sourceDir}|Thư mục gốc của source project|
|${sourceParentDir}|Thư mục cha của ${sourceDir}|
|${sourceDirName}|Tên thư mục source|
|${presetName}|Tên của preset hiện tại|
|${generator}|Generator được sử dụng|

Enviroment variables có 2 cú pháp quan trọng:
```bash
$env{VARIABLE} # lấy environment variable của môi trường hiện tại.
$penv{VARIABLE} # lấy environment variable từ process cha (parent environment).
```

property quan trọng trong preset:
| Property         | Dùng để làm gì                   |
| ---------------- | -------------------------------- |
| `name`           | Tên preset                       |
| `displayName`    | Tên hiển thị                     |
| `description`    | Mô tả preset                     |
| `generator`      | Chọn CMake generator             |
| `binaryDir`      | Chọn thư mục build               |
| `cacheVariables` | Thiết lập CMake cache variables  |
| `environment`    | Thiết lập environment variables  |
| `toolchainFile`  | Chọn toolchain file              |
| `architecture`   | Chọn kiến trúc, ví dụ `x64`      |
| `toolset`        | Chọn toolset/compiler            |
| `inherits`       | Kế thừa preset khác              |
| `condition`      | Điều kiện để preset được sử dụng |
