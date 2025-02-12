project(MachineLib)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.14)

set(SOURCE_FILES
        pch.h
        IMachineSystem.h
        MachineSystemFactory.cpp MachineSystemFactory.h
        MachineDialog.cpp MachineDialog.h include/machine-api.h
        Const.cpp
        Const.h
        MachineSystemStandin.h
        MachineSystemStandin.cpp
        MachineStandin.cpp
        MachineStandin.h
        Polygon.cpp
        Polygon.h
        Cylinder.cpp
        Cylinder.h
        MachineSystem.cpp
        MachineSystem.h
        Machine.cpp
        Machine.h
        Machine1Factory.cpp
        Machine1Factory.h
        Component.cpp
        Component.h
        Box.cpp
        Box.h
        Sparty.cpp
        Sparty.h
        Crank.cpp
        Crank.h
        RotationSource.cpp
        RotationSource.h
        Shaft.cpp
        Shaft.h
        Pulley.cpp
        Pulley.h
        Cam.cpp
        Cam.h
        IRotationSink.cpp
        IRotationSink.h
        IKeyDropListener.cpp
        IKeyDropListener.h
        Banner.cpp
        Banner.h
        Machine2Factory.cpp
        Machine2Factory.h
)

find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
