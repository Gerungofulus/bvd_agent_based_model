cmake_minimum_required(VERSION 3.9)
project(bvd_agent_based_model_develop)

set(CMAKE_CXX_STANDARD 11)

add_executable(bvd_agent_based_model_develop
        include/AdvancedOutput.h
        include/BVD_Random_Number_Generator.h
        include/BVDContainmentStrategy.h
        include/BVDOptions.h
        include/BVDSettings.h
        include/CommandlineOptions.h
        include/Cow.h
        include/CowWellFarm.h
        include/CowWellFarmManager.h
        include/CSV_Reader.h
        include/CSVFileHandler.h
        include/Events.h
        include/Farm.h
        include/FarmManager.h
        include/FileHandler.h
        include/HDF5Handler.h
        include/Herd.h
        include/Initializer.h
        include/Market.h
        include/Model_Constants.h
        include/Output.h
        include/OutputTable.h
        include/Simple_One_Herd_Farm.h
        include/SimpleFarmManager.h
        include/Slaughterhouse.h
        include/SlaughterHouseManager.h
        include/Small_One_Herd_Farm.h
        include/SmallFarmManager.h
        include/SQLiteHandler.h
        include/System.h
        include/TableBasedOutput.h
        include/TradeFilter.h
        include/Utilities.h
        projectImports/Catch/catch.hpp
        projectImports/FakeIt/fakeit.hpp
        projectImports/inih/cpp/INIReader.cpp
        projectImports/inih/cpp/INIReader.h
        projectImports/inih/examples/ini_dump.c
        projectImports/inih/examples/ini_example.c
        projectImports/inih/examples/ini_xmacros.c
        projectImports/inih/examples/INIReaderExample.cpp
        projectImports/inih/tests/unittest.c
        projectImports/inih/tests/unittest_string.c
        projectImports/inih/ini.c
        projectImports/inih/ini.h
        src/AdvancedOutput.cpp
        src/Breeding_module_parameter_gnu.cpp
        src/BVD_Random_Number_Generator.cpp
        src/BVDContainmentStrategy.cpp
        src/BVDOptions.cpp
        src/BVDSettings.cpp
        src/CommandlineOptions.cpp
        src/Cow.cpp
        src/CowWellFarm.cpp
        src/CowWellFarmManager.cpp
        src/CSVFileHandler.cpp
        src/Events.cpp
        src/Farm.cpp
        src/FarmManager.cpp
        src/FileHandler.cpp
        src/HDF5Handler.cpp
        src/Herd.cpp
        src/Initializer.cpp
        src/Market.cpp
        src/Output.cpp
        src/OutputTable.cpp
        src/programm.cpp
        src/Simple_One_Herd_Farm.cpp
        src/SimpleFarmManager.cpp
        src/Slaughterhouse.cpp
        src/SlaughterHouseManager.cpp
        src/Small_One_Herd_Farm.cpp
        src/SmallFarmManager.cpp
        src/SQLiteHandler.cpp
        src/System.cpp
        src/TableBasedOutput.cpp
        src/TradeFilter.cpp
        src/Utilities.cpp
        tests/test_cow.cpp
        tests/test_csv_reader.cpp
        tests/test_event.cpp
        tests/test_herd.cpp
        tests/test_initializer.cpp
        tests/test_market.cpp
        tests/test_output.cpp
        tests/test_system.cpp
        tests/tests.cpp
        config.h)

include_directories(include
        /usr/include/hdf5/serial
        projectImports
        projectImports/inih
        projectImports/inih/cpp
        .)