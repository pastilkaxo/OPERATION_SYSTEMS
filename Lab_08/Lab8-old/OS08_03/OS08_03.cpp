#include <iostream>
#include <iomanip>
#include <Windows.h>

#define PAGE_SIZE 4096       // Размер страницы: 4 KB
#define TABLE_SIZE 1024      // Количество элементов в таблице

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");

    // Данные задачи
    DWORD CR3 = 0x13907000;           // Базовый адрес таблицы страниц (Page Directory)
    DWORD VirtualAddress = 0x0167015F; // Виртуальный адрес

    // Разбиваем виртуальный адрес на части
    DWORD PageDirIndex = (VirtualAddress >> 22) & 0x3FF;    // 10 бит для индекса в Page Directory
    DWORD PageTableIndex = (VirtualAddress >> 12) & 0x3FF;  // 10 бит для индекса в Page Table
    DWORD PageOffset = VirtualAddress & 0xFFF;              // 12 бит для смещения внутри страницы

    // Выводим промежуточные данные
    cout << "Виртуальный адрес: 0x" << hex << VirtualAddress << dec << "\n";
    cout << "Регистр CR3 (база таблицы страниц): 0x" << hex << CR3 << "\n";
    cout << "Индекс в Page Directory: " << PageDirIndex << "\n";
    cout << "Индекс в Page Table: " << PageTableIndex << "\n";
    cout << "Смещение внутри страницы: " << PageOffset << dec << " байт\n";

    // Симуляция таблицы страниц
    DWORD PageDirectory[TABLE_SIZE]; // Таблица директорий страниц
    DWORD PageTable[TABLE_SIZE];     // Таблица страниц

    // Заполняем таблицу директорий страниц (для простоты)
    for (int i = 0; i < TABLE_SIZE; i++) {
        PageDirectory[i] = CR3 + i * PAGE_SIZE; // Линейное отображение страниц
    }

    // Заполняем таблицу страниц (для простоты)
    for (int i = 0; i < TABLE_SIZE; i++) {
        PageTable[i] = CR3 + (i + 1) * PAGE_SIZE; // Линейное отображение страниц
    }


    // Адрес записи в каталоге страниц (PDE)
    DWORD PageDirectoryEntryAddress = CR3 + PageDirIndex * sizeof(DWORD);
    cout << "Адрес записи в каталоге страниц (PDE): 0x" << hex << PageDirectoryEntryAddress << dec << "\n";

    // Адрес записи в таблице страниц (PTE)
    DWORD PageTableBaseAddress = PageDirectory[PageDirIndex];
    DWORD PageTableEntryAddress = PageTableBaseAddress + PageTableIndex * sizeof(DWORD);
    cout << "Адрес записи в таблице страниц (PTE): 0x" << hex << PageTableEntryAddress << dec << "\n";


    // Базовый физический адрес страницы
    DWORD BasePhysicalPageAddress = PageTable[PageTableIndex];
    cout << "Базовый физический адрес страницы: 0x" << hex << BasePhysicalPageAddress << dec << "\n";

    // Получаем физический адрес
    DWORD PhysicalAddress = BasePhysicalPageAddress + PageOffset;

    cout << "Физический адрес: 0x" << hex << PhysicalAddress << dec << "\n";

    // Симуляция чтения из физической памяти
    BYTE* physicalMemory = new BYTE[256 * PAGE_SIZE]; // Симуляция физической памяти
    for (int i = 0; i < 256 * PAGE_SIZE; i++) {
        physicalMemory[i] = i % 256; // Заполняем тестовыми данными
    }

    // Читаем значение по физическому адресу
    BYTE value = physicalMemory[PhysicalAddress % (256 * PAGE_SIZE)];
    cout << "Содержимое байта по физическому адресу: 0x" << hex << (int)value << dec << "\n";

    // Освобождаем память
    delete[] physicalMemory;

    return 0;
}
