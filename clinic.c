#include <stdio.h>
#include <stdlib.h>
#include "../STD_TYPES.h"

typedef struct patient patient;

struct patient
{
	u8 ID;
	u8 name[25];
	u8 age;
	u8 gender;
	patient *next;
};

patient *head;
patient *end;
u8 ID = 1;

patient *reservations[5];

u8 check_mode();
void admin();
void start();
void add_new_patient();
void edit_patient();
void reserve_slot();
void cancel_reservation();
void view_reservations();

void user();
patient *view_patient();

void main()
{
	start();
}

void start()
{
	printf("\tWelcome to Manwil's Clinic");
	// 0-> admin     1 -> user    2-> block
	u8 mode = check_mode();

	if (mode == 0)
	{
		// admin features
		admin();
	}
	else if (mode == 1)
	{
		// user features
		user();
	}
}

u8 check_mode()
{
	printf("\n\nChoose mode\n\t1. Admin mode\n\t2. User mode");
	u8 mode;
	printf("\n\nYour choice : ");
	scanf("%d", &mode);

	if (mode == 1)
	{
		// admin check

		u16 pass = 1234;
		u16 password;

		u8 tries = 3;

		while (tries > 0)
		{
			printf("\nEnter Admin Password : ");
			scanf("%d", &password);

			// check password

			if (pass == password)
			{
				return 0;
				break;
			}
			else
			{
				tries--;
				printf("\nInvalid password %d tries left", tries);
			}
		}

		printf("\n\n You have Entered Wrong Password 3 Times.\n\tYou have been blocked");
		return 2;
	}
	else if (mode == 2)
	{
		// user check
		return 1;
	}
	else
	{
		printf("Invalid choice");
		check_mode();
	}
}

void admin()
{
	printf("\n\nWhat would you like to do\n\t1. Add new patient\n\t2. Edit / View patient record\n\t3. Reserve slot\n\t4. Cancel reservation\n\t5. Logout");
	u8 action;
	printf("\n\nYour choice : ");
	scanf("%d", &action);

	switch (action)
	{
	case 1:
		add_new_patient();
		admin();
		break;
	case 2:
		edit_patient();
		admin();
		break;
	case 3:
		reserve_slot();
		admin();
		break;
	case 4:
		cancel_reservation();
		admin();
		break;
	case 5:
		printf("\n\tLogout Successfull\n\n****************************************\n\n");
		start();
		break;
	default:
		printf("Invalid Choice , Try again \n");
		admin();
	}
}

void add_new_patient()
{

	u8 name[25];
	u8 age;
	u8 gender;

	patient *new = (patient *)malloc(sizeof(patient));

	if (new != NULL)
	{

		printf("\nEnter patient name : ");
		scanf("%25s", new->name);

		printf("Enter patient age : ");
		scanf("%d", &new->age);

		printf("Enter patient gender (m / f) : ");
		scanf(" %c", &new->gender);

		new->ID = ID++;

		printf("\nNew patient created \nName : %s | Age: %d | Gender: %c | Id : %d", (new->name), (new->age), (new->gender), (new->ID));
		new->next = NULL;

		if (head == NULL)
		{
			head = new;
			end = new;
			printf("\nHead not previously defined , Set new Head And End");
		}
		else
		{
			end->next = new;
			end = new;
		}
	}
	else
	{
		printf("Error occured in malloc ... You might have run out of memory");
	}
}

patient *view_patient()
{
	u8 patient_id;
	printf("\nEnter user ID to View and Edit : ");
	scanf("%d", &patient_id);

	if (patient_id > (ID - 1) || patient_id < 1)
	{
		if (head != NULL)
		{
			printf("ID not valid , try again");
			edit_patient();
		}else{
			printf("\nNo Patients Created , Create Patients first\n");
		}
	}

	patient *search = head;

	// Cut time by checking if asked id is the last one
	if (patient_id == (ID - 1))
	{
		search = end;
	}
	else
	{
		while (search != NULL)
		{
			if (search->ID == patient_id)
			{
				break;
			}
			search = search->next;
		}
	}

	if (search == NULL)
	{
		printf("\n Patient With ID %d Not Found", patient_id);
	}
	else
	{
		printf("\nID : %d | Name : %s | Age : %d | Gender : %c", search->ID, search->name, search->age, search->gender);
		return search;
	}
}

void edit_patient()
{
	// ask user if he wants to
	patient *search = view_patient();
	u8 yn;
	printf("\nWould you like to edit ? (y / n) :");
	scanf(" %c", &yn);

	if (yn == 'y')
	{
		u8 name[25];
		u8 age;
		u8 gender;

		printf("\nEnter patient name : ");
		scanf("%25s", search->name);

		printf("Enter patient age : ");
		scanf("%d", &search->age);

		printf("Enter patient gender (m / f) : ");
		scanf(" %c", &search->gender);

		printf("\n\n\tUPDATED SUCCESS\n");
	}
}

