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