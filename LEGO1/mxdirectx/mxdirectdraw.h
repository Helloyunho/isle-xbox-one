#ifndef MXDIRECTDRAW_H
#define MXDIRECTDRAW_H

#include "lego1_export.h"
#include "mxdirectxinfo.h"

#ifdef MINIWIN
#include "miniwin/ddraw.h"
#include "miniwin/windows.h"
#else
#include <ddraw.h>
#include <windows.h>
#endif

// VTABLE: LEGO1 0x100db818
// VTABLE: BETA10 0x101c1b10
// SIZE 0x880
class MxDirectDraw {
public:
	typedef void (*ErrorHandler)(const char*, HRESULT, void*);

	LEGO1_EXPORT static int GetPrimaryBitDepth();

	MxDirectDraw();
	virtual ~MxDirectDraw();

	virtual BOOL Create(
		HWND hWnd,
		BOOL fullscreen_1,
		BOOL surface_fullscreen,
		BOOL onlySystemMemory,
		int width,
		int height,
		int bpp,
		const PALETTEENTRY* pPaletteEntries,
		int paletteEntryCount
	);                                      // vtable+0x04
	virtual void Destroy();                 // vtable+0x08
	virtual void DestroyButNotDirectDraw(); // vtable+0x0c

	IDirectDraw* DirectDraw() { return m_pDirectDraw; }

	// FUNCTION: BETA10 0x100d8ab0
	IDirectDrawSurface* FrontBuffer() { return m_pFrontBuffer; }

	// FUNCTION: BETA10 0x100d8ae0
	IDirectDrawSurface* BackBuffer() { return m_pBackBuffer; }

	// FUNCTION: BETA10 0x100d8b10
	IDirectDrawClipper* Clipper() { return m_pClipper; }

	// FUNCTION: BETA10 0x1011c190
	DeviceModesInfo::Mode* CurrentMode() { return &m_currentMode; }

	// FUNCTION: BETA10 0x1011c170
	BOOL IsFullScreen() { return m_bFullScreen; }

	int Pause(BOOL);
	BOOL RestoreSurfaces();

	virtual const char* ErrorToString(HRESULT p_error); // vtable+0x10
	int FlipToGDISurface();

protected:
	BOOL SetPaletteEntries(const PALETTEENTRY* pPaletteEntries, int paletteEntryCount, BOOL fullscreen);
	BOOL CacheOriginalPaletteEntries();
	BOOL RestoreOriginalPaletteEntries();
	BOOL RestorePaletteEntries();

	BOOL DDInit(BOOL fullscreen);
	BOOL DDSetMode(int width, int height, int bpp);
	BOOL DDCreateSurfaces();
	HRESULT CreateDDSurface(LPDDSURFACEDESC a2, LPDIRECTDRAWSURFACE* a3, IUnknown* a4);
	BOOL GetDDSurfaceDesc(LPDDSURFACEDESC lpDDSurfDesc, LPDIRECTDRAWSURFACE lpDDSurf);
	BOOL CreateZBuffer(DDSCapsFlags memorytype, DWORD depth);

	void Error(const char* p_message, int p_error);

	BOOL RecreateDirectDraw(GUID** a2);
	void ClearBackBuffers();
	void FUN_1009d920();

	// SYNTHETIC: LEGO1 0x1009d510
	// SYNTHETIC: BETA10 0x10122f80
	// MxDirectDraw::`scalar deleting destructor'

protected:
	BOOL m_bOnlySoftRender;                     // 0x04
	BOOL m_bFlipSurfaces;                       // 0x08
	IDirectDraw* m_pDirectDraw;                 // 0x0c
	IDirectDrawSurface* m_pFrontBuffer;         // 0x10
	IDirectDrawSurface* m_pBackBuffer;          // 0x14
	IDirectDrawSurface* m_pZBuffer;             // 0x18
	IDirectDrawClipper* m_pClipper;             // 0x24
	IDirectDrawPalette* m_pPalette;             // 0x28
	PALETTEENTRY m_paletteEntries[256];         // 0x2c
	PALETTEENTRY m_originalPaletteEntries[256]; // 0x42c
	SIZE m_text1SizeOnSurface;                  // 0x82c
	SIZE m_text2SizeOnSurface;                  // 0x834
	HWND m_hWndMain;                            // 0x83c
	HFONT m_hFont;                              // 0x840
	BOOL m_bIgnoreWMSIZE;                       // 0x844
	BOOL m_bPrimaryPalettized;                  // 0x848
	BOOL m_bFullScreen;                         // 0x84c
	void* m_unk0x850;                           // 0x850
	BOOL m_bOnlySystemMemory;                   // 0x854
	BOOL m_bIsOnPrimaryDevice;                  // 0x858
	ErrorHandler m_pErrorHandler;               // 0x85c
	ErrorHandler m_pFatalErrorHandler;          // 0x860
	void* m_pErrorHandlerArg;                   // 0x864
	void* m_pFatalErrorHandlerArg;              // 0x868
	int m_pauseCount;                           // 0x86c
	DeviceModesInfo* m_currentDevInfo;          // 0x870
	DeviceModesInfo::Mode m_currentMode;        // 0x874
};

#endif // MXDIRECTDRAW_H
