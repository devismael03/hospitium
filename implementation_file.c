#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models.h"
#include "function_declarations.h"

void appendPatient(patient data){
	FILE* fp = fopen("patients.bin","ab");
	if(fp == NULL){
		puts("Error in file creation");
	}else{
		fwrite(&data,sizeof(patient),1,fp);
		fclose(fp);
	}
}

int getLastPatientId(){
	FILE* fp = fopen("patients.bin","rb");
	if(fp == NULL){
		return 0;
	}else{
		int lastId = 0;
		patient temp;
		while(fread(&temp, sizeof(patient),1,fp) !=0){
			lastId=temp.id;
		}
		fclose(fp);
		return lastId;
	}


}

patient getPatientbyName(char* name){
	FILE* fp = fopen("patients.bin","rb");
	if(fp == NULL){
		puts("File doesn't exist");
	}else{
		patient temp;
		while(fread(&temp, sizeof(patient),1,fp) !=0){
			if(strcmp(temp.name, name) == 0){
				fclose(fp);
				return temp;
			}
		}
		fclose(fp);
	}

}

patient getPatientbyId(int id){
	FILE* fp = fopen("patients.bin","rb");
	if(fp == NULL){
		puts("File doesn't exist");
	}else{
		patient temp;
		while(fread(&temp, sizeof(patient),1,fp) !=0){
			if(temp.id == id){
				fclose(fp);
				return temp;
			}
		}
		fclose(fp);
	}
}

void showAllPatients(){
	FILE* fp = fopen("patients.bin","rb");
	if(fp == NULL){
		puts("File doesn't exist");
	
	}else{
		patient temp;
		printf("\n");
		while(fread(&temp, sizeof(patient), 1, fp) != 0){
			doctor docofPatient = getDoctorbyId(temp.doctor);
			printf("ID: %d - Name: %s - Age: %d - Gender: %s - Diagnosis: %s - Doctor: %s - Room: %d\n",temp.id, temp.name,temp.age,temp.gender,temp.diagnosis,docofPatient.name,temp.room);

		}
		fclose(fp);
	}
}

void showPatientsbyRoom(int roomno){
	FILE* fp = fopen("patients.bin","rb");
	if(fp == NULL){
		puts("File doesn't exist");
	
	}else{
		patient temp;
		int counter=0;
		printf("Patients in room %d:\n",roomno);
		while(fread(&temp, sizeof(patient), 1, fp) != 0){
			if(temp.room == roomno){
				counter++;
				doctor doc = getDoctorbyId(temp.doctor);
				printf("ID: %d - Name: %s - Age: %d - Gender: %s - Diagnosis: %s - Doctor: %s - Room: %d\n",temp.id,temp.name,temp.age,temp.gender,temp.diagnosis,doc.name,temp.room);
			}
		}
		if(counter == 0){
			printf("There is currently no patient in room %d\n",roomno);
		}
		fclose(fp);
	}
}

void showPatientsbyDoctor(int doctorid){
	FILE* fp = fopen("patients.bin","rb");
	if(fp == NULL){
		puts("File doesn't exist");
	
	}else{
		FILE* fpdoctors = fopen("doctors.bin","rb");
		if(fpdoctors == NULL){
			puts("File doesn't exist");
		}
		else{
			doctor tempdoctor;
			int doctorcounter = 0;
			while(fread(&tempdoctor,sizeof(doctor), 1, fpdoctors) != 0){
				if(tempdoctor.id == doctorid){
					doctorcounter++;
					break;
				}
			}
			if(doctorcounter == 0){
				printf("There is no doctor with ID:%d",doctorid);
			}else{
				patient temp;
				int counter=0;
				printf("Patients under control of doctor %s:\n",tempdoctor.name);
				while(fread(&temp, sizeof(patient), 1, fp) != 0){
					if(temp.doctor == doctorid){
						counter++;
				               	printf("ID: %d - Name: %s - Age: %d - Gender: %s - Diagnosis: %s - Room: %d\n",temp.id,temp.name,temp.age,temp.gender,temp.diagnosis,temp.room);
					}
				}
				if(counter == 0){
					printf("There is currently no patient under control of doctor %s\n",tempdoctor.name);
				}
			}


			fclose(fpdoctors);		
		}
		fclose(fp);
	}
}

