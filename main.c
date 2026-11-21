#include <stdio.h>
#include <string.h>

#define MAX_MEDICINES 100

struct Medicine
{
    char name[50];
    char dosage[30];
    char time[20];
    char frequency[30];
    int duration;
};

/* Function declarations */
void addMedicine(struct Medicine medicines[], int *count);
void viewMedicines(struct Medicine medicines[], int count);
void searchMedicine(struct Medicine medicines[], int count);
void updateMedicine(struct Medicine medicines[], int count);
void deleteMedicine(struct Medicine medicines[], int *count);
void dailySchedule(struct Medicine medicines[], int count);

void saveMedicines(struct Medicine medicines[], int count);
void loadMedicines(struct Medicine medicines[], int *count);


int main()
{
    struct Medicine medicines[MAX_MEDICINES];

    int count = 0;
    int choice;


    loadMedicines(medicines, &count);

    do
    {
        printf("\n=====================================\n");
        printf("       MEDICINE REMINDER SYSTEM\n");
        printf("=====================================\n");

        printf("1. Add Medicine\n");
        printf("2. View Medicines\n");
        printf("3. Search Medicine\n");
        printf("4. Update Medicine\n");
        printf("5. Delete Medicine\n");
        printf("6. Daily Schedule\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addMedicine(medicines, &count);
                break;

            case 2:
                viewMedicines(medicines, count);
                break;

            case 3:
                searchMedicine(medicines, count);
                break;

            case 4:
                updateMedicine(medicines, count);
                break;

            case 5:
                deleteMedicine(medicines, &count);
                break;

            case 6:
                dailySchedule(medicines, count);
                break;

            case 7:
                saveMedicines(medicines, count);
                printf("\nData saved successfully.\n");
                printf("Thank you for using Medicine Reminder System!\n");
                break;

            default:
                printf("\nInvalid choice! Please enter 1 to 7.\n");
        }

    } while(choice != 7);

    return 0;
}


/* ================= ADD MEDICINE ================= */

void addMedicine(struct Medicine medicines[], int *count)
{
    if(*count >= MAX_MEDICINES)
    {
        printf("\nMedicine storage is full!\n");
        return;
    }

    printf("\n========== ADD MEDICINE ==========\n");

    printf("Enter medicine name: ");
    scanf(" %49[^\n]", medicines[*count].name);

    printf("Enter dosage (example 500mg): ");
    scanf(" %29[^\n]", medicines[*count].dosage);

    printf("Enter reminder time (example 09:00AM): ");
    scanf(" %19[^\n]", medicines[*count].time);

    printf("Enter frequency (example Twice Daily): ");
    scanf(" %29[^\n]", medicines[*count].frequency);

    printf("Enter duration in days: ");
    scanf("%d", &medicines[*count].duration);

    (*count)++;

    saveMedicines(medicines, *count);

    printf("\nMedicine added successfully!\n");
}


/* ================= VIEW MEDICINES ================= */

void viewMedicines(struct Medicine medicines[], int count)
{
    int i;

    printf("\n========== MEDICINE LIST ==========\n");

    if(count == 0)
    {
        printf("No medicines are currently stored.\n");
        return;
    }

    for(i = 0; i < count; i++)
    {
        printf("\nMedicine %d\n", i + 1);
        printf("-----------------------------------\n");

        printf("Name      : %s\n", medicines[i].name);
        printf("Dosage    : %s\n", medicines[i].dosage);
        printf("Time      : %s\n", medicines[i].time);
        printf("Frequency : %s\n", medicines[i].frequency);
        printf("Duration  : %d days\n", medicines[i].duration);
    }
}


/* ================= SEARCH MEDICINE ================= */

