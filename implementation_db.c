#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models.h"
#include "function_declarations.h"


void appendPatient(patient data){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="INSERT INTO Patients(age,room,doctor,name,gender,diagnosis) VALUES(?,?,?,?,?,?);";
		
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res, 1, data.age);
			sqlite3_bind_int(res, 2, data.room);
			sqlite3_bind_int(res, 3, data.doctor);
			sqlite3_bind_text(res, 4, data.name,-1, NULL);
			sqlite3_bind_text(res, 5, data.gender,-1, NULL);
			sqlite3_bind_text(res, 6, data.diagnosis,-1,NULL);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		sqlite3_finalize(res);
		sqlite3_close(db);
	}
}

int getLastPatientId(){
	return 12; //this line doesn't matter, because table will automotacilayy increment patient id
}

patient getPatientbyName(char* name){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="SELECT * FROM Patients WHERE name=?;";
		patient result;

		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_text(res, 1, name,-1, NULL);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		if(step == SQLITE_ROW){
			result.id = sqlite3_column_int(res,0);
			result.age = sqlite3_column_int(res,1);
			result.room = sqlite3_column_int(res,2);
			result.doctor = sqlite3_column_int(res,3);
			strcpy(result.name,sqlite3_column_text(res,4));
			strcpy(result.gender,sqlite3_column_text(res,5));
			strcpy(result.diagnosis,sqlite3_column_text(res,6));
		}
		sqlite3_finalize(res);
		sqlite3_close(db);
		return result;
	}


}

patient getPatientbyId(int id){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="SELECT * FROM Patients WHERE id=?;";
		patient result;

		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res, 1, id);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		if(step == SQLITE_ROW){
			result.id = sqlite3_column_int(res,0);
			result.age = sqlite3_column_int(res,1);
			result.room = sqlite3_column_int(res,2);
			result.doctor = sqlite3_column_int(res,3);
			strcpy(result.name,sqlite3_column_text(res,4));
			strcpy(result.gender,sqlite3_column_text(res,5));
			strcpy(result.diagnosis,sqlite3_column_text(res,6));
		}
		sqlite3_finalize(res);
		sqlite3_close(db);
		return result;
	}



}

void showAllPatients(){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="SELECT * FROM Patients INNER JOIN Doctors ON Doctors.id=Patients.doctor;";

		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc != SQLITE_OK){
			printf("Failed to execute statement");
		}
		while(sqlite3_step(res) == SQLITE_ROW){
			patient temp;
			temp.id = sqlite3_column_int(res,0);
			temp.age = sqlite3_column_int(res,1);
			temp.room = sqlite3_column_int(res,2);
			temp.doctor = sqlite3_column_int(res,3);
			strcpy(temp.name,sqlite3_column_text(res,4));
			strcpy(temp.gender,sqlite3_column_text(res,5));
			strcpy(temp.diagnosis,sqlite3_column_text(res,6));
			char doctorName[50];
		       	strcpy(doctorName,sqlite3_column_text(res,10));
			printf("ID: %d - Name: %s - Age: %d - Gender: %s - Diagnosis: %s - Doctor:%s  - Room: %d\n",temp.id, temp.name,temp.age,temp.gender,temp.diagnosis,doctorName,temp.room);
		}
		sqlite3_finalize(res);
		sqlite3_close(db);
	}


}

void showPatientsbyRoom(int roomno){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		int counter = 0;
		char *sql="SELECT * FROM Patients INNER JOIN Doctors ON Doctors.id=Patients.doctor WHERE room=?;";
		

		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res,1,roomno);
		}
		else{
			printf("Failed to execute statement");
		}
		printf("Patients in room %d:\n",roomno);
		while(sqlite3_step(res) == SQLITE_ROW){
			counter++;
			patient temp;
			temp.id = sqlite3_column_int(res,0);
			temp.age = sqlite3_column_int(res,1);
			temp.room = sqlite3_column_int(res,2);
			temp.doctor = sqlite3_column_int(res,3);
			strcpy(temp.name,sqlite3_column_text(res,4));
			strcpy(temp.gender,sqlite3_column_text(res,5));
			strcpy(temp.diagnosis,sqlite3_column_text(res,6));
			char doctorName[50];
		       	strcpy(doctorName,sqlite3_column_text(res,10));
			printf("ID: %d - Name: %s - Age: %d - Gender: %s - Diagnosis: %s - Doctor:%s  - Room: %d\n",temp.id, temp.name,temp.age,temp.gender,temp.diagnosis,doctorName,temp.room);
		}
		if(counter == 0){
			printf("There is currently no patient in room %d",roomno);
		}
		sqlite3_finalize(res);
		sqlite3_close(db);
	}


}

