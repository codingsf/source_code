#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream> 
//using namespace std;
class DateOper
{
public:
	DateOper(int year = 1900, int mouth = 1, int day = 1);//���캯�� 
	bool operator == (const DateOper& d);//���ڱȽϷ��ŵ����� 
	bool operator <(const DateOper& d);
	bool operator <=(const DateOper& d);
	bool operator >(const DateOper& d);
	bool operator >=(const DateOper& d);
	bool operator !=(const DateOper& d);
	DateOper operator+ (int day);//����������� 
	DateOper operator+= (int day);
	DateOper operator- (int day);
	DateOper operator-= (int day);
	DateOper operator++();
	DateOper operator++(int);
	DateOper operator--();
	DateOper operator--(int);
	void display();//��ӡ������Ұ��������cout 
	int operator-(const DateOper& d);//
	int GetYear() { return _year; }
	int GetMonth() { return _mouth;}
	int GetDay() { return _day; }
private:
	bool IsLeapYear(int year);//�ж������˽���ຯ�� 
	int GetMonthDay(int year, int month);//��ȡ�·ݵ�˽���ຯ�� 
	int _year;
	int _mouth;
	int _day;
};