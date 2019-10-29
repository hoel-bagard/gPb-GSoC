#include "process.h"

void process(const cv::Mat &im, cv::Mat &gPb, cv::Mat &ucm2) {

  cv::Mat ucm, gPb_thin;
  std::vector<cv::Mat> gPb_ori;

  cv::globalPb(im, gPb, gPb_thin, gPb_ori);

  // if you wanna conduct interactive segmentation later, choose
  // DOUBLE_SIZE, otherwise SINGLE_SIZE will do either.
  cv::contour2ucm(gPb, gPb_ori, ucm, SINGLE_SIZE);

  cout<<"copyto ucm"<<endl;
  ucm.copyTo(ucm2);

  cout<<"convert gpb"<<endl;
  gPb.convertTo(gPb, CV_8UC3, 255.0);
  cout<<"convert ucm"<<endl;
  ucm2.convertTo(ucm2, CV_8UC3, 255.0);
  cout<<"done"<<endl;

}
