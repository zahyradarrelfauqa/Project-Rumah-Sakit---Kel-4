#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <sstream>
#include <ctime>
#include <algorithm> // Untuk std::remove_if
#include <iomanip> // For std::fixed and std::setprecision

using namespace std;

// --- Utility Functions ---
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << (ltm->tm_mday < 10 ? "0" : "") << ltm->tm_mday << "-"
       << (ltm->tm_mon + 1 < 10 ? "0" : "") << (ltm->tm_mon + 1) << "-"
       << (1900 + ltm->tm_year);
    return ss.str();
}

// --- Class Definitions ---

class Pasien {
public:
    string nama;
    string nik;
    int umur;
    string password;
    string jenisKelamin; // Dari kode 3 untuk statistik
    string alamat;       // Tambahan agar lebih lengkap

    void tampilkanData() const {
        cout << "Nama            : " << nama << endl;
        cout << "NIK             : " << nik << endl;
        cout << "Umur            : " << umur << endl;
        cout << "Jenis Kelamin   : " << jenisKelamin << endl;
        cout << "Alamat          : " << alamat << endl;
    }
};

class RekamMedis {
public:
    string nikPasien; // Menggunakan nikPasien agar konsisten dengan Pasien.nik
    string tanggal;
    string diagnosis;
    string catatanTambahan; // Dari kode 2 (catatanMedis)
    string hasilDiagnostik; // Dari kode 2 (hasilDiagnostik)
    string resepObat;       // Dari kode 2 (resepObat)

    void tampilkanRekam() const {
        cout << "NIK Pasien      : " << nikPasien << endl;
        cout << "Tanggal         : " << tanggal << endl;
        cout << "Diagnosis       : " << diagnosis << endl;
        cout << "Catatan Tambahan: " << catatanTambahan << endl;
        cout << "Hasil Diagnostik: " << hasilDiagnostik << endl;
        cout << "Resep Obat      : " << resepObat << endl;
    }
};

class RawatInap {
public:
    string nikPasien;
    string ruangan;
    string tanggalMasuk;
    string tanggalKeluar;

    void tampilkanRawat() const {
        cout << "NIK Pasien      : " << nikPasien << endl;
        cout << "Ruangan         : " << ruangan << endl;
        cout << "Tanggal Masuk   : " << tanggalMasuk << endl;
        cout << "Tanggal Keluar  : " << tanggalKeluar << endl;
    }
};

class Pembayaran {
public:
    string nikPasien;
    string tanggal;
    string jenisPembayaran; // Rawat Inap, Pemeriksaan, dll.
    double jumlah;

    void tampilkanPembayaran() const {
        cout << "NIK Pasien      : " << nikPasien << endl;
        cout << "Tanggal         : " << tanggal << endl;
        cout << "Jenis Pembayaran: " << jenisPembayaran << endl;
        cout << "Jumlah          : Rp" << fixed << setprecision(2) << jumlah << endl;
    }
};

class Dokter {
public:
    string nama;
    string jamPraktek;
    string spesialisasi; // Tambahan untuk detail dokter

    void tampilkan() const {
        cout << "Nama Dokter     : " << nama << endl;
        cout << "Spesialisasi    : " << spesialisasi << endl;
        cout << "Jam Praktek     : " << jamPraktek << endl;
    }
};

class Klinik {
public:
    string namaKlinik;
    vector<Dokter> daftarDokter;

    Klinik(const string& nama = "") : namaKlinik(nama) {}

    void tampilkanDokter() const {
        cout << "Dokter di Klinik " << namaKlinik << ":\n";
        if (daftarDokter.empty()) {
            cout << "   Belum ada dokter yang terdaftar.\n";
        } else {
            for (size_t i = 0; i < daftarDokter.size(); ++i) {
                cout << "   " << (i + 1) << ". ";
                daftarDokter[i].tampilkan();
                cout << "--------------------------------\n";
            }
        }
    }

    void tambahDokter() {
        Dokter d;
        cout << "Masukkan nama dokter: ";
        getline(cin, d.nama);
        cout << "Masukkan spesialisasi: ";
        getline(cin, d.spesialisasi);
        cout << "Masukkan jam praktek (contoh: 08:00-14:00): ";
        getline(cin, d.jamPraktek);

        daftarDokter.push_back(d);
        cout << ">> Dokter berhasil ditambahkan ke Klinik " << namaKlinik << ".\n";
    }

