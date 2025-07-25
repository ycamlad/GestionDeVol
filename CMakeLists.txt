cmake_minimum_required(VERSION 4.0)
project(Gestion_de_vol)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# ==================== GoogleTest ====================
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# ==================== Qt ====================
find_package(Qt5 COMPONENTS Widgets Svg Sql REQUIRED)
include_directories(Sources DataBase)

# ==================== Main Executable ====================
add_executable(Gestion_de_vol main.cpp
        Sources/Aeroport.cpp
        Sources/Arrivee.cpp
        Sources/ContratException.cpp
        Sources/Depart.cpp
        Sources/validationFormat.cpp
        Sources/Vol.cpp
        Sources/VolException.h
        Sources/VolDejaPresentException.h
        Sources/VolAbsentException.h
        Interface/AjouterArrivee.cpp
        Interface/AjouterDepart.cpp
        Interface/FenetrePrincipal.cpp
        Interface/SupprimerVol.cpp
        DataBase/databasemanager.cpp
        DataBase/databasemanager.h
        DataBase/DataBaseException.h
        Interface/Login.cpp
        Interface/Login.h
        Interface/Login.ui
        Interface/Modifiervol.cpp
        Interface/Modifiervol.h
        Interface/Modifiervol.ui
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(TARGET Gestion_de_vol POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "Running windeployqt for Debug build..."
            COMMAND "C:/Qt/5.15.2/mingw81_64/bin/windeployqt.exe"
            "$<TARGET_FILE:Gestion_de_vol>"
    )
endif()

#add_custom_command(TARGET Gestion_de_vol POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        "C:/Users/chris/OneDrive/Documents/Voldb.db"
#        "$<TARGET_FILE_DIR:Gestion_de_vol>/Voldb.db"
#)


target_link_libraries(Gestion_de_vol
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Svg
        Qt5::Sql
)
qt5_add_resources(GENERATED_RESOURCES Resources/resources.qrc)
target_sources(Gestion_de_vol PRIVATE ${GENERATED_RESOURCES})

add_executable(Console
        Console/main.cpp
        DataBase/databasemanager.cpp
        Sources/Aeroport.cpp
        Sources/Arrivee.cpp
        Sources/ContratException.cpp
        Sources/Depart.cpp
        Sources/validationFormat.cpp
        Sources/Vol.cpp
        Sources/VolException.h
        Sources/VolDejaPresentException.h
        Sources/VolAbsentException.h
        DataBase/DataBaseException.h
)

target_link_libraries(Console
        Qt5::Sql
)
if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

# ==================== Test Executables ====================
enable_testing()

add_executable(volTests
        Sources/tests/VolTesteur.cpp
        Sources/Aeroport.cpp
        Sources/Vol.cpp
        Sources/ContratException.cpp
        Sources/validationFormat.cpp
)
target_link_libraries(volTests gtest_main)

add_executable(departTests
        Sources/tests/DepartTesteur.cpp
        Sources/Depart.cpp
        Sources/Vol.cpp
        Sources/ContratException.cpp
        Sources/validationFormat.cpp
)
target_link_libraries(departTests gtest_main)

add_executable(arriveTests
        Sources/tests/ArriveeTesteur.cpp
        Sources/Arrivee.cpp
        Sources/Vol.cpp
        Sources/ContratException.cpp
        Sources/validationFormat.cpp
)
target_link_libraries(arriveTests gtest_main)

add_executable(aeroportTests
        Sources/tests/AeroportTesteur.cpp
        Sources/Aeroport.cpp
        Sources/ContratException.cpp
        Sources/validationFormat.cpp
        Sources/VolException.h
        Sources/VolDejaPresentException.h
        Sources/VolAbsentException.h
        Sources/Arrivee.cpp
        Sources/Vol.cpp
        Sources/Depart.cpp
)
target_link_libraries(aeroportTests gtest_main)

add_executable(DBTests
        DataBase/tests/DatabaseManagerTesteur.cpp
        Sources/Aeroport.cpp
        Sources/ContratException.cpp
        Sources/validationFormat.cpp
        Sources/VolException.h
        Sources/VolDejaPresentException.h
        Sources/VolAbsentException.h
        Sources/Arrivee.cpp
        Sources/Vol.cpp
        Sources/Depart.cpp
        DataBase/DataBaseException.h
)
target_link_libraries(DBTests gtest_main)
# ==================== Google Test Discovery ====================
include(GoogleTest)
gtest_discover_tests(volTests)
gtest_discover_tests(departTests)
gtest_discover_tests(arriveTests)
gtest_discover_tests(aeroportTests)
gtest_discover_tests(DBTests)

# ==================== Manual Test Registration (Optional) ====================
add_test(NAME VolTests COMMAND volTests)
add_test(NAME DepartTests COMMAND departTests)
add_test(NAME ArriveeTests COMMAND arriveTests)
add_test(NAME AeroportTests COMMAND aeroportTests)
add_test(NAME DBtests COMMAND dbTests)
