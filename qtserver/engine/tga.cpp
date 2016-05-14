#include "tga.h"

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <assert.h>


#pragma pack(push, 1)
struct TrueColour
{
    unsigned char r,g,b,a;	// this is the format GL is expecting.
};

struct TGAHeader
{
    unsigned char identSize;
    unsigned char colourmaptype;
    unsigned char imagetype;
    unsigned short colourmapstart;
    unsigned short colourmaplength;
    unsigned char colourmapbits;
    unsigned short xstart;
    unsigned short ystart;
    unsigned short width;
    unsigned short height;
    unsigned char bits;
    unsigned char descriptor;
};
#pragma pack(pop)



////////// READING

const char *loadTGAPixelData( TrueColour *pixels, bool &hasAlpha, unsigned char *dataBuffer, const TGAHeader &header )
{
    int pixelCount = header.width * header.height;
    int bpp = header.bits / 8;
    int pbpp = header.colourmapbits / 8;
    
    // skip any ident field
    dataBuffer += header.identSize;
    
    
    unsigned char *pixelBuffer = dataBuffer + header.colourmaplength * pbpp;
    
    printf("image type %d, %s ",header.imagetype,(header.descriptor & (1<<5))?"INVERTED":"        ");
    printf("\n");
    
    switch( header.imagetype )
    {
    case 1: // indexed
        hasAlpha = ( pbpp == 4 );
        for( int i = 0; i < pixelCount; ++i )
        {
            int p = pixelBuffer[ i * bpp ];
            pixels[ i ].r = dataBuffer[ p * pbpp + 2 ];
            pixels[ i ].g = dataBuffer[ p * pbpp + 1 ];
            pixels[ i ].b = dataBuffer[ p * pbpp + 0 ];
            if( hasAlpha )
                pixels[ i ].a = dataBuffer[ p * pbpp + 3 ];
            else
                pixels[ i ].a = 255;
        }
        break;
    case 2: // rgb(a)
        hasAlpha = ( bpp == 4 );
        for( int i = 0; i < pixelCount; ++i )
        {
            pixels[ i ].r = dataBuffer[ i * bpp + 2 ];
            pixels[ i ].g = dataBuffer[ i * bpp + 1 ];
            pixels[ i ].b = dataBuffer[ i * bpp + 0 ];
            if( hasAlpha )
                pixels[ i ].a = dataBuffer[ i * bpp + 3 ];
            else
                pixels[ i ].a = 255;
        }
        break;
    case 3: // greyscale
        hasAlpha = false;
        for( int i = 0; i < pixelCount; ++i )
        {
            pixels[ i ].r = dataBuffer[ i * bpp ];
            pixels[ i ].g = dataBuffer[ i * bpp ];
            pixels[ i ].b = dataBuffer[ i * bpp ];
            pixels[ i ].a = 255;
        }
        break;
    case 9:
        {
            hasAlpha = ( pbpp == 4 );
            int pixelCaret = 0;
            int dataCaret = 0;
            while( pixelCount > pixelCaret )
            {
                int numToRead = ((int)( pixelBuffer[dataCaret] & 127 )) + 1;
                bool readRun = pixelBuffer[dataCaret] > 127;
                ++dataCaret;
                
                for( int i = 0; i < numToRead; ++i )
                {
                    int p = pixelBuffer[ dataCaret ];
                    
                    pixels[ pixelCaret+i ].r = pixelBuffer[ dataCaret + 2 ];
                    
                    pixels[ i ].r = dataBuffer[ p * pbpp + 2 ];
                    pixels[ i ].g = dataBuffer[ p * pbpp + 1 ];
                    pixels[ i ].b = dataBuffer[ p * pbpp + 0 ];
                    if( hasAlpha )
                        pixels[ i ].a = dataBuffer[ p * pbpp + 3 ];
                    else
                        pixels[ i ].a = 255;
                    
                    if( !readRun )
                    {
                        dataCaret += bpp;
                    }
                }
                if( readRun )
                {
                    dataCaret += bpp;
                }
                pixelCaret += numToRead;
            }
            if( pixelCaret != pixelCount )
            {
                return( "Failed to load RLE" );
            }
        }
        break;
    case 10:
        {
            hasAlpha = ( bpp == 4 );
            int pixelCaret = 0;
            int dataCaret = 0;
            while( pixelCount > pixelCaret )
            {
                int numToRead = ((int)( dataBuffer[dataCaret] & 127 )) + 1;
                bool readRun = dataBuffer[dataCaret] > 127;
                ++dataCaret;
                
                for( int i = 0; i < numToRead; ++i )
                {
                    pixels[ pixelCaret+i ].r = dataBuffer[ dataCaret + 2 ];
                    pixels[ pixelCaret+i ].g = dataBuffer[ dataCaret + 1 ];
                    pixels[ pixelCaret+i ].b = dataBuffer[ dataCaret + 0 ];
                    if( hasAlpha )
                        pixels[ pixelCaret+i ].a = dataBuffer[ dataCaret + 3 ];
                    else
                        pixels[ i ].a = 255;
                    if( !readRun )
                    {
                        dataCaret += bpp;
                    }
                }
                if( readRun )
                {
                    dataCaret += bpp;
                }
                pixelCaret += numToRead;
            }
            if( pixelCaret != pixelCount )
            {
                return( "Failed to load RLE" );
            }
        }
        break;
    case 11:
        return( "Cannot convert RLE type 11" );
    default:
        return( "Bad Image Type" );
    }
    return NULL;
}

