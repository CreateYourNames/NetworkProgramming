#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>		//<file> - ���������� ����� ������ file � ��������� ������ �������� Visual Studio
#include <CommCtrl.h>
#include <cstdio>
#include "resource.h"		//"file" - ���������� ����� ������ file ������� � �������� � ��������, � ����� � �������

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CheckMask(DWORD mask)
{
	//DWORD pattern = 1 << 32;
	for (int i = 0; i < 32; i++)
	{

	}
	return TRUE;
}
INT CountOnes(DWORD mask)
{
	INT zero_bits = 0;
	DWORD power;
	for (int i = 1; i; i <<= 1, zero_bits++)
	{
		if (mask & i)
		{
			power = i;
			break;
		}
	}

	return 32-zero_bits;
}

CHAR* ParseAddress(CHAR sz_address[], DWORD dw_address)
{
	sprintf
	(
		sz_address,
		"%s:\t\t\t%i.%i.%i.%i",
		FIRST_IPADDRESS( dw_address),
		SECOND_IPADDRESS(dw_address),
		THIRD_IPADDRESS(dw_address),
		FOURTH_IPADDRESS(dw_address)
	);
	return sz_address;
}
CHAR* ParseAddress(CHAR sz_address[], CONST CHAR sz_description[], DWORD dw_address)
{
	sprintf
	(
		sz_address,
		"%s%i.%i.%i.%i", sz_description,
		FIRST_IPADDRESS(dw_address),
		SECOND_IPADDRESS(dw_address),
		THIRD_IPADDRESS(dw_address),
		FOURTH_IPADDRESS(dw_address)
	);
	return sz_address;
}

