#include <iostream>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "Hello\n";
    std::cout << "✓ Success\n";

    system("pause");
    return 0;
}
