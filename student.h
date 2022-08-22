
 #ifndef STUDENT_H
 #define STUDENT_H
#define MAXSV 5000
#include"constant.h"
#include"globalvariable.h"
#include"display.h"
#include"validate.h"
#include<iostream>
#include<cstring>
#include<string>
struct student{
	char idStudent[16];
	char idClass[16];
	char fistName[21], lastName[11];
	int sex = 1; // 1 male, 2 female
	char phoneNUmber[13];
	int yearAdmission; // nam nhap hoc
	float mediumScore = 0;	
};
typedef struct student STUDENT;

struct ListSV
{			
	STUDENT nodes[MAXSV];
	int n=0;
};

bool isEmpty (ListSV pList)
{
  return (pList.n == 0 ? TRUE : FALSE);
};

bool isFull (ListSV pList)
{
  return (pList.n == MAXSV ? TRUE : FALSE);
};

int checkId(ListSV &ds, char s[]){
	for(int i=0; i<ds.n;i++)
		if(strcmp(ds.nodes[i].idStudent, s)==0)
			return 1;
	return 0;
}
// Them sinh vien vao vi tri thu i trong danh sach
int insertSV(ListSV &ds, int i, STUDENT sv){
	if(i<0||ds.n==MAXSV||i>ds.n)
		return 0;
	else
		for(int j=ds.n-1; j>=i;j++){
			ds.nodes[j+1]=ds.nodes[j];
		}
		ds.nodes[i]=sv;
		ds.n++;
		return 1;
}

void InsertListStudent(ListSV &ds, STUDENT sv){
	insertSV(ds, 0, sv);
}

//delete vị trí thứ i
void DeleteByOrdinal (struct ListSV &ds, int i)
{
  int j;
  int temp;
  if (i <= 0 || i > ds.n || isEmpty(ds))
  {
    return;
  }
  for (j = i; j < ds.n; j++)
  {
    ds.nodes[j-1] = ds.nodes[j];
  }
  ds.n--;
}

// Xoa sinh vien theo ma sinh vien
int deleteSV(ListSV &ds, char* s){
	if(ds.n==0)
		return 0;
	else{
		for(int i=1;i<ds.n;i++){
			if(strcmp(ds.nodes[i].idStudent, s)==0){
				for(int j=i; j<ds.n; j++){
					ds.nodes[j]=ds.nodes[j+1];
				}
				//delete ds.nodes[ds.n];
				int sizeDs = ds.n;
				DeleteByOrdinal(ds, sizeDs);
			}
		}
		ds.n--;
		return 1;
	}
}

// dung selection sort

void swapSV(STUDENT &a, STUDENT &b){
	STUDENT temp = a;
	a=b;
	b=temp;
}
void selectionSortSV(ListSV &ds){
	int min;
	STUDENT temp;
	for(int i=0;i<ds.n;i++){
		min = i;
		for(int j= i+1; j<ds.n; j++){
			if(strcmp(ds.nodes[j].lastName, ds.nodes[min].lastName)<0)
				min = j;
		}
		if(min!=i)
			swapSV(ds.nodes[i], ds.nodes[min]);
	}
}


int FindIndexStudent(ListSV ds, char* ma){
	if(ds.n==0) return -1;
	else{
		for(int i=0; i<ds.n; i++){
			if(strcmp(ds.nodes[i].idStudent, ma)==0)
				return i;
		}
	}
	return -1;
}

STUDENT BinarySearchStudent(ListSV ds, char* id){
	if(!isEmpty(ds))
		for(int i= 0; i<ds.n;i++){
			if(strcmp(ds.nodes[i].idStudent, id)==0)
				return ds.nodes[i];
		}
}

STUDENT FindStudent(ListSV ds, char* id)
{
	if(!isEmpty(ds))
		for(int i= 0; i<ds.n;i++){
			if(strcmp(ds.nodes[i].idStudent, id)==0)
				return ds.nodes[i];
		}
	else{
		STUDENT st;
		st.sex = -1;
		return st;
	}
}

