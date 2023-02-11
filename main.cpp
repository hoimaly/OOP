#include <iostream>
#include "vector"
#include "string"

using namespace std;

bool invalid_date(int d, int m, int y) {
    int AD = 0;

    if (m == 4 || m == 6 || m == 9 || m == 11) { // nhung thang co 30 ngay
        if (d > 30) return true;
    } else if (m == 2) {
        while (AD < y) AD += 4; // nam Cong Nguyen tien dan ve nam hien tai, chu ky 4 nam
        if (y == AD) { // nam nhuan => thang 2 co 29 ngay
            if (d > 29) return true;
        } else { // nam ko nhuan => thang 2 co 28 ngay
            if (d > 28) return true;
        }
    } else { // nhung thang co 31 ngay
        if (d > 31) return true;
    }
    return false;
}

bool input_datein(string data);

bool input_namein(const string& data);

bool input_agein(const string& data);

class Manager {
protected:
    vector <string> arrayNames, arrayDates, arrayAges; // khai bao vector
    string data;
    bool flag = true;
    int option = 0, edit = 0, subtract = 0;
    unsigned long long position = 0;
public:
    Manager() {
        cout << "Truy cap vao cac tai khoan cong ti cua ban\n";
    }
    void input_names();
    void input_dates();
    void input_ages();
    void check_bindingData();
    void output_all();
    void reset();
private:
    static bool format_input(const string& format, const string& input_data);
    bool same_input(const string& format, const string& input_data);
};

void Manager::input_names() {
    cout << "Nhap ho ten (Alphabet) nhan vien vao mang (nhap '/' => End Type)\n=>";
    rename:
    while (cin >> data && data != "/") {
        if (!Manager::format_input("name", data)) {
            cout << "Khong duoc chua dau ' ' hoac ky tu khac Alphabet !\n";
            flag = false;
        } else {
            if (Manager::same_input("name", data)) {
                cout << "Ten nay ban da nhap roi !\n";
                flag = false;
            }
        }
        if (flag) arrayNames.push_back(data);
        for (const auto & arrayName : arrayNames) cout << "\"" << arrayName << "\" ";
        cout << "=>";
        if (!flag) {
            flag = true;
            goto rename;
        }
    }
}

void Manager::input_dates() {
    cout << "Nhap ngay thang nam sinh (dd/mm/yyyy) nhan vien vao mang (nhap '/' => End Type)\n=>";
    redate:
    while (cin >> data && data != "/") {
        if (!Manager::format_input("date", data)) {
            cout << "Khong duoc nhap khac format: dd/mm/yyyy !\n";
            flag = false;
        } else {
            if (Manager::same_input("date", data)) {
                cout << "Ngay sinh nay ban da nhap roi !\n";
                flag = false;
            }
        }
        if (flag) arrayDates.push_back(data);
        for (const auto & arrayDate : arrayDates) cout << "\"" << arrayDate << "\" ";
        cout << "=>";
        if (!flag) {
            flag = true;
            goto redate;
        }
    }
}

void Manager::input_ages() {
    cout << "Nhap tuoi [18 - 60) nhan vien vao mang (nhap '/' => End Type)\n=>";
    reage:
    while (cin >> data && data != "/") {
        if (!Manager::format_input("age", data)) {
            cout << "Khong duoc nhap ngoai do tuoi cho phep !\n";
            flag = false;
        } else {
            if (Manager::same_input("age", data)) {
                cout << "Tuoi nay ban da nhap roi !\n";
                flag = false;
            }
        }
        if (flag) arrayAges.push_back(data);
        for (const auto & arrayAge : arrayAges) cout << "\"" << arrayAge << "\" ";
        cout << "=>";
        if (!flag) {
            flag = true;
            goto reage;
        }
    }
}

bool Manager::format_input(const string& format, const string& input_data) {
    if (format == "name") {
        if (!input_namein(input_data)) return false;
    } else if (format == "date") {
        if (!input_datein(input_data)) return false;
    } else {
        if (!input_agein(input_data)) return false;
    }
    return true;
}

bool Manager::same_input(const string& format, const string& input_data) {
    if (format == "name") {
        for (auto& sameName : arrayNames) {
            if (input_data == sameName) return true;
        }
    } else if (format == "date") {
        for (auto& sameDate : arrayDates) {
            if (input_data == sameDate) return false;
        }
    } else {
        for (auto& sameAge : arrayAges) {
            if (input_data == sameAge) return false;
        }
    }
    return false;
}

