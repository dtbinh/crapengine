INCLUDE(ExternalProject)

SET(Bullet_args
	-DBUILD_BULLET2_DEMOS=OFF
	-DBUILD_BULLET3_DEMOS=OFF
	-DBUILD_CPU_DEMOS=OFF
	-DBUILD_EXTRAS=OFF
	-DBUILD_SHARED_LIBS=OFF
	-DBUILD_UNIT_TESTS=OFF
	-DINSTALL_LIBS=ON
)

#MESSAGE ("WARNING: Library path is "${CRAP_LIBRARIES_PATH})
#MESSAGE ("WARNING: Binary path is "${CMAKE_BINARY_DIR})

EXTERNALPROJECT_ADD(
	bullet
	SOURCE_DIR ${CRAP_LIBRARIES_PATH}/bullet
	PREFIX ${CMAKE_BINARY_DIR}/bullet
	CMAKE_ARGS ${Bullet_args}
	BINARY_DIR ${CMAKE_BINARY_DIR}/bullet
	INSTALL_COMMAND ""
)
