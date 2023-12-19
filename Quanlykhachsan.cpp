#include <iostream>

#include <fstream>

#include <string>

#include <sstream>

#include <vector>

#include <cctype>

#include<algorithm>

using namespace std;

class Room {
  private: int MaPhong;
  int SoGiuong;
  double Gia;
  bool isBooked;
  public: Room(): isBooked(false),
  MaPhong(0),
  SoGiuong(0),
  Gia(0.0) {}

  Room(int nMaPhong, int nSoGiuong, double nGia, bool nisBooked): MaPhong(nMaPhong),
  SoGiuong(nSoGiuong),
  Gia(nGia),
  isBooked(nisBooked) {}

  ~Room() {}

  void taoRoom() {
    cout << "Nhap ma phong: ";
    cin >> MaPhong;
    cout << "Nhap so giuong: ";
    cin >> SoGiuong;
    cout << "Nhap gia: ";
    cin >> Gia;

    ofstream file("rooms.txt", ios::app);
    if (file.is_open()) {
      file << MaPhong << " " << SoGiuong << " " << Gia << " " << isBooked << endl;
      file.close();
      cout << "Tao phong thanh cong!" << endl;
    } else {
      cout << "Loi khi tao phong moi!" << endl;
    }
  }

  int getMaPhong() const {
    return MaPhong;
  }

  int getSoGiuong() const {
    return SoGiuong;
  }

  double getGia() const {
    return Gia;
  }

  bool getTrangThai() const {
    return isBooked;
  }

  void setMaPhong(int value) {
    MaPhong = value;
  }

  void setSoGiuong(int value) {
    SoGiuong = value;
  }

  void setGia(double value) {
    Gia = value;
  }

  void setTrangThai(bool value) {
    isBooked = value;
  }
  vector < Room > DanhSachPhong;
  void layDuLieu() {
    ifstream file("rooms.txt");
    int i = 0;
    if (file.is_open()) {
      string line;
      while (getline(file, line)) {
        bool isWhitespace = true;
        for (size_t j = 0; j < line.length(); ++j) {
          if (!std::isspace(line[j])) {
            isWhitespace = false;
            break;
          }
        }

        if (isWhitespace) {
          continue;
        }

        istringstream iss(line);
        int storedMaPhong;
        int storedSoGiuong;
        double storedGia;
        bool storedisBooked;
        iss >> storedMaPhong >> storedSoGiuong >> storedGia >> storedisBooked;

        Room phong(storedMaPhong, storedSoGiuong, storedGia, storedisBooked);
        DanhSachPhong.push_back(phong);
      }
      file.close();
    }
  }

  void xuatPhong() {
    DanhSachPhong.clear();
    layDuLieu();
    for (int i = 0; i < DanhSachPhong.size(); i++) {
      cout << "Ma phong: " << DanhSachPhong[i].getMaPhong() << " | So giuong: " << DanhSachPhong[i].getSoGiuong() <<
        " | Gia: " << DanhSachPhong[i].getGia() << " | Trang thai: " << (DanhSachPhong[i].getTrangThai() ? "Da duoc dat" : "Chua duoc dat") << endl;
    }
  }
  void xuatPhongTrong() {
    DanhSachPhong.clear();
    layDuLieu();
    cout << "Danh sach cac phong chua duoc dat:\n";
    for (int i = 0; i < DanhSachPhong.size(); i++) {
      if (!DanhSachPhong[i].getTrangThai()) {
        cout << "Ma phong: " << DanhSachPhong[i].getMaPhong() << " | So giuong: " <<
          DanhSachPhong[i].getSoGiuong() << " | Gia: " << DanhSachPhong[i].getGia() << endl;
      }
    }
  }
};

void xoaPhongCu(Room & room) {
  ifstream inputFile("rooms.txt");
  ofstream outputFile("temprooms.txt");
  string deleteline;
  stringstream ss;
  ss << room.getMaPhong() << " " << room.getSoGiuong() << " " << room.getGia() << " " << room.getTrangThai();
  deleteline = ss.str();

  string line;
  while (getline(inputFile, line)) {
    if (line != deleteline) {
      outputFile << line << endl;
    }
  }

  inputFile.close();
  outputFile.close();
  remove("rooms.txt");
  rename("temprooms.txt", "rooms.txt");
}

