#include"student.h"


int main() {
    Read();
    while(1)
    {
        switch(menu())
        {
            case 1:
                login();
                break;
            case 2:
                Show();
                break;
            case 3:
                change();
                break;
            case 4:
                delete();
                break;
            case 5:
                Save();
                exit(0);
                break;
            default:
                break;
        }
        system("PAUSE");
    }
    return 0;
}
