option(COMPRESSION_SOFTWARE_USE_ZLIB "Support Zlib compression" ON)
option(COMPRESSION_SOFTWARE_USE_ZSTD "Support Zstd compression" ON)

if(COMPRESSION_SOFTWARE_USE_ZLIB)
    message("I will use Zlib!")
    # ...
endif()
if(COMPRESSION_SOFTWARE_USE_ZSTD)
  message("I will use Zstd!")
  # ...
endif()
