#include <iostream>
#include <iomanip> 
#include <math.h> // library math
#include <vector> 
#include <cstdio> //operasi file
using namespace std;

float x, y, v, t, theta,dronex,droney;
float drone_x = 0.0;
float drone_y = 0.0;
vector<pair<float, float>> history;
vector<pair<float, float>> Undo;

void lokasi() {
    //history.push_back(make_pair(drone_x, drone_y)); //perintah undo
    //Undo.clear();
    cout << "Koordinat x : ";//input koordinat x dengan variabel drone_x
    cin >> x; 
    cout << "Koordinat y : ";//input koordinat y dengan variabel drone_y
    cin >> y; 
    //membuat output agar 2 angka dibelakang koma
    cout << fixed << setprecision(2) << "(" << x << "," << y << ")" << endl;
}

void gerak(double dx, double dy) {
    history.push_back(make_pair(drone_x, drone_y));//perintah undo
    Undo.clear();
    drone_x += dx; //menambahkan pergerakan posisi
    drone_y += dy;
    cout << "(" << fixed << setprecision(2) << drone_x << "," << drone_y << ")" << endl;
}

void gerak_2(float kecepatan, float waktu, float tetha) {
    history.push_back(make_pair(drone_x, drone_y));//perintah undo
    Undo.clear();
    // Menghitung perpindahan horizontal dan vertikal
    float deltaX = kecepatan * waktu * cos(tetha * M_PI / 180.0);
    float deltaY = kecepatan * waktu * sin(tetha * M_PI / 180.0);
    // Menggerakkan drone
    dronex += deltaX;
    droney += deltaY;

    cout << "Drone bergerak ke (" << fixed << setprecision(2) << dronex << ", " << droney << ")" << endl;
}
//fungsi untuk undo
void undo() {
    if (history.size() == 0) {
        cout << "Tidak dapat undo" << endl;
        return;
    }

    Undo.push_back(make_pair(drone_x, drone_y));

    pair<float, float> posisi_akhir = history.back();
    history.pop_back();

    drone_x = posisi_akhir.first;
    drone_y = posisi_akhir.second;
    cout << "undo berhasil" << endl;
    cout << " (" << fixed << setprecision(2) << drone_x << ", " << drone_y << ")" << endl;
}
//fungsi membuat file
void save() {
    FILE *fwriteSave;
    fopen_s(&fwriteSave, "./koordinat.txt", "w"); 

    if (fwriteSave == NULL) {
        cout << "tidak dapat membuat file" << endl;
    } else {
        fprintf(fwriteSave, "%.2f\n%.2f\n", drone_x, drone_y); 
        fclose(fwriteSave);
    }
}
//fungsi membaca file
void load() {
    FILE *freadSave;
    fopen_s(&freadSave, "./koordinat.txt", "r");

    if (freadSave == NULL) {
        cout << "Koordinat belum ada" << endl;

        FILE *fwriteSave;
        fopen_s(&fwriteSave, "./koordinat.txt", "w");
        if (fwriteSave == NULL) {
            cout << "file koordinat tidak bisa dibuat" << endl;
        } else {
            fprintf(fwriteSave, "%.2f\n%.2f\n", drone_x, drone_y);
            fclose(fwriteSave);
        }
    } else {
        fscanf(freadSave, "%f\n%f\n", &drone_x, &drone_y);
        fclose(freadSave);
    }
}

int main() {
    load();
    int pilih;
    while (true) {
        cout << "1. lokasi" << endl;
        cout << "2. gerak" << endl;
        cout << "3. Pergerakan drone dengan kecepatan dan waktu " << endl;
        cout << "4. undo" << endl;
        cout << "5. exit" << endl;
        cout << "Pilih menu: ";
        cin >> pilih;

        switch (pilih)
        
        {
        case 1:
            lokasi();
            save();
            break;
        case 2:
            double dx, dy;
            cout << "Masukkan perpindahan x : ";
            cin >> dx;
            cout << "Masukkan perpindahan y : ";
            cin >> dy;
            gerak(dx, dy);
            save();
            break; 
        case 3:
            cout << "v : ";
            cin >> v;
            cout << "t : ";
            cin >> t;
            cout << "tetha : ";
            cin >> theta;
            gerak_2(v, t, theta);
            save();
            break;
        case 4:
            undo();
            break; 
        case 5:
            return 0;
        default:
            break;
        }
    }

    return 0; 
}

