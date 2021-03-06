#pragma once

#include "resource.h"
#include "GetPrnDC.h"
#include "Print.h"

BOOL PrintMyPage(HWND hwnd)
{
	static DOCINFO di = { sizeof(DOCINFO), TEXT("Print1: Printing") };
	BOOL bSuccess = TRUE;
	HDC hdcPrn;
	int xPage, yPage;

	if (NULL == (hdcPrn = GetPrinterDC()))
		return FALSE;
	xPage = GetDeviceCaps(hdcPrn, HORZRES);
	yPage = GetDeviceCaps(hdcPrn, VERTRES);

	if (StartDoc(hdcPrn, &di) > 0)
	{
		if (StartPage(hdcPrn) > 0)
		{
			PageGDICalls(hdcPrn, xPage, yPage);

			if (EndPage(hdcPrn) > 0)
				EndDoc(hdcPrn);
			else
				bSuccess = FALSE;
		}
	}
	else
		bSuccess = FALSE;
	DeleteDC(hdcPrn);
	return bSuccess;
}