void showPatientsbyDoctor(int doctorid){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *resdoc;
	sqlite3_stmt *respat;
	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		int counter = 0;
		int counterdoc=0;
		char docName[50];
		char *sql="SELECT * FROM Doctors WHERE id=?;";

		rc = sqlite3_prepare_v2(db, sql, -1, &resdoc, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(resdoc,1,doctorid);
		}
		else{
			printf("Failed to execute statement");
		}

		while(sqlite3_step(resdoc) == SQLITE_ROW){
			strcpy(docName,sqlite3_column_text(resdoc,3));
			counterdoc++;
		}
		sqlite3_finalize(resdoc);

		if(counterdoc == 0){
			printf("There is no doctor with Id: %d",doctorid);
		}

		else{
			char *sqlPatients="SELECT * FROM Patients INNER JOIN Doctors ON Doctors.id=Patients.doctor WHERE Doctors.id=?;";

			rc = sqlite3_prepare_v2(db, sqlPatients, -1, &respat, 0);
			if(rc == SQLITE_OK){
				sqlite3_bind_int(respat,1,doctorid);
			}
			else{
				printf("Failed to execute statement");
			}
			printf("Patients under control of doctor %s:\n",docName);
			while(sqlite3_step(respat) == SQLITE_ROW){
				counter++;
				patient temp;
				temp.id = sqlite3_column_int(respat,0);
				temp.age = sqlite3_column_int(respat,1);
				temp.room = sqlite3_column_int(respat,2);
				temp.doctor = sqlite3_column_int(respat,3);
				strcpy(temp.name,sqlite3_column_text(respat,4));
				strcpy(temp.gender,sqlite3_column_text(respat,5));
				strcpy(temp.diagnosis,sqlite3_column_text(respat,6));
				printf("ID: %d - Name: %s - Age: %d - Gender: %s - Diagnosis: %s - Doctor:%s  - Room: %d\n",temp.id, temp.name,temp.age,temp.gender,temp.diagnosis,docName,temp.room);
			}
			if(counter == 0){
				printf("There is currently no patient under control of doctor %s\n",docName);
			}
		}

		sqlite3_finalize(respat);
		sqlite3_close(db);
	}
}

void modifyPatient(patient data){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="UPDATE Patients SET age=?,room=?,doctor=?,name=?,gender=?,diagnosis=? WHERE id=?";
		
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res, 1, data.age);
			sqlite3_bind_int(res, 2, data.room);
			sqlite3_bind_int(res, 3, data.doctor);
			sqlite3_bind_text(res, 4, data.name,-1, NULL);
			sqlite3_bind_text(res, 5, data.gender,-1, NULL);
			sqlite3_bind_text(res, 6, data.diagnosis,-1,NULL);
			sqlite3_bind_int(res, 7, data.id);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		sqlite3_finalize(res);
		sqlite3_close(db);
	}
}

void deletePatient(int id){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="DELETE FROM Patients WHERE id=?";
		
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res, 1, id);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		sqlite3_finalize(res);
		sqlite3_close(db);
	}
}


void appendDoctor(doctor data){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="INSERT INTO Doctors(age,department,name,gender) VALUES(?,?,?,?);";
		
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res, 1, data.age);
			sqlite3_bind_int(res, 2, data.department);
			sqlite3_bind_text(res, 3, data.name,-1, NULL);
			sqlite3_bind_text(res, 4, data.gender,-1, NULL);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		sqlite3_finalize(res);
		sqlite3_close(db);
	}
}

int getLastDoctorId(){
	return 12;
}

doctor getDoctorbyName(char* name){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="SELECT * FROM Doctors WHERE name=?;";
		doctor result;

		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_text(res, 1, name,-1, NULL);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		if(step == SQLITE_ROW){
			result.id = sqlite3_column_int(res,0);
			result.age = sqlite3_column_int(res,1);
			result.department = sqlite3_column_int(res,2);
			strcpy(result.name,sqlite3_column_text(res,3));
			strcpy(result.gender,sqlite3_column_text(res,4));
		}
		sqlite3_finalize(res);
		sqlite3_close(db);
		return result;
	}
}

doctor getDoctorbyId(int id){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="SELECT * FROM Doctors WHERE id=?;";
		doctor result;
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res, 1, id);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		if(step == SQLITE_ROW){
			
			result.id = sqlite3_column_int(res,0);
			result.age = sqlite3_column_int(res,1);
			result.department = sqlite3_column_int(res,2);
			strcpy(result.name,sqlite3_column_text(res,3));
			strcpy(result.gender,sqlite3_column_text(res,4));
			
		}
		sqlite3_finalize(res);
		sqlite3_close(db);
		return result;
	}
}

