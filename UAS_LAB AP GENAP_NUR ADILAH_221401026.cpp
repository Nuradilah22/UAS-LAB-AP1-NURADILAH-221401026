/*program Command Line Interface(CLI) untuk membuat program dengan menggunakan bahasa C++. 
program ini dapat membuat, melihat, mengedit serta menghapus catatan.*/
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// struktur catatan untuk menyimpan judul, isi, dan waktu pembuatan catatan.
struct Catatan {
    std::string judul;
    std::string isi;
    std::time_t waktuDibuat;
};

// fungsi untuk mencetak menu utama, dan meminta user untuk memilih nomor menu.
void tampilkanMenu() {
    std::cout << "====== Menu Utama ======" << std::endl;
    std::cout << "1. Tambah catatan " << std::endl;
    std::cout << "2. Lihat catatan " << std::endl;
    std::cout << "3. Edit catatan " << std::endl;
    std::cout << "4. Hapus catatan " << std::endl;
    std::cout << "5. Exit " << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Silahkan Pilih nomor : ";
}

/*fungsi untuk menampilkan daftar catatan yang ada di dalam vektor 'catatan'
dan mencetak judul, isi, dan waktu pembuatan setiap catatan.*/
void tampilkanCatatan(const std::vector<Catatan>& catatan) {

    std::cout << "=== Daftar catatan ===" << std::endl;
    for (const Catatan& catat : catatan) {
        std::cout << "Judul : " << catat.judul << std::endl;
        std::cout << "Isi : " << catat.isi << std::endl;
        std::cout << "Waktu Pembuatan : " << std::ctime(&catat.waktuDibuat);
        std::cout << "----------------" << std::endl;
    }
    std::cout << std::endl;
}
// fungsi ini digunakan untuk menambah catatan baru kedalam vektor 'catatan'.
void tambahCatatan(std::vector<Catatan>& catatan) {
    std::string judul, isi;
    std::cout << "Masukkan judul : ";
    std::cin.ignore();
    std::getline(std::cin, judul);
    std::cout << "Masukkan isi catatan : ";
    std::getline(std::cin, isi);
    
    std::time_t waktuPembuatan = std::time(nullptr);
    catatan.push_back({ judul, isi, waktuPembuatan });
    
    std::cout << "Catatan ditambahkan!" << std::endl << std::endl;
}

/*fungsi ini berisi objek-objek 'catatan' dan sebuah string yang bertujuan untuk 
mencari indeks pertama yang dimana judul catatan pada vektor sesuai dengan string yang diberikan.*/
int MencariIndeksCatatan(const std::vector<Catatan>& catatan, const std::string& judul) {
    for (size_t i = 0; i < catatan.size(); ++i) {
         if (catatan[i].judul == judul ) {
            return i;
         }
    }
    return -1; // jika tidak menemukan catatan nilai -1 dapat digunakan sebagai penanda bahwa juduk tidak valid.
}

// fungsi ini digunakan untuk mengubah isi dari sebuah catatan berdasarkan judul yang diberikan oleh user.
void editCatatan(std::vector<Catatan>& catatan) {
    std::cout << "Masukkan judul sebelumnya : ";
    std::cin.ignore();
    std::string judul;
    std::getline(std::cin, judul);
    int index = MencariIndeksCatatan(catatan, judul);

    if (index != -1){
        std::cout << "Masukkan isi catatan yang baru : ";
        std::cin.ignore();
        std::getline(std::cin, catatan[index].isi);
        std::cout << "Catatan sudah diubah\n";
    } else {
        std::cout << "Judul tidak valid.\n";
    }
}

// fungsi ini meminta user untuk memasukkan judul catatan yang ingin di hapus.
void hapusCatatan(std::vector<Catatan>& catatan) {
    std::cout << "Masukkan judul catatan yang ingin dihapus : ";
    std::string judul;
    std::cin.ignore(); // untuk mengabaikan karakter yang tersisa di buffer masukan.
    std::getline(std::cin, judul); // untuk membaca garis masukkan dari penggguna dan di simpan dalam variabel judul.
    
    int index = MencariIndeksCatatan(catatan, judul);

/*memeriksa apakah index memiliki nilai yang tidak sama dengan -1. 
Hal ini digunakan untuk memvalidasi apakah judul catatan yang dimasukkan oleh pengguna telah ditemukan dalam vektor catatan.*/
    if (index != -1){
        std::cout << "Catatan ditemukan :\n";
        std::cout << "Judul : " << catatan[index].judul << std::endl;
        std::cout << "Isi : " << catatan[index].isi << std::endl;
        std::cout << "Waktu pembuatan : " << ctime(&catatan[index].waktuDibuat) << std::endl;

        std::cout << "Apakah Anda yakin ingin menghapus catatan? (yes/no) : ";
        std::string konfirmasi;
        std::cin >> konfirmasi;

        if (konfirmasi == "yes") {
            catatan.erase(catatan.begin() + index);
            std::cout << "Catatan telah dihapus.\n";
        } else {
            std::cout << "Penghapusan catatan dibatalkan.\n";
        }
    } else {
        std::cout << "Catatan tidak valid.\n";
    }
}

// untuk memulai program utama
int main() {
    // membuat vektor yang akan digunakan untuk menyimpan semua catatan yang telah dibuat.
    std::vector<Catatan> catatan;
    int pilihan; 

    do {
        tampilkanMenu();
        std::cin >> pilihan;
        // menggunakan statement switch untuk memproses pilihan yang dimasukkan pengguna.
        switch (pilihan) {
            case 1:
                tambahCatatan(catatan);
                break;
            case 2:
                tampilkanCatatan(catatan);
                break;
            case 3:
                editCatatan(catatan);
                break;
            case 4:
                hapusCatatan(catatan);
                break;
            case 5:
                std::cout << "Terima kasih telah menggunakan program ini!. Keluar dari program..." << std::endl;
                break;
            default:
                std::cout << "Pilihan tidak valid!" << std::endl;
                break;
        }

        std::cout << std::endl;
    } while (pilihan != 5);

    return 0;
}
