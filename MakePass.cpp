#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


static inline bool is_base64(unsigned char c)
{
	return (isalnum(c) || (c == '+') || (c == '/'));
}

string base64_encode(const char *bytes_to_encode, unsigned int in_len)
{
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];  // store 3 byte of bytes_to_encode
	unsigned char char_array_4[4];  // store encoded character to 4 bytes

	while (in_len--)
	{
		char_array_3[i++] = *(bytes_to_encode++);  // get three bytes (24 bits)
		if (i == 3)
		{
			// eg. we have 3 bytes as ( 0100 1101, 0110 0001, 0110 1110) --> (010011, 010110, 000101, 101110)
			char_array_4[0] = (char_array_3[0] & 0xfc) >>
			                  2; // get first 6 bits of first byte,
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >>
			                  4); // get last 2 bits of first byte and first 4 bit of second byte
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >>
			                  6); // get last 4 bits of second byte and first 2 bits of third byte
			char_array_4[3] = char_array_3[2] & 0x3f; // get last 6 bits of third byte

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >>
		                  4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >>
		                  6);

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}

	return ret;

}

string base64_decode(const std::string& encoded_string)
{
	size_t in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (encoded_string[in_] != '=')
	       && is_base64(encoded_string[in_]))
	{
		char_array_4[i++] = encoded_string[in_];
		in_++;
		if (i == 4)
		{
			for (i = 0; i < 4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]) & 0xff;

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >>
			                  2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i)
	{
		for (j = 0; j < i; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]) & 0xff;

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >>
		                  2);

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}

int main()
{
	ll a, b;
	cin >> a >> b;
	string s;
	cin >> s;
	int num = 1;
	for (int i = 0; i < 128; i++)
	{
		num = num * a;
		num %= 10000000007;
		num *= a;
		num*(a + b);
		num %= 10000000007;
		num *= (a + b);
		num %= 10000000007;
		num += (a * b);
		num %= 10000000007;
		num += a;
		num *= a;
		num %= 10000000007;
		num -= b * b;
		num %= 10000000007;
		num = abs(num);
	}
	for (int i = 0; i < s.size(); i++)
	{
		num *= (ll)(s[i]);
		num %= 10000000007;
		num += (ll)(s[i]);
		num %= 10000000007;
		num = abs(num);
	}
	char PassT[1024];
	sprintf(PassT, "%d%d", num %= 10000000007);
//	char S_PASS[1024];
	string S_PASS=base64_encode(PassT,strlen(PassT));
	for(int i=5;i<S_PASS.size();i++)
	{
		S_PASS[i]=PassT[i-5];
	}
	for(int i=0;i<10;i++)
	{
		cout<<S_PASS[i];
	}
	return 0;
}