void showAllDoctors(){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="SELECT * FROM Doctors INNER JOIN Departments ON Departments.id=Doctors.department;";

		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc != SQLITE_OK){
			printf("Failed to execute statement");
		}
		while(sqlite3_step(res) == SQLITE_ROW){
			doctor temp;
			temp.id = sqlite3_column_int(res,0);
			temp.age = sqlite3_column_int(res,1);
			temp.department = sqlite3_column_int(res,2);
			strcpy(temp.name,sqlite3_column_text(res,3));
			strcpy(temp.gender,sqlite3_column_text(res,4));
			char departTitle[50];
		       	strcpy(departTitle,sqlite3_column_text(res,6));	
			printf("ID: %d - Name: %s - Gender: %s - Age: %d - Department: %s\n",temp.id, temp.name,temp.gender,temp.age,departTitle);
		}
		sqlite3_finalize(res);
		sqlite3_close(db);
	}
		
}

void showDoctorsbyDepartment(int departmentid){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *resdep;
	sqlite3_stmt *resdoc;
	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		int counter = 0;
		int counterdep=0;
		char depName[50];
		char *sql="SELECT * FROM Departments WHERE id=?;";

		rc = sqlite3_prepare_v2(db, sql, -1, &resdep, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(resdep,1,departmentid);
		}
		else{
			printf("Failed to execute statement");
		}

		while(sqlite3_step(resdep) == SQLITE_ROW){
			strcpy(depName,sqlite3_column_text(resdep,1));
			counterdep++;
		}
		sqlite3_finalize(resdep);

		if(counterdep == 0){
			printf("There is no department with Id: %d",departmentid);
		}

		else{
			char *sqlDoctors="SELECT * FROM Doctors INNER JOIN Departments ON Departments.id=Doctors.department WHERE Departments.id=?;";

			rc = sqlite3_prepare_v2(db, sqlDoctors, -1, &resdoc, 0);
			if(rc == SQLITE_OK){
				sqlite3_bind_int(resdoc,1,departmentid);
			}
			else{
				printf("Failed to execute statement");
			}
			printf("Doctors working in %s department:\n",depName);
			while(sqlite3_step(resdoc) == SQLITE_ROW){
				counter++;
				doctor temp;
				temp.id = sqlite3_column_int(resdoc,0);
				temp.age = sqlite3_column_int(resdoc,1);
				temp.department = sqlite3_column_int(resdoc,2);
				strcpy(temp.name,sqlite3_column_text(resdoc,3));
				strcpy(temp.gender,sqlite3_column_text(resdoc,4));
				printf("ID: %d - Name: %s - Age: %d - Gender: %s - Department: %s\n",temp.id, temp.name,temp.age,temp.gender,depName);
			}
			if(counter == 0){
				printf("There is currently no doctor working in %s department\n",depName);
			}
		}

		sqlite3_finalize(resdoc);
		sqlite3_close(db);
	}

}

void modifyDoctor(doctor data){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="UPDATE Doctors SET age=?,department=?,name=?,gender=? WHERE id=?";
		
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res, 1, data.age);
			sqlite3_bind_int(res, 2, data.department);
			sqlite3_bind_text(res, 3, data.name,-1, NULL);
			sqlite3_bind_text(res, 4, data.gender,-1, NULL);
			sqlite3_bind_int(res, 5, data.id);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		sqlite3_finalize(res);
		sqlite3_close(db);
	}

}

void deleteDoctor(int id){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="DELETE FROM Doctors WHERE id=?";
		
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res, 1, id);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		sqlite3_finalize(res);
		sqlite3_close(db);
	}

}



void appendRoom(room data){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="INSERT INTO Rooms(no,capacity) VALUES(?,?);";
		
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res, 1, data.no);
			sqlite3_bind_int(res, 2, data.capacity);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		sqlite3_finalize(res);
		sqlite3_close(db);
	}
}

int isRoomUnique(int no){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="SELECT * FROM Rooms WHERE no=?;";
		int roomCount = 0;
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res, 1, no);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		if(step == SQLITE_ROW){
			roomCount++;
		}
		sqlite3_finalize(res);
		sqlite3_close(db);
		if(roomCount > 0){
			return 0;
		}else{
			return 1;
		}
		
	}


}

room getRoombyNo(int no){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="SELECT * FROM Rooms WHERE no=?;";
		room result;
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res, 1, no);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		if(step == SQLITE_ROW){
			result.no = sqlite3_column_int(res,0);
			result.capacity = sqlite3_column_int(res,1);
		}
		sqlite3_finalize(res);
		sqlite3_close(db);
		return result;
		
	}

}

