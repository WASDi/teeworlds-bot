#ifndef NULLGRAPHICS_H
#define NULLGRAPHICS_H

#include <engine/graphics.h>

class NullGraphics : public IEngineGraphics {
public:
	NullGraphics();
	
	virtual void Clear(float r, float g, float b);

	virtual void ClipEnable(int x, int y, int w, int h);
	virtual void ClipDisable();

	virtual void MapScreen(float TopLeftX, float TopLeftY, float BottomRightX, float BottomRightY);
	virtual void GetScreen(float *pTopLeftX, float *pTopLeftY, float *pBottomRightX, float *pBottomRightY);

	virtual void BlendNone();
	virtual void BlendNormal();
	virtual void BlendAdditive();
	virtual void WrapNormal();
	virtual void WrapClamp();
	virtual int MemoryUsage() const;

	virtual int LoadPNG(CImageInfo *pImg, const char *pFilename, int StorageType);
	virtual int UnloadTexture(int Index);
	virtual int LoadTextureRaw(int Width, int Height, int Format, const void *pData, int StoreFormat, int Flags);
	virtual int LoadTexture(const char *pFilename, int StorageType, int StoreFormat, int Flags);
	virtual int LoadTextureRawSub(int TextureID, int x, int y, int Width, int Height, int Format, const void *pData);
	virtual void TextureSet(int TextureID);
	
	virtual void LinesBegin();
	virtual void LinesEnd();
	virtual void LinesDraw(const CLineItem *pArray, int Num);

	virtual void QuadsBegin();
	virtual void QuadsEnd();
	virtual void QuadsSetRotation(float Angle);
	virtual void QuadsSetSubset(float TopLeftY, float TopLeftV, float BottomRightU, float BottomRightV);
	virtual void QuadsSetSubsetFree(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);
	
	virtual void QuadsDraw(CQuadItem *pArray, int Num);
	virtual void QuadsDrawTL(const CQuadItem *pArray, int Num);
	
	virtual void QuadsDrawFreeform(const CFreeformItem *pArray, int Num);
	virtual void QuadsText(float x, float y, float Size, const char *pText);
	
	virtual void SetColorVertex(const CColorVertex *pArray, int Num);
	virtual void SetColor(float r, float g, float b, float a);

	virtual void TakeScreenshot(const char *pFilename);
	virtual int GetVideoModes(CVideoMode *pModes, int MaxModes);

	virtual void Swap();

	virtual void InsertSignal(class semaphore *pSemaphore);
	virtual bool IsIdle();
	virtual void WaitForIdle();
	
	virtual int Init();
	virtual void Shutdown();

	virtual void Minimize();
	virtual void Maximize();

	virtual int WindowActive();
	virtual int WindowOpen();

};

#endif /* NULLGRAPHICS_H */