void themPhongMoi(Room & room) {
  ofstream file("rooms.txt", ios::app);
  if (file.is_open()) {
    file << room.getMaPhong() << " " << room.getSoGiuong() << " " <<
      room.getGia() << " " << room.getTrangThai() << endl;
  }
  file.close();
}

void SuaPhong(Room & room, vector < Room > & DanhSachPhong) {
  int IdRoomToEdit;
  cout << "Danh sach phong: " << endl;
  DanhSachPhong.clear();
  room.layDuLieu();
  room.xuatPhong();
  cout << "Nhap ma phong can can sua: ";
  cin >> IdRoomToEdit;

  int nMaPhong;
  int nSoGiuong;
  double nGia;
  bool nisBooked;

  for (int i = 0; i < DanhSachPhong.size(); i++) {
    if (DanhSachPhong[i].getMaPhong() == IdRoomToEdit) {
      nMaPhong = DanhSachPhong[i].getMaPhong();
      cout << "Nhap so giuong moi: ";
      cin >> nSoGiuong;
      cout << "Nhap gia: ";
      cin >> nGia;
      DanhSachPhong[i].setSoGiuong(nSoGiuong);
      DanhSachPhong[i].setGia(nGia);
      xoaPhongCu(room);
      ofstream file("rooms.txt");
      if (file.is_open()) {
        for (int j = 0; j < DanhSachPhong.size(); j++) {
          file << DanhSachPhong[j].getMaPhong() << " " << DanhSachPhong[j].getSoGiuong() <<
            " " << DanhSachPhong[j].getGia() << " " << DanhSachPhong[j].getTrangThai() << endl;
        }
        file.close();
        cout << "Sua phong thanh cong!" << endl;
        return;
      } else {
        cout << "Loi khi mo file!" << endl;
      }
    }
  }
  cout << "Ma phong khong hop le.\n";
}

void XoaPhong(Room & room, vector < Room > & DanhSachPhong) {
  int IdRoomToDelete;
  cout << "Danh sach phong: " << endl;
  DanhSachPhong.clear();
  room.layDuLieu();
  room.xuatPhong();
  cout << "Nhap ma phong can can xoa: ";
  cin >> IdRoomToDelete;

  for (int i = 0; i < DanhSachPhong.size(); i++) {
    if (DanhSachPhong[i].getMaPhong() == IdRoomToDelete) {
    xoaPhongCu(DanhSachPhong[i]);
    DanhSachPhong.erase(DanhSachPhong.begin() + i);
    cout << "Xoa phong thanh cong!" << endl;
    return;
    }
  }
  cout << "Ma phong khong hop le.\n";
}

class User {
  private: string Ten;
  int CCCD;
  int Tuoi;
  string MatKhau;
  bool isAdmin;
  vector < Room > DanhSachPhongDat;
  bool isLogged;

  public: User(): isAdmin(false),
  isLogged(false) {}

  User(string nTen, int nCCCD, int nTuoi, string nMatKhau, bool nisAdmin): Ten(nTen),
  CCCD(nCCCD),
  Tuoi(nTuoi),
  MatKhau(nMatKhau),
  isAdmin(nisAdmin) {}

  ~User() {}

  bool getIsAdmin() const {
    return isAdmin;
  }
  bool getIsLogged() const {
    return isLogged;
  }

  void setIsAdmin(bool value) {
    isAdmin = value;
  }

