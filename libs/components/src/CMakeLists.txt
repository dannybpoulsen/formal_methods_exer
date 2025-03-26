add_library (stdcomponents STATIC frontend.cpp  graph.cpp )
target_link_libraries(stdcomponents PUBLIC whiley ir cgraph PRIVATE fmt)
target_include_directories(stdcomponents PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library (compiler STATIC compiler.cpp )
target_link_libraries(compiler PUBLIC whiley ir cgraph PRIVATE fmt)
target_include_directories(compiler PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library (compiler_student STATIC compiler_student.cpp )
target_link_libraries(compiler_student PUBLIC whiley ir cgraph PRIVATE fmt)
target_include_directories(compiler_student PUBLIC ${PROJECT_SOURCE_DIR}/include)


add_library (explicit STATIC explicit_mc.cpp)
target_link_libraries(explicit PUBLIC whiley ir cgraph PRIVATE fmt) 
target_include_directories(explicit PUBLIC ${PROJECT_SOURCE_DIR}/include)


add_library (explicit_student STATIC explicit_mc_student.cpp)
target_link_libraries(explicit_student PUBLIC whiley ir cgraph PRIVATE fmt) 
target_include_directories(explicit_student PUBLIC ${PROJECT_SOURCE_DIR}/include)



add_library (uninit STATIC uninit.cpp)
target_link_libraries(uninit PUBLIC whiley ir cgraph PRIVATE fmt) 
target_include_directories(uninit PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library (uninit_student STATIC uninit_student.cpp)
target_link_libraries(uninit_student PUBLIC whiley ir cgraph PRIVATE fmt) 
target_include_directories(uninit_student PUBLIC ${PROJECT_SOURCE_DIR}/include)
				  
