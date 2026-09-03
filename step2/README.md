# CMAKE TUTORIAL STEP1
> Lưu ý: hướng dẫn này sử dụng cmake 3.31 trên ubuntu jammy (22.04)

## cmake language
CMake cung cấp một ngôn ngữ lập trình chuyên dụng, có khả năng thực hiện mọi thao tác cần thiết trong quá trình xây dựng phần mềm. Việc nắm vững các nguyên lý cơ bản của ngôn ngữ này là điều cần thiết khi chúng ta viết các tập lệnh CMake phức tạp hơn. 

Ngôn ngữ này được gọi là `CMake Language`. Trong giao tiếp hàng ngày, người ta thường gọi nó là `CMakeLang`.

## Background

Trong CMakeLang, chỉ có hai kiểu dữ liệu cơ bản, đó là `string` và `list`. 

Mọi đối tượng trong CMake đều là `string`. `list` thực chất cũng là những `string`, trong đó dấu chấm phẩy được dùng làm ký tự phân cách các phần tử trong `list`.

Tạo ra một biến:
```cmake
set(var "world")
```
Giá trị của một biến có thể được truy cập bằng cách sử dụng cấu trúc dấu ngoặc nhọn. Để in ra sử dụng `message()`:

Ví dụ 1:
```cmake
set(var "World!")
message("Hello ${var}")
```
Kiểm tra bằng cách:
```bash
cmake -P CMakeLists.txt
```
> Lưu ý rằng chế độ cmake -P được gọi là `script mode`. Chế độ này thông báo cho CMake rằng tệp tin này không nhằm mục đích chứa các lệnh `project()` . Chúng ta không tạo ra bất kỳ phần mềm nào cả; thay vào đó, chúng ta chỉ sử dụng CMake như một công cụ dùng để giải thích các lệnh mà thôi.



Những giá trị được coi là `đúng` bao gồm `True`, `On`, `Yes`, cùng các chuỗi biểu diễn các số khác không. Ngược lại, các giá trị `False`, `Off`, `No`, `0`, `Ignore`, `NotFound` và chuỗi rỗng đều được coi là `sai`.


Các danh sách là những chuỗi ký tự chứa dấu chấm phẩy. Lệnh `list()` rất hữu ích để thao tác với các danh sách này. Nhiều cấu trúc trong CMake đều yêu cầu việc sử dụng quy ước này. Ví dụ, chúng ta có thể sử dụng lệnh foreach() để lặp qua từng phần tử trong danh sách.

Ví dụ 2:
```cmake
set(fruits "Banana;Apple")
list(APPEND fruits "Cucumber")
message("${fruits}")
foreach(fruit IN LISTS fruits)
    message("Hello, ${fruit}")
endforeach()
```

## Macros, Functions, and Lists

CMake cho phép chúng ta tự tạo ra các hàm và macro riêng. 

Ví dụ 3:
```cmake
macro(MyMacro MacroArgument)
    message("${MacroArgument}\n\t\tFrom Macro")
endmacro()

function(MyFunc FuncArgument)
  MyMacro("${FuncArgument}\n\tFrom Function")
endfunction()

MyFunc("From TopLevel")
```

macro() gần giống việc CMake thay thế lời gọi macro bằng phần nội dung của macro ngay tại vị trí gọi nó. Vì vậy, macro không tạo ra một scope riêng; các thay đổi biến bên trong macro có thể ảnh hưởng đến scope nơi macro được gọi.

> Lưu ý: Trong CMake 3.25, tùy chọn return(PROPAGATE) được thêm vào.

Ví dụ 4:
```cmake
cmake_minimum_required(VERSION 3.25)
function(test1)
    set(name1 "John")
    set(name1 "${name1}" PARENT_SCOPE)
endfunction()

function(test2)
    set(name2 "Smith")
    return(PROPAGATE name2)
endfunction(test2)

test1()
test2()

message("${name1}")
message("${name2}")
```


Khi mở rộng biến bằng `${ListVar}` , chúng ta sẽ nhận được tên của danh sách đó. Nếu mở rộng tên đó bằng `${${ListVar}}` , chúng ta sẽ nhận được các giá trị mà danh sách đó chứa.

Ví dụ 5:
```cmake
set(ListVar "MyList")
set(MyList "Banana;Tomato")

message("${ListVar}")
message("${${ListVar}}")

function(FuncAppend ListVar Value)
    set(${ListVar} "${${ListVar}};${Value}")
    set(${ListVar} "${${ListVar}}" PARENT_SCOPE)    
endfunction(FuncAppend)

FuncAppend(${ListVar} "Cucumber")
message("${${ListVar}}")
```


## Câu lệnh điều kiện 

`if` Dùng để kiểm tra điều kiện.

```cmake
if(condition)
    # code
elseif(another_condition)
    # code
else()
    # code
endif()
```

Ví dụ:

```cmake
set(Value "Hello")

if(Value STREQUAL "Hello")
    message("Value is Hello")
else()
    message("Value is not Hello")
endif()
```

---

Các toán tử điều kiện thường dùng

