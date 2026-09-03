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