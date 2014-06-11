#pragma once

#include "gpucore_export.h"

#include <vector>
#include <cstddef>

namespace Gadgetron{

  class EXPORTGPUCORE cudaDeviceManager 
  {
  public:

    // This class is used as a singleton.
    // Use Instance() to access the public member functions.
    //

    static cudaDeviceManager* Instance();
    
    // Public member functions.
    // If the function does not take a device id, it will use the current device.
    //

    inline int warp_size(int device){ return _warp_size[device]; }
    inline int max_blockdim(int device){ return _max_blockdim[device]; }
    inline int max_griddim(int device){ return _max_griddim[device]; }
    inline int major_version(int device){ return _major[device]; }
    inline int minor_version(int device){ return _minor[device]; }

    int major_version();
    int minor_version();
    int warp_size();
    int max_blockdim();
    int max_griddim();

    int getCurrentDevice();

    size_t getFreeMemory();
    size_t getFreeMemory(int device);

    size_t getTotalMemory();
    size_t getTotalMemory(int device);

  private:

    // Use the Instance() method to access the singleton
    //

    cudaDeviceManager();
    ~cudaDeviceManager();

    static void CleanUp();
    
    int _num_devices;
    std::vector<int> _warp_size;
    std::vector<int> _max_blockdim;
    std::vector<int> _max_griddim;
    std::vector<int> _major;
    std::vector<int> _minor;
    static cudaDeviceManager * _instance;    
  };
}
