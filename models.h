typedef struct{
	int id;
	int age;
	int room;
	int doctor;
	char name[50];
	char gender[10];
	char diagnosis[100];
} patient;

typedef struct{
	int id;
	int age;
	int department;
	char name[50];
	char gender[10];
} doctor;

typedef struct{
	int no;
	int capacity;
} room;

typedef struct{
	int id;
	char title[50];
} department;


