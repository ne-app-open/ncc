# Copyright 2024-2026, Ne.app, all rights reserved.
# Licensed under the Apache License, Version 2.0 (See accompanying
# file LICENSE or copy at http://www.apache.org/licenses/LICENSE-2.0)
# Official repository: https://github.com/ne-app-open/ncc

if (DEFINED NCC_BUILD_COMMONCORE_POSIX)

    message("Running the CommonCore builds for NCC...")
    execute_process(COMMAND nebld ncc-posix.json WORKING_DIRECTORY ../private/src/CompilerKit)
    
elseif (DEFINED NCC_BUILD_COMMONCORE_OSX)

    message("Running the CommonCore builds for NCC...")
    execute_process(COMMAND nebld ncc-osx.json WORKING_DIRECTORY ../private/src/CompilerKit)
    
elseif (DEFINED NCC_BUILD_COMMONCORE_WIN64)

    message("Running the CommonCore builds for NCC...")
    execute_process(COMMAND nebld ncc-win64.json WORKING_DIRECTORY ../private/src/CompilerKit)
    
endif()
