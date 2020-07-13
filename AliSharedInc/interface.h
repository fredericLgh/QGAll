#ifndef __STEEL_DETECT_HEADER__
#define __STEEL_DETECT_HEADER__

/**
 * @brief:  Detect flaws in steel.
 *
 * date:    2020-04-21
 */

#include <vector>
#include <string>

enum ViewType
{
    UNDER_VIEW,
    UPPER_VIEW
};

/* Strcucture of input image data */
typedef struct ImageData
{
    /* Basic information of input image */
    unsigned char * data;   // data pointer of input image
    int wd;                 // width of input image
    int ht;                 // height of input image
    int ch;                 // channel of input image
    ViewType type;          // view type of image

    /* Other attributes of input image */
    int camIdx;         // cam index
    int patchIdx;        //steel patch index

    int reserved1;    // reserved number 1
    int reserved2;    // reserved number 2

}ImageData;

/* Strcucture of each flaw */
typedef struct SteelFlaw
{
    /* Basic information of flaw */
    int label;          // flaw class index
    std::string name;   // flaw class name

    float conf;         // flaw confidence

    float xmin;        // flaw location: horizonal location of left-up point
    float ymin;        // flaw location: vertical location of left-up point
    float xmax;        // flaw location: horizonal location of right-bottom point
    float ymax;        // flaw location: vertical location of right-bottom point
    
    /* Other attributes of flaw */
    float len;          // flaw's length
    float area;         // flaw's area
    float contrast;     // flaw's contrast
    float reserved1;    // reserved number 1
    float reserved2;    // reserved number 2

}SteelFlaw;


class CDetectFlawClass
{
public:
    /*!
    @brief: get steel flaw detection instance pointer, not singleton pattern
    @param: NULL
    @return:the instance object pointer of CDetectFlawClass
    */
    static CDetectFlawClass * GetInstance(void);

    /*!
    @brief: release the corresponding instance object pointer
    @param: obj, [in/out] the object to be released, it will be assigned null
    @return:
    0, successful
    1, failed
    */
    static int ReleaseInstance(CDetectFlawClass * obj);

public:
    /*!
    @brief: initialize all resource of steel flaw detection
    @param: path, [in] the path of the .ini setting file

    @return:
    0, successful
    1, failed
    */
    virtual int Initialize(char * path, int gpuIdx) = 0;
    
    /*!
    @brief: detect flaws in one steel image
    @param: image, [in] data of input image
            result, [in/out] flaw results detected

    @return:
    0, successful
    1, failed
    */
    virtual int DetectFrame(const ImageData &image, std::vector<SteelFlaw> &result) = 0;
    
    /*!
    @brief: detect flaws in one batch of steel images
    @param: images, [in] data of input images
            results, [in/out] flaw results detected

    @return:
    0, successful
    1, failed
    */
    virtual int DetectBatch(const std::vector<ImageData> &images, std::vector<std::vector<SteelFlaw> > &results) = 0;


};

#endif
