#include <iostream>
#include <string>
#include <bitset>
#include <iostream>
#include <conio.h>

using namespace std;


bitset<48> key(0xEF66EF3CB3AA);
bitset<48> after_sbox;
bitset<32> after_sbox_normalize;
bitset<32> final;
bitset<48> plain_text(0x444412341234);
bitset<48> tab[8];

int s5[4][16] =
{
	2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
	14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
	4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
	11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
};

void s_box()
{
	int new_i = 0;
	int new_j = 0;

	for (int i = 0; i < 8; i++)
	{
		if (key[0] == 0 && key[5] == 0) new_i = 0;//sprawdzam pierwszy i ostatni bit do wyznaczenia kolumny S-boxa
		else if (key[0] == 1 && key[5] == 0) new_i = 1;
		else if (key[0] == 0 && key[5] == 1) new_i = 2;
		else if (key[0] == 1 && key[5] == 1) new_i = 3;

		bitset<48> test = key & bitset<48>(0x1E);
		test>>=1; //przesuniecie logiczne w prawo
		new_j = (int)test.to_ulong();

		key >>= 6;

		tab[i] = s5[new_i][new_j];
		auto show = (int)tab[i].to_ulong();
		auto show_bitset = bitset<4>(show);
		cout << "wiersz: " << new_i+1 << "  |  kolumna: " << new_j+1 << "  ->  wartosc: " << show_bitset << endl << endl;
	}

	for (int i = 7; i >=0; i--)
	{
		after_sbox <<= 4;
		after_sbox |= tab[i]; 
	}

	auto demo = (int)(after_sbox.to_ulong());
	after_sbox_normalize = bitset<32> (demo);

	cout << endl << endl << "Blok po S-boxie:    " << after_sbox_normalize << endl << endl;
}
void p_box()
{

	final[0] = after_sbox_normalize[15];
	final[1] = after_sbox_normalize[6];
	final[2] = after_sbox_normalize[19];
	final[3] = after_sbox_normalize[20];
	final[4] = after_sbox_normalize[28];
	final[5] = after_sbox_normalize[11];
	final[6] = after_sbox_normalize[27];
	final[7] = after_sbox_normalize[16];
	final[8] = after_sbox_normalize[0];
	final[9] = after_sbox_normalize[14];
	final[10] = after_sbox_normalize[22];
	final[11] = after_sbox_normalize[25];
	final[12] = after_sbox_normalize[4];
	final[13] = after_sbox_normalize[17];
	final[14] = after_sbox_normalize[30];
	final[15] = after_sbox_normalize[9];
	final[16] = after_sbox_normalize[1];
	final[17] = after_sbox_normalize[7];
	final[18] = after_sbox_normalize[23];
	final[19] = after_sbox_normalize[13];
	final[20] = after_sbox_normalize[31];
	final[21] = after_sbox_normalize[26];
	final[22] = after_sbox_normalize[2];
	final[23] = after_sbox_normalize[8];
	final[24] = after_sbox_normalize[18];
	final[25] = after_sbox_normalize[12];
	final[26] = after_sbox_normalize[29];
	final[27] = after_sbox_normalize[5];
	final[28] = after_sbox_normalize[21];
	final[29] = after_sbox_normalize[10];
	final[30] = after_sbox_normalize[3];
	final[31] = after_sbox_normalize[24];

	cout << "Blok po permutacji: " << final << endl;
}


int main()
{

	cout << "Podany blok tekstu jawnego: " << plain_text << endl << endl;
	cout << "Podany klucz:               " << key << endl << endl;
	key ^= plain_text;
	cout << "Blok sprzezony z kluczem:   " << key << endl << endl << endl << endl;

	s_box();
	p_box();

	cout << endl << endl << endl << "Nacisnij dowolny klawisz....";
	getchar();




}



