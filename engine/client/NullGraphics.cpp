//File located in wrong folder because teeworlds compilation config doesn't include other folders here
#include "headless/NullGraphics.h"

NullGraphics::NullGraphics() {
}

void NullGraphics::Clear(float r, float g, float b) {
}

void NullGraphics::ClipEnable(int x, int y, int w, int h) {
}

void NullGraphics::ClipDisable() {
}

void NullGraphics::MapScreen(float TopLeftX, float TopLeftY, float BottomRightX, float BottomRightY) {
}

void NullGraphics::GetScreen(float *pTopLeftX, float *pTopLeftY, float *pBottomRightX, float *pBottomRightY) {
}

void NullGraphics::BlendNone() {
}

void NullGraphics::BlendNormal() {
}

void NullGraphics::BlendAdditive() {
}

void NullGraphics::WrapNormal() {
}

void NullGraphics::WrapClamp() {
}

int NullGraphics::MemoryUsage() const {
	return 0;
}

int NullGraphics::LoadPNG(CImageInfo *pImg, const char *pFilename, int StorageType) {
	return 0;
}

int NullGraphics::UnloadTexture(int Index) {
	return 0;
}

int NullGraphics::LoadTextureRaw(int Width, int Height, int Format, const void *pData, int StoreFormat, int Flags) {
	return 0;
}

int NullGraphics::LoadTexture(const char *pFilename, int StorageType, int StoreFormat, int Flags) {
	return 0;
}

int NullGraphics::LoadTextureRawSub(int TextureID, int x, int y, int Width, int Height, int Format, const void *pData) {
	return 0;
}

void NullGraphics::TextureSet(int TextureID) {
}

void NullGraphics::LinesBegin() {
}

void NullGraphics::LinesEnd() {
}

void NullGraphics::LinesDraw(const CLineItem *pArray, int Num) {
}

void NullGraphics::QuadsBegin() {
}

void NullGraphics::QuadsEnd() {
}

void NullGraphics::QuadsSetRotation(float Angle) {
}

void NullGraphics::QuadsSetSubset(float TopLeftY, float TopLeftV, float BottomRightU, float BottomRightV) {
}

void NullGraphics::QuadsSetSubsetFree(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
}

void NullGraphics::QuadsDraw(CQuadItem *pArray, int Num) {
}

void NullGraphics::QuadsDrawTL(const CQuadItem *pArray, int Num) {
}

void NullGraphics::QuadsDrawFreeform(const CFreeformItem *pArray, int Num) {
}

void NullGraphics::QuadsText(float x, float y, float Size, const char *pText) {
}

void NullGraphics::SetColorVertex(const CColorVertex *pArray, int Num) {
}

void NullGraphics::SetColor(float r, float g, float b, float a) {
}

void NullGraphics::TakeScreenshot(const char *pFilename) {
}

int NullGraphics::GetVideoModes(CVideoMode *pModes, int MaxModes) {
	return 0;
}

void NullGraphics::Swap() {
}

void NullGraphics::InsertSignal(class semaphore *pSemaphore) {
}

bool NullGraphics::IsIdle() {
	return false;
}

void NullGraphics::WaitForIdle() {
}

int NullGraphics::Init() {
	return 0;
}

void NullGraphics::Shutdown() {
}

void NullGraphics::Minimize() {
}

void NullGraphics::Maximize() {
}

int NullGraphics::WindowActive() {
	return 0;
}

int NullGraphics::WindowOpen() {
	return 0;
}