// x - exit - cancel �� �����
//��������� ���� - ��� ����� ������� �������, �������� ���������� ��� ������� ����.
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//��� ����������� ��������� - ��� �������� �������� ������ 4 �����.
	//HWND - Handler to Window (���������� ����) - ��� �����, ������� �������������� ����.
	//����� ��������� � ���� ����� ��������� ������ ����� ��� ����������.
	//uMsg (Message) - ���������, ������ ������������ � ����.
	//wParam, lParam - ��������� ���������. ��� ��� ������� �� LOWORD � HIWORD.
	//LOWORD - ��� ������� �����.
	//HIWORD - ������� �����.
	//WORD (�����) - ��� ��� �����.
	int a = 2;
	{
		int a = 2;
	}
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hUpDown = GetDlgItem(hwnd, IDC_SPIN_PREFIX);
		//������� GetDlgItem() �������� HWND �������� ���������� �� ��� ID
		SendMessage(hUpDown, UDM_SETRANGE32, 0, 32);

		HWND hIPaddress = GetDlgItem(hwnd, IDC_IPADDRESS);
		SetFocus(hIPaddress);        //��� ��������  ���������, ���������� ������ �� ����� IP-������
	}
		break;
	case WM_COMMAND:
		//WM_ - Window Message
		switch (LOWORD(wParam))
		{
		case IDC_IPADDRESS:
		{
			CONST INT SIZE = 256;
			CHAR sz_info[SIZE]{};

			HWND hIPadress = GetDlgItem(hwnd, IDC_IPADDRESS);
			HWND hStaticInfo = GetDlgItem(hwnd, IDC_STATIC_INFO);
			HWND hEditPrefix = GetDlgItem(hwnd, IDC_EDIT_PREFIX);
			//EN_ - Edit Notification (�����������)
			if (HIWORD(wParam) == EN_CHANGE)
			{
				//BYTE = 8 bit; (Assembler)		CHAR (C++)
				//WORD = 2 Bytes (16 bit);		SHORT
				//DWORD (Double Word - ������� �����) 4 Bytes (32 bit)		INT
				//QWORD (Quad Word - ����������� �����) = 8 Bytes (64 bit)		LONG LONG
				//TBYTE (Ten Bytes - ������ ����) = 80 bit;
				//DQWORD (Double Quad Word - ������� ����������� �����) = 128 bit;
				DWORD dw_address;
				SendMessage(hIPadress, IPM_GETADDRESS, 0, (LPARAM) & dw_address);
				INT first = FIRST_IPADDRESS(dw_address);
				INT second = SECOND_IPADDRESS(dw_address);
				INT third = THIRD_IPADDRESS(dw_address);
				INT fourth = FOURTH_IPADDRESS(dw_address);

				sprintf_s(sz_info, SIZE, "Info:\nFirst: %i, Second: %i, Third: %i, Forth: %i", first, second, third, fourth);
				SendMessage(hStaticInfo, WM_SETTEXT, 0, (LPARAM)sz_info);

				/////////////////////////////////////////////////////////////////////////////////////////////

				if (first < 128)SendMessage(hEditPrefix, WM_SETTEXT, 0, (LPARAM)"8");
				else if (first < 192)SendMessage(hEditPrefix, WM_SETTEXT, 0, (LPARAM)"16");
				else if (first < 224)SendMessage(hEditPrefix, WM_SETTEXT, 0, (LPARAM)"24");
			}
		}
		break;
		case IDC_IPMASK:
		{
			//if (HIWORD(wParam) == EN_CHANGE)
			//{
			//	HWND hIPmask = GetDlgItem(hwnd, IDC_IPMASK);
			//	HWND hEditPrefix = GetDlgItem(hwnd, IDC_EDIT_PREFIX);
			//	DWORD dw_mask = 0;
			//	SendMessage(hIPmask, IPM_GETADDRESS, 0, (LPARAM)&dw_mask);
			//	INT prefix = CountOnes(dw_mask);
			//	CHAR sz_prefix[3] = {}; //sz_ - string zero (������, ��������������� ����)
			//	sprintf(sz_prefix, "%i", prefix);
			//	SendMessage(hEditPrefix, WM_SETTEXT, 0, (LPARAM)sz_prefix);
			//	//SendMessage(hIPmask, IPM_SETADDRESS, 0, dw_mask >> (32 - prefix) << (32 - prefix));
			//}
		}
			break;
		case IDC_EDIT_PREFIX:
		{
			HWND hIPAddress = GetDlgItem(hwnd, IDC_IPADDRESS);
			HWND hEditPrefix = GetDlgItem(hwnd, IDC_EDIT_PREFIX);
			HWND hIPmask = GetDlgItem(hwnd, IDC_IPMASK);
			HWND hStaticInfo = GetDlgItem(hwnd, IDC_STATIC_INFO);
			//DWORD dw_mask = UINT_MAX;
			DWORD dw_mask = ~0;
			if (HIWORD(wParam) == EN_CHANGE)
			{
				CONST INT SIZE_PREFIX = 8;
				CHAR sz_buffer[SIZE_PREFIX];
				SendMessage(hEditPrefix, WM_GETTEXT, SIZE_PREFIX, (LPARAM)sz_buffer);
				//MessageBox(hwnd, sz_buffer, "Prefix", MB_OK | MB_ICONINFORMATION);  �������� �����
				INT shift = atoi(sz_buffer);
				//      2 + 3;
				//dw_mask >>= (32 - shift);   //������� atoi() ����������� ASCII-������ � �������� ���� 'int'
				//dw_mask <<= (32 - shift);
				//SendMessage(hIPmask, IPM_SETADDRESS, 0, dw_mask);
				SendMessage(hIPmask, IPM_SETADDRESS, 0, dw_mask /*>> (32 - shift)*/ <<= (32 - shift)); //�������� ����� � ����� � ������� ������ ��������� � �������� ������� �����

				///////////////////				Info			///////////////////////////////
				CONST INT SIZE = 256;
				CHAR sz_info[SIZE]{};
				CHAR sz_network_address[SIZE]{};
				CHAR sz_broadcast_address[SIZE]{};
				CHAR sz_number_of_hosts[SIZE]{};
				CHAR sz_first_address[SIZE] = "��������� IP-�����:";
				CHAR sz_last_address[SIZE] = "��������� IP-�����:";

				DWORD dw_address = 0;
				SendMessage(hIPAddress, IPM_GETADDRESS, 0, (LPARAM)&dw_address);
				DWORD dw_network_address = dw_address & dw_mask;	
				ParseAddress(sz_network_address, "����� ����:\t\t\t", dw_network_address);
				
				DWORD dw_broadcast_address = ~dw_mask | dw_network_address;
				ParseAddress(sz_broadcast_address, "����������������� �����:\t", dw_broadcast_address);				

				DWORD dw_number_of_hosts = dw_broadcast_address - dw_network_address - 1;
				sprintf(sz_number_of_hosts, "���������� �����:\t\t%u", dw_number_of_hosts);

				ParseAddress(sz_first_address, "��������� IP-�����:\t\t", dw_network_address + 1);
				ParseAddress(sz_last_address, "��������� IP-�����:\t\t", dw_broadcast_address - 1);

					sprintf
					(
						sz_info, 
						"Info:\n%s\n%s\n%s\n%s\n%s",
						sz_network_address,
						sz_broadcast_address,
						sz_number_of_hosts,
						sz_first_address,
						sz_last_address
					);
				SendMessage(hStaticInfo, WM_SETTEXT, 0, (LPARAM)sz_info);
			}
		}
			break;
		case IDOK:MessageBox(hwnd, "���� ������ ������ ��", "Info", MB_OK | MB_ICONINFORMATION); break;
			//  MB_OK | MB_ICONINFORMATION - MB_OK or MB_ICONINFORMATION
			// || - ���������� 'OR'
			// | - ��������� 'OR'
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_NOTIFY:
	{
		HWND hIPmask = GetDlgItem(hwnd, IDC_IPMASK);
		HWND hEditPrefix = GetDlgItem(hwnd, IDC_EDIT_PREFIX);
		switch (wParam)
		{
				case IDC_IPMASK:
				{
					DWORD dw_mask = 0;
					SendMessage(hIPmask, IPM_GETADDRESS, 0, (LPARAM)&dw_mask);
					int i = 32;
					for (; dw_mask & 1 ^ 1; i--)dw_mask >>= 1;
					CHAR sz_prefix[5]{};
					sprintf(sz_prefix, "%i", i);
					SendMessage(hEditPrefix, WM_SETTEXT, 0, (LPARAM)sz_prefix);
				}
				break;
		}
		break;
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}