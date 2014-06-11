cuda_add_library(backproject_utils 
  cuNDArray_operators.cu cuNDArray_elemwise.cu cuNDArray_utils.cu cuNDFFT.cpp cudaDeviceManager.cpp
  )

target_link_libraries(backproject_utils
  ${Boost_LIBRARIES}
  ${CUDA_LIBRARIES}
  )

install(TARGETS backproject_utils DESTINATION lib)
