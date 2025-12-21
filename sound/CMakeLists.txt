cmake_minimum_required(VERSION 3.10)
project(sound_processor)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Исходные файлы
set(SOURCES
    main.cpp
    config/ConfigParser.cpp
    converters/ConverterFactory.cpp
    converters/EchoConverter.cpp
    converters/MixConverter.cpp
    converters/MuteConverter.cpp
    processor/Processor.cpp
    wav/WavReader.cpp
    wav/WavWriter.cpp
)

# Заголовочные файлы
set(HEADERS
    config/ConfigParser.hpp
    converters/Converter.hpp
    converters/ConverterFactory.hpp
    converters/EchoConverter.hpp
    converters/MixConverter.hpp
    converters/MuteConverter.hpp
    exceptions/Exceptions.hpp
    processor/Processor.hpp
    wav/WavReader.hpp
    wav/WavWriter.hpp
)

# Создаем исполняемый файл
add_executable(sound_processor ${SOURCES} ${HEADERS})

# Указываем директории, где искать заголовочные файлы
target_include_directories(sound_processor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
