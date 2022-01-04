#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "models.h"
#include "function_declarations.h"
int main(){
	printf("\t WELCOME TO HOSPITIUM - HOSPITAL MANAGEMENT SYSTEM\n");

	
	int sectionSelection = 0;
	
	while(sectionSelection !=5){
		system("clear");
		printf("1.Patients\n2.Doctors\n3.Departments\n4.Rooms\n5.Exit\n");
		printf("PLease enter section number to make operations:");	
		scanf("%d",&sectionSelection);
	
		if(sectionSelection == 1){
			int patientSectionSelection = 0;
			while(patientSectionSelection != 6){
				puts("\n\t Patient operations menu");
				puts("1.New patient\n2.Show all patients\n3.Search patient\n4.Modify patient\n5.Delete patient\n6.Exit\n");
				printf("Please enter operation number to proceed:");
				scanf("%d",&patientSectionSelection);
				if(patientSectionSelection == 1){
					patient p;
					p.id=getLastPatientId() + 1;
					puts("\nWhich room will the patient stay in? Available rooms are:");
					showAvailableRooms();
					do{
						printf("PLease enter room no from available rooms list:");
						scanf("%d",&p.room);
					}while(isRoomAvailable(p.room) !=1);
					puts("\nWhich doctor will the patient will under control be? Available doctors are:");
					showAllDoctors();		
					printf("Please enter doctor id:");
					scanf("%d",&p.doctor);	
					printf("Please enter age of patient:");
					scanf("%d",&p.age);
					while((getchar()) != '\n');
					printf("Please enter name of patient:");
					fgets(p.name, 50, stdin);
					printf("Please enter gender of patient:");
					fgets(p.gender, 10, stdin);
					printf("Please enter diagnosis of patient:");
					fgets(p.diagnosis, 100, stdin);

					p.name[strlen(p.name)-1]='\0';
					p.gender[strlen(p.gender)-1]='\0';
					p.diagnosis[strlen(p.diagnosis)-1]='\0';
					
					appendPatient(p);
					system("clear");
					puts("Patient successfully added");
				}
				
				else if(patientSectionSelection == 2){
					puts("\n ALl patients:");
					showAllPatients();
				}

				else if(patientSectionSelection == 3){
					puts("\n\n1.Search by Id\n2.Search by Name\n3.List by doctor ID\n4.List by room no");
					printf("Please enter search criteria:");
					int searchCriteria;
					scanf("%d",&searchCriteria);
					if(searchCriteria == 1){
						int id;
						printf("\nPlease enter ID of patient:");
						scanf("%d",&id);
						patient result = getPatientbyId(id);
						doctor docofPatient = getDoctorbyId(result.doctor);
						printf("\nID: %d - Name: %s - Age: %d - Gender: %s - Diagnosis: %s - Doctor: %s - Room: %d\n",result.id,result.name,result.age,result.gender,result.diagnosis,docofPatient.name,result.room);
					}

					else if(searchCriteria == 2){
						char name[50];
						printf("\nPlease enter name of patient:");
						while((getchar()) !='\n');
						fgets(name,50,stdin);
						name[strlen(name)-1]='\0';
						patient result = getPatientbyName(name);
						doctor docofPatient = getDoctorbyId(result.doctor);
						printf("\nID: %d - Name: %s - Age: %d - Gender: %s - Diagnosis: %s - Doctor: %s - Room: %d\n",result.id,result.name,result.age,result.gender,result.diagnosis,docofPatient.name,result.room);

					}

					else if(searchCriteria == 3){
						int doctorid;
						showAllDoctors();
						printf("\nPlease enter doctor ID to list patients by appropriate doctor:");
						scanf("%d",&doctorid);
						showPatientsbyDoctor(doctorid);
					}

					else if(searchCriteria == 4){
						int roomno;
						showAllRooms();
						printf("\nPlease enter room no to list patients by appropriate room:");
						scanf("%d",&roomno);
						showPatientsbyRoom(roomno);
					}
				}

				else if(patientSectionSelection == 4){
					showAllPatients();
					printf("\nPlease enter ID of patient for modification:");
					patient p;
					int patientModify;
					scanf("%d",&patientModify);
					p = getPatientbyId(patientModify);
					puts("\nPlease enter updated details of patient");
					puts("\nWhich room will the patient stay in? Available rooms are:");
					showAvailableRooms();
					printf("\nYou can also input current room, which is room %d\n",p.room);
					int roomSelection;
					do{
						printf("PLease enter room no from available rooms list:");
						scanf("%d",&roomSelection);
					}while(isRoomAvailable(roomSelection) !=1 && roomSelection != p.room);
					p.room = roomSelection;
					puts("\nWhich doctor will the patient will under control be? Available doctors are:");
					showAllDoctors();		
					printf("Please enter doctor id (Current: %d):",p.doctor);
					scanf("%d",&p.doctor);	
					printf("Please enter age of patient (Current: %d):",p.age);
					scanf("%d",&p.age);
					while((getchar()) != '\n');
					printf("Please enter name of patient (Current: %s):",p.name);
					fgets(p.name, 50, stdin);
					printf("Please enter gender of patient (Current: %s):",p.gender);
					fgets(p.gender, 10, stdin);
					printf("Please enter diagnosis of patient (Current: %s):",p.diagnosis);
					fgets(p.diagnosis, 100, stdin);

					p.name[strlen(p.name)-1]='\0';
					p.gender[strlen(p.gender)-1]='\0';
					p.diagnosis[strlen(p.diagnosis)-1]='\0';
					modifyPatient(p);
					system("clear");
					puts("Patient successfuly modified");
				}

				else if(patientSectionSelection == 5){
					showAllPatients();
					printf("\nPlease enter ID of patient you want to delete:");
					int patientDelete;
					scanf("%d",&patientDelete);
					deletePatient(patientDelete);
					system("clear");
					puts("Patient successfully deleted");
				}
			
			}
		}

		else if(sectionSelection == 2){
			int doctorSectionSelection = 0;
			while(doctorSectionSelection != 6){
				puts("\n\t Doctor operations menu");
				puts("1.New doctor\n2.Show all doctors\n3.Search doctor\n4.Modify doctor\n5.Delete doctor\n6.Exit\n");
				printf("Please enter operation number to proceed:");
				scanf("%d",&doctorSectionSelection);
				if(doctorSectionSelection == 1){
					doctor d;
					d.id=getLastDoctorId() + 1;
					puts("\nWhich department will the doctor work in? Available departments are:");
					showAllDepartments();		
					printf("Please enter department id:");
					scanf("%d",&d.department);	
					printf("Please enter age of doctor:");
					scanf("%d",&d.age);
					while((getchar()) != '\n');
					printf("Please enter name of doctor:");
					fgets(d.name, 50, stdin);
					printf("Please enter gender of doctor:");
					fgets(d.gender, 10, stdin);

					d.name[strlen(d.name)-1]='\0';
					d.gender[strlen(d.gender)-1]='\0';
					
					appendDoctor(d);
					system("clear");
					puts("Doctor successfully added");

				}
				
				else if(doctorSectionSelection == 2){
					puts("\nAll doctors:");
					showAllDoctors();
				}

				else if(doctorSectionSelection == 3){
					puts("\n\n1.Search by Id\n2.Search by Name\n3.List by department");
					printf("Please enter search criteria:");
					int searchCriteria;
					scanf("%d",&searchCriteria);
					if(searchCriteria == 1){
						int id;
						printf("\nPlease enter ID of doctor:");
						scanf("%d",&id);
						doctor result = getDoctorbyId(id);
						department depofDoc = getDepartmentbyId(result.department);
						printf("ID: %d - Name: %s - Gender: %s - Age: %d - Department: %s\n",result.id, result.name,result.gender,result.age,depofDoc.title);
					}

					else if(searchCriteria == 2){
						char name[50];
						printf("\nPlease enter name of doctor:");
						while((getchar()) !='\n');
						fgets(name,50,stdin);
						name[strlen(name)-1]='\0';
						doctor result = getDoctorbyName(name);
						department depofDoc = getDepartmentbyId(result.department);
						printf("ID: %d - Name: %s - Gender: %s - Age: %d - Department: %s\n",result.id, result.name,result.gender,result.age,depofDoc.title);				
					}

					else if(searchCriteria == 3){
						int departid;
						showAllDepartments();
						printf("\nPlease enter department ID to list doctors by appropriate department:");
						scanf("%d",&departid);
						showDoctorsbyDepartment(departid);
					}
				}

				else if(doctorSectionSelection == 4){
					showAllDoctors();
					printf("\nPlease enter ID of doctor for modification:");
					doctor d;
					int doctorModify;
					scanf("%d",&doctorModify);
					d = getDoctorbyId(doctorModify);
					puts("\nPlease enter updated details of doctor");
					puts("\nWhich department will the doctor work in? Available departments are:");
					showAllDepartments();		
					printf("Please enter department id (Current: %d):",d.department);
					scanf("%d",&d.department);	
					printf("Please enter age of doctor (Current: %d):",d.age);
					scanf("%d",&d.age);
					while((getchar()) != '\n');
					printf("Please enter name of doctor (Current: %s):",d.name);
					fgets(d.name, 50, stdin);
					printf("Please enter gender of doctor (Current: %s):",d.gender);
					fgets(d.gender, 10, stdin);

					d.name[strlen(d.name)-1]='\0';
					d.gender[strlen(d.gender)-1]='\0';
					modifyDoctor(d);
					system("clear");
					puts("Doctor successfuly modified");
				}

				else if(doctorSectionSelection == 5){
					showAllDoctors();
					printf("\nPlease enter ID of doctor you want to delete:");
					int doctorDelete;
					scanf("%d",&doctorDelete);
					deleteDoctor(doctorDelete);
					system("clear");
					puts("Doctor successfully deleted");
				}
			
			}
		}

		else if(sectionSelection == 3){
			int departmentSectionSelection = 0;
			while(departmentSectionSelection != 6){
				puts("\n\t Department operations menu");
				puts("1.New department\n2.Show all departments\n3.Search department\n4.Modify department\n5.Delete department\n6.Exit\n");
				printf("Please enter operation number to proceed:");
				scanf("%d",&departmentSectionSelection);
				if(departmentSectionSelection == 1){
					department d;
					d.id=getLastDepartmentId() + 1;
					printf("Please enter title of department:");
					while((getchar()) != '\n');
					fgets(d.title, 50, stdin);
					
					d.title[strlen(d.title)-1]='\0';
					
					appendDepartment(d);
					system("clear");
					puts("Department successfully added");

				}
				
				else if(departmentSectionSelection == 2){
					puts("\nAll departments:");
					showAllDepartments();
				}

				else if(departmentSectionSelection == 3){
					puts("\n\n1.Search by Id\n2.Search by department title");
					printf("Please enter search criteria:");
					int searchCriteria;
					scanf("%d",&searchCriteria);
					if(searchCriteria == 1){
						int id;
						printf("\nPlease enter ID of department:");
						scanf("%d",&id);
						department result = getDepartmentbyId(id);
						printf("ID:%d - %s department\n",result.id,result.title);
					}

					else if(searchCriteria == 2){
						char title[50];
						printf("\nPlease enter title of department:");
						while((getchar()) !='\n');
						fgets(title,50,stdin);
						title[strlen(title)-1]='\0';				
						department result = getDepartmentbyTitle(title);
						printf("ID:%d - %s department\n",result.id,result.title);
					}
				}

				else if(departmentSectionSelection == 4){
					showAllDepartments();
					printf("\nPlease enter ID of department for modification:");
					department d;
					int departmentModify;
					scanf("%d",&departmentModify);
					d = getDepartmentbyId(departmentModify);
					puts("\nPlease enter updated details of department");
					while((getchar()) != '\n');
					printf("Please enter title of department (Current: %s):",d.title);
					fgets(d.title, 50, stdin);

					d.title[strlen(d.title)-1]='\0';
					modifyDepartment(d);
					system("clear");
					puts("Department successfuly modified");
				}

				else if(departmentSectionSelection == 5){
					showAllDepartments();
					printf("\nPlease enter ID of department you want to delete:");
					int departmentDelete;
					scanf("%d",&departmentDelete);
					deleteDepartment(departmentDelete);
					system("clear");
					puts("Department successfully deleted");
				}
			
			}
		}

		else if(sectionSelection == 4){
			int roomSectionSelection = 0;
			while(roomSectionSelection != 6){
				puts("\n\t Room operations menu");
				puts("1.New room\n2.Show all rooms\n3.Search room\n4.Modify room\n5.Delete room\n6.Exit\n");
				printf("Please enter operation number to proceed:");
				scanf("%d",&roomSectionSelection);
				if(roomSectionSelection == 1){
					room r;
					puts("Current rooms are following:");
					showAllRooms();
					do{
						printf("Please enter unique room no:");
						scanf("%d",&r.no);
					}while(isRoomUnique(r.no) != 1);
					printf("Please enter capacity of room:");
					scanf("%d",&r.capacity);
					appendRoom(r);
					system("clear");
					puts("Room successfully added");

				}
				
				else if(roomSectionSelection == 2){
					puts("\nAll rooms:");
					showAllRooms();
				}

				else if(roomSectionSelection == 3){
					int no;
					printf("\nPlease enter no of room:");
					scanf("%d",&no);
					room result = getRoombyNo(no);
					char isAvailable[4];
					if(isRoomAvailable(no) == 1){
						strcpy(isAvailable,"Yes");
					}else{
						strcpy(isAvailable,"No");
					}
					printf("Room %d - Capacity %d - Is room available: %s\n",result.no, result.capacity,isAvailable);
				}

				else if(roomSectionSelection == 4){
					showAllRooms();
					printf("\nPlease enter no of room for modification:");
					room r;
					int roomModify;
					scanf("%d",&roomModify);
					r = getRoombyNo(roomModify);
					puts("\nPlease enter updated details of room");
					printf("Please enter capacity of room (Current: %d):",r.capacity);
					scanf("%d",&r.capacity);
					modifyRoom(r);
					system("clear");
					puts("Room successfuly modified");
				}

				else if(roomSectionSelection == 5){
					showAllRooms();
					printf("\nPlease enter no of room you want to delete:");
					int roomDelete;
					scanf("%d",&roomDelete);
					deleteRoom(roomDelete);
					system("clear");
					puts("Room successfully deleted");
				}
			
			}
		}
	
	
	
	}

	printf("\t GOOD BYE!\n");
	return 0;
}
