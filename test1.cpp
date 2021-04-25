// test1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<windows.h>
#include<wtypes.h>
#include <winbase.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include "skfapi.h"
using namespace std;
typedef ULONG (DEVAPI *pOpen)(LPSTR szDevName, ULONG* pulDevNameLen, ULONG* pulEvent);
typedef ULONG (DEVAPI *pEnumDev)(BOOL bPresent, LPSTR szNameList, ULONG* pulSize);
typedef ULONG(DEVAPI *pConnect)(LPSTR szName, DEVHANDLE* phDev);
typedef ULONG(DEVAPI* pGetState)(LPSTR szDevName, ULONG* pulDevState);
typedef ULONG(DEVAPI* pGetInfo)(DEVHANDLE hDev, DEVINFO* pDevInfo);
typedef ULONG(DEVAPI* pCreateApp)(DEVHANDLE hDev, LPSTR szAppName, LPSTR szAdminPin,DWORD dwAdminPinRetryCount, LPSTR szUserPin, DWORD dwUserPinRetryCount,DWORD dwCreateFileRights,HAPPLICATION *phApplication);
typedef ULONG(DEVAPI* pEnumApp)(DEVHANDLE hDev, LPSTR szAppName, ULONG* pulSize);
typedef ULONG(DEVAPI* pOpenApp)(DEVHANDLE hDev, LPSTR szAppName, HAPPLICATION* phApplication);
typedef ULONG(DEVAPI* pCreateContainer)(HAPPLICATION hApplication, LPSTR szContainerName, HCONTAINER* phContainer);
typedef ULONG(DEVAPI* pOpenContainer)(HAPPLICATION hApplication, LPSTR szContainerName, HCONTAINER* phContainer);
typedef ULONG(DEVAPI* pVerifyPin)(HAPPLICATION hApplication, ULONG ulPINType, LPSTR szPIN, ULONG* pulRetryCount);
typedef ULONG(DEVAPI* pContainerType)(HCONTAINER hContainer, ULONG* pulContainerType);
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
    pCreateApp createapp;
    pEnumApp enumapp;
    pOpenApp openapp;
    pCreateContainer createcontainer;
    pOpenContainer opencontainer;
    pVerifyPin verifypin;
    pContainerType containertype;
    hDLL = LoadLibrary(L"mtoken_gm3000.dll");  //加载 DLL文件
    if (hDLL == NULL)
        cout << "Error!!!\n";
    else
        cout << "已加载动态库\n";
    open = (pOpen)GetProcAddress(hDLL, "SKF_WaitForDevEvent");//等待设备插拔函数
    enumdev = (pEnumDev)GetProcAddress(hDLL, "SKF_EnumDev");//枚举设备函数
    connect = (pConnect)GetProcAddress(hDLL, "SKF_ConnectDev");//连接设备函数
    getstate = (pGetState)GetProcAddress(hDLL, "SKF_GetDevState");//获取设备状态函数
    getdevinfo = (pGetInfo)GetProcAddress(hDLL, "SKF_GetDevInfo");//获取设备信息函数
    createapp = (pCreateApp)GetProcAddress(hDLL, "SKF_CreateApplication");//创建应用函数
    enumapp = (pEnumApp)GetProcAddress(hDLL, "SKF_EnumApplication");//枚举应用函数
    openapp = (pOpenApp)GetProcAddress(hDLL, "SKF_OpenApplication");//打开应用函数
    createcontainer = (pCreateContainer)GetProcAddress(hDLL, "SKF_CreateContainer");//创建容器函数
    opencontainer = (pOpenContainer)GetProcAddress(hDLL, "SKF_OpenContainer");//打开容器函数
    verifypin = (pVerifyPin)GetProcAddress(hDLL, "SKF_VerifyPIN");//校验PIN函数
    containertype = (pContainerType)GetProcAddress(hDLL, "SKF_GetContainerType");//获得容器类型函数
    //取DLL中的函数地址，以备调用
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
    if (createapp == NULL)
        cout << "Error!!!\n";
    else
        cout << "查找到创建应用函数\n";
    if (enumapp == NULL)
        cout << "Error!!!\n";
    else
        cout << "查找到枚举应用函数\n";
    if (openapp == NULL)
        cout << "Error!!!\n";
    else
        cout << "查找到打开应用函数\n";
    if (createcontainer == NULL)
        cout << "Error!!!\n";
    else
        cout << "查找到创建容器函数\n";
    if (opencontainer == NULL)
        cout << "Error!!!\n";
    else
        cout << "查找到打开容器函数\n";
    if (verifypin == NULL)
        cout << "Error!!!\n";
    else
        cout << "查找到校验PIN函数\n";
    if ( containertype== NULL)
        cout << "Error!!!\n";
    else
        cout << "查找到获得容器类型函数\n";
    LPSTR szDevName = new char[20];
    ULONG pulDevNameLen=20;
    ULONG pulEvent=1;

    BOOL bPresent;
    LPSTR szNameList = new char[50];
    ULONG pulSize = 50;
    LPSTR zName = new char[20];
    DEVHANDLE phDev;
    ULONG pulDevState = 20;
    DEVINFO pDevInfo;

    LPSTR szAppName = new char[10];
    char appname[10] = "GM3000RSA";
    szAppName = appname;
    HAPPLICATION phApplication;
    LPSTR szAdminPin = new char[10];
    char AdminPin[10] = "admin";
    szAdminPin = AdminPin;
    LPSTR szUserPin = new char[10];
    char userpin[10] = "12345678";
    szUserPin = userpin;

    ULONG pulRetryCount;

    LPSTR szAppNameList = new char[15];

    LPSTR szContainerName = new char[11];
    char container[11] = "Container";
    szContainerName = container;
    HCONTAINER phContainer;

    ULONG pulContainerType;

    ULONG a;
    a = open(szDevName, &pulDevNameLen, &pulEvent);
    if (pulEvent == 1)
        bPresent = TRUE;
    else
        bPresent = FALSE;
    ULONG b = enumdev(bPresent, szNameList, &pulSize);
    ULONG DEVAPI c = connect(szDevName, &phDev);
    ULONG DEVAPI d = getstate(szDevName, &pulDevState);
    ULONG DEVAPI e = getdevinfo(phDev, &pDevInfo);
    ULONG DEVAPI f = openapp(phDev, szAppName, &phApplication);
    ULONG DEVAPI g = verifypin(phApplication, 1, szUserPin,&pulRetryCount);
   // ULONG DEVAPI h = createapp(phDev, szAppName, szAdminPin, 10, szUserPin, 10, SECURE_EVERYONE_ACCOUNT, &phApplication);
    ULONG DEVAPI i = enumapp(phDev, szAppNameList, &pulSize);
    ULONG DEVAPI j = createcontainer(phApplication, szContainerName, &phContainer);
    ULONG DEVAPI k = containertype(phContainer, &pulContainerType);
    cout<<"设备名称："<< szDevName <<endl<<"等待设备插拔函数: "<<a<<endl;
    cout << "设备名称列表：" << szNameList<<endl<< "枚举设备函数: " << b << endl;
    cout<<"设备操作句柄：" << phDev << endl << "连接设备函数: " << c << endl;
    cout<< "设备状态：" << pulDevState << endl << "获取设备状态函数: " << d << endl;
    cout << pDevInfo.SerialNumber<< pDevInfo.Version.minor<<pDevInfo.Manufacturer << endl<<"获取设备信息函数: " << e << endl;
    cout << "应用句柄：" << phApplication << endl << "打开应用函数：" << f << endl;
    cout << "校验PIN函数：" << g << endl;
    //cout << "创建应用函数：" << h << endl;
    cout << "应用名称列表：" << szAppNameList << endl << "枚举应用函数：" << i << endl;
    cout << "容器句柄：" << phContainer << endl << "创建容器函数：" << j << endl;
    cout << "容器类型：" << pulContainerType << endl << "获得容器类型函数：" << k << endl;
    FreeLibrary(hDLL);

     return 0;  
}