// test1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<windows.h>
#include<wtypes.h>
#include <winbase.h>
#include <iostream>
#include <stdio.h>
#include "skfapi.h"
using namespace std;
typedef ULONG (DEVAPI *pOpen)(LPSTR szDevName, ULONG* pulDevNameLen, ULONG* pulEvent);
typedef ULONG (DEVAPI *pEnumDev)(BOOL bPresent, LPSTR szNameList, ULONG* pulSize);
typedef ULONG(DEVAPI *pConnect)(LPSTR szName, DEVHANDLE* phDev);
typedef ULONG(DEVAPI* pGetState)(LPSTR szDevName, ULONG* pulDevState);
typedef ULONG(DEVAPI* pGetInfo)(DEVHANDLE hDev, DEVINFO* pDevInfo);
//typedef ULONG(*pOpen)();

int main()
{

    HINSTANCE hDLL;
   // pAdd Add;
    pOpen open;
    pEnumDev enumdev;
    pConnect connect;
    pGetState getstate;
    pGetInfo getdevinfo;
    hDLL = LoadLibrary(L"mtoken_gm3000.dll");  //加载 DLL文件
    if (hDLL == NULL)
        cout << "Error!!!\n";
    else
        cout << "已加载动态库\n";
    open = (pOpen)GetProcAddress(hDLL, "SKF_WaitForDevEvent");
    enumdev = (pEnumDev)GetProcAddress(hDLL, "SKF_EnumDev");
    connect = (pConnect)GetProcAddress(hDLL, "SKF_ConnectDev");
    getstate = (pGetState)GetProcAddress(hDLL, "SKF_GetDevState");
    getdevinfo = (pGetInfo)GetProcAddress(hDLL, "SKF_GetDevInfo");//取DLL中的函数地址，以备调用
    if (open == NULL)
        cout << "Error!!!\n";
    else
        cout << "查找到等待设备插拔函数\n";
    if (enumdev == NULL)
        cout << "Error!!!\n";
    else
        cout << "查找到枚举设备函数\n";
    if (connect == NULL)
        cout << "Error!!!\n";
    else
        cout << "查找到连接设备函数\n";
    if (getstate == NULL)
        cout << "Error!!!\n";
    else
        cout << "查找到获取设备状态函数\n";
    if (getdevinfo == NULL)
        cout << "Error!!!\n";
    else
        cout << "查找到获取设备信息函数\n";
    LPSTR szDevName = new char(20);
    ULONG pulDevNameLen=20;
    ULONG pulEvent=1;
    BOOL bPresent;
    LPSTR szNameList = new char(50);
    ULONG pulSize = 50;
    LPSTR zName = new char(20);
    DEVHANDLE phDev;
    ULONG pulDevState = 20;
    DEVINFO pDevInfo;
    ULONG DEVAPI a = open(szDevName, &pulDevNameLen, &pulEvent);
    if (pulEvent == 1)
        bPresent = TRUE;
    else
        bPresent = FALSE;
    ULONG DEVAPI b = enumdev(bPresent, szNameList, &pulSize);
    ULONG DEVAPI c = connect(szDevName, &phDev);
    ULONG DEVAPI d = getstate(szDevName, &pulDevState);
    ULONG DEVAPI e = getdevinfo(phDev, &pDevInfo);
    cout<<"设备名称："<< szDevName <<endl<<"等待设备插拔函数: "<<a<<endl;
    cout << "设备名称列表：" << szNameList<<endl<< "枚举设备函数: " << b << endl;
    cout<<"设备操作句柄：" << phDev << endl << "连接设备函数: " << c << endl;
    cout<< "设备状态：" << pulDevState << endl << "获取设备状态函数: " << d << endl;
    cout << "获取设备信息函数: " << e << endl;
    FreeLibrary(hDLL);

     return 0;  
}