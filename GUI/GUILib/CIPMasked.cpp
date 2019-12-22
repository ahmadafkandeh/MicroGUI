#include "CIPMasked.h"
#include "Cstring"
using std::strcpy;
using std::strlen;
char m_IPText[4][4]={{'1','9','2',0},{'1','6','8',0},{'0'},{'1'}};
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Constructor Of CIpMasked Class
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CIpMasked::CIpMasked()
{
	m_Size.width=(CHAR_W+2)*16+3;
	m_Size.height=CHAR_H;
	ConvertIpToText();
	m_state=3;
	m_ID=IPMASKED_ID;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//in this function we will get the key and change the IP.
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CIpMasked::KeyPress(char* key)
{
	char temp[4];
	strcpy(temp,m_IPText[m_state]);
	int number=ConvertTextToNumber(temp);
	if (*key>='0' & *key<='9')
	{
		if (strlen(temp)<3)
		{
			int num=number*10;
			if (num<250)
			{
				number=num+ConvertTextToNumber(key);
				strcpy(m_IPText[m_state],ConvertNumberToText(number));
			}
			else if(num==250)
			{
				num=ConvertTextToNumber(key);
				number=(num<=5?num+250:number);
				strcpy(m_IPText[m_state],ConvertNumberToText(number));
			}
		}
		else
		{
			m_state++;
			KeyPress(key);
		}
	}
	else
	{
		if (*key==KEYS_DELETE)
		{
			number=number/10;
			strcpy(m_IPText[m_state],ConvertNumberToText(number));
			if (number==0)m_state--;
		}
	}
	ConvertIpToText();
	if (m_state>3)m_state=3;
	if (m_state<0)m_state=0;
	if(m_Parent!=0)Draw();
	if (KeyPressHandler!=POINTERS_POINT_TO_ZERO)Event(KeyPressHandler,WM_KeyPress,(void*)key);
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//this func convert the text to numbers, so we can calculate the Ip
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
int CIpMasked::ConvertTextToNumber(char* text)
{
	int Num=0;
	while(*text)
	{
		if(*text>='0' && *text<='9')
			Num=(Num)*10+(*text-'0');
	}
	return Num;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//this function converts the numbers to text, so we can save it as text
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
char* CIpMasked::ConvertNumberToText(int number)
{
	char temp[4]={0,0,0,0};
	int count=1;
	if (number>=10) count=2;
	if (number>=100) count=3;
	int digit[3];
	digit[0]=(number/100)%10;
	digit[1]=(number/10)%10;
	digit[2]=number%10;
int z=3-count;;
	for(int i=0;i<count;i++)
		{
			temp[i]=digit[z++]+'0';
		}
	temp[3]=0;
	return temp;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//this func will converts the ip array to ipText, so we can show the IP into TextBox
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CIpMasked::ConvertIpToText()
{
	char text[15];
	int count=0;
	for (int z=0;z<4;z++)
	{
		for (int i=0;i<3;i++)
		{
			char temp=m_IPText[z][i];
			text[count++]=( temp==0 ? ' ' : temp );
		}
		if (z<3)text[count++]='.';
	}
	text[count]=0;
	SetText(text);
}
void CIpMasked::SetSize(coordinate _width,coordinate _height)
{/*it's empty becuase the IPTextBox's Size is Constant*/}
