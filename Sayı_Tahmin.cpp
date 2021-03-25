#include<iostream>
#include<ctime>
#include<locale>
#include<fstream>
#include<string>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Turkish");

	srand(time(NULL));

	int a, b, c, d, sayi, tahmin_sayi, binler, yuzler, onlar, birler, sayac = 0, top_arti = 0, top_eksi = 0;
	float puan;

	do {
		a = (rand() % 10);
	} while (a == 0);

	do {
		b = (rand() % 10);
	} while (a == b);

	do {
		c = (rand() % 10);
	} while (a == c || b == c);

	do {
		d = (rand() % 10);
	} while (a == d || b == d || c == d);

	sayi = (a * 1000) + (b * 100) + (c * 10) + d;

	cout << "-------------Random Sayı: " << sayi << "--------------" << endl;

	cout << "--------------------------------------------" << endl;
	cout << "------Sayı Bulmaca Oyununa Hoşgeldiniz------" << endl;
	cout << "--------------------------------------------" << endl;


	while (sayac < 10) {
		cout << endl;
		cout << "--------------------------------------------" << endl;
		cout << "----------" << (10 - sayac) << " deneme hakkınız kaldı----------" << endl;
		cout << "--------------------------------------------" << endl;

		int eksi = 0, arti = 0;
		bool kontrol = false;
		do {
			cout << "Dört basamaklı, basamakları birbirinden farklı bir sayı giriniz:";
			cin >> tahmin_sayi;

			int gecici_sayi = tahmin_sayi;

			birler = gecici_sayi % 10;
			gecici_sayi /= 10;
			onlar = gecici_sayi % 10;
			gecici_sayi /= 10;
			yuzler = gecici_sayi % 10;
			gecici_sayi /= 10;
			binler = gecici_sayi;

			if (tahmin_sayi < 1000 || tahmin_sayi>9999 && binler == yuzler || binler == onlar || binler == birler || yuzler == onlar || yuzler == birler || onlar == birler) {
				cout << "--------------------------------------------" << endl;
				cout << "Geçersiz tahmin. Lütfen 4 basamaklı, basamakları birbirinden farklı bir sayı giriniz." << endl;
				cout << "--------------------------------------------" << endl;

				kontrol = true;
			}
			else
				kontrol = false;
		} while (kontrol);


		if (binler == a || yuzler == a || onlar == a || birler == a)
			if (binler == a)
				arti += 1;
			else
				eksi -= 1;
		if (binler == b || yuzler == b || onlar == b || birler == b)
			if (yuzler == b)
				arti += 1;
			else
				eksi -= 1;

		if (binler == c || yuzler == c || onlar == c || birler == c)
			if (onlar == c)
				arti += 1;
			else
				eksi -= 1;

		if (binler == d || yuzler == d || onlar == d || birler == d)
			if (birler == d)
				arti += 1;
			else
				eksi -= 1;

		top_eksi -= eksi;
		top_arti += arti;

		cout << "--------------------------------------------" << endl;
		cout << "Girdiğiniz sayı:" << tahmin_sayi << "-->" << arti << " tanesi doğru yerde," << eksi << " tanesi yanlış yerde." << endl;
		cout << "--------------------------------------------" << endl;

		sayac += 1;

		if (tahmin_sayi == sayi)
		{
			puan = (10 * top_arti) + (5 * top_eksi) + ((1 / sayac) * 100) - ((top_arti * top_eksi) / (top_arti + top_eksi));
			cout << endl;
			cout << "--------------------------------------------" << endl;
			cout << "----------Tebrikler Sayıyı Bildiniz---------" << endl;
			cout << "--------------------------------------------" << endl;
			cout << "---------------" << puan << "---------------" << endl;
			break;
		}
	}
	if (sayac == 9) {
		cout << endl;
		cout << "--------------------------------------------" << endl;
		cout << "----Hakkınız bitti. Maalesef Kaybettiniz----" << endl;
		cout << "--------------------------------------------" << endl;
		return 0;
	}

	struct oyuncu {
		int sira_no;
		string ad;
		float puan;
	}siralama[10];

	for (int i = 0; i < 10; i++) {
		siralama[i].sira_no = i;
		siralama[i].ad = "-";
		siralama[i].puan = 0;
	}

	int son = 0;

	fstream dosya;

	dosya.open("puan_tablosu.txt", ios::in);

	if (dosya.is_open())
	{
		while (!dosya.eof())
		{
			dosya >> siralama[son].sira_no >> siralama[son].ad >> siralama[son].puan;
			son++;
		}
	}
	dosya.close();
	dosya.open("puan_tablosu.txt", ios::out);

	string ad;
	cout << "İsim giriniz:";
	cin >> ad;

	if (siralama[9].puan < puan) {

		for (int i = 0; i < 9; i++) {
			if (puan > siralama[i].puan) {
				for (int j = 8; j >= i; j--) {
					siralama[j + 1].sira_no = siralama[j].sira_no;
					siralama[j + 1].ad = siralama[j].ad;
					siralama[j + 1].puan = siralama[j].puan;
				}
				siralama[i].sira_no = i + 1;
				siralama[i].ad = ad;
				siralama[i].puan = puan;
				break;
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		dosya << (i + 1) << " " << siralama[i].ad << " " << siralama[i].puan << endl;
	}
	dosya.close();
	return 0;
}