void searchMedicine(struct Medicine medicines[], int count)
{
    char searchName[50];
    int i;
    int found = 0;

    if(count == 0)
    {
        printf("\nNo medicines available to search.\n");
        return;
    }

    printf("\n========== SEARCH MEDICINE ==========\n");

    printf("Enter medicine name: ");
    scanf(" %49[^\n]", searchName);

    for(i = 0; i < count; i++)
    {
        if(strcmp(medicines[i].name, searchName) == 0)
        {
            printf("\nMedicine found!\n");
            printf("-----------------------------------\n");

            printf("Name      : %s\n", medicines[i].name);
            printf("Dosage    : %s\n", medicines[i].dosage);
            printf("Time      : %s\n", medicines[i].time);
            printf("Frequency : %s\n", medicines[i].frequency);
            printf("Duration  : %d days\n", medicines[i].duration);

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nMedicine not found!\n");
    }
}


/* ================= UPDATE MEDICINE ================= */

void updateMedicine(struct Medicine medicines[], int count)
{
    char searchName[50];
    int i;
    int found = 0;

    if(count == 0)
    {
        printf("\nNo medicines available to update.\n");
        return;
    }

    printf("\n========== UPDATE MEDICINE ==========\n");

    printf("Enter medicine name to update: ");
    scanf(" %49[^\n]", searchName);

    for(i = 0; i < count; i++)
    {
        if(strcmp(medicines[i].name, searchName) == 0)
        {
            printf("\nEnter new medicine name: ");
            scanf(" %49[^\n]", medicines[i].name);

            printf("Enter new dosage: ");
            scanf(" %29[^\n]", medicines[i].dosage);

            printf("Enter new reminder time: ");
            scanf(" %19[^\n]", medicines[i].time);

            printf("Enter new frequency: ");
            scanf(" %29[^\n]", medicines[i].frequency);

            printf("Enter new duration in days: ");
            scanf("%d", &medicines[i].duration);

            saveMedicines(medicines, count);

            printf("\nMedicine updated successfully!\n");

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nMedicine not found!\n");
    }
}


/* ================= DELETE MEDICINE ================= */

void deleteMedicine(struct Medicine medicines[], int *count)
{
    char searchName[50];
    int i, j;
    int found = 0;

    if(*count == 0)
    {
        printf("\nNo medicines available to delete.\n");
        return;
    }

    printf("\n========== DELETE MEDICINE ==========\n");

    printf("Enter medicine name to delete: ");
    scanf(" %49[^\n]", searchName);

    for(i = 0; i < *count; i++)
    {
        printf("\nStored name: [%s]\n", medicines[i].name);
        printf("Search name: [%s]\n", searchName);

        printf("Stored length: %zu\n", strlen(medicines[i].name));
        printf("Search length: %zu\n", strlen(searchName));

        printf("Comparison result: %d\n",
               strcmp(medicines[i].name, searchName));

        if(strcmp(medicines[i].name, searchName) == 0)
        {
            for(j = i; j < (*count) - 1; j++)
            {
                medicines[j] = medicines[j + 1];
            }

            (*count)--;

            saveMedicines(medicines, *count);

            printf("\nMedicine deleted successfully!\n");

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nMedicine not found!\n");
    }
}

/* ================= DAILY SCHEDULE ================= */

void dailySchedule(struct Medicine medicines[], int count)
{
    int i;

    printf("\n========== DAILY MEDICINE SCHEDULE ==========\n");

    if(count == 0)
    {
        printf("No medicines scheduled.\n");
        return;
    }

    printf("\n%-20s %-15s %-15s %-20s\n",
           "Medicine", "Dosage", "Time", "Frequency");

    printf("-----------------------------------------------------------------------\n");

    for(i = 0; i < count; i++)
    {
        printf("%-20s %-15s %-15s %-20s\n",
               medicines[i].name,
               medicines[i].dosage,
               medicines[i].time,
               medicines[i].frequency);
    }
}


/* ================= SAVE DATA ================= */

void saveMedicines(struct Medicine medicines[], int count)
{
    FILE *file;

    file = fopen("medicines.dat", "wb");

    if(file == NULL)
    {
        printf("\nError saving medicine data!\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);

    fwrite(medicines,
           sizeof(struct Medicine),
           count,
           file);

    fclose(file);
}


/* ================= LOAD DATA ================= */

void loadMedicines(struct Medicine medicines[], int *count)
{
    FILE *file;

    file = fopen("medicines.dat", "rb");

    if(file == NULL)
    {
        *count = 0;
        return;
    }

    fread(count, sizeof(int), 1, file);

    if(*count > MAX_MEDICINES)
    {
        *count = 0;
        fclose(file);
        return;
    }

    fread(medicines,
          sizeof(struct Medicine),
          *count,
          file);

    fclose(file);
}