  void registerUser() {
    cin.ignore();
    cout << "Ten: ";
    getline(cin, Ten);
    cout << "Nhap so CCCD: ";
    cin >> CCCD;
    cout << "Nhap tuoi: ";
    cin >> Tuoi;
    cin.ignore();
    cout << "Nhap mat khau: ";
    getline(cin, MatKhau);
    isAdmin = false;

    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
      file << Ten << "," << CCCD << " " << Tuoi << " " << MatKhau << " " << isAdmin << endl;
      file.close();
      cout << "Dang ky thanh cong!" << endl;
    } else {
      cout << "Loi khi mo file!" << endl;
    }
  }

  bool loginUser() {
    cout << "Nhap so CCCD: ";
    int inputCCCD;
    cin >> inputCCCD;
    cin.ignore();
    cout << "Nhap mat khau: ";
    string inputMatKhau;
    getline(cin, inputMatKhau);

    ifstream file("users.txt");
    if (file.is_open()) {
      string line;
      while (getline(file, line)) {
        istringstream iss(line);
        string storedTen;
        int storedCCCD;
        int storedTuoi;
        string storedMatKhau;
        bool storedIsAdmin;
        getline(iss, storedTen, ',');
        iss >> storedCCCD >> storedTuoi >> storedMatKhau >> storedIsAdmin;
        if (storedCCCD == inputCCCD && storedMatKhau == inputMatKhau) {
          Ten = storedTen;
          CCCD = storedCCCD;
          Tuoi = storedTuoi;
          MatKhau = storedMatKhau;
          isAdmin = storedIsAdmin;
          isLogged = true;
          file.close();
          return true;
        }
      }
      file.close();
    }

    return false;
  }

  void displayUserInfo() const {
    cout << "Ten: " << Ten << " | CCCD: " << CCCD << " | Tuoi: " << Tuoi << " | Vai tro: " << (isAdmin ? "admin" : "user") << endl;
  }

  void DatPhong(Room & room, User & user) {
    if (isLogged) {
      int IdRoomToBook;
      cout << "Danh sach phong con trong: " << endl;
      room.xuatPhongTrong();
      cout << "Nhap ma phong can dat: ";
      cin >> IdRoomToBook;
      for (int i = 0; i < room.DanhSachPhong.size(); i++) {
        if (room.DanhSachPhong[i].getMaPhong() == IdRoomToBook && !room.DanhSachPhong[i].getTrangThai()) {
          xoaPhongCu(room.DanhSachPhong[i]);
          room.DanhSachPhong[i].setTrangThai(true);
          themPhongMoi(room.DanhSachPhong[i]);
          room.DanhSachPhong.clear();
          room.layDuLieu();
          user.DanhSachPhongDat.push_back(room.DanhSachPhong[i]);
          ofstream file("datrooms.txt", ios::app);
          if (file.is_open()) {
            file << room.DanhSachPhong[i].getMaPhong() << " " << room.DanhSachPhong[i].getSoGiuong() << " " << room.DanhSachPhong[i].getGia() << " " << room.DanhSachPhong[i].getTrangThai() << endl;
            file.close();
            cout << "Dat phong thanh cong!\n";
            return;
          }
        }
      }
      cout << "Ma phong khong hop le hoac da duoc dat truoc do.\n";
    } else
      cout << "Vui long dang nhap de dat phong!";
  }

  void quanLyPhong(Room & room) {
    if (!getIsAdmin()) {
      cout << "Ban khong co quyen truy cap chuc nang nay.\n";
      return;
    }

    int choice;
    do {
      cout << "\nChon chuc nang quan ly phong:\n";
      cout << "1. Them phong moi\n";
      cout << "2. Hien thi danh sach phong\n";
      cout << "3. Sua thong tin phong\n";
      cout << "4. Xoa phong\n";
      cout << "5. Quay lai\n";
      cout << "Nhap lua chon: ";
      cin >> choice;

      switch (choice) {
      case 1:
        room.taoRoom();
        break;
      case 2:
        room.xuatPhong();
        break;
      case 3:
        cout << "Sua thong tin phong.\n";
        SuaPhong(room, room.DanhSachPhong);
        break;
      case 4:
        cout << "Xoa phong.\n";
        XoaPhong(room, room.DanhSachPhong);
        break;
      case 5:
        cout << "Quay lai.\n";
        break;
      default:
        cout << "Lua chon khong hop le. Vui long nhap lai.\n";
        break;
      }
    } while (choice != 5);
  }

  void xuatPhongDat() {
    DanhSachPhongDat.clear();
    layDuLieuPhongDat();
    for (int i = 0; i < DanhSachPhongDat.size(); i++) {
      cout << "Ma phong: " << DanhSachPhongDat[i].getMaPhong() << " | So giuong: " << DanhSachPhongDat[i].getSoGiuong() <<
        " | Gia: " << DanhSachPhongDat[i].getGia() << endl;
    }
  }
  void layDuLieuPhongDat() {
    ifstream file("datrooms.txt");
    int i = 0;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            // Ki?m tra n?u dòng ch? ch?a ký t? tr?ng ho?c là dòng tr?ng
            bool isWhitespace = true;
            for (size_t j = 0; j < line.length(); ++j) {
                if (!std::isspace(line[j])) {
                    isWhitespace = false;
                    break;
                }
            }

            if (isWhitespace || line.empty()) {
                continue;
            }

            istringstream iss(line);
            int storedMaPhong;
            int storedSoGiuong;
            double storedGia;
            bool storedisBooked;
            iss >> storedMaPhong >> storedSoGiuong >> storedGia >> storedisBooked;

            Room phong(storedMaPhong, storedSoGiuong, storedGia, storedisBooked);
            DanhSachPhongDat.push_back(phong);
        }
        i++;
    }
    if (!DanhSachPhongDat.empty()) {
        DanhSachPhongDat.erase(DanhSachPhongDat.begin());
    }
    file.close();
  }

  void xoaPhongDatCu(Room & room) {
    ifstream inputFile("datrooms.txt");
    ofstream outputFile("tempdatrooms.txt");
    string deleteline;
    stringstream ss;
    ss << room.getMaPhong() << " " << room.getSoGiuong() << " " << room.getGia() << " " << room.getTrangThai();
    deleteline = ss.str();
    string line;
    while (getline(inputFile, line)) {
      if (line != deleteline) {
        outputFile << line << endl;
      }
    }

    inputFile.close();
    outputFile.close();
    remove("datrooms.txt");
    rename("tempdatrooms.txt", "datrooms.txt");
  }

  void TraPhong(Room & room, User & user, vector<Room> & DanhSachPhong) {
    if (user.getIsLogged()) {
        if (user.DanhSachPhongDat.empty()) {
            cout << "Danh sach phong da dat trong. Khong co phong nao de tra.\n";
            return;
        }

        int IdRoomToReturn;
        cout << "Danh sach phong da dat: " << endl;
        user.xuatPhongDat();
        cout << "Nhap ma phong can tra: ";
        cin >> IdRoomToReturn;

        for (int i = 0; i < user.DanhSachPhongDat.size(); i++) {
            if (user.DanhSachPhongDat[i].getMaPhong() == IdRoomToReturn) {
                for (int j = 0; j < room.DanhSachPhong.size(); j++) {
                    if (room.DanhSachPhong[j].getMaPhong() == IdRoomToReturn) {
                        room.DanhSachPhong[j].setTrangThai(false);
                        xoaPhongCu(room.DanhSachPhong[j]);
                        themPhongMoi(room.DanhSachPhong[j]);
                        DanhSachPhong.clear();
                        room.layDuLieu();
                        break;
                    }
                }
                user.xoaPhongDatCu(user.DanhSachPhongDat[i]);
                cout << "Tra phong thanh cong!\n";
                return;
            }
        }
        cout << "Ma phong khong hop le hoac khong thuoc danh sach phong da dat.\n";
    } else {
        cout << "Vui long dang nhap de tra phong!\n";
    }
}

};

void runProgram(User &currentUser, Room &room) {
    int choice;
    
    do {
        cout << "\nChon chuc nang:\n";
        cout << "1. Dang ky\n";
        cout << "2. Dang nhap\n";
        cout << "3. Quan ly phong\n";
        cout << "4. Dat phong\n";
        cout << "5. Tra phong\n";
        cout << "6. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Dang ky: " << endl;
                currentUser.registerUser();
                break;
            case 2:
                if (currentUser.loginUser()) {
                    cout << "Dang nhap thanh cong!" << endl;
                    currentUser.displayUserInfo();
                } else {
                    cout << "Dang nhap that bai. Vui long kiem tra lai tai khoan hoac mat khau.\n";
                }
                break;
            case 3:
                currentUser.quanLyPhong(room);
                break;
            case 4:
                currentUser.DatPhong(room, currentUser);
                break;
            case 5:
                cout << "Tra phong" << endl;
                currentUser.TraPhong(room, currentUser, room.DanhSachPhong);
                break;
            case 6:
                cout << "Thoat.\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai.\n";
                break;
        }
    } while (choice != 6);
}

int main() {
	User currentUser;
    Room room;
    room.layDuLieu();
  	runProgram(currentUser,room);
  	return 0;
}
