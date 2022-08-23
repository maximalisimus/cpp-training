//---------------------------------------------------------------------------

#ifndef UNICODE
#define UNICODE
#endif

#pragma comment(lib, netapi32.lib)

#define INFO_BUFFER_SIZE 32767

#include <stdio.h>
#include <assert.h>
#include <windows.h>
#include <lm.h>

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    LPUSER_INFO_0 pBuf = NULL;
    LPUSER_INFO_0 pTmpBuf;
    DWORD dwLevel = 0;
    DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
    DWORD dwEntriesRead = 0;
    DWORD dwTotalEntries = 0;
    DWORD dwResumeHandle = 0;
    DWORD i;
    DWORD dwTotalCount = 0;
    NET_API_STATUS nStatus;
    LPTSTR pszServerName = NULL;
    WCHAR  infoBuf[INFO_BUFFER_SIZE];
    DWORD  bufCharCount = INFO_BUFFER_SIZE;

    //GetComputerName(infoBuf, &bufCharCount);
    //wprintf(L"Using local, \%s", infoBuf);
    pszServerName = infoBuf;

    do // begin do
	{
		nStatus = NetUserEnum((LPCWSTR) pszServerName,
				       dwLevel,
				       FILTER_NORMAL_ACCOUNT, // global users
				       (LPBYTE*)&pBuf,
				       dwPrefMaxLen,
				       &dwEntriesRead,
				       &dwTotalEntries,
				       &dwResumeHandle);

		// If the call succeeds,
		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
		{
			//wprintf(L"NetUserEnum() looks fine!\n");
                        //printf("\nNetUserEnum() looks fine!\n");
			if ((pTmpBuf = pBuf) != NULL)
			{
				// Loop through the entries.
				for (i = 0; (i < dwEntriesRead); i++)
				{
					assert(pTmpBuf != NULL);
						if (pTmpBuf == NULL)
						{
							//fwprintf_s(stderr, L"An access violation has occurred\n");
                                                        printf("An access violation has occurred: %s\n", stderr);
							break;
						}
					//  Print the name of the user account.
					wprintf(L"%d. %s\n", i+1, pTmpBuf->usri0_name);
					pTmpBuf++;
					dwTotalCount++;
				}
			}
		}
		// Otherwise, print the system error.
		else
		{
                        //wprintf(L'NetUserEnum() failed!\n');
                        printf("NetUserEnum() failed!\n");
                        printf("A system error has occurred: %d\n%s", nStatus, stderr);
                        //fwprintf_s(stderr, L'A system error has occurred: %d\n', nStatus);
		}
        // Free the allocated buffer.
		if (pBuf != NULL)
		{
			NetApiBufferFree(pBuf);
			pBuf = NULL;
		}
	}
	// Continue to call NetUserEnum while there are more entries.
	while (nStatus == ERROR_MORE_DATA); // end do
	// Check again for allocated memory.
	if (pBuf != NULL)
		NetApiBufferFree(pBuf);
	// Print the final count of users enumerated.
	//fwprintf_s(stderr, L'\nTotal of %d entries enumerated\n', dwTotalCount);
          //printf("\nTotal of %d entries enumerated\n%s", dwTotalCount, stderr);
    return 0;
}
//---------------------------------------------------------------------------
 