void reserve_slot()
{
	printf("\nEnter Patient ID : ");
	u8 patient_id;
	scanf("%d", &patient_id);

	if (patient_id > (ID - 1) || patient_id < 1)
	{
		if (head != NULL)
		{
			printf("ID not valid , try again");
			reserve_slot();
		}else{
			printf("\nNo Patients Created , Create Patients first\n");
		}
	}

	u16 reserve;
	patient *search = head;

	// Get Patient with ID patient_id
	if (patient_id == (ID - 1))
	{
		search = end;
	}
	else
	{
		while (search != NULL)
		{
			if (search->ID == patient_id)
			{
				break;
			}
			search = search->next;
		}
	}

	printf("\nAvailable Time Slots : ");

	if (reservations[0] == NULL)
	{
		printf("\n\t1. 2pm -> 2:30pm");
	}
	if (reservations[1] == NULL)
	{
		printf("\n\t2. 2:30pm -> 3pm");
	}
	if (reservations[2] == NULL)
	{
		printf("\n\t3. 3pm -> 3:30pm");
	}
	if (reservations[3] == NULL)
	{
		printf("\n\t4. 4pm -> 4:30pm");
	}
	if (reservations[4] == NULL)
	{
		printf("\n\t5. 4:30pm -> 5pm");
	}

	printf("\n\nWhich Time Slots would you like to reserve : ");
	scanf("%d", &reserve);

	switch (reserve)
	{
	case 1:
		if (reservations[0] == NULL)
		{

			reservations[0] = search;
			printf("\n\n\tRESERVATION SUCCESS\n");
		}
		else
		{
			printf("\nthis slot is not available for reservation");
			printf("\n\tRESERVATION FAIL\n");
		}
		break;
	case 2:
		if (reservations[1] == NULL)
		{

			reservations[1] = search;
			printf("\n\n\tRESERVATION SUCCESS\n");
		}
		else
		{
			printf("\nthis slot is not available for reservation");
			printf("\n\tRESERVATION FAIL\n");
		}
		break;
	case 3:
		if (reservations[2] == NULL)
		{

			reservations[2] = search;
			printf("\n\n\tRESERVATION SUCCESS\n");
		}
		else
		{
			printf("\nthis slot is not available for reservation");
			printf("\n\tRESERVATION FAIL\n");
		}
		break;
	case 4:
		if (reservations[3] == NULL)
		{

			reservations[3] = search;
			printf("\n\n\tRESERVATION SUCCESS\n");
		}
		else
		{
			printf("\nthis slot is not available for reservation");
			printf("\n\tRESERVATION FAIL\n");
		}
		break;
	case 5:
		if (reservations[4] == NULL)
		{

			reservations[4] = search;
			printf("\n\n\tRESERVATION SUCCESS\n");
		}
		else
		{
			printf("\nthis slot is not available for reservation");
			printf("\n\tRESERVATION FAIL\n");
		}
		break;
	default:
		printf("Invalid Time Slot");
	}
}

void cancel_reservation()
{
	printf("\nAvailable cancellations :");

	if (reservations[0] != NULL)
	{
		printf("\n\t1. 2pm -> 2:30pm");
	}
	if (reservations[1] != NULL)
	{
		printf("\n\t2. 2:30pm -> 3pm");
	}
	if (reservations[2] != NULL)
	{
		printf("\n\t3. 3pm -> 3:30pm");
	}
	if (reservations[3] != NULL)
	{
		printf("\n\t4. 4pm -> 4:30pm");
	}
	if (reservations[4] != NULL)
	{
		printf("\n\t5. 4:30pm -> 5pm");
	}

	printf("\nWhich Time Slots would you like to cancel : ");
	u8 cancel;
	scanf("%d", &cancel);

	switch (cancel)
	{
	case 1:
		if (reservations[0] != NULL)
		{
			reservations[0] = NULL;
			printf("\n\n\tCANCELATION SUCCESS\n");
		}
		else
		{
			printf("\nthis slot is already empty");
			printf("\n\n\tCANCELATION FAIL\n");
		}
		break;
	case 2:
		if (reservations[1] != NULL)
		{
			reservations[1] = NULL;
			printf("\n\n\tCANCELATION SUCCESS\n");
		}
		else
		{
			printf("\nthis slot is already empty");
			printf("\n\n\tCANCELATION FAIL\n");
		}
		break;
	case 3:
		if (reservations[2] != NULL)
		{
			reservations[2] = NULL;
			printf("\n\n\tCANCELATION SUCCESS\n");
		}
		else
		{
			printf("\nthis slot is already empty");
			printf("\n\n\tCANCELATION FAIL\n");
		}
		break;
	case 4:
		if (reservations[3] != NULL)
		{
			reservations[3] = NULL;
			printf("\n\n\tCANCELATION SUCCESS\n");
		}
		else
		{
			printf("\nthis slot is already empty");
			printf("\n\n\tCANCELATION FAIL\n");
		}
		break;
	case 5:
		if (reservations[4] != NULL)
		{
			reservations[4] = NULL;
			printf("\n\tCANCELATION SUCCESS\n");
		}
		else
		{
			printf("\nthis slot is already empty");
			printf("\n\n\tCANCELATION FAIL\n");
		}
		break;
	default:
		printf("Invalid Time Slot");
	}
}

void user()
{
	printf("\n\nWhat would you like to do\n\t1. View Patient\n\t2. View Reservations\n\t3. Logout");
	u8 action;
	printf("\n\nYour choice : ");
	scanf("%d", &action);

	switch (action)
	{
	case 1:
		view_patient();
		user();
		break;
	case 2:
		view_reservations();
		user();
		break;
	case 3:
		printf("\n\tLogout Successfull\n\n*****************************************************\n\n");
		start();
		break;
	default:
		printf("Invalid Choice , Try again \n");
		user();
	}
}

void view_reservations()
{
	if (reservations[0] != NULL)
	{
		printf("\n\t2pm -> 2:30pm by patient id :%d", reservations[0]->ID);
	}
	if (reservations[1] != NULL)
	{
		printf("\n\t2:30pm -> 3pm by patient id :%d", reservations[1]->ID);
	}
	if (reservations[2] != NULL)
	{
		printf("\n\t3pm -> 3:30pm by patient id :%d", reservations[2]->ID);
	}
	if (reservations[3] != NULL)
	{
		printf("\n\t4pm -> 4:30pm by patient id :%d", reservations[3]->ID);
	}
	if (reservations[4] != NULL)
	{
		printf("\n\t4:30pm -> 5pm by patient id :%d", reservations[4]->ID);
	}
}