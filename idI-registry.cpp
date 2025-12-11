#include <iostream>
#include <limits>   // untuk numeric_limits
#include <string>   // untuk std::string

// Project Name: Citizen ID Registry

struct KtpRecord {
    std::string name;
    std::string address;
    std::string bloodType;
};

class DoublyLinkedList {
private:
    struct Node {
        KtpRecord data;
        Node* next;
        Node* prev;

        Node(const KtpRecord& d) : data(d), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        clear();
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void pushFront(const KtpRecord& rec) {
        Node* node = new Node(rec);

        if (isEmpty()) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
    }

    void pushBack(const KtpRecord& rec) {
        Node* node = new Node(rec);

        if (isEmpty()) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    bool popFront() {
        if (isEmpty()) {
            return false;
        }

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
        }
        return true;
    }

    void printAll() const {
        if (isEmpty()) {
            std::cout << "Data masih kosong.\n";
            return;
        }

        const Node* curr = head;
        int index = 1;

        while (curr != nullptr) {
            std::cout << "-------------------------------\n";
            std::cout << "Data ke-" << index++ << "\n";
            std::cout << "Nama           : " << curr->data.name << "\n";
            std::cout << "Alamat         : " << curr->data.address << "\n";
            std::cout << "Golongan Darah : " << curr->data.bloodType << "\n";
            curr = curr->next;
        }
        std::cout << "-------------------------------\n";
    }

    void clear() {
        while (!isEmpty()) {
            popFront();
        }
    }
};

// Utility untuk input aman dengan getline
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

KtpRecord inputKtpRecord() {
    KtpRecord rec;

    std::cout << "Nama           : ";
    std::getline(std::cin, rec.name);

    std::cout << "Alamat         : ";
    std::getline(std::cin, rec.address);

    std::cout << "Golongan darah : ";
    std::getline(std::cin, rec.bloodType);

    return rec;
}

int main() {
    DoublyLinkedList list;
    int choice = 0;

    do {
        std::cout << "\n=========== CITIZEN ID REGISTRY ===========\n";
        std::cout << "1. Input data di depan\n";
        std::cout << "2. Input data di belakang\n";
        std::cout << "3. Hapus data di depan\n";
        std::cout << "4. Tampilkan semua data\n";
        std::cout << "5. Keluar\n";
        std::cout << "Pilihan Anda: ";
        std::cin >> choice;

        // Bersihkan newline sisa input angka
        clearInputBuffer();

        switch (choice) {
        case 1: {
            std::cout << "\n--- Input Data di Depan ---\n";
            KtpRecord rec = inputKtpRecord();
            list.pushFront(rec);
            std::cout << "Data berhasil ditambahkan di depan.\n";
            break;
        }
        case 2: {
            std::cout << "\n--- Input Data di Belakang ---\n";
            KtpRecord rec = inputKtpRecord();
            list.pushBack(rec);
            std::cout << "Data berhasil ditambahkan di belakang.\n";
            break;
        }
        case 3: {
            std::cout << "\n--- Hapus Data di Depan ---\n";
            if (list.popFront()) {
                std::cout << "Data pertama berhasil dihapus.\n";
            } else {
                std::cout << "Tidak ada data yang bisa dihapus (list kosong).\n";
            }
            break;
        }
        case 4:
            std::cout << "\n--- Daftar Seluruh Data ---\n";
            list.printAll();
            break;
        case 5:
            std::cout << "Keluar dari program...\n";
            break;
        default:
            std::cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            break;
        }

    } while (choice != 5);

    return 0;
}
