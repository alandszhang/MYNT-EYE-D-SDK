#include <iostream>
#include <fstream>

#include "mynteyed/camera.h"
#include "mynteyed/utils.h"

MYNTEYE_USE_NAMESPACE

int main(int argc, char *argv[]) {
  Camera cam;
  DeviceInfo dev_info;
  if (!util::select(cam, &dev_info)) {
    return 1;
  }
  util::print_stream_infos(cam, dev_info.index);

  std::cout << "Open device: " << dev_info.index << ", "
    << dev_info.name << std::endl << std::endl;

  OpenParams params(dev_info.index);
  cam.Open(params);

  std::cout << std::endl;
  if (!cam.IsOpened()) {
    std::cerr << "Error: Open camera failed" << std::endl;
    return 1;
  }
  std::cout << "Open device success" << std::endl << std::endl;

  // std::ofstream out("image_params.params");
  auto data = cam.GetCameraCalibration(StreamMode::STREAM_640x480);
  data->CamMat1[0] = 521.56915283203125000;
  bool in_ok = cam.WriteCameraCalibration(*data, StreamMode::STREAM_640x480);
  cam.Close();
  return 0;
}