    void ubahDokter() {
        if (daftarDokter.empty()) {
            cout << "Tidak ada dokter untuk diubah.\n";
            return;
        }
        cout << "Daftar dokter di Klinik " << namaKlinik << ":\n";
        for (size_t i = 0; i < daftarDokter.size(); ++i) {
            cout << (i + 1) << ". " << daftarDokter[i].nama << " (" << daftarDokter[i].spesialisasi << ", " << daftarDokter[i].jamPraktek << ")\n";
        }
        cout << "Pilih nomor dokter yang akan diubah: ";
        int pilihan;
        cin >> pilihan;
        clearInput();
        if (pilihan < 1 || pilihan > static_cast<int>(daftarDokter.size())) {
            cout << "Pilihan tidak valid.\n";
            return;
        }
        cout << "Masukkan nama dokter baru (kosongkan jika tidak ingin diubah): ";
        string namaBaru;
        getline(cin, namaBaru);
        if (!namaBaru.empty()) daftarDokter[pilihan - 1].nama = namaBaru;
        cout << "Masukkan spesialisasi baru (kosongkan jika tidak ingin diubah): ";
        string spesialisasiBaru;
        getline(cin, spesialisasiBaru);
        if (!spesialisasiBaru.empty()) daftarDokter[pilihan - 1].spesialisasi = spesialisasiBaru;
        cout << "Masukkan jam praktek baru (kosongkan jika tidak ingin diubah): ";
        string jamBaru;
        getline(cin, jamBaru);
        if (!jamBaru.empty()) daftarDokter[pilihan - 1].jamPraktek = jamBaru;
        cout << ">> Dokter berhasil diubah.\n";
    }

    void hapusDokter() {
        if (daftarDokter.empty()) {
            cout << "Tidak ada dokter untuk dihapus.\n";
            return;
        }
        cout << "Daftar dokter di Klinik " << namaKlinik << ":\n";
        for (size_t i = 0; i < daftarDokter.size(); ++i) {
            cout << (i + 1) << ". " << daftarDokter[i].nama << " (" << daftarDokter[i].spesialisasi << ", " << daftarDokter[i].jamPraktek << ")\n";
        }
        cout << "Pilih nomor dokter yang akan dihapus: ";
        int pilihan;
        cin >> pilihan;
        clearInput();
        if (pilihan < 1 || pilihan > static_cast<int>(daftarDokter.size())) {
            cout << "Pilihan tidak valid.\n";
            return;
        }
        daftarDokter.erase(daftarDokter.begin() + (pilihan - 1));
        cout << ">> Dokter berhasil dihapus.\n";
    }
};

class PenyakitPrioritas {
public:
    string namaPenyakit;
    string pasienNik;
    string tanggalDiagnosis;
    string status; // misal: dalam perawatan, sembuh, meninggal

    void tampilkan() const {
        cout << "NIK Pasien      : " << pasienNik << endl;
        cout << "Penyakit        : " << namaPenyakit << endl;
        cout << "Tanggal Diagnosa: " << tanggalDiagnosis << endl;
        cout << "Status          : " << status << endl;
    }
};

// --- Global Data Vectors ---
vector<Pasien> daftarPasien;
vector<RekamMedis> daftarRekamMedis;
vector<RawatInap> daftarRawatInap;
vector<Pembayaran> daftarPembayaran;
vector<PenyakitPrioritas> daftarPenyakitPrioritas;

Klinik klinikJantung("Jantung");
Klinik klinikKemoterapi("Kemoterapi");
Klinik klinikMaternalPerinatal("Maternal-Perinatal");
Klinik klinikHemodialisis("Hemodialisis");

// --- File I/O Functions ---

// Pasien
void simpanPasienKeFile() {
    ofstream file("data_pasien.txt");
    for (const auto& p : daftarPasien) {
        file << p.nama << "," << p.nik << "," << p.umur << "," << p.password << "," << p.jenisKelamin << "," << p.alamat << endl;
    }
}

void muatPasienDariFile() {
    daftarPasien.clear();
    ifstream file("data_pasien.txt");
    string line;
    while (getline(file, line)) {
        Pasien p;
        stringstream ss(line);
        string segment;
        getline(ss, p.nama, ',');
        getline(ss, p.nik, ',');
        getline(ss, segment, ',');
        p.umur = stoi(segment);
        getline(ss, p.password, ',');
        getline(ss, p.jenisKelamin, ',');
        getline(ss, p.alamat); // Alamat adalah bagian terakhir
        daftarPasien.push_back(p);
    }
}

// Rekam Medis
void simpanRekamMedisKeFile() {
    ofstream file("data_rekam_medis.txt");
    for (const auto& r : daftarRekamMedis) {
        file << r.nikPasien << "," << r.tanggal << "," << r.diagnosis << "," << r.catatanTambahan << "," << r.hasilDiagnostik << "," << r.resepObat << endl;
    }
}

void muatRekamMedisDariFile() {
    daftarRekamMedis.clear();
    ifstream file("data_rekam_medis.txt");
    string line;
    while (getline(file, line)) {
        RekamMedis r;
        stringstream ss(line);
        getline(ss, r.nikPasien, ',');
        getline(ss, r.tanggal, ',');
        getline(ss, r.diagnosis, ',');
        getline(ss, r.catatanTambahan, ',');
        getline(ss, r.hasilDiagnostik, ',');
        getline(ss, r.resepObat);
        daftarRekamMedis.push_back(r);
    }
}