STUDENT FindStudentByOrdinal(ListSV ds, int ordinal){
	if(!isEmpty(ds)&&ds.n-1>=ordinal) 
	{
		return ds.nodes[ordinal];
	}
}

bool isDelete(ListSV &ds, int ordinal){
	if(ds.n==0||ds.n<ordinal) return false;
	
	DeleteByOrdinal(ds, ordinal);
	
	for(int i=ordinal; i<ds.n - ordinal;i++){
		ds.nodes[i]=ds.nodes[i+1];
	}
	ds.n=ds.n-1;
	return true;
}

bool IsDeletedStudentWithId(ListSV &ds, STUDENT data){
	if(ds.n==0) return false;
	int index = FindIndexStudent(ds, data.idStudent);
	if(index > -1){
		return isDelete(ds, index);
	}else return false;
}

bool ClearListStudent(ListSV &ds){
	for(int i = 0; i<ds.n; i++)
		DeleteByOrdinal(ds, i);
		
	ds.n=0;
}

void OutputStudent(STUDENT sv, int locate){
	DeleteOldData(sizeof(keyDisplayStudent)/sizeof(string), locate);
	Gotoxy(xKeyDisplay[0]+1, Y_DISPLAY + 3 + locate); cout<<sv.idStudent;
	Gotoxy(xKeyDisplay[1]+1, Y_DISPLAY + 3 + locate); cout<<sv.fistName;
	Gotoxy(xKeyDisplay[2]+1, Y_DISPLAY + 3 + locate); cout<<sv.lastName;
	Gotoxy(xKeyDisplay[3]+1, Y_DISPLAY + 3 + locate);
	if(sv.sex == 1) cout<<"Nam";
	else cout<<"Nu";
	Gotoxy(xKeyDisplay[4]+1, Y_DISPLAY + 3 + locate); cout<<sv.phoneNUmber;
	Gotoxy(xKeyDisplay[5]+1, Y_DISPLAY + 3 + locate); cout<<sv.idClass;
}

void OutputListStudentWithIdClassPerPage(ListSV ds, int indexBegin){
	if(ds.n==0) return;
	int count = -1;
	for(int i = 0 ; i<ds.n; i++){
		count++;
		if(count == indexBegin){
			int j= -1;
			while(i<QUANTITY_PER_PAGE - 1&&i<ds.n){
				OutputStudent(ds.nodes[i], (++j)*2);
				i++;
			}
			break;
		}
	}
	
	Gotoxy(X_PAGE, Y_PAGE);
	cout<<"Trang "<< pageNowStudent<<"/"<<totalPageStudent;
}