void modifyPatient(patient data){
	FILE* fp = fopen("patients.bin","rb+");
	int counter = 0;
	if(fp == NULL){
		puts("File doesn't exist");
	}else{
		patient temp;
		while(fread(&temp, sizeof(patient),1,fp) !=0){
			counter++;
			if(temp.id == data.id){
				fseek(fp,((counter-1)*sizeof(patient)),0);
				fwrite(&data,sizeof(patient),1,fp);
				break;
			}
		}
		fclose(fp);
	}
}

void deletePatient(int id){
	FILE* fp = fopen("patients.bin","rb");
	FILE* ftemp = fopen("temppatients.bin","wb");
	if(fp == NULL){
		puts("File doesn't exist");
	}else{
		patient temp;
		while(fread(&temp, sizeof(patient),1,fp) !=0){
			if(temp.id != id){
				fwrite(&temp,sizeof(patient),1,ftemp);
			}
		}
		fclose(fp);
		fclose(ftemp);
		remove("patients.bin");
		rename("temppatients.bin","patients.bin");
	}
}


void appendDoctor(doctor data){
	FILE* fp = fopen("doctors.bin","ab");
	if(fp == NULL){
		puts("Error in file creation");
	}else{
		fwrite(&data,sizeof(doctor),1,fp);
		fclose(fp);
	}
}

int getLastDoctorId(){
	FILE* fp = fopen("doctors.bin","rb");
	if(fp == NULL){
		return 0;
	}else{
		int lastId = 0;
		doctor temp;
		while(fread(&temp, sizeof(doctor),1,fp) !=0){
			lastId=temp.id;
		}
		fclose(fp);
		return lastId;
	}
}

doctor getDoctorbyName(char* name){
	FILE* fp = fopen("doctors.bin","rb");
	if(fp == NULL){
		puts("File doesn't exist");
	}else{
		doctor temp;
		while(fread(&temp, sizeof(doctor),1,fp) !=0){
			if(strcmp(temp.name, name) == 0){
				fclose(fp);
				return temp;
			}
		}
		fclose(fp);
	}
}

doctor getDoctorbyId(int id){
	FILE* fp = fopen("doctors.bin","rb");
	if(fp == NULL){
		puts("File doesn't exist");
	}else{
		doctor temp;
		while(fread(&temp, sizeof(doctor),1,fp) !=0){
			if(temp.id == id){
				fclose(fp);
				return temp;
			}
		}
		fclose(fp);
	}
}

void showAllDoctors(){
	FILE* fp = fopen("doctors.bin","rb");
	if(fp == NULL){
		puts("File doesn't exist");
	
	}else{
		doctor temp;
		printf("\n");
		while(fread(&temp, sizeof(doctor), 1, fp) != 0){
			department departDoctor = getDepartmentbyId(temp.department);
			printf("ID: %d - Name: %s - Gender: %s - Age: %d - Department: %s\n",temp.id, temp.name,temp.gender,temp.age,departDoctor.title);
		}
		fclose(fp);
	}
}

void showDoctorsbyDepartment(int departmentid){
	FILE* fp = fopen("doctors.bin","rb");
	if(fp == NULL){
		puts("File doesn't exist");
	
	}else{
		FILE* fpdepartments = fopen("departments.bin","rb");
		if(fpdepartments == NULL){
			puts("File doesn't exist");
		}
		else{
			department tempdepartment;
			int departmentcounter = 0;
			while(fread(&tempdepartment,sizeof(department), 1, fpdepartments) != 0){
				if(tempdepartment.id == departmentid){
					departmentcounter++;
					break;
				}
			}
			if(departmentcounter == 0){
				printf("There is no department with ID:%d",departmentid);
			}else{
				doctor temp;
				int counter=0;
				printf("Doctors working in %s department:\n",tempdepartment.title);
				while(fread(&temp, sizeof(doctor), 1, fp) != 0){
					if(temp.department == departmentid){
						counter++;
				               	printf("ID: %d - Name: %s - Gender: %s - Age: %d\n",temp.id,temp.name,temp.gender,temp.age);
					}
				}
				if(counter == 0){
					printf("There is currently no doctor working in %s department\n",tempdepartment.title);
				}
			}


			fclose(fpdepartments);		
		}
		fclose(fp);
	}
}

