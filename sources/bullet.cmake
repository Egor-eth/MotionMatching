

if(WIN32)
  set(ADDITIONAL_LIBS ${ADDITIONAL_LIBS} bullet)


  add_library(bullet STATIC IMPORTED)
  set_target_properties(bullet PROPERTIES
          IMPORTED_LOCATION_DEBUG "${CMAKE_BINARY_DIR}/../bullet.lib"
          IMPORTED_LOCATION_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/../bullet.lib"
          IMPORTED_LOCATION_RELEASE "${CMAKE_BINARY_DIR}/../bullet.lib"
          LINKER_LANGUAGE CXX)
else()
  find_package(Bullet REQUIRED)
  include_directories(${BULLET_INCLUDE_DIRS})
endif()

link_libraries(
        BulletDynamics BulletCollision LinearMath
)