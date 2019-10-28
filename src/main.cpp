#include "process.h"


// this is for testing the seg-fault
int main(int argc, char* argv[]) {
    std::vector<std::string> cmdLineArgs(argv, argv+argc);

    if(cmdLineArgs.size() != 4)
    {
        std::cout << "This needs three paths as arguments:\n";
        std::cout << "    Path of input image\n";
        std::cout << "    Path of output gPb image\n";
        std::cout << "    Path of output ucm image\n";
        return 1;
    }

  cv::Mat img0 = cv::imread(argv[1], -1);
  std::string gpb_path = argv[2];
  std::string ucm_path = argv[3];
  cv::Mat gpb0, ucm0;

  process(img0, gpb0, ucm0);
  cv::imwrite(gpb_path, gpb0);
  cv::imwrite(ucm_path, ucm0);

  return 1;
}
