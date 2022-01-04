#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "models.h"
#include "function_declarations.h"
int main(){
	department depart1;
	depart1.id = getLastDepartmentId() + 1;
	strcpy(depart1.title,"Pharmacy");
	appendDepartment(depart1);

	department depart2;
	depart2.id = getLastDepartmentId() + 1;
	strcpy(depart2.title,"Oncology");
	appendDepartment(depart2);

	department depart3;
	depart3.id = getLastDepartmentId() + 1;
	strcpy(depart3.title,"Cardiology");
	appendDepartment(depart3);

	room room1;
	room1.no = 122;
	room1.capacity =2;
	if(isRoomUnique(122)){
		appendRoom(room1);
	}

	
	room room2;
	room2.no = 123;
	room2.capacity=4;
	if(isRoomUnique(123)){
		appendRoom(room2);
	}

	room room3;
	room3.no =345;
	room3.capacity =1;
	if(isRoomUnique(345)){
		appendRoom(room3);
	}

	doctor doc1;
	doc1.id = getLastDoctorId() + 1;
	doc1.age = 25;
	doc1.department = 1;
	strcpy(doc1.name, "Joe Doe");
	strcpy(doc1.gender,"Male");
	appendDoctor(doc1);
	
	doctor doc2;
	doc2.id = getLastDoctorId() + 1;
	doc2.age = 46;
	doc2.department = 2;
	strcpy(doc2.name, "Kate");
	strcpy(doc2.gender,"Female");
	appendDoctor(doc2);

	doctor doc3;
	doc3.id = getLastDoctorId() + 1;
	doc3.age = 34;
	doc3.department = 3;
	strcpy(doc3.name, "Trump");
	strcpy(doc3.gender,"Male");
	appendDoctor(doc3);

	doctor doc4;
	doc4.id = getLastDoctorId() + 1;
	doc4.age = 25;
	doc4.department = 2;
	strcpy(doc4.name, "Mary");
	strcpy(doc4.gender,"Female");
	appendDoctor(doc4);



	patient pat1;
	pat1.id = getLastPatientId()+1;
	pat1.age = 25;
	pat1.doctor = 4;
	pat1.room = 122;
	strcpy(pat1.name, "Mary");
	strcpy(pat1.gender,"Female");
	strcpy(pat1.diagnosis,"Blabla");
	appendPatient(pat1);

	patient pat2;
	pat2.id = getLastPatientId()+1;
	pat2.age = 26;
	pat2.doctor = 4;
	pat2.room = 123;
	strcpy(pat2.name, "Harry");
	strcpy(pat2.gender,"Male");
	strcpy(pat2.diagnosis,"Blabla");
	appendPatient(pat2);
	

	patient pat3;
	pat3.id = getLastPatientId() + 1;
	pat3.age = 25;
	pat3.doctor = 2;
	pat3.room = 122;
	strcpy(pat3.name, "Kate");
	strcpy(pat3.gender,"Female");
	strcpy(pat3.diagnosis,"blabla");
	appendPatient(pat3);

	patient pat4;
	pat4.id = getLastPatientId() +1;
	pat4.age = 25;
	pat4.doctor = 1;
	pat4.room = 345;
	strcpy(pat4.name, "Mike");
	strcpy(pat4.gender,"Male");
	strcpy(pat4.diagnosis,"Blabla");
	appendPatient(pat4);


	return 0;
}