// Rawat Inap
void simpanRawatInapKeFile() {
    ofstream file("data_rawat_inap.txt");
    for (const auto& r : daftarRawatInap) {
        file << r.nikPasien << "," << r.ruangan << "," << r.tanggalMasuk << "," << r.tanggalKeluar << endl;
    }
}

void muatRawatInapDariFile() {
    daftarRawatInap.clear();
    ifstream file("data_rawat_inap.txt");
    string line;
    while (getline(file, line)) {
        RawatInap r;
        stringstream ss(line);
        getline(ss, r.nikPasien, ',');
        getline(ss, r.ruangan, ',');
        getline(ss, r.tanggalMasuk, ',');
        getline(ss, r.tanggalKeluar);
        daftarRawatInap.push_back(r);
    }
}

// Pembayaran
void simpanPembayaranKeFile() {
    ofstream file("data_pembayaran.txt");
    for (const auto& p : daftarPembayaran) {
        file << p.nikPasien << "," << p.tanggal << "," << p.jenisPembayaran << "," << p.jumlah << endl;
    }
}

void muatPembayaranDariFile() {
    daftarPembayaran.clear();
    ifstream file("data_pembayaran.txt");
    string line;
    while (getline(file, line)) {
        Pembayaran p;
        stringstream ss(line);
        string segment;
        getline(ss, p.nikPasien, ',');
        getline(ss, p.tanggal, ',');
        getline(ss, p.jenisPembayaran, ',');
        getline(ss, segment);
        p.jumlah = stod(segment);
        daftarPembayaran.push_back(p);
    }
}

// Dokter & Klinik
void simpanDokterKeFile(const Klinik& klinik, const string& filename) {
    ofstream file(filename);
    for (const auto& d : klinik.daftarDokter) {
        file << d.nama << "," << d.spesialisasi << "," << d.jamPraktek << endl;
    }
}

void muatDokterDariFile(Klinik& klinik, const string& filename) {
    klinik.daftarDokter.clear();
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Dokter d;
        stringstream ss(line);
        getline(ss, d.nama, ',');
        getline(ss, d.spesialisasi, ',');
        getline(ss, d.jamPraktek);
        klinik.daftarDokter.push_back(d);
    }
}

// Penyakit Prioritas
void simpanPenyakitPrioritasKeFile() {
    ofstream file("data_penyakit_prioritas.txt");
    for (const auto& p : daftarPenyakitPrioritas) {
        file << p.pasienNik << "," << p.namaPenyakit << "," << p.tanggalDiagnosis << "," << p.status << endl;
    }
}

void muatPenyakitPrioritasDariFile() {
    daftarPenyakitPrioritas.clear();
    ifstream file("data_penyakit_prioritas.txt");
    string line;
    while (getline(file, line)) {
        PenyakitPrioritas p;
        stringstream ss(line);
        getline(ss, p.pasienNik, ',');
        getline(ss, p.namaPenyakit, ',');
        getline(ss, p.tanggalDiagnosis, ',');
        getline(ss, p.status);
        daftarPenyakitPrioritas.push_back(p);
    }
}

// --- Pasien Features ---
void registrasiPasien() {
    Pasien p;
    cout << "\n=== REGISTRASI PASIEN ===\n";
    cout << "Nama lengkap        : "; getline(cin, p.nama);
    cout << "NIK                 : "; getline(cin, p.nik);
    // Cek apakah NIK sudah terdaftar
    for(const auto& existingPasien : daftarPasien) {
        if (existingPasien.nik == p.nik) {
            cout << ">> NIK sudah terdaftar. Registrasi gagal.\n";
            return;
        }
    }
    cout << "Umur                : "; cin >> p.umur;
    clearInput();
    cout << "Jenis Kelamin (L/P): "; getline(cin, p.jenisKelamin);
    cout << "Alamat              : "; getline(cin, p.alamat);
    cout << "Password            : "; getline(cin, p.password);

    daftarPasien.push_back(p);
    simpanPasienKeFile();
    cout << ">> Registrasi berhasil!\n";
}

Pasien* loginPasien() {
    string nikInput, passInput;
    cout << "\n=== LOGIN PASIEN ===\n";
    cout << "NIK             : "; getline(cin, nikInput);
    cout << "Password        : "; getline(cin, passInput);

    for (auto &p : daftarPasien) {
        if (p.nik == nikInput && p.password == passInput) {
            cout << ">> Login berhasil. Selamat datang, " << p.nama << "!\n";
            return &p;
        }
    }
    cout << ">> Login gagal. NIK atau password salah.\n";
    return nullptr;
}

