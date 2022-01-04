void appendPatient(patient data);
int getLastPatientId();
patient getPatientbyName(char* name);
patient getPatientbyId(int id);
void showAllPatients();
void showPatientsbyRoom(int roomno);
void showPatientsbyDoctor(int doctorid);
void modifyPatient(patient data);
void deletePatient(int id);


void appendDoctor(doctor data);
int getLastDoctorId();
doctor getDoctorbyName(char* name);
doctor getDoctorbyId(int id);
void showAllDoctors();
void showDoctorsbyDepartment(int departmentid);
void modifyDoctor(doctor data);
void deleteDoctor(int id);

void appendRoom(room data);
room getRoombyNo(int no);
void showAllRooms();
void showAvailableRooms();
int isRoomAvailable(int no);
int isRoomUnique(int no);
void modifyRoom(room data);
void deleteRoom(int no);	
	

void appendDepartment(department data);
int getLastDepartmentId();
department getDepartmentbyTitle(char* title);
department getDepartmentbyId(int id);
void showAllDepartments();
void modifyDepartment(department data);
void deleteDepartment(int id);
