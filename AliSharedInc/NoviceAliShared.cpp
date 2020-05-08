#include "interface.h"
#include <thread>

class noviceTestShared : public CDetectFlawClass
{
  public:
  
    int Initialize(char * path, int gpuIdx);
    
    int DetectFrame(const ImageData &image, std::vector<SteelFlaw> &result);
    
    int DetectBatch(const std::vector<ImageData> &images, std::vector<std::vector<SteelFlaw> > &results);
};

int noviceTestShared::Initialize(char * path, int gpuIdx)
{
  return 0;
}

int noviceTestShared::DetectFrame(const ImageData &image, std::vector<SteelFlaw> &result)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  return 0;
} 

int noviceTestShared::DetectBatch(const std::vector<ImageData> &images, std::vector<std::vector<SteelFlaw> > &results)
{
  return 0;
}


CDetectFlawClass * CDetectFlawClass::GetInstance()
{
    return new noviceTestShared();
}

int CDetectFlawClass::ReleaseInstance(CDetectFlawClass * obj)
{
    if(obj)
    {
      delete obj;
    }
    return 0;
}

