// number_client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Tao client nhan du lieu tu server va in ra man hinh.
//

#include <stdio.h>
#include <WinSock2.h>
#include <string.h>
#include <string>
using namespace std;

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1234);

    system("pause");

    int ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("Ket noi khong thanh cong - %d\n", ret);
        return 1;
    }
    const char* str = "Ten may tinh la: ";
    send(client, str, strlen(str), 0);
    char name[256];
    DWORD size = sizeof(name);
    GetComputerNameA(name, &size);
    send(client, name, size, 0);

    const char* str2 = "\nDanh sach cac o trong may tinh: ";
    send(client, str2, strlen(str2), 0);
    // Buffer length
    DWORD mydrives = 15;
    // Buffer for drive string storage
    char lpBuffer[18];
    // You may want to try the wmain() version
    DWORD test;
    DWORD dwSectPerClust,dwBytesPerSect,dwFreeClusters,dwTotalClusters;
    LPCWSTR pszDrive = NULL;
    test = GetLogicalDriveStrings(mydrives, (LPWSTR)lpBuffer);
    for (int i = 0; i < sizeof(lpBuffer); i++) {
        const char buf2 = lpBuffer[i];
        printf("%c", buf2);
        send(client, &buf2, sizeof(buf2), 0);
    }
    BOOL fresult = GetDiskFreeSpace(pszDrive,&dwSectPerClust,&dwBytesPerSect,&dwFreeClusters,&dwTotalClusters);
    wstring wstr = to_wstring(dwTotalClusters);
    string res(wstr.begin(), wstr.end());
    string message = "total cluster:" + res;
    const char* diskspace = message.c_str();
    send(client, diskspace, strlen(diskspace), 0);
       

    printf("\n");
    closesocket(client);
    WSACleanup();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