void InputStudent(ListSV &ds, STUDENT sv, bool isEdited = false){
	ShowCur(true);
	int ordinal = 0;
	bool isMoveUp = false;
	bool isSave = false;
	bool idIsExist = false;
	
	string idStudent, firstName, lastName, idClass, phoneNumber;
	int yearAdmission = 0, sex = 0;
	
	if(isEdited){
		idStudent = sv.idStudent;
		firstName = sv.fistName;
		lastName = sv.lastName;
		idClass = sv.idClass;
		sex = sv.sex;
		phoneNumber = sv.phoneNUmber;
		
		Gotoxy(X_ADD  + 20 + 7, 0 * 3 + Y_ADD);
		cout << idStudent;
		Gotoxy(X_ADD + 17 + 7, 1 * 3 + Y_ADD);
		cout << firstName;
		Gotoxy(X_ADD + 18 + 7, 2 * 3 + Y_ADD);
		cout << lastName;		
		Gotoxy(X_ADD + 19 + 7, 3 * 3 + Y_ADD);
		cout << sex;
		Gotoxy(X_ADD + 20 + 7, 4 * 3 + Y_ADD);
		cout << phoneNumber;
		Gotoxy(X_ADD + 21 + 7, 5 * 3 + Y_ADD);
		cout << idClass;
	}
	while(true){
		switch(ordinal){
			case 0:
				if(isEdited) break;
				CheckMoveAndValidateID(idStudent, isMoveUp, ordinal, isSave, 20 + 7, 12);
				if(FindStudent(ds, (char *)idStudent.c_str()).sex != -1){
					idIsExist = false;
					break;
				}
				idIsExist = true;
				break;
			case 1:
				CheckMoveAndValidateNameSubject(firstName, isMoveUp, ordinal, isSave, 17+7, 20);
				break;
			case 2:
				CheckMoveAndValidateNameSubject(lastName, isMoveUp, ordinal, isSave, 18+7, 10);
				break;
			case 3:
				CheckMoveAndValidateNumber(sex, isMoveUp, ordinal, isSave, 19+7, 2);
				break;
			case 4:
				CheckMoveAndValidateID(phoneNumber, isMoveUp, ordinal, isSave, 20+7,11);
				break;
			case 5:
				CheckMoveAndValidateNumber(yearAdmission, isMoveUp, ordinal, isSave, 21 + 7, 2019);
				break;
		}
		if(isMoveUp){
			if(ordinal == 0);
				isMoveUp = false;
			ordinal--;
		}
		else{
			if(ordinal == 5)
				isMoveUp = true;
			ordinal++;
		}
		if(isSave){
			Gotoxy(X_NOTIFY, Y_NOTIFY);
			cout<< setw(50)<<setfill(' ')<<" ";
			trim(firstName);
			trim(lastName);
			StandarString(firstName);
			StandarString(lastName);
			
			if(sex==0 || firstName.empty()|| lastName.empty()|| phoneNumber.empty())
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout<<"Cac truong du lieu khong duoc de trong";
			} 
			else if(idIsExist){
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout<<"Ma sinh vien khong duoc trung";
			}
		}
		
		if (isMoveUp)
		{
			if (ordinal == 0)
				isMoveUp = false;
			ordinal--;
		}
		else
		{
			if (ordinal == 5)
				isMoveUp = true;
			ordinal++;
		}		
		if(isSave)
		{	
			Gotoxy(X_NOTIFY, Y_NOTIFY);			
			cout << setw(50) << setfill(' ') << " ";
			trim(firstName);
			trim(lastName);
			StandarString(firstName);
			StandarString(lastName);
		
			if(sex == 0 || firstName.empty() || lastName.empty() || yearAdmission == 0 || phoneNumber.empty() )
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Cac truong du lieu khong dc de trong";
			}
			else if(idIsExist)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Ma sinh vien khong duoc trung";
			}
			else
			{						
				strcpy(sv.idStudent, idStudent.c_str());				
				strcpy(sv.fistName, firstName.c_str());
				strcpy(sv.lastName, lastName.c_str());
				strcpy(sv.phoneNUmber, phoneNumber.c_str());
				sv.sex = sex;
				
				sv.yearAdmission = yearAdmission;
				StandardName(sv.lastName);
				StandardName(sv.fistName);
				
				if(isEdited)
				{
					STUDENT p = sv;
				}else
				{				
					InsertListStudent(ds, sv);				
				}
				totalPageStudent =((ds.n - 1) / QUANTITY_PER_PAGE) + 1;
				DeleteMenuAdd();
				return;		
			}
			isSave = false;
		}
		else
		{
			isSave = false;
		}
	}
	ShowCur(false);
}

void SetDefaultChooseStudent(STUDENT st, int ordinal)
{
	SetBGColor(GREEN);
	OutputStudent(st, (ordinal % QUANTITY_PER_PAGE) * 2);
	//SetBGColor(PURPLE);
}

void EffectiveMenuStudent(int ordinal, STUDENT stnew, STUDENT stold)
{
	int current = ordinal;
	SetDefaultChooseStudent(stnew, current);
	OutputStudent(stold, (currposPrecStudent % QUANTITY_PER_PAGE) * 2);
	currposPrecStudent = current;
}

void ChangePageChooseStudent(ListSV ds)
{
	clrscr();
	Display(keyDisplayStudent, sizeof(keyDisplayStudent) / sizeof(string));
	currposStudent = (pageNowStudent - 1) * QUANTITY_PER_PAGE;
	currposPrecStudent = (pageNowStudent - 1) * QUANTITY_PER_PAGE;
}