void showAllRooms(){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="SELECT * FROM Rooms;";

		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc != SQLITE_OK){
			printf("Failed to execute statement");
		}
		while(sqlite3_step(res) == SQLITE_ROW){
			room temp;
			temp.no = sqlite3_column_int(res,0);
			temp.capacity = sqlite3_column_int(res,1);
			char isAvailable[4];
			if(isRoomAvailable(temp.no) == 1){
				strcpy(isAvailable,"Yes");
			}else{
				strcpy(isAvailable,"No");
			}

			printf("Room %d - Capacity %d - Is room available: %s\n",temp.no, temp.capacity,isAvailable);
		}
		sqlite3_finalize(res);
		sqlite3_close(db);
	}
}
void showAvailableRooms(){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="SELECT * FROM Rooms;";

		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc != SQLITE_OK){
			printf("Failed to execute statement");
		}
		while(sqlite3_step(res) == SQLITE_ROW){
			room temp;
			temp.no = sqlite3_column_int(res,0);
			temp.capacity = sqlite3_column_int(res,1);
			
			if(isRoomAvailable(temp.no) == 1){
				printf("Room %d\n",temp.no);
			}

		}
		sqlite3_finalize(res);
		sqlite3_close(db);
	}
}

int isRoomAvailable(int no){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="SELECT COUNT(*) FROM Patients WHERE room=?;";
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res, 1, no);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		int patientsInRoom = 0;
		if(step == SQLITE_ROW){
			patientsInRoom = sqlite3_column_int(res,0);
		}
		room search = getRoombyNo(no);

		sqlite3_finalize(res);
		sqlite3_close(db);
		
		if(search.capacity > patientsInRoom && !isRoomUnique(no)){
			return 1;
		}else{
			return 0;
		}	
		
	}
}

void modifyRoom(room data){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="UPDATE Rooms SET capacity=? WHERE no=?";
		
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res, 1, data.capacity);
			sqlite3_bind_int(res, 2, data.no);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		sqlite3_finalize(res);
		sqlite3_close(db);
	}

}

void deleteRoom(int no){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="DELETE FROM Rooms WHERE no=?";
		
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res, 1, no);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		sqlite3_finalize(res);
		sqlite3_close(db);
	}
}





void appendDepartment(department data){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="INSERT INTO Departments(title) VALUES(?);";
		
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_text(res, 1, data.title,-1, NULL);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		sqlite3_finalize(res);
		sqlite3_close(db);
	}
}

int getLastDepartmentId(){
	return 12;
}

department getDepartmentbyTitle(char* title){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="SELECT * FROM Departments WHERE title=?;";
		department result;

		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_text(res, 1, title,-1, NULL);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		if(step == SQLITE_ROW){
			result.id = sqlite3_column_int(res,0);
			strcpy(result.title,sqlite3_column_text(res,1));
		}
		sqlite3_finalize(res);
		sqlite3_close(db);
		return result;
	}


}

department getDepartmentbyId(int id){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="SELECT * FROM Departments WHERE id=?;";
		department result;

		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res, 1, id);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		if(step == SQLITE_ROW){
			result.id = sqlite3_column_int(res,0);
			strcpy(result.title,sqlite3_column_text(res,1));
		}
		sqlite3_finalize(res);
		sqlite3_close(db);
		return result;
	}

}

void showAllDepartments(){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="SELECT * FROM Departments;";

		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc != SQLITE_OK){
			printf("Failed to execute statement");
		}
		while(sqlite3_step(res) == SQLITE_ROW){
			department temp;
			temp.id = sqlite3_column_int(res,0);
			strcpy(temp.title,sqlite3_column_text(res,1));
			printf("ID:%d - %s department\n",temp.id,temp.title);
		}
		sqlite3_finalize(res);
		sqlite3_close(db);
	}
}

void modifyDepartment(department data){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="UPDATE Departments SET title=? WHERE id=?";
		
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_text(res, 1, data.title, -1, NULL);
			sqlite3_bind_int(res, 2, data.id);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		sqlite3_finalize(res);
		sqlite3_close(db);
	}

}

void deleteDepartment(int id){
	sqlite3 *db;
	char *err_msg = 0;
	sqlite3_stmt *res;

	int rc = sqlite3_open("hospitium.db", &db);

	if (rc != SQLITE_OK) {
		printf("Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}else{
		
		char *zErrMsg;
		char *sql="DELETE FROM Departments WHERE id=?";
		
		rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
		if(rc == SQLITE_OK){
			sqlite3_bind_int(res, 1, id);
		}
		else{
			printf("Failed to execute statement");
		}
		int step = sqlite3_step(res);
		sqlite3_finalize(res);
		sqlite3_close(db);
	}
}