//////// WRITING

void writeTGAIndex( const char *filename, int *pixelIndices, TrueColour *palette, int width, int height, bool hadAlpha )
{
    FILE *fp = fopen( filename, "wb" );
    if( fp == NULL )
        return;
    
    TGAHeader tHeader;
    tHeader.identSize = 0;
    tHeader.colourmaptype = 1;
    tHeader.imagetype = 1;
    tHeader.colourmapstart = 0;
    tHeader.colourmaplength = 256;
    tHeader.colourmapbits = 24;
    tHeader.xstart = 0;
    tHeader.ystart = 0;
    tHeader.width = width;
    tHeader.height = height;
    tHeader.bits = 8;
    tHeader.descriptor = 8;
    
    fwrite( &tHeader, sizeof( tHeader ), 1, fp );
    for( int lPE = 0; lPE < 256; ++lPE )
    {
        fwrite( &palette[lPE].b, 1, 1, fp );
        fwrite( &palette[lPE].g, 1, 1, fp );
        fwrite( &palette[lPE].r, 1, 1, fp );
        //fwrite( &palette[lPE].a, 1, 1, fp );
    }
    for( int lPixel = 0; lPixel < width * height; ++lPixel )
    {
        fwrite( &pixelIndices[lPixel], 1, 1, fp );
        //fwrite( &palette[pixelIndices[lPixel]].b, 1, 1, fp );
        //fwrite( &palette[pixelIndices[lPixel]].g, 1, 1, fp );
        //fwrite( &palette[pixelIndices[lPixel]].r, 1, 1, fp );
        //fwrite( &palette[pixelIndices[lPixel]].a, 1, 1, fp );
    }
    fclose( fp );
}

void writeTGARGBA( const char *filename, TrueColour *pixels, int width, int height, bool hadAlpha )
{
    FILE *fp = fopen( filename, "wb" );
    if( fp == NULL )
        return;
    
    TGAHeader tHeader;
    tHeader.identSize = 0;
    tHeader.colourmaptype = 0;
    tHeader.imagetype = 2;
    tHeader.colourmapstart = 0;
    tHeader.colourmaplength = 0;
    tHeader.colourmapbits = 0;
    tHeader.xstart = 0;
    tHeader.ystart = 0;
    tHeader.width = width;
    tHeader.height = height;
    tHeader.bits = hadAlpha ? 32 : 24;
    tHeader.descriptor = 0;
    
    fwrite( &tHeader, sizeof( tHeader ), 1, fp );
    
    for( int lPixel = 0; lPixel < width * height; ++lPixel )
    {
        fwrite( &pixels[lPixel].b, 1, 1, fp );
        fwrite( &pixels[lPixel].g, 1, 1, fp );
        fwrite( &pixels[lPixel].r, 1, 1, fp );
        if( hadAlpha )
            fwrite( &pixels[lPixel].a, 1, 1, fp );
    }
    
    fclose( fp );
}



/*****************************************************************************
 * 
 * 
 * 
 * 
 * 
 * 
 ****************************************************************************/

TGAFile::TGAFile(const char *name)
{
    // first, suck in the file
    FILE *targaFile = fopen( name, "rb" );
    valid=false;
    err="cannot find file";
    
    printf("  loading tex: %s ",name);
    
    
    mH = 0;
    mW = 0;
    
    if( targaFile != NULL )
    {
        fseek( targaFile, 0, SEEK_END );
        int targaFileSize = ftell( targaFile );
        fseek( targaFile, 0, SEEK_SET );    
        
        header = (TGAHeader *)malloc(sizeof(TGAHeader));
        fread( header, sizeof( TGAHeader ), 1, targaFile );
        
        int dataSize = targaFileSize - sizeof( TGAHeader );
        void *data = malloc( dataSize );
        fread( data, 1, dataSize, targaFile );
        
        int pixelCount = header->width * header->height;
        
        pixels = (TrueColour*)malloc( sizeof( TrueColour ) * pixelCount );
        
        bool hadAlpha;
        err = loadTGAPixelData( pixels, hadAlpha, (unsigned char*)data, *header );
        if(err)
        {
            free(pixels);
            free(header);
        }
        else
            valid = true;
        
        fclose(targaFile);
        free(data);
        
        mW = header->width;
        mH = header->height;
        mDepth = header->bits;
    }
}

TGAFile::~TGAFile()
{
    if(valid)
    {
        free(pixels);
        free(header);
    }
}

unsigned long TGAFile::getPixel(int x,int y)
{
    TrueColour &p = pixels[x*mW+y];
    
    return (p.a << 24) + (p.r<<16) + (p.g<<8) + p.b;
}

float TGAFile::getLuminosity(int x,int y)
{
    TrueColour &p = pixels[x*mW+y];
    float c = (float)(p.r) + (float)(p.b) + (float)(p.g);
    return c/(255.0f*3.0f);
}

float TGAFile::getHeightRGB(int x,int y)
{
    TrueColour &p = pixels[x*mW+y];
    
    float r = (float)(p.r)/255.0f;
    float g = (float)(p.g)/255.0f;
    float b = (float)(p.b)/255.0f;
    
    //	return r*8.0f + b/32.0f + g/8192.0f;
    return r*8.0f + b + g/8.0f;
}
