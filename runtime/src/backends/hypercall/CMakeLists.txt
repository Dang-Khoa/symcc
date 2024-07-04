
set(SymCCRtSrc ${SHARED_RUNTIME_SOURCES} Runtime.cpp)

add_library(SymCCRtObj OBJECT
        ${SymCCRtSrc})

set_property(TARGET SymCCRtObj PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(SymCCRtShared SHARED $<TARGET_OBJECTS:SymCCRtObj>)
add_library(SymCCRtStatic STATIC $<TARGET_OBJECTS:SymCCRtObj>)

set(SymCCRtDeps ${Z3_LIBRARIES})

# Object libraries cannot be linked directly
# https://gitlab.kitware.com/cmake/cmake/-/issues/18090
target_link_libraries(SymCCRtShared ${SymCCRtDeps})
target_link_libraries(SymCCRtStatic ${SymCCRtDeps})

set_target_properties(SymCCRtObj PROPERTIES COMPILE_FLAGS "-Werror -Wno-error=deprecated-declarations")

