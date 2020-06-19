#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<windows.h>

void hidefile(char* filename,char* bmpfilename);
char* getfilecontent(char* filename,DWORD* filesize);
void saveFile(char* fp,DWORD filesize, char* filename);
void showfile(char *newfilename, char *bmpfilename);

int main()
{
    using namespace std;
    int n;
    char filename[MAX_PATH]={0};
    char bmpfilename[MAX_PATH]={0};
    char newfilename[MAX_PATH]={0};
    while(1)
    {
        cout<<"隐藏（1）或者恢复（2）："<<endl;
        cin>>n;
        if(1==n)
        {
            cout<<"请输入要隐藏的文件名："<<endl;
            cin>>filename;
            cout<<"请输入要隐藏到的文件名："<<endl;
            cin>>bmpfilename;
            hidefile(filename,bmpfilename);
            DeleteFileA(filename);
        }
        else if(2==n)
        {
            cout <<"请输入要显示的文件名"<<endl;
            cin>>newfilename;
            cout <<"请输入隐藏的位置"<<endl;
            cin>>bmpfilename;
            showfile(newfilename,bmpfilename);
        }
        else
            break;
    }
    std::cout <<"按任意键退出...";
    cin.get();
    return 0;
}

void hidefile(char* filename,char* bmpfilename)
{
    DWORD filesize=1;
    DWORD bmpfilesize=1;
    char* fpfile;
    char* fpbmp;

    fpfile=getfilecontent(filename,&filesize);
    fpbmp=getfilecontent(bmpfilename,&bmpfilesize);
    char* fpcurrentfile=fpfile;
    char* fpcurrentbmp=fpbmp;

    DWORD* poffbits= (DWORD*)(fpcurrentbmp+10);

    fpcurrentbmp+=(*(poffbits)+3);

    *((DWORD*)fpcurrentbmp)=filesize;

    std::cout << filesize<<" hided" <<std::endl;

    fpcurrentbmp+=6;
    while(1)
    {
        if(fpcurrentbmp>=(fpbmp+bmpfilesize)||
           fpcurrentfile>=(fpfile+filesize))
        {
            break;
        }
        *fpcurrentbmp=*fpcurrentfile;
        fpcurrentfile++;
        fpcurrentbmp+=6;
    }

    saveFile(fpbmp,bmpfilesize, bmpfilename);

    delete[] fpfile;
    delete[] fpbmp;
    return;
}

void saveFile(char* fp,DWORD filesize, char* filename)
{
    using namespace std;
    HANDLE hfile=CreateFileA(
            filename,
            GENERIC_ALL,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_ALWAYS,
            NULL,NULL);
    if(INVALID_HANDLE_VALUE == hfile)
    {
        cout << "打开文件失败1";
        return;
    }
    SetFilePointer(hfile,0,0,FILE_BEGIN);
    DWORD writesize;
    WriteFile(hfile,fp,filesize,&writesize,NULL);

    if(writesize ==filesize)
        cout << "写入数据成功"<<endl;

    CloseHandle(hfile);
}
char* getfilecontent(char* filename,DWORD* filesize)
{
    using namespace std;
    HANDLE hfile=CreateFile(
            filename,
            GENERIC_ALL,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            NULL,NULL);
    if(INVALID_HANDLE_VALUE == hfile)
    {
        cout << "打开文件失败2";
        return NULL;
    }
    DWORD filesizehigh;
    DWORD filesizelow;
    filesizelow =GetFileSize(hfile,&filesizehigh);
    *filesize=filesizelow;
    DWORD readsize;
    char* filedata=new char[filesizelow];
    ReadFile(hfile,filedata,filesizelow,&readsize,NULL);

    if(readsize !=filesizelow)
    {
        cout<< "Failed in reading file!";
        return NULL;
    }

    CloseHandle(hfile);

    return filedata;
}
void showfile(char *newfilename, char *bmpfilename)
{
    DWORD bmpfilesize=1;
    char* fpbmp;

    fpbmp=getfilecontent(bmpfilename,&bmpfilesize);
    char* fpcurrentbmp=fpbmp;

    DWORD* poffbits= (DWORD*)(fpcurrentbmp+10);

    fpcurrentbmp+=(*(poffbits)+3);

    DWORD newfilesize=*((DWORD*)fpcurrentbmp);

    std::cout << newfilesize<<" revealed" <<std::endl;

    char* newfile=new char[newfilesize];
    char* fpcurrentnewfile=newfile;

    fpcurrentbmp+=6;

    for(int i=0;i<newfilesize;i++)
    {
        *fpcurrentnewfile=*fpcurrentbmp;
        fpcurrentnewfile++;
        fpcurrentbmp+=6;
    }
    saveFile(newfile,newfilesize,newfilename);
    delete[] fpbmp;
    delete[] newfile;
}