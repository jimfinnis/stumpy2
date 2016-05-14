#ifndef _TGA_STUFF_H_
#define _TGA_STUFF_H_


class TGAFile
{
public:
    TGAFile(const char *name);
    ~TGAFile();
    
    int getWidth() { return mW; }
    int getHeight() { return mH; }
    
    unsigned long getPixel(int x,int y);
    float getLuminosity(int x,int y);
    float getHeightRGB(int x,int y); // uses all 3 channels - red*4+g*2+b
    
    int getDepth()
    {
        return mDepth;
    }
    
    const char *getData()
    {
        return (char *)pixels;
    }
    
    bool isValid()
    {
        return valid;
    }
    
    const char *getError()
    {
        return err;
    }
    
private:
    bool valid;
    int mW,mH,mDepth;
    const char *err;
    
    struct TGAHeader *header;
    struct TrueColour *pixels;
    
};







#endif // _TGA_STUFF_H_