void tambahRekamMedis(const string &nik) {
    RekamMedis r;
    r.nikPasien = nik;
    cout << "\n=== INPUT REKAM MEDIS ===\n";
    r.tanggal = getCurrentDate(); // Otomatis tanggal hari ini
    cout << "Diagnosis           : "; getline(cin, r.diagnosis);
    cout << "Catatan Tambahan    : "; getline(cin, r.catatanTambahan);
    cout << "Hasil Diagnostik    : "; getline(cin, r.hasilDiagnostik);
    cout << "Resep Obat          : "; getline(cin, r.resepObat);

    daftarRekamMedis.push_back(r);
    simpanRekamMedisKeFile();
    cout << ">> Rekam medis berhasil disimpan.\n";
}

void lihatRekamMedis(const string &nik) {
    cout << "\n=== DATA REKAM MEDIS ===\n";
    bool ditemukan = false;
    for (const auto& r : daftarRekamMedis) {
        if (r.nikPasien == nik) {
            r.tampilkanRekam();
            cout << "---------------------\n";
            ditemukan = true;
        }
    }
    if (!ditemukan)
        cout << ">> Tidak ada data rekam medis untuk NIK ini.\n";
}

void tambahRawatInap(const string &nik) {
    RawatInap r;
    r.nikPasien = nik;

    cout << "\n=== INPUT RAWAT INAP ===\n";

    int pilihanLayanan;
    cout << "Pilih layanan rawat inap:\n";
    cout << "1. BPJS\n";
    cout << "2. Umum\n";
    cout << "Pilihan(1/2): ";
    cin >> pilihanLayanan;
    clearInput();

    vector<string> pilihanRuangan;

    if(pilihanLayanan == 1) {
        cout << "Pilih ruangan BPJS:\n";
        pilihanRuangan = {"Kelas 1", "Kelas 2", "Kelas 3"};
    } else if (pilihanLayanan == 2) {
        cout << "Pilih ruangan Umum:\n";
        pilihanRuangan = {"VIP", "Kelas 1", "Kelas 2", "Kelas 3"};
    } else {
        cout << ">> Pilihan layanan tidak valid.\n";
        return;
    }

    for (size_t i = 0; i < pilihanRuangan.size(); ++i) {
        cout << i + 1 << ". " << pilihanRuangan[i] << endl;
    }

    int pilihanRuang;
    cout << "Pilih ruangan (1-" << pilihanRuangan.size() << "): ";
    cin >> pilihanRuang;
    clearInput();

    if (pilihanRuang < 1 || pilihanRuang > static_cast<int>(pilihanRuangan.size())) {
        cout << ">> Pilihan ruangan tidak valid.\n";
        return;
    }

    r.ruangan = pilihanRuangan[pilihanRuang - 1];
    cout << "Tanggal masuk (dd-mm-yyyy): "; getline(cin, r.tanggalMasuk);
    cout << "Tanggal keluar (dd-mm-yyyy): "; getline(cin, r.tanggalKeluar); // Bisa kosong jika masih dirawat

    daftarRawatInap.push_back(r);
    simpanRawatInapKeFile();
    cout << ">> Rawat inap berhasil disimpan.\n";
}

void lihatRawatInap(const string &nik) {
    cout << "\n=== DATA RAWAT INAP ===\n";
    bool ditemukan = false;
    for (const auto& r : daftarRawatInap) {
        if (r.nikPasien == nik) {
            r.tampilkanRawat();
            cout << "---------------------\n";
            ditemukan = true;
        }
    }
    if (!ditemukan)
        cout << ">> Tidak ada data rawat inap untuk NIK ini.\n";
}

void tambahPembayaran(const string &nik) {
    Pembayaran p;
    p.nikPasien = nik;
    cout << "\n=== NOTA PEMBAYARAN ===\n";

    // Ambil nama pasien berdasarkan NIK
    string namaPasien = "Tidak ditemukan";
    for (const auto &pasien : daftarPasien) {
        if (pasien.nik == nik) {
            namaPasien = pasien.nama;
            break;
        }
    }

    cout << "NIK Pasien          : " << nik << endl;
    cout << "Nama Pasien         : " << namaPasien << endl;

    // Input tanggal dan jenis pembayaran
    p.tanggal = getCurrentDate(); // Otomatis tanggal hari ini
    cout << "Jenis Pembayaran    : "; getline(cin, p.jenisPembayaran);

    // Input jumlah tagihan
    cout << "Tagihan (Rp)        : "; cin >> p.jumlah;

    double bayar;
    cout << "Dibayar (Rp)        : "; cin >> bayar;
    clearInput();

    double kembalian = bayar - p.jumlah;

    // Tampilkan kembalian atau error jika uang kurang
    if (kembalian < 0) {
        cout << ">> Uang tidak cukup. Pembayaran gagal.\n";
        return;
    }

    cout << "\n=== STRUK PEMBAYARAN ===\n";
    cout << "NIK Pasien          : " << p.nikPasien << endl;
    cout << "Nama Pasien         : " << namaPasien << endl;
    cout << "Tanggal             : " << p.tanggal << endl;
    cout << "Jenis Pembayaran    : " << p.jenisPembayaran << endl;
    cout << "Jumlah Tagihan      : Rp" << fixed << setprecision(2) << p.jumlah << endl;
    cout << "Dibayar             : Rp" << fixed << setprecision(2) << bayar << endl;
    cout << "Kembalian           : Rp" << fixed << setprecision(2) << kembalian << endl;

    // Simpan hanya jika uang cukup
    daftarPembayaran.push_back(p);
    simpanPembayaranKeFile();

    cout << ">> Pembayaran berhasil disimpan.\n";
}

