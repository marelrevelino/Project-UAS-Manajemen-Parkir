#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std; // Menggunakan namespace standar

// Konstanta
const int MAX_PARKIR = 100; // Kapasitas maksimal parkir (100 kendaraan)
const double TARIF_MOTOR = 2000; // Tarif parkir motor per jam
const double TARIF_MOBIL = 5000; // Tarif parkir mobil per jam

// Struktur data untuk kendaraan
struct Kendaraan {
    string jenis; // Jenis kendaraan (motor/mobil)
    string platNomor; // Plat nomor kendaraan
    time_t waktuMasuk; // Waktu masuk parkir (tipe time_t)
    time_t waktuKeluar; // Waktu keluar parkir (tipe time_t)
};

// Array untuk menyimpan data kendaraan yang parkir
Kendaraan parkir[MAX_PARKIR]; // Array untuk menyimpan data kendaraan yang sedang parkir
int jumlahKendaraan = 0; // Jumlah kendaraan yang sedang parkir, diinisialisasi dengan 0

// Struktur data untuk log kendaraan
struct LogKendaraan {
    string jenis; // Jenis kendaraan (motor/mobil)
    string platNomor; // Plat nomor kendaraan
    time_t waktuMasuk; // Waktu masuk parkir
    time_t waktuKeluar; // Waktu keluar parkir
    double biaya; // Biaya parkir
};

vector<LogKendaraan> logParkir; // Vektor untuk menyimpan log parkir