void modifyDoctor(doctor data){
	FILE* fp = fopen("doctors.bin","rb+");
	int counter = 0;
	if(fp == NULL){
		puts("File doesn't exist");
	}else{
		doctor temp;
		while(fread(&temp, sizeof(doctor),1,fp) !=0){
			counter++;
			if(temp.id == data.id){
				fseek(fp,((counter-1)*sizeof(doctor)),0);
				fwrite(&data,sizeof(doctor),1,fp);
				break;
			}
		}
		fclose(fp);
	}
}

void deleteDoctor(int id){
	FILE* fp = fopen("doctors.bin","rb");
	FILE* ftemp = fopen("tempdoctors.bin","wb");
	if(fp == NULL){
		puts("File doesn't exist");
	}else{
		doctor temp;
		while(fread(&temp, sizeof(doctor),1,fp) !=0){
			if(temp.id != id){
				fwrite(&temp,sizeof(doctor),1,ftemp);
			}
		}
		fclose(fp);
		fclose(ftemp);
		remove("doctors.bin");
		rename("tempdoctors.bin","doctors.bin");
	}

}



void appendRoom(room data){
	FILE* fp = fopen("rooms.bin","ab");
	if(fp == NULL){
		puts("Error in file creation");
	}else{
		fwrite(&data,sizeof(room),1,fp);
		fclose(fp);
	}

}

int isRoomUnique(int no){
	FILE* fp = fopen("rooms.bin","rb");
	if(fp == NULL){
		return 1;
	}else{
		room temp;
		while(fread(&temp, sizeof(room),1,fp) !=0){
			if(temp.no == no){
				fclose(fp);
				return 0;
			}
		}
		fclose(fp);
		return 1;
	}
}

room getRoombyNo(int no){
	FILE* fp = fopen("rooms.bin","rb");
	if(fp == NULL){
		puts("File doesn't exist");
	}else{
		room temp;
		while(fread(&temp, sizeof(room),1,fp) !=0){
			if(temp.no == no){
				fclose(fp);
				return temp;
			}
		}
		fclose(fp);
	}

}

void showAllRooms(){
	FILE* fp = fopen("rooms.bin","rb");
	if(fp == NULL){
		puts("File doesn't exist");
	
	}else{
		room temp;
		printf("\n");
		while(fread(&temp, sizeof(room), 1, fp) != 0){
			char isAvailable[4];
			if(isRoomAvailable(temp.no) == 1){
				strcpy(isAvailable,"Yes");
			}else{
				strcpy(isAvailable,"No");
			}	
			printf("Room %d - Capacity %d - Is room available: %s\n",temp.no, temp.capacity,isAvailable);
		}
		fclose(fp);
	}
}

void showAvailableRooms(){
	FILE* fp = fopen("rooms.bin","rb");
	if(fp == NULL){
		puts("File doesn't exist");
	
	}else{
		room temp;
		printf("\n");
		while(fread(&temp, sizeof(room), 1, fp) != 0){
			if(isRoomAvailable(temp.no)){
				printf("Room %d\n",temp.no);
			}
		}
		fclose(fp);
	}
}

int isRoomAvailable(int no){
	FILE* fp = fopen("rooms.bin","rb");
	if(fp == NULL){
		puts("File doesn't exist");
		return 0;
	}else{
		room temp;
		while(fread(&temp, sizeof(room), 1, fp) != 0){
			if(temp.no == no){
				FILE* fppatients = fopen("patients.bin","rb");
				if(fppatients == NULL){
					return 1;
				}else{
					patient temppatient;
					int roomCapCounter=0;
					while(fread(&temppatient, sizeof(patient), 1, fppatients) != 0){
						if(temppatient.room == no){
							roomCapCounter++;
						}
					}
					fclose(fppatients);
					fclose(fp);
					if(roomCapCounter >= temp.capacity){
						return 0;
					}else{
						return 1;
					}
				}	
			}		
		}
		fclose(fp);
		return 0;
	}

}