void lihatPembayaran(const string &nik) {
    cout << "\n=== RIWAYAT PEMBAYARAN ===\n";
    bool ditemukan = false;
    for (const auto& p : daftarPembayaran) {
        if (p.nikPasien == nik) {
            p.tampilkanPembayaran();
            cout << "---------------------\n";
            ditemukan = true;
        }
    }
    if (!ditemukan)
        cout << ">> Tidak ada riwayat pembayaran untuk NIK ini.\n";
}

void menuPasien(Pasien* pasien) {
    int pilihan;
    do {
        cout << "\n=== MENU PASIEN (" << pasien->nama << ") ===\n";
        cout << "1. Lihat Profil\n";
        cout << "2. Tambah Rekam Medis Pribadi (Untuk Staff/Dokter)\n"; // Hanya admin/staff yang bisa tambah
        cout << "3. Lihat Rekam Medis\n";
        cout << "4. Tambah Rawat Inap (Untuk Staff/Dokter)\n";
        cout << "5. Lihat Rawat Inap\n";
        cout << "6. Lihat Pembayaran\n";
        cout << "7. Tambah Pembayaran (Untuk Kasir)\n";
        cout << "0. Logout\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        clearInput();
        switch (pilihan) {
            case 1: pasien->tampilkanData(); break;
            case 2: cout << ">> Fungsi ini hanya dapat diakses oleh Admin atau Dokter.\n"; break; // Disarankan oleh admin
            case 3: lihatRekamMedis(pasien->nik); break;
            case 4: cout << ">> Fungsi ini hanya dapat diakses oleh Admin atau Dokter.\n"; break; // Disarankan oleh admin
            case 5: lihatRawatInap(pasien->nik); break;
            case 6: lihatPembayaran(pasien->nik); break;
            case 7: cout << ">> Fungsi ini hanya dapat diakses oleh Admin atau Staff Kasir.\n"; break; // Disarankan oleh admin
            case 0: cout << ">> Logout berhasil.\n"; break;
            default: cout << ">> Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}

// --- Admin Features ---
bool loginAdmin() {
    string username, password;
    cout << "\n=== LOGIN ADMIN ===\n";
    cout << "Username: "; getline(cin, username);
    cout << "Password: "; getline(cin, password);
    return username == "admin" && password == "admin123";
}

void menuManajemenDokter(Klinik &klinik) {
    int pilihan;
    do {
        cout << "\n--- Manajemen Dokter Klinik " << klinik.namaKlinik << " ---\n";
        cout << "1. Lihat Dokter\n";
        cout << "2. Tambah Dokter\n";
        cout << "3. Ubah Dokter\n";
        cout << "4. Hapus Dokter\n";
        cout << "0. Kembali\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        clearInput();
        switch (pilihan) {
            case 1: klinik.tampilkanDokter(); break;
            case 2: klinik.tambahDokter(); break;
            case 3: klinik.ubahDokter(); break;
            case 4: klinik.hapusDokter(); break;
            case 0: break;
            default: cout << "Pilihan tidak valid.\n";
        }
        // Simpan perubahan dokter setiap kali ada operasi
        if (pilihan != 0) {
            if (klinik.namaKlinik == "Jantung") simpanDokterKeFile(klinik, "dokter_jantung.txt");
            else if (klinik.namaKlinik == "Kemoterapi") simpanDokterKeFile(klinik, "dokter_kemoterapi.txt");
            else if (klinik.namaKlinik == "Maternal-Perinatal") simpanDokterKeFile(klinik, "dokter_maternal.txt");
            else if (klinik.namaKlinik == "Hemodialisis") simpanDokterKeFile(klinik, "dokter_hemodialisis.txt");
        }
    } while (pilihan != 0);
}

void menuManajemenKlinikKhusus() {
    int pilihan;
    do {
        cout << "\n=== Menu Klinik Khusus dan Layanan Unggulan ===\n";
        cout << "1. Klinik Jantung\n";
        cout << "2. Klinik Kemoterapi\n";
        cout << "3. Klinik Maternal-Perinatal\n";
        cout << "4. Klinik Hemodialisis\n";
        cout << "0. Kembali\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        clearInput();
        switch (pilihan) {
            case 1: menuManajemenDokter(klinikJantung); break;
            case 2: menuManajemenDokter(klinikKemoterapi); break;
            case 3: menuManajemenDokter(klinikMaternalPerinatal); break;
            case 4: menuManajemenDokter(klinikHemodialisis); break;
            case 0: break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}

void tambahPenyakitPrioritas() {
    PenyakitPrioritas p;
    cout << "\n=== Tambah Data Penyakit Prioritas ===\n";
    cout << "NIK Pasien: "; getline(cin, p.pasienNik);
    // Cek apakah NIK terdaftar di daftar pasien
    bool pasienDitemukan = false;
    for(const auto& pasien : daftarPasien) {
        if(pasien.nik == p.pasienNik) {
            pasienDitemukan = true;
            break;
        }
    }
    if (!pasienDitemukan) {
        cout << ">> NIK Pasien tidak ditemukan di daftar pasien. Silakan registrasikan pasien terlebih dahulu.\n";
        return;
    }

    cout << "Nama Penyakit (Kanker, Stroke, Diabetes, KIA, TBC, dll): "; getline(cin, p.namaPenyakit);
    cout << "Tanggal Diagnosa (dd-mm-yyyy): "; getline(cin, p.tanggalDiagnosis);
    cout << "Status (Perawatan/Sembuh/Meninggal): "; getline(cin, p.status);
    daftarPenyakitPrioritas.push_back(p);
    simpanPenyakitPrioritasKeFile();
    cout << ">> Data penyakit prioritas berhasil ditambahkan.\n";
}

void lihatPenyakitPrioritas() {
    cout << "\n=== Data Penyakit Prioritas Nasional ===\n";
    if (daftarPenyakitPrioritas.empty()) {
        cout << "Belum ada data penyakit prioritas.\n";
        return;
    }
    for (const auto& p : daftarPenyakitPrioritas) {
        p.tampilkan();
        cout << "-------------------------\n";
    }
}

void editPenyakitPrioritas() {
    cout << "\n=== Edit Data Penyakit Prioritas ===\n";
    if (daftarPenyakitPrioritas.empty()) {
        cout << "Belum ada data penyakit prioritas untuk diedit.\n";
        return;
    }
    string nikCari;
    cout << "Masukkan NIK pasien yang datanya ingin diedit: ";
    getline(cin, nikCari);

    bool ditemukan = false;
    for (size_t i = 0; i < daftarPenyakitPrioritas.size(); ++i) {
        if (daftarPenyakitPrioritas[i].pasienNik == nikCari) {
            cout << "\nData ditemukan:\n";
            daftarPenyakitPrioritas[i].tampilkan();
            cout << "-------------------------\n";

            cout << "Masukkan nama penyakit baru (kosongkan jika tidak diubah): ";
            string namaBaru; getline(cin, namaBaru);
            if (!namaBaru.empty()) daftarPenyakitPrioritas[i].namaPenyakit = namaBaru;

            cout << "Masukkan tanggal diagnosis baru (kosongkan jika tidak diubah): ";
            string tanggalBaru; getline(cin, tanggalBaru);
            if (!tanggalBaru.empty()) daftarPenyakitPrioritas[i].tanggalDiagnosis = tanggalBaru;

            cout << "Masukkan status baru (kosongkan jika tidak diubah): ";
            string statusBaru; getline(cin, statusBaru);
            if (!statusBaru.empty()) daftarPenyakitPrioritas[i].status = statusBaru;

            simpanPenyakitPrioritasKeFile();
            cout << ">> Data penyakit prioritas berhasil diperbarui.\n";
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) {
        cout << ">> Data penyakit prioritas dengan NIK tersebut tidak ditemukan.\n";
    }
}

void hapusPenyakitPrioritas() {
    cout << "\n=== Hapus Data Penyakit Prioritas ===\n";
    if (daftarPenyakitPrioritas.empty()) {
        cout << "Belum ada data penyakit prioritas untuk dihapus.\n";
        return;
    }
    string nikHapus;
    cout << "Masukkan NIK pasien yang datanya ingin dihapus: ";
    getline(cin, nikHapus);

    size_t initialSize = daftarPenyakitPrioritas.size();
    daftarPenyakitPrioritas.erase(
        remove_if(daftarPenyakitPrioritas.begin(), daftarPenyakitPrioritas.end(),
                  [&](const PenyakitPrioritas& p) { return p.pasienNik == nikHapus; }),
        daftarPenyakitPrioritas.end());

    if (daftarPenyakitPrioritas.size() < initialSize) {
        simpanPenyakitPrioritasKeFile();
        cout << ">> Data penyakit prioritas berhasil dihapus.\n";
    } else {
        cout << ">> Data penyakit prioritas dengan NIK tersebut tidak ditemukan.\n";
    }
}

void menuPemantauanPenyakitPrioritas() {
    int pilihan;
    do {
        cout << "\n=== Menu Pemantauan Penyakit Prioritas Nasional ===\n";
        cout << "1. Tambah Data Penyakit Prioritas\n";
        cout << "2. Lihat Data Penyakit Prioritas\n";
        cout << "3. Edit Data Penyakit Prioritas\n";
        cout << "4. Hapus Data Penyakit Prioritas\n";
        cout << "0. Kembali\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        clearInput();
        switch (pilihan) {
            case 1: tambahPenyakitPrioritas(); break;
            case 2: lihatPenyakitPrioritas(); break;
            case 3: editPenyakitPrioritas(); break;
            case 4: hapusPenyakitPrioritas(); break;
            case 0: break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}

void laporanStatistik() {
    cout << "\n=== Laporan Statistik Pasien ===\n";

    if (daftarPasien.empty()) {
        cout << "Belum ada data pasien untuk statistik.\n";
        return;
    }

    // Rekap: jumlah pasien per jenis kelamin
    int countL = 0, countP = 0;
    for (const auto& p : daftarPasien) {
        if (p.jenisKelamin == "L" || p.jenisKelamin == "l") countL++;
        else if (p.jenisKelamin == "P" || p.jenisKelamin == "p") countP++;
    }
    cout << "Jumlah pasien per jenis kelamin:\n";
    cout << " - Laki-laki    : " << countL << endl;
    cout << " - Perempuan    : " << countP << endl;

    // Rekap umur pasien (kelompok umur)
    int umur0_18 = 0, umur19_40 = 0, umur41_60 = 0, umur61up = 0;
    for (const auto& p : daftarPasien) {
        if (p.umur <= 18) umur0_18++;
        else if (p.umur <= 40) umur19_40++;
        else if (p.umur <= 60) umur41_60++;
        else umur61up++;
    }
    cout << "Jumlah pasien per kelompok umur:\n";
    cout << " - 0-18 tahun       : " << umur0_18 << endl;
    cout << " - 19-40 tahun      : " << umur19_40 << endl;
    cout << " - 41-60 tahun      : " << umur41_60 << endl;
    cout << " - 61 tahun ke atas : " << umur61up << endl;

    // Rekap: jumlah pasien rawat inap
    cout << "Jumlah pasien rawat inap: " << daftarRawatInap.size() << endl;

    // Rekap: jumlah rekam medis
    cout << "Jumlah rekam medis: " << daftarRekamMedis.size() << endl;
}

void menuLaporanStatistik() {
    int pilihan;
    do {
        cout << "\n=== Menu Laporan dan Statistik Pasien ===\n";
        cout << "1. Lihat Laporan Statistik\n";
        cout << "0. Kembali\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        clearInput();
        switch (pilihan) {
            case 1: laporanStatistik(); break;
            case 0: break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}

void kelolaDataPasien() {
    int pilihan;
    do {
        cout << "\n=== Kelola Data Pasien (Admin) ===\n";
        cout << "1. Lihat Semua Pasien\n";
        cout << "2. Tambah Rekam Medis untuk Pasien (Oleh Dokter/Staff)\n";
        cout << "3. Lihat Rekam Medis Semua Pasien\n";
        cout << "4. Tambah Rawat Inap untuk Pasien (Oleh Staff)\n";
        cout << "5. Lihat Rawat Inap Semua Pasien\n";
        cout << "6. Tambah Pembayaran untuk Pasien (Oleh Kasir)\n";
        cout << "7. Lihat Semua Pembayaran\n";
        cout << "0. Kembali\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        clearInput();
        string nikTarget;
        switch (pilihan) {
            case 1:
                cout << "\n--- DATA SEMUA PASIEN ---\n";
                if (daftarPasien.empty()) {
                    cout << "Belum ada pasien terdaftar.\n";
                } else {
                    for (const auto& p : daftarPasien) {
                        p.tampilkanData();
                        cout << "-------------------\n";
                    }
                }
                break;
            case 2:
                cout << "Masukkan NIK Pasien untuk Rekam Medis: "; getline(cin, nikTarget);
                if (any_of(daftarPasien.begin(), daftarPasien.end(), [&](const Pasien& p){ return p.nik == nikTarget; })) {
                    tambahRekamMedis(nikTarget);
                } else {
                    cout << ">> NIK Pasien tidak ditemukan.\n";
                }
                break;
            case 3:
                cout << "\n--- SEMUA REKAM MEDIS ---\n";
                if (daftarRekamMedis.empty()) {
                    cout << "Belum ada rekam medis.\n";
                } else {
                    for (const auto& r : daftarRekamMedis) {
                        r.tampilkanRekam();
                        cout << "-------------------\n";
                    }
                }
                break;
            case 4:
                cout << "Masukkan NIK Pasien untuk Rawat Inap: "; getline(cin, nikTarget);
                 if (any_of(daftarPasien.begin(), daftarPasien.end(), [&](const Pasien& p){ return p.nik == nikTarget; })) {
                    tambahRawatInap(nikTarget);
                } else {
                    cout << ">> NIK Pasien tidak ditemukan.\n";
                }
                break;
            case 5:
                cout << "\n--- SEMUA RAWAT INAP ---\n";
                if (daftarRawatInap.empty()) {
                    cout << "Belum ada data rawat inap.\n";
                } else {
                    for (const auto& r : daftarRawatInap) {
                        r.tampilkanRawat();
                        cout << "-------------------\n";
                    }
                }
                break;
            case 6:
                cout << "Masukkan NIK Pasien untuk Pembayaran: "; getline(cin, nikTarget);
                if (any_of(daftarPasien.begin(), daftarPasien.end(), [&](const Pasien& p){ return p.nik == nikTarget; })) {
                    tambahPembayaran(nikTarget);
                } else {
                    cout << ">> NIK Pasien tidak ditemukan.\n";
                }
                break;
            case 7:
                cout << "\n--- SEMUA PEMBAYARAN ---\n";
                if (daftarPembayaran.empty()) {
                    cout << "Belum ada data pembayaran.\n";
                } else {
                    for (const auto& p : daftarPembayaran) {
                        p.tampilkanPembayaran();
                        cout << "-------------------\n";
                    }
                }
                break;
            case 0: break;
            default: cout << ">> Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}


void menuAdmin() {
    int pilihan;
    do {
        cout << "\n=== MENU ADMIN ===\n";
        cout << "1. Kelola Data Pasien & Rekam Medis (CRUD)\n";
        cout << "2. Manajemen Klinik Khusus & Layanan Unggulan\n";
        cout << "3. Pemantauan Penyakit Prioritas Nasional\n";
        cout << "4. Laporan dan Statistik Pasien\n";
        cout << "0. Logout\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        clearInput();
        switch (pilihan) {
            case 1: kelolaDataPasien(); break;
            case 2: menuManajemenKlinikKhusus(); break;
            case 3: menuPemantauanPenyakitPrioritas(); break;
            case 4: menuLaporanStatistik(); break;
            case 0: cout << ">> Logout admin berhasil.\n"; break;
            default: cout << ">> Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}

// --- Main Program ---
void muatSemuaData() {
    muatPasienDariFile();
    muatRekamMedisDariFile();
    muatRawatInapDariFile();
    muatPembayaranDariFile();
    muatPenyakitPrioritasDariFile();

    muatDokterDariFile(klinikJantung, "dokter_jantung.txt");
    muatDokterDariFile(klinikKemoterapi, "dokter_kemoterapi.txt");
    muatDokterDariFile(klinikMaternalPerinatal, "dokter_maternal.txt");
    muatDokterDariFile(klinikHemodialisis, "dokter_hemodialisis.txt");
}

void simpanSemuaData() {
    simpanPasienKeFile();
    simpanRekamMedisKeFile();
    simpanRawatInapKeFile();
    simpanPembayaranKeFile();
    simpanPenyakitPrioritasKeFile();

    simpanDokterKeFile(klinikJantung, "dokter_jantung.txt");
    simpanDokterKeFile(klinikKemoterapi, "dokter_kemoterapi.txt");
    simpanDokterKeFile(klinikMaternalPerinatal, "dokter_maternal.txt");
    simpanDokterKeFile(klinikHemodialisis, "dokter_hemodialisis.txt");
}

void tampilkanDashboard() {
    cout << "\n=== SISTEM INFORMASI RSUD KOTA YOGYAKARTA ===\n";
    cout << "1. Registrasi Pasien\n";
    cout << "2. Login Pasien\n";
    cout << "3. Login Admin\n";
    cout << "0. Keluar\n";
    cout << "Pilihan: ";
}

int main() {
    muatSemuaData(); // Muat semua data saat program dimulai

    int pilihan;
    do {
        tampilkanDashboard();
        cin >> pilihan;
        clearInput();
        switch (pilihan) {
            case 1: registrasiPasien(); break;
            case 2: {
                Pasien* p = loginPasien();
                if (p) menuPasien(p);
                break;
            }
            case 3:
                if (loginAdmin()) menuAdmin();
                else cout << ">> Login admin gagal.\n";
                break;
            case 0:
                cout << ">> Terima kasih telah menggunakan sistem ini.\n";
                break;
            default:
                cout << ">> Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    simpanSemuaData(); // Simpan semua data saat program berakhir
    return 0;
}