STUDENT ChooseStudent(ListSV ds)
{
	int keyboard_read = 0;
	ShowCur(false);
	pageNowStudent = 1;
	currposStudent = (pageNowStudent - 1) * QUANTITY_PER_PAGE;
	currposPrecStudent = (pageNowStudent - 1) * QUANTITY_PER_PAGE;
	totalPageStudent = ((ds.n-1) / QUANTITY_PER_PAGE) + 1;
	
	STUDENT newNodeStudent = FindStudentByOrdinal(ds, currposStudent);
	STUDENT oldNodeStudent;
	
	OutputListStudentWithIdClassPerPage(ds, (pageNowStudent - 1) * QUANTITY_PER_PAGE);
	SetDefaultChooseStudent(newNodeStudent, currposStudent);
	
	while(true)
	{
		keyboard_read = _getch();
		if (keyboard_read == 0)
			keyboard_read = _getch();
		switch (keyboard_read)
		{
			case KEY_UP:
				if(currposStudent % QUANTITY_PER_PAGE > 0)
				{
					currposStudent = currposStudent - 1;
					oldNodeStudent = newNodeStudent;
					//for(newNodeStudent = l.pHead; newNodeStudent->pNext != oldNodeStudent; newNodeStudent = newNodeStudent->pNext);
					for(int i= 0; i<ds.n;i++){
						newNodeStudent = ds.nodes[i];
						if(newNodeStudent.idStudent != oldNodeStudent.idStudent) break;
					}
					EffectiveMenuStudent(currposStudent, newNodeStudent, oldNodeStudent);				
				}
				break;
			case KEY_DOWN:
				if(currposStudent % QUANTITY_PER_PAGE < QUANTITY_PER_PAGE - 1 && ds.n >= currposStudent + 1)
				{
					currposStudent = currposStudent + 1;
					oldNodeStudent = newNodeStudent;
					newNodeStudent = ds.nodes[currposStudent];
					EffectiveMenuStudent(currposStudent, newNodeStudent, oldNodeStudent);
				}
				break;
			case PAGE_DOWN:
				if(pageNowStudent < totalPageStudent)
				{
					pageNowStudent++;
					ChangePageChooseStudent(ds);
					OutputListStudentWithIdClassPerPage(ds, (pageNowStudent - 1) * QUANTITY_PER_PAGE);
					
					newNodeStudent = FindStudentByOrdinal(ds, currposStudent);
					SetDefaultChooseStudent(newNodeStudent, currposStudent);				
				}
				break;
			case PAGE_UP:
				if(pageNowStudent > 1)
				{
					pageNowStudent--;
					ChangePageChooseStudent(ds);
					OutputListStudentWithIdClassPerPage(ds, (pageNowStudent - 1) * QUANTITY_PER_PAGE);
					newNodeStudent = FindStudentByOrdinal(ds, currposStudent);
					SetDefaultChooseStudent(newNodeStudent, currposStudent);
				}
				break;
			case ENTER:  //enter
				ShowCur(true);
				return newNodeStudent;
				break;
			case 27: 
				STUDENT st;
				st.sex = -1;
				return st; 
				break;	
		}
	}	
}

void ChangePageManageStudent(ListSV ds, string idClass)
{
	Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY SINH VIEN LOP: " + idClass ;
	OutputListStudentWithIdClassPerPage(ds, (pageNowStudent - 1) * QUANTITY_PER_PAGE);	
	Display(keyDisplayStudent, sizeof(keyDisplayStudent) / sizeof(string));
}

