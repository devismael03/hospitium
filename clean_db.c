#include <sqlite3.h>
#include <stdio.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
}


int main(){
	sqlite3 *db;
	int rc;
	char *zErrMsg;
	rc = sqlite3_open("hospitium.db", &db);

   	if( rc ) {
      		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      		return(0);
   	} else {
      		fprintf(stderr, "Opened database successfully\n");
  	}

	char* createTablePatients = "DROP TABLE IF EXISTS Patients; CREATE TABLE Patients("  \
      	"id INTEGER PRIMARY KEY NOT NULL," \
      	"age INT  NOT NULL," \
	"room INT  NOT NULL," \
	"doctor INT NOT NULL," \
	"name CHAR(50) NOT NULL," \
     	"gender CHAR(10) NOT NULL," \
      	"diagnosis CHAR(100) NOT NULL);";
	

   	rc = sqlite3_exec(db, createTablePatients, callback, 0, &zErrMsg);
	
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Patients table created successfully\n");
	}


	char* createTableDoctors = "DROP TABLE IF EXISTS Doctors; CREATE TABLE Doctors("  \
      	"id INTEGER PRIMARY KEY NOT NULL," \
      	"age INT  NOT NULL," \
	"department INT  NOT NULL," \
	"name CHAR(50) NOT NULL," \
     	"gender CHAR(10) NOT NULL);";
	

   	rc = sqlite3_exec(db, createTableDoctors, callback, 0, &zErrMsg);
	
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Doctors table created successfully\n");
	}

	char* createTableRooms = "DROP TABLE IF EXISTS Rooms; CREATE TABLE Rooms("  \
      	"no INT NOT NULL," \
     	"capacity INT NOT NULL);";
	

   	rc = sqlite3_exec(db, createTableRooms, callback, 0, &zErrMsg);
	
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Rooms table created successfully\n");
	}

	char* createTableDepartments = "DROP TABLE IF EXISTS Departments; CREATE TABLE Departments("  \
      	"id INTEGER PRIMARY KEY NOT NULL," \
     	"title CHAR(50) NOT NULL);";
	

   	rc = sqlite3_exec(db, createTableDepartments, callback, 0, &zErrMsg);
	
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Departments table created successfully\n");
	}
	
   	sqlite3_close(db);
	return 0;
}