`So sánh chuỗi`

```cmake
if(A STREQUAL B)
```

Kiểm tra `A` và `B` có bằng nhau hay không.

```cmake
if(A MATCHES regex)
```

Kiểm tra `A` có khớp với biểu thức chính quy `regex` hay không.

Ví dụ:

```cmake
if("HelloFoo" MATCHES "Foo")
    message("Found Foo")
endif()
```

`So sánh số`

```cmake
if(A LESS B)       # A < B
if(A GREATER B)    # A > B
if(A EQUAL B)      # A == B
```

Ngoài ra:

```cmake
if(A LESS_EQUAL B)       # A <= B
if(A GREATER_EQUAL B)    # A >= B
```

`Logic`

```cmake
if(A AND B)
if(A OR B)
if(NOT A)
```

Có thể kết hợp:

```cmake
if(A AND (B OR C))
    message("True")
endif()
```
`Kiểm tra biến tồn tại với DEFINED`
Có thể dùng:
```cmake
if(DEFINED variable)
```

Ví dụ:
```
set(Name "John")

if(DEFINED Name)
    message("Name is defined")
else()
    message("Name is not defined")
endif()
```
---
## Vòng lặp
`foreach()`

Dùng để lặp qua các phần tử.

```cmake
foreach(item IN LISTS MyList)
    message("${item}")
endforeach()
```

Ví dụ:

```cmake
set(MyList "Apple;Banana;Orange")

foreach(item IN LISTS MyList)
    message("${item}")
endforeach()
```

Kết quả:

```text
Apple
Banana
Orange
```

---

`foreach()` với nhiều giá trị trực tiếp

Có thể truyền các giá trị trực tiếp:

```cmake
foreach(item Apple Banana Orange)
    message("${item}")
endforeach()
```

Kết quả:

```text
Apple
Banana
Orange
```

---

`foreach()` với `RANGE`

Dùng để lặp qua một khoảng số:

```cmake
foreach(i RANGE 5)
    message("${i}")
endforeach()
```

Kết quả:

```text
0
1
2
3
4
5
```

Có thể chỉ định giá trị bắt đầu và kết thúc:

```cmake
foreach(i RANGE 1 5)
    message("${i}")
endforeach()
```

Kết quả:

```text
1
2
3
4
5
```

---

`while()` Lặp khi điều kiện còn đúng:

```cmake
while(condition)
    # code
endwhile()
```

Ví dụ:

```cmake
set(i 0)

while(i LESS 5)
    message("${i}")
    math(EXPR i "${i} + 1")
endwhile()
```

Kết quả:

```text
0
1
2
3
4
```

---

`break()` Dừng vòng lặp ngay lập tức:

```cmake
foreach(item IN LISTS MyList)

    if(item STREQUAL "Banana")
        break()
    endif()

    message("${item}")

endforeach()
```

Nếu list là:

```text
Apple;Banana;Orange
```

thì chỉ in:

```text
Apple
```

---

`continue()` Bỏ qua **lần lặp hiện tại** và chuyển sang phần tử tiếp theo:

```cmake
foreach(item IN LISTS MyList)

    if(item STREQUAL "Banana")
        continue()
    endif()

    message("${item}")

endforeach()
```

Kết quả:

```text
Apple
Orange
```


## include
`include()` dùng để nạp và thực thi một file CMake khác trong file CMake hiện tại.

Ví dụ, tạo cấu trúc:
```bash
.
├── CMakeLists.txt
└── config.cmake
```

File `config.cmake`:
```cmake
set(PROJECT_NAME "my_project")
set(PROJECT_VERSION "3.31")
```

File `CMakeLists.txt`
```cmake
include(config.cmake)

message("project: ${PROJECT_NAME}")
message("version: ${PROJECT_VERSION}")
```
> Tham khảo `example/step2/example6`

## Variadic arguments — ARGV và ARGN

function() và macro() có thể nhận số lượng đối số thay đổi.

Có hai biến đặc biệt:

ARGV: chứa toàn bộ các đối số được truyền vào.
ARGN: chứa các đối số sau những đối số đã được khai báo.

Xét ví dụ sau:
```cmake
function(Test first second)
    message("first: ${first}")
    message("second: ${second}")
    message("ARGV: ${ARGV}")
    message("ARGN: ${ARGN}")
endfunction()
Test(Banana Tomatoe Apple)
```
> Tham khảo `example/step2/example7`

Kết quả:

```bash
first: Banana
second: Tomatoe
ARGV: Banana;Tomatoe;Apple
ARGN: Apple
```
## Quoting — dấu `"`
Trong CMake, mọi object cơ bản đều là string nên dấu `"` không phải lúc nào cũng bắt buộc.

Tuy nhiên, khi chuỗi chứa khoảng trắng thì cần dùng dấu " ":
```cmake
set(name "Donal Trump")
```
Quote khi expand list:
```cmake
set(fruits "Apple;Banana;Orange")
```
Không quote:
```cmake
message(${fruits})
```
CMake có thể truyền các phần tử list thành các argument riêng biệt.