void MenuManagerStudent(ListSV &ds)
{
backMenu:
	clrscr();
	int key;
	string idClass;
	Gotoxy(X_TITLE, Y_TITLE);
	cout << "NHAP VAO MA LOP CAN QUAN LY: ";
	
	DisplayEdit(keyDisplayEditClass, sizeof(keyDisplayEditClass) / sizeof(string), 35);
	CheckMoveAndValdateIdClass(idClass, 28);
	Gotoxy(X_NOTIFY - 10, Y_NOTIFY);
	cout << "BAN CO MUON SUA LAI MA LOP";
	Gotoxy(X_NOTIFY - 10, Y_NOTIFY + 1);
	cout <<"ENTER: TIEO TUC - ESC: THOAT - AN PHIM BAT KI DE NHAP LAI";
 
	key = _getch();
	if(key == ESC)
		return;
	else if(key == ENTER)
	{
	
		ListSV temp;
		int n = 0;
//
//		for(int i=0; i<ds.n; i++){
//			if(strcmp(ds.nodes[i].idClass, (char*)idClass.c_str())==0){
//				temp.nodes[n] = ds.nodes[i];
//				n++;
//				temp.n = n;
//			}
//		}
//		pageNowStudent = 1;
//		totalPageStudent = ((n - 1) / QUANTITY_PER_PAGE) + 1;
//		OutputListStudentWithIdClassPerPage(temp, 0);
		
		Display(keyDisplayStudent, sizeof(keyDisplayStudent) / sizeof(string));
//		Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY SINH VIEN LOP: " + idClass ;
//		
//		while(true)
//		{
//			while(_kbhit())
//			{
//				key = _getch();
//				if (key == 0 || key == 224)
//				{
//					key = _getch();
//					if(key == KEY_F2)
//					{	
//						STUDENT st;
//						strcpy(st.idClass, idClass.c_str());
//						DisplayEdit(keyDisplayStudent, sizeof(keyDisplayStudent) / sizeof(string), 35);
//						InputStudent(ds, st, false);
//						if(strlen(st.idStudent) == 0) return;
//						
//						InsertListStudent(temp, st);
//						
//						n++;
//						totalPageStudent = ((n - 1) / QUANTITY_PER_PAGE) + 1;
//						clrscr();
//						ChangePageManageStudent(temp, idClass);
//						Gotoxy(X_NOTIFY, Y_NOTIFY);
//						cout << "Them thanh cong";
//					}
//					else if( key == KEY_F3)
//					{
//						STUDENT k = ChooseStudent(temp);
//						if(k.sex == -1) goto backMenu;
//						
//						Gotoxy(X_NOTIFY, Y_NOTIFY);
//						cout << "Ban co chac chan xoa? Enter dong y";
//						key = _getch();
//						if(key == ENTER)
//						{
//							string idSt = k.idStudent;
//							STUDENT p = FindStudent(ds, (char*)idSt.c_str());
//							IsDeletedStudentWithId(ds, p);
//							if(IsDeletedStudentWithId(temp, k))
//							{
//								n--;
//								totalPageStudent = ((n - 1) / QUANTITY_PER_PAGE) + 1;
//								if(n % QUANTITY_PER_PAGE == 0) pageNowStudent--;
//								clrscr();
//								ChangePageManageStudent(temp, idClass);
//								Gotoxy(X_NOTIFY, Y_NOTIFY);
//								cout << "Xoa thanh cong";
//							}
//						}else goto backMenu;
//					}
//					else if( key == KEY_F4)
//					{
//						STUDENT k = ChooseStudent(temp);
//						if(k.sex == -1) goto backMenu;
//						
//						DisplayEdit(keyDisplayStudent, sizeof(keyDisplayStudent) / sizeof(string), 35);
//						InputStudent(ds, k, true);
//						
//						clrscr();
//						ChangePageManageStudent(temp, idClass);
//						Gotoxy(X_NOTIFY, Y_NOTIFY);
//						cout << "Sua thanh cong";
//					}
//					else if(key == PAGE_DOWN && pageNowStudent < totalPageStudent)
//					{
//						pageNowStudent++;
//						clrscr();
//						ChangePageManageStudent(temp, idClass);
//					}
//					else if(key == PAGE_UP && pageNowStudent > 1)
//					{
//						pageNowStudent--;
//						clrscr();
//						ChangePageManageStudent(temp, idClass);
//					}
//				}
//				else if(key == ESC)
//				{
//					ClearListStudent(temp);
//					return;
//				}
//			}			
//		}
	}
	else
	 goto backMenu;	
}
 #endif
