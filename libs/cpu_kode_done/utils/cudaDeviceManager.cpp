#include "cudaDeviceManager.h"
#include "check_CUDA.h"

#include <boost/thread/mutex.hpp>
#include <boost/shared_array.hpp>
#include <cuda_runtime_api.h>
#include <stdlib.h>
#include <sstream>

namespace Gadgetron{

  static boost::shared_array<boost::mutex> _mutex;
  cudaDeviceManager* cudaDeviceManager::_instance = 0;

  cudaDeviceManager::cudaDeviceManager() {

    // This constructor is executed only once for a singleton
    //

    atexit(&CleanUp);

    if( cudaGetDeviceCount( &_num_devices ) != cudaSuccess) {
      _num_devices = 0;
      throw cuda_error( "Error: no Cuda devices present.");
    }

    _mutex = boost::shared_array<boost::mutex>(new boost::mutex[_num_devices]);

    int old_device;
    if( cudaGetDevice(&old_device) != cudaSuccess ) {
      throw std::runtime_error( "Error: unable to get device no");
    }

    _warp_size = std::vector<int>(_num_devices,0);
    _max_blockdim = std::vector<int>(_num_devices,0);
    _max_griddim = std::vector<int>(_num_devices,0);
    _major = std::vector<int>(_num_devices,0);
    _minor = std::vector<int>(_num_devices,0);

    for( int device=0; device<_num_devices; device++ ){

      if( cudaSetDevice(device) != cudaSuccess ) {
	throw cuda_error( "Error: unable to set device no");
      }

      cudaDeviceProp deviceProp;

      if( cudaGetDeviceProperties( &deviceProp, device ) != cudaSuccess) {
	throw cuda_error("Error: unable to determine device properties.");
      }

      _warp_size[device] = deviceProp.warpSize;
      _max_blockdim[device] = deviceProp.maxThreadsDim[0];
      _max_griddim[device] = deviceProp.maxGridSize[0];
      _major[device] = deviceProp.major;
      _minor[device] = deviceProp.minor;
    }

    if( cudaSetDevice(old_device) != cudaSuccess ) {
      throw cuda_error( "Error: unable to restore device no");
    }
  }

  cudaDeviceManager::~cudaDeviceManager() 
  {
  }

  int cudaDeviceManager::max_blockdim()
  {
    int device;
    CUDA_CALL(cudaGetDevice(&device));
    return _max_blockdim[device];
  }

  int cudaDeviceManager::max_griddim()
  {
    int device;
    CUDA_CALL(cudaGetDevice(&device));
    return _max_griddim[device];
  }

  int cudaDeviceManager::warp_size()
  {
    int device;
    CUDA_CALL(cudaGetDevice(&device));
    return _warp_size[device];
  }

  int cudaDeviceManager::major_version()
  {
    int device;
    CUDA_CALL(cudaGetDevice(&device));
    return _major[device];
  }

  int cudaDeviceManager::minor_version()
  {
    int device;
    CUDA_CALL(cudaGetDevice(&device));
    return _minor[device];
  }

  size_t cudaDeviceManager::getFreeMemory()
  {
    size_t free,total;
    CUDA_CALL(cudaMemGetInfo(&free,&total));
    return free;
  }

  size_t cudaDeviceManager::getTotalMemory()
  {
    size_t free,total;
    CUDA_CALL(cudaMemGetInfo(&free,&total));
    return total;
  }

  size_t cudaDeviceManager::getFreeMemory(int device)
  {
    int oldDevice;
    CUDA_CALL(cudaGetDevice(&oldDevice));
    CUDA_CALL(cudaSetDevice(device));
    size_t ret = getFreeMemory();
    CUDA_CALL(cudaSetDevice(oldDevice));
    return ret;
  }

  size_t cudaDeviceManager::getTotalMemory(int device)
  {
    int oldDevice;
    CUDA_CALL(cudaGetDevice(&oldDevice));
    CUDA_CALL(cudaSetDevice(device));
    size_t ret = getTotalMemory();
    CUDA_CALL(cudaSetDevice(oldDevice));
    return ret;
  }

  cudaDeviceManager* cudaDeviceManager::Instance()
  {
    if (_instance == 0 ) _instance = new cudaDeviceManager;
    return _instance;
  }

  int cudaDeviceManager::getCurrentDevice()
  {
    int device;
    CUDA_CALL(cudaGetDevice(&device));
    return device;
  }

  void cudaDeviceManager::CleanUp()
  {
    delete _instance; _instance = 0;
  }
}