void Manager::check_bindingData() {
    if (arrayNames.size() != arrayDates.size() || arrayNames.size() != arrayAges.size() || arrayDates.size() != arrayAges.size()) {
        cout << "Chua co su dong nhat du lieu giua cac thuoc tinh (Names: " << arrayNames.size() << " - Dates: " << arrayDates.size() << " - Ages: " << arrayAges.size() << ')';
        bindingData:
        cout << "\nLua chon thuoc tinh can chinh sua lai:";
        cout << "\n0 - Ho ten";
        cout << "\n1 - Ngay thang nam sinh";
        cout << "\n2 - Tuoi";
        cout << "\n=>";
        cin >> option;
        if (option >= 0 && option <= 2) {
            cout << "Ban muon xoa hay them du lieu vao thuoc tinh nay ? (0 - Xoa / !0 - Them) =>";
            cin >> edit;
            if (edit == 0) {
                if (option == 0) position = arrayNames.size();
                else if (option == 1) position = arrayDates.size();
                else position = arrayAges.size();
                subtract:
                cout << "Ban muon xoa bao nhieu phan tu bi thua ra? =>";
                cin >> subtract;
                if (subtract > position || subtract <= 0) {
                    cout << "Gia tri ban vua nhap khong dung so voi kich thuoc cua mang Ho ten. Moi ban nhap lai !\n";
                    goto subtract;
                } else {
                    if (option == 0) arrayNames.erase(arrayNames.end() - subtract, arrayNames.begin() + position);
                    else if (option == 1) arrayDates.erase(arrayDates.end() - subtract, arrayDates.begin() + position);
                    else arrayAges.erase(arrayAges.end() - subtract, arrayAges.begin() + position);
                }
            } else {
                if (option == 0) Manager::input_names();
                else if (option == 1) Manager::input_dates();
                else Manager::input_ages();
                Manager::check_bindingData();
            }
        } else {
            cout << "Gia tri ban vua nhap khong phu hop. Moi ban nhap lai !\n";
            goto bindingData;
        }
    }
}

void Manager::output_all() {
    cout << "Thong tin nhan vien cong ti cua ban, bao gom:";
    cout << "\n1/ Ho ten cac nhan vien: ";
    for (auto& names : arrayNames) cout << '\"' << names << "\" ";
    cout << "\n2/ Ngay thang nam sinh cac nhan vien: ";
    for (auto& dates : arrayDates) cout << '\"' << dates << "\" ";
    cout << "\n3/ Tuoi cac nhan vien: ";
    for (auto& ages : arrayAges) cout << '\"' << ages << "\" ";
    cout << endl;
}

void Manager::reset() {
    arrayNames.clear();
    arrayDates.clear();
    arrayAges.clear();
    flag = true;
    option = 0;
    edit = 0;
    subtract = 0;
    position = 0;
}

int main() {
    auto* DevCom = new Manager;
    int i = 0;

    do {
        DevCom->input_names();
        DevCom->input_dates();
        DevCom->input_ages();
        DevCom->check_bindingData(); // rang buoc du lieu
        DevCom->output_all(); // xuat thong tin dau ra

        cout << "Ban co muon kiem tra voi luong du lieu khac ? (0 - Khong / !0 - Co) =>";
        cin >> i;
        if (i == 0) {
            cout << "Cam on ban da su dung chuong trinh !\n";
            system("pause");
        } else {
            DevCom->reset(); // reset all
        }
    } while (i != 0);
    return 0;
}

bool input_datein(string data) {
    bool flag = true;
    int m, m_pos, num, day, month, year;
    int flat = 0, counter = 0, minimize_num = 0;

    data.push_back('/'); // => x/x/x/
    for (m = 0; m < data.length(); m++) {
        if (data[m] != '/') {
            minimize_num++;
        } else {
            flat++;
            if (flat == 1 || flat == 2) {
                if (minimize_num < 2) return false;
            } else {
                if (minimize_num < 4) return false;
            }
            minimize_num = 0;
        }
    }
    for (m = 0; m < data.length(); m++) { // 05/05/2003/
        if (data[m] != '/') {
            counter++;
            if (flag) { // lay gia tri m dau tien hoac sau dau '/'
                m_pos = m;
                flag = false;
            }
            if (data[m] < '0' || data[m] > '9') return false; // vd: 5-/05/2003
        } else {
            num = stoi(data.substr(m_pos, counter)); // quy doi sang dang so nguyen
            if (m == 2) {
                if (num > 0 && num < 31) day = num;
            } else {
                if (num > 0 && num < 12) month = num;
                else year = num;
            }
            counter = 0;
            flag = true;
        }
    }
    if (invalid_date(day, month, year)) return false;
    return true;
}

bool input_namein(const string& data) {
    for (char i : data) {
        if (!isalpha(i) || i == ' ') return false;
    }
    return true;
}

bool input_agein(const string& data) {
    if (data.length() > 2) {
        return false;
    } else {
        for (char i : data) {
            if (i < '0' || i > '9') return false;
        }
        int valid_age = stoi(data);
        if (valid_age < 18 || valid_age >= 60) return false;
    }
    return true;
}