// Fungsi untuk mendapatkan input waktu dari pengguna dan mengkonversinya ke time_t
time_t getTimeInput() {
    int year, month, day, hour, minute, second; // Mendeklarasikan variabel untuk menyimpan input waktu

    // Input dan validasi tahun
    while (true) {
        cout << "Masukkan tahun (YYYY): "; // Meminta input tahun
        cin >> year; // Membaca input tahun
        if (cin.fail() || year < 1900 || year > 2100) { // Validasi input tahun
            cout << "Input tahun tidak valid. Silakan masukkan tahun antara 1900 dan 2100.\n";
            cin.clear(); // Menghapus flag error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan karakter yang tersisa di buffer input
        } else {
            break;
        }
    }


    // Input dan validasi bulan
    while (true) {
        cout << "Masukkan bulan (MM): "; // Meminta input bulan
        cin >> month; // Membaca input bulan
        if (cin.fail() || month < 1 || month > 12) { // Validasi input bulan
            cout << "Input bulan tidak valid. Silakan masukkan bulan antara 1 dan 12.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    // Input dan validasi tanggal
    while (true) {
        cout << "Masukkan tanggal (DD): "; // Meminta input tanggal
        cin >> day; // Membaca input tanggal
        if (cin.fail() || day < 1 || day > 31) { // Validasi input tanggal (sementara, validasi lebih lanjut di bawah)
            cout << "Input tanggal tidak valid. Silakan masukkan tanggal antara 1 dan 31.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    // Input dan validasi jam
    while (true) {
        cout << "Masukkan jam (HH): "; // Meminta input jam
        cin >> hour; // Membaca input jam
        if (cin.fail() || hour < 0 || hour > 23) { // Validasi input jam
            cout << "Input jam tidak valid. Silakan masukkan jam antara 0 dan 23.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    // Input dan validasi menit
    while (true) {
        cout << "Masukkan menit (MM): "; // Meminta input menit
        cin >> minute; // Membaca input menit
        if (cin.fail() || minute < 0 || minute > 59) { // Validasi input menit
            cout << "Input menit tidak valid. Silakan masukkan menit antara 0 dan 59.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    // Input dan validasi detik
    while (true) {
        cout << "Masukkan detik (SS): "; // Meminta input detik
        cin >> second; // Membaca input detik
        if (cin.fail() || second < 0 || second > 59) { // Validasi input detik
            cout << "Input detik tidak valid. Silakan masukkan detik antara 0 dan 59.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }


    tm t; // Membuat objek struct tm untuk menyimpan waktu
    t.tm_year = year - 1900; // Menentukan tahun (tahun - 1900)
    t.tm_mon = month - 1; // Menentukan bulan (bulan - 1, karena indeks bulan mulai dari 0)
    t.tm_mday = day; // Menentukan hari
    t.tm_hour = hour; // Menentukan jam
    t.tm_min = minute; // Menentukan menit
    t.tm_sec = second; // Menentukan detik
    t.tm_isdst = -1; // Biarkan sistem menentukan Daylight Saving Time (DST)

    time_t waktu = mktime(&t); // Mengkonversi struct tm ke time_t

    // Validasi tanggal lebih lanjut setelah mktime
    if (waktu == -1 || t.tm_mday != day) { // Memeriksa apakah konversi berhasil dan tanggal valid
        cout << "Format waktu tidak valid. Periksa kembali tanggal yang dimasukkan.\n"; // Menampilkan pesan kesalahan jika konversi gagal atau tanggal tidak valid
        return -1; // Mengembalikan -1 untuk menunjukkan kesalahan
    }

    return waktu; // Mengembalikan nilai time_t
}

// Fungsi untuk menambahkan kendaraan ke parkir
void tambahKendaraan() {
    if (jumlahKendaraan < MAX_PARKIR) { // Memeriksa apakah parkir masih tersedia
        string jenis; // Menyimpan input jenis kendaraan sementara
        while (true) { // Loop untuk validasi input jenis kendaraan
            cout << "Jenis kendaraan (motor/mobil): "; // Meminta input jenis kendaraan
            cin >> jenis; // Membaca input jenis kendaraan
            if (jenis == "motor" || jenis == "mobil") { // Memeriksa apakah jenis kendaraan valid
                parkir[jumlahKendaraan].jenis = jenis; // Menugaskan jenis kendaraan jika valid
                break; // Keluar dari loop jika valid
            } else {
                cout << "Jenis kendaraan tidak valid. Masukkan 'motor' atau 'mobil'.\n"; // Menampilkan pesan kesalahan jika tidak valid
            }
        }

        cout << "Plat nomor: "; // Meminta input plat nomor
        cin >> parkir[jumlahKendaraan].platNomor; // Membaca input plat nomor

        cout << "Waktu masuk:\n"; // Menampilkan pesan untuk input waktu masuk
        parkir[jumlahKendaraan].waktuMasuk = getTimeInput(); // Memanggil fungsi getTimeInput() untuk mendapatkan waktu masuk
        if (parkir[jumlahKendaraan].waktuMasuk == -1) return; // Jika input waktu tidak valid, keluar dari fungsi


        jumlahKendaraan++; // Menambah jumlah kendaraan
        cout << "Kendaraan berhasil ditambahkan.\n"; // Menampilkan pesan sukses
    } else {
        cout << "Parkir penuh!\n"; // Menampilkan pesan jika parkir penuh
    }
}

// Fungsi untuk menghitung biaya parkir
double hitungBiaya(time_t waktuMasuk, time_t waktuKeluar, string jenis) {
    double diffInSeconds = difftime(waktuKeluar, waktuMasuk); // Menghitung selisih waktu masuk dan keluar dalam detik
    double lamaParkir = ceil(diffInSeconds / 3600.0); // Menghitung lama parkir dalam jam, dibulatkan ke atas
    double tarif = (jenis == "motor") ? TARIF_MOTOR : TARIF_MOBIL; // Menentukan tarif berdasarkan jenis kendaraan
    return tarif * lamaParkir; // Mengembalikan biaya parkir
}

// Fungsi untuk mengeluarkan kendaraan dari parkir
void keluarkanKendaraan() {
    string platNomor; // Mendeklarasikan variabel untuk menyimpan input plat nomor
    cout << "Masukkan plat nomor kendaraan yang akan keluar: "; // Meminta input plat nomor
    cin >> platNomor; // Membaca input plat nomor

    for (int i = 0; i < jumlahKendaraan; i++) { // Melakukan iterasi pada array parkir
        if (parkir[i].platNomor == platNomor) { // Memeriksa apakah plat nomor cocok
            cout << "Waktu keluar:\n"; // Meminta input waktu keluar
            parkir[i].waktuKeluar = getTimeInput(); // Memanggil fungsi getTimeInput() untuk mendapatkan waktu keluar
            if (parkir[i].waktuKeluar == -1) return; // Jika input waktu tidak valid, keluar dari fungsi

            // Validasi waktu keluar lebih kecil dari waktu masuk
            if (parkir[i].waktuKeluar < parkir[i].waktuMasuk) {
                cout << "Waktu keluar tidak valid. Waktu keluar harus setelah waktu masuk.\n";
                return;
            }


            double biaya = hitungBiaya(parkir[i].waktuMasuk, parkir[i].waktuKeluar, parkir[i].jenis); // Menghitung biaya parkir

            // Tambahkan ke log
            LogKendaraan logEntry; // Membuat objek LogKendaraan untuk menyimpan data log
            logEntry.jenis = parkir[i].jenis; // Menyimpan jenis kendaraan ke log
            logEntry.platNomor = parkir[i].platNomor; // Menyimpan plat nomor ke log
            logEntry.waktuMasuk = parkir[i].waktuMasuk; // Menyimpan waktu masuk ke log
            logEntry.waktuKeluar = parkir[i].waktuKeluar; // Menyimpan waktu keluar ke log
            logEntry.biaya = biaya; // Menyimpan biaya parkir ke log
            logParkir.push_back(logEntry); // Menambahkan data log ke vektor logParkir


            cout << "\nDetail Kendaraan:\n"; // Menampilkan detail kendaraan
            cout << "Jenis: " << parkir[i].jenis << endl; // Menampilkan jenis kendaraan
            cout << "Plat Nomor: " << parkir[i].platNomor << endl; // Menampilkan plat nomor
            cout << "Biaya Parkir: Rp " << fixed << setprecision(0) << biaya << endl; // Menampilkan biaya parkir

            // Menggeser elemen array untuk menghapus kendaraan yang keluar
            for (int j = i; j < jumlahKendaraan - 1; j++) { // Menggeser elemen array setelah kendaraan yang dikeluarkan
                parkir[j] = parkir[j + 1]; // Menimpa elemen saat ini dengan elemen berikutnya
            }
            jumlahKendaraan--; // Mengurangi jumlah kendaraan

            cout << "Kendaraan berhasil dikeluarkan.\n"; // Menampilkan pesan sukses
            return; // Keluar dari fungsi
        }
    }

    cout << "Kendaraan dengan plat nomor tersebut tidak ditemukan.\n"; // Menampilkan pesan jika kendaraan tidak ditemukan
}

// Fungsi untuk menampilkan daftar kendaraan yang parkir
void tampilkanDaftarKendaraan() {
    if (jumlahKendaraan == 0) { // Memeriksa apakah parkir kosong
        cout << "Parkir kosong.\n"; // Menampilkan pesan jika parkir kosong
        return; // Keluar dari fungsi
    }

    cout << "\nDaftar Kendaraan yang Parkir:\n"; // Menampilkan judul daftar kendaraan
    cout << "-----------------------------\n"; // Menampilkan garis pembatas
    for (int i = 0; i < jumlahKendaraan; i++) { // Melakukan iterasi pada array parkir
        cout << i + 1 << ". Jenis: " << parkir[i].jenis << ", Plat Nomor: " << parkir[i].platNomor << endl; // Menampilkan informasi kendaraan
    }
    cout << "-----------------------------\n"; // Menampilkan garis pembatas
}


// Fungsi untuk menampilkan log parkir
void tampilkanLogParkir() {
    if (logParkir.empty()) { // Memeriksa apakah log parkir kosong
        cout << "Log parkir kosong.\n"; // Menampilkan pesan jika log parkir kosong
        return; // Keluar dari fungsi
    }

    cout << "\nLog Parkir:\n"; // Menampilkan judul log parkir
    cout << "-----------------------------\n"; // Menampilkan garis pembatas
    for (const auto& log : logParkir) { // Melakukan iterasi pada vektor logParkir
        cout << "Jenis: " << log.jenis << endl; // Menampilkan jenis kendaraan
        cout << "Plat Nomor: " << log.platNomor << endl; // Menampilkan plat nomor
        cout << "Waktu Masuk: " << ctime(&(log.waktuMasuk)); // Menampilkan waktu masuk
        cout << "Waktu Keluar: " << ctime(&(log.waktuKeluar)); // Menampilkan waktu keluar
        cout << "Biaya: Rp " << fixed << setprecision(0) << log.biaya << endl; // Menampilkan biaya parkir
        cout << "-----------------------------\n"; // Menampilkan garis pembatas

    }
}

int main() {
    int pilihan; // Mendeklarasikan variabel untuk menyimpan pilihan menu

    do {
        cout << "\nMenu:\n"; // Menampilkan menu
        cout << "1. Tambah Kendaraan\n"; // Opsi untuk menambahkan kendaraan
        cout << "2. Keluarkan Kendaraan\n"; // Opsi untuk mengeluarkan kendaraan
        cout << "3. Tampilkan Daftar Kendaraan\n"; // Opsi untuk menampilkan daftar kendaraan
        cout << "4. Tampilkan Log Parkir\n"; // Opsi untuk menampilkan log parkir
        cout << "5. Keluar\n"; // Opsi untuk keluar dari program
        cout << "Pilihan: "; // Meminta input pilihan
        cin >> pilihan; // Membaca input pilihan

        switch (pilihan) { // Melakukan switch case berdasarkan pilihan
            case 1:
                system("cls");
                tambahKendaraan(); // Memanggil fungsi tambahKendaraan()
                break; // Keluar dari switch case
            case 2:
                system("cls");
                keluarkanKendaraan(); // Memanggil fungsi keluarkanKendaraan()
                break; // Keluar dari switch case
            case 3:
                system("cls");
                tampilkanDaftarKendaraan(); // Memanggil fungsi tampilkanDaftarKendaraan()
                break; // Keluar dari switch case
            case 4:
                system("cls");
                tampilkanLogParkir(); // Memanggil fungsi tampilkanLogParkir()
                break; // Keluar dari switch case
            case 5:
                system("cls");
                cout << "Terima kasih!\n"; // Menampilkan pesan terima kasih
                break; // Keluar dari switch case
            default:
                system("cls");
                cout << "Pilihan tidak valid.\n"; // Menampilkan pesan jika pilihan tidak valid
        }
    } while (pilihan != 5); // Mengulang loop selama pilihan bukan 5

    return 0; // Mengembalikan 0 untuk menunjukkan program berakhir dengan sukses
}