void modifyRoom(room data){
	FILE* fp = fopen("rooms.bin","rb+");
	int counter = 0;
	if(fp == NULL){
		puts("File doesn't exist");
	}else{
		room temp;
		while(fread(&temp, sizeof(room),1,fp) !=0){
			counter++;
			if(temp.no == data.no){
				fseek(fp,((counter-1)*sizeof(room)),0);
				fwrite(&data,sizeof(room),1,fp);
				break;
			}
		}
		fclose(fp);
	}
}

void deleteRoom(int no){
	FILE* fp = fopen("rooms.bin","rb");
	FILE* ftemp = fopen("temprooms.bin","wb");
	if(fp == NULL){
		puts("File doesn't exist");
	}else{
		room temp;
		while(fread(&temp, sizeof(room),1,fp) !=0){
			if(temp.no != no){
				fwrite(&temp,sizeof(room),1,ftemp);
			}
		}
		fclose(fp);
		fclose(ftemp);
		remove("rooms.bin");
		rename("temprooms.bin","rooms.bin");
	}
}





void appendDepartment(department data){
	FILE* fp = fopen("departments.bin","ab");
	if(fp == NULL){
		puts("Error in file creation");
	}else{
		fwrite(&data,sizeof(department),1,fp);
		fclose(fp);
	}
}

int getLastDepartmentId(){
	FILE* fp = fopen("departments.bin","rb");
	if(fp == NULL){
		return 0;
	}else{
		int lastId = 0;
		department temp;
		while(fread(&temp, sizeof(department),1,fp) !=0){
			lastId=temp.id;
		}
		fclose(fp);
		return lastId;
	}

}

department getDepartmentbyTitle(char* title){
	FILE* fp = fopen("departments.bin","rb");
	if(fp == NULL){
		puts("File doesn't exist");
	}else{
		department temp;
		while(fread(&temp, sizeof(department),1,fp) !=0){
			if(strcmp(temp.title, title) == 0){
				fclose(fp);
				return temp;
			}
		}
		fclose(fp);
	}
}

department getDepartmentbyId(int id){
	FILE* fp = fopen("departments.bin","rb");
	if(fp == NULL){
		puts("File doesn't exist");
	}else{
		department temp;
		while(fread(&temp, sizeof(department),1,fp) !=0){
			if(temp.id == id){
				fclose(fp);
				return temp;
			}
		}
		fclose(fp);
	}

}

void showAllDepartments(){
	FILE* fp = fopen("departments.bin","rb");
	if(fp == NULL){
		puts("File doesn't exist");
	}else{
		department temp;
		printf("\n");
		while(fread(&temp, sizeof(department),1,fp) !=0){
			printf("ID:%d - %s department\n",temp.id,temp.title);
		}
		fclose(fp);
	}

}

void modifyDepartment(department data){
	FILE* fp = fopen("departments.bin","rb+");
	int counter = 0;
	if(fp == NULL){
		puts("File doesn't exist");
	}else{
		department temp;
		while(fread(&temp, sizeof(department),1,fp) !=0){
			counter++;
			if(temp.id == data.id){
				fseek(fp,((counter-1)*sizeof(department)),0);
				fwrite(&data,sizeof(department),1,fp);
				break;
			}
		}
		fclose(fp);
	}

}

void deleteDepartment(int id){
	FILE* fp = fopen("departments.bin","rb");
	FILE* ftemp = fopen("tempdepartments.bin","wb");
	if(fp == NULL){
		puts("File doesn't exist");
	}else{
		department temp;
		while(fread(&temp, sizeof(department),1,fp) !=0){
			if(temp.id != id){
				fwrite(&temp,sizeof(department),1,ftemp);
			}
		}
		fclose(fp);
		fclose(ftemp);
		remove("departments.bin");
		rename("tempdepartments.bin","departments.bin");
	}
}
