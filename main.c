/*
setup code(array_open, print_array, linked_open, print_linked) - 202035318 Kim wonjong
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define DATA_NUM 30

typedef struct DATA
{
  int tag;
  char date[20];
  char fee_paid[10];
  char name[25];
  int age;
  char organization[30];
  char job[15];
  struct DATA *next;
} Data;

//-----------------------------
//Function prototype
//-----------------------------

int array_open(Data *);
void print_array(Data *, int); // setup
Data *linked_open();
void print_linked(Data *);

void array_findname(Data *); //1-1
void array_findorg(Data *);  //2-1
void search_Choi(Data *);    //1-2
void search_Gachon(Data *);  //2-2

void sort_tag(Data *, Data *, int);
Data *tag_linked(Data *, int);

void ageOrder(Data *, int);
int choi(Data *, int);
Data *choiNode(Data *);

void add_data_to_array(Data *, int *, int, char *, char *, char *, int, char *, char *);
void add_data_to_linked(Data *, int, char *, char *, char *, int, char *, char *);
void copy_is_vaild(Data *, int);
void compare_checksum();

//-----------------------------
//MAIN
//-----------------------------

int main()
{
  Data regi_data[50];
  Data *regi_head;
  int data_num;

  Data tsort_data[50]; //tsort_data -> sorted data in tag order
  Data *tsort_head;    //tsort linked list's head

  data_num = array_open(regi_data);
  print_array(regi_data, data_num);

  printf("\n");

  regi_head = linked_open();
  print_linked(regi_head->next);

  //P1-1, 202035352 안현진
  printf("\n===P1-1===\n");
  array_findname(regi_data);

  //P1-2, 202035352 안현진
  printf("\n===P1-2===\n");
  search_Choi(regi_head);

  //P2-1, 202035352 안현진
  printf("\n===P2-1===\n");
  array_findorg(regi_data);

  //P2-2, 202035352 안현진
  printf("\n===P2-2===\n");
  search_Gachon(regi_head);

  //P3-1, 202035318 Kim wonjong
  printf("\n===P3-1===\n");
  sort_tag(regi_data, tsort_data, data_num);
  print_array(tsort_data, data_num);

  //P4-1, 202035318 Kim wonjong
  printf("\n===P4-1===\n");
  tsort_head = tag_linked(tsort_data, data_num);
  print_linked(tsort_head->next);

  //P5-1, 201835546 함건욱
  ageOrder(regi_data, data_num);

  //P6-1, 201835546 함건욱
  printf("\n===P6-1===\n");
  data_num = choi(regi_data, data_num);
  printf("Choi canceled registration\n");
  print_array(regi_data, data_num);

  //P6-2, 201835546 함건욱
  printf("\n===P6-2===\n");
  regi_head = choiNode(regi_head);
  printf("Choi cencled list\n");
  print_linked(regi_head->next);

  // P7-1, 201834735 LeeJiheon
  add_data_to_array(regi_data, &data_num, 100, "2020-11-30", "yes", "Ildang Paik", 22, "Gachon University", "engineer");

  // P7-2, 201834735 LeeJiheon
  add_data_to_linked(regi_head, 100, "2020-11-30", "yes", "Ildang Paik", 22, "Gachon University", "engineer");

  // P8-1, 201834735 LeeJiheon
  copy_is_vaild(regi_data, data_num);

  return 0;
}

//-----------------------------
//Read registraion_data.txt and store the data in a struct array
//-----------------------------

int array_open(Data *regi_data)
{
  int i = 0, data_num = 0;
  FILE *regi_file;

  regi_file = fopen("registraion_data.txt", "r");
  if (regi_file == NULL)
    printf("file open error\n");
  else
  {
    while (fscanf(regi_file, "%d %*[/] %[^/] %*[/] %[^/] %*[/] %[^/] %*[/] %d %*[/] %[^/] %*[/] %s", &regi_data[i].tag, regi_data[i].date, regi_data[i].fee_paid, regi_data[i].name, &regi_data[i].age, regi_data[i].organization, regi_data[i].job) == 7)
      i++;
  }
  data_num = i;

  fclose(regi_file);

  return data_num;
}

//-----------------------------
//Print array
//-----------------------------

void print_array(Data *regi_data, int data_num)
{
  printf("===array===\n");

  for (int i = 0; i < data_num; i++)
    printf("%d %s %s %s %d %s %s\n", regi_data[i].tag, regi_data[i].date, regi_data[i].fee_paid, regi_data[i].name, regi_data[i].age, regi_data[i].organization, regi_data[i].job);
  printf("======\n");
}

//-----------------------------
//Store the data in a linked list
//-----------------------------

Data *linked_open()
{
  int i = 0;
  FILE *regi_file;
  Data *node;
  Data *head;
  Data *prev_node;

  head = (Data *)malloc(sizeof(Data));
  prev_node = head;

  regi_file = fopen("registraion_data.txt", "r");
  if (regi_file == NULL)
    printf("file open error\n");
  else
  {
    node = (Data *)malloc(sizeof(Data));
    while (fscanf(regi_file, "%d %*[/] %[^/] %*[/] %[^/] %*[/] %[^/] %*[/] %d %*[/] %[^/] %*[/] %s", &node->tag, node->date, node->fee_paid, node->name, &node->age, node->organization, node->job) == 7)
    {
      prev_node->next = node;
      prev_node = node;
      node = (Data *)malloc(sizeof(Data));
    }
    free(node);             //free trash node
    prev_node->next = NULL; //last node
  }

  fclose(regi_file);

  return head;
}

//-----------------------------
//Print linked list
//-----------------------------

void print_linked(Data *ptr)
{
  printf("===linked list===\n");
  while (ptr != NULL)
  {
    printf("%d %s %s %s %d %s %s\n", ptr->tag, ptr->date, ptr->fee_paid, ptr->name, ptr->age, ptr->organization, ptr->job);
    ptr = ptr->next;
  }
  printf("======\n");
}

//-----------------------------
//P1-1 / 202035352 안현진
// Search for "Choi" in the array
// if found, print all info of the persons
//-----------------------------
void array_findname(Data *regi_data)
{
  FILE *myfile;
  char name[20] = "Choi";
  char buffer[300];
  char buffer_2[300];
  int line_num = 0;
  int count = 29;
  char org[35];
  char fname[30] = "registraion_data.txt";
  printf("----------------search array---------------\n");
  printf("name to search: Choi");

  myfile = fopen(fname, "r");
  if (myfile == NULL)
  {
    fprintf(stderr, "Can't open the file%s \n", fname);
    exit(1);
  }
  printf("\n");
  for (int i = 0; i < 30; i++)
  {
    fgets(buffer, 300, myfile);
    if (strstr(buffer, name)) //function to find string
    {
      printf("%d %s %s %s %d %s %s\n", regi_data[i].tag, regi_data[i].date, regi_data[i].fee_paid, regi_data[i].name, regi_data[i].age, regi_data[i].organization, regi_data[i].job);
    }
  }
  fclose(myfile);

} //FINISH

//-----------------------------
//P1-2 / 202035352 안현진
// Search for "Choi" in the linked list
// if found, print all info of the persons
//-----------------------------
void search_Choi(Data *head)
{

  Data *node = head->next, *prev = head; //set node & prev

  while (node)
  {
    if (strstr(node->name, "Choi") != NULL)
    {
      printf("%d %s %s %s %d %s %s\n", node->tag, node->date, node->fee_paid, node->name, node->age, node->organization, node->job);
    }
    prev = node;
    node = node->next;
  }
} //finish

//-----------------------------
//P2-1 / 202035352 안현진
// Search for all from Gachon University in the array
// if found, print all info of the persons
//-----------------------------
void array_findorg(Data *regi_data)
{
  FILE *myfile;
  char name[20];
  char buffer[300];
  char buffer_2[300];
  int line_num = 0;
  int count = 29;
  char org[35] = "Gachon University";
  char fname[30] = "registraion_data.txt";
  printf("----------------search array---------------\n");
  printf("org to search: Gachon University");

  myfile = fopen(fname, "r");
  if (myfile == NULL)
  {
    fprintf(stderr, "Can't open the file%s \n", fname);
    exit(1);
  }
  printf("\n");
  for (int i = 0; i < 30; i++)
  {
    fgets(buffer_2, 300, myfile);
    if (strstr(buffer_2, org)) //function to find string
    {
      printf("%d %s %s %s %d %s %s\n", regi_data[i].tag, regi_data[i].date, regi_data[i].fee_paid, regi_data[i].name, regi_data[i].age, regi_data[i].organization, regi_data[i].job);
    }
  }
  fclose(myfile);

} //FINISH

//-----------------------------
//P2-2 / 202035352 안현진
// Search for all from Gachon University in the linked list
// if found, print all info of the persons
//-----------------------------
void search_Gachon(Data *head)
{

  Data *node = head->next, *prev = head; //set node & prev

  while (node)
  {
    if (strstr(node->organization, "Gachon University") != NULL)
    {
      printf("%d %s %s %s %d %s %s\n", node->tag, node->date, node->fee_paid, node->name, node->age, node->organization, node->job);
    }
    prev = node;
    node = node->next;
  }
} //finish

//-----------------------------
//P3-1 / 202035318 - Kim wonjong
//Sort the data in the array in tag# order
//-----------------------------

void sort_tag(Data *regi_data, Data *tsort_data, int data_num)
{
  Data temp;

  //tsort initialization
  for (int i = 0; i < data_num; i++)
    tsort_data[i] = regi_data[i];

  //Sort the data
  for (int i = 0; i < data_num - 1; i++)
  {
    for (int j = 0; j < data_num - 1 - i; j++)
    {
      if (tsort_data[j].tag > tsort_data[j + 1].tag)
      {
        temp = tsort_data[j];
        tsort_data[j] = tsort_data[j + 1];
        tsort_data[j + 1] = temp;
      }
    }
  }
}

//-----------------------------
//P4-1 / 202035318 - Kim wonjong
//Create a linked list using the sorted data
//-----------------------------

Data *tag_linked(Data *tsort_data, int data_num)
{
  Data *tsort_head;
  Data *node, *prev_node;

  //node and head allocation
  tsort_head = (Data *)malloc(sizeof(Data));
  node = (Data *)malloc(sizeof(Data));
  *node = tsort_data[0];
  tsort_head->next = node;
  prev_node = node;

  //list -> linked list
  for (int i = 1; i < data_num; i++)
  {
    node = (Data *)malloc(sizeof(Data));
    *node = tsort_data[i];
    prev_node->next = node;
    prev_node = node;
  }
  node->next = NULL; //last node

  return tsort_head;
}

//------------------------------------------
//P5-1 / 201835546 함건욱
//Sort the data in the array in age group order (using selection sort – self-study)
//**“age group” means 10, 20, 30, ….
//Write the sorted data to a text file. (Mark P5 - 1 in code, submit textfile 5 - 1.txt)
//------------------------------------------

void ageOrder(Data *array, int data_num) //bring array and data_num
{
  Data temp;

  for (int i = 0; i < data_num; i++) //sort data age order
  {
    for (int j = 0; j < data_num - i; j++)
    {
      if (array[j].age > array[j + 1].age)
      {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }

  for (int k = 0; k < data_num; k++)
  {
    temp = array[k + 1];
    array[k] = temp;
  }

  FILE *age_file; // FIle header

  age_file = fopen("5-1.txt", "w"); //write data to 5-1.txt
  {
    fprintf(age_file, "===age order array===\n");
    for (int i = 0; i < data_num; i++)
    {
      fprintf(age_file, "%d %s %s %s %d %s %s\n", array[i].tag, array[i].date, array[i].fee_paid, array[i].name, array[i].age, array[i].organization, array[i].job);
    }
    fprintf(age_file, "======\n");
  }

  fclose(age_file);
}

//------------------------------------------
//P6-1 / 201835546 함건욱
//All “Choi”s canceled registration. Remove the data from the array
//------------------------------------------

int choi(Data *array, int data_num)
{
  Data temp[100];
  int i = 0, j = 0;

  for (i = 0; i < data_num; i++)
  {
    char *ptr = strstr(array[i].name, "Choi");

    if (ptr != NULL)
    {
      i++;
      if (strstr(array[i].name, "Choi") != NULL)
      {
        i++;
        temp[j] = array[i];
        j++;
      }
      else
      {
        temp[j] = array[i];
        j++;
      }
    }
    else
    {
      temp[j] = array[i];
      j++;
    }
  }
  data_num = j;

  for (j = 0; j < data_num; j++)
  {
    array[j] = temp[j];
  }

  return data_num;
}

//------------------------------------------
//P6-2 / 201835546 함건욱
//All “Choi”s canceled registration. Remove the data from the linked list
//------------------------------------------

Data *choiNode(Data *head)
{

  Data *ptr = head->next, *prev = head, *temp; //set ptr & prev

  while (ptr)
  {
    if (strstr(ptr->name, "Choi") != NULL)
    {
      if (strstr((ptr->next)->name, "Choi") != NULL) // if nex next node is "Choi" again
      {
        prev->next = ((ptr->next)->next); //delete two node
        prev = ptr;
        ptr = ptr->next;
      }
      else
      {
        prev->next = ptr->next; /* node deleted */
        prev = ptr;
        ptr = ptr->next;
      }
    }
    else
    {
      prev = ptr;
      ptr = ptr->next;
    }
  }

  prev = head; //sort tag order
  ptr = prev;
  while (ptr->next != NULL)
  {
    if (ptr->tag > ptr->next->tag)
    {
      temp = ptr->next;
      ptr->next = ptr->next->next;
      temp->next = prev;
      prev = ptr = temp;
      continue;
    }
    ptr = ptr->next;
  }

  return head;
}

// ------------------------------------------
// P7-1 / 201834735 LeeJiheon
// One “Paik” registered late. Add the data to the array(sorted order)
// ------------------------------------------

void add_data_to_array(Data *regi_data, int *data_num, int tag, char *date, char *fee_paid, char *name, int age, char *organization, char *job)
{
  printf("\n===P7-1===\n");

  // Arrays start at 0, so 1 is not added
  int new_data_num = *data_num;

  regi_data[new_data_num].tag = tag;
  strcpy(regi_data[new_data_num].date, date);
  strcpy(regi_data[new_data_num].fee_paid, fee_paid);
  strcpy(regi_data[new_data_num].name, name);
  regi_data[new_data_num].age = age;
  strcpy(regi_data[new_data_num].organization, organization);
  strcpy(regi_data[new_data_num].job, job);

  *data_num += 1;
  new_data_num = *data_num;

  Data temp;

  //  Bubble sort by age
  for (int i = 0; i < new_data_num; i++)
  {
    for (int j = 0; j < new_data_num - 1; j++)
    {
      if (regi_data[j].age > regi_data[j + 1].age)
      {
        temp = regi_data[j];
        regi_data[j] = regi_data[j + 1];
        regi_data[j + 1] = temp;
      }
    }
  }

  for (int i = 0; i < new_data_num; i++)
  {
    printf("%d %s %s %s %d %s %s", regi_data[i].tag, regi_data[i].date, regi_data[i].fee_paid, regi_data[i].name, regi_data[i].age, regi_data[i].organization, regi_data[i].job);
    // Data mark added
    if (!strcmp(regi_data[i].name, name) && regi_data[i].tag == tag)
    {
      printf(" <===== added data");
    }
    printf("\n");
  }
  printf("==========\n");
}

// ------------------------------------------
// P7-2 / 201834735 LeeJiheon
// One “Paik” registered late. Add the data to the linked list(sorted order)
// ------------------------------------------

void add_data_to_linked(Data *regi_head, int tag, char *date, char *fee_paid, char *name, int age, char *organization, char *job)
{
  printf("\n===P7-2===\n");

  // Create node to be added
  Data *new_node = (Data *)malloc(sizeof(Data));
  new_node->tag = tag;
  strcpy(new_node->date, date);
  strcpy(new_node->fee_paid, fee_paid);
  strcpy(new_node->name, name);
  new_node->age = age;
  strcpy(new_node->organization, organization);
  strcpy(new_node->job, job);
  new_node->next = NULL;

  Data *ptr, *phead, *temp;

  // Insert new node into last node
  ptr = regi_head->next;
  while (ptr->next != NULL)
  {
    ptr = ptr->next;
  }
  ptr->next = new_node;

  //  Bubble sort by tag
  phead = regi_head;
  ptr = phead;
  while (ptr->next != NULL)
  {
    if (ptr->tag > ptr->next->tag)
    {
      temp = ptr->next;
      ptr->next = ptr->next->next;
      temp->next = phead;
      phead = ptr = temp;
      continue;
    }
    ptr = ptr->next;
  }

  // Print added data and sorted linked list
  ptr = regi_head->next;
  while (ptr != NULL)
  {
    printf("%d %s %s %s %d %s %s", ptr->tag, ptr->date, ptr->fee_paid, ptr->name, ptr->age, ptr->organization, ptr->job);
    // Data mark added
    if (!strcmp(ptr->name, new_node->name) && ptr->tag == new_node->tag)
    {
      printf(" <===== added data");
    }
    printf("\n");
    ptr = ptr->next;
  }
  printf("==========\n");
}

// ------------------------------------------
// P8-1 / 201834735 LeeJiheon
// Copy and compare
// ------------------------------------------

void copy_is_vaild(Data *regi_data, int data_num)
{
  printf("\n===P8-1===\n");

  // Currently, the data in the array are sorted by age in 7-1.

  FILE *copyFile = fopen("8-1.txt", "w");
  char checksum = '\0';

  // Create checksum insert location on first line.
  fprintf(copyFile, "%s\n", "00");

  // 5 most recent data names in array
  // Currently data_num is a number containing the last null character(= '\0'), so -1.
  for (int i = data_num - 1; i > data_num - 6; i--)
  {
    fprintf(copyFile, "%s\n", regi_data[i].name);

    int j = 0;
    while (regi_data[i].name[j] != '\0')
    {
      // using bitwise ExclusiveOR
      checksum ^= regi_data[i].name[j];
      j++;
    }
  }
  // Move the file pointer position to the start point. And Overwrite checksum value.
  fseek(copyFile, 0, SEEK_SET);
  fprintf(copyFile, "%d\n", checksum);

  fclose(copyFile);

  compare_checksum();
}

void compare_checksum()
{
  FILE *readFile = fopen("8-1.txt", "r");
  char str[25];
  char read_checksum = '\0', calculate_checksum = '\0';

  int line = 1;
  while (fgets(str, 25, readFile) != NULL)
  {
    // Since there is a checksum on the first line, it counts by excluding the first line.
    if (line != 1)
    {
      int i = 0;
      // Currently, str contains '\n', so exclude it.
      while (str[i] != '\n')
      {
        // using bitwise ExclusiveOR
        calculate_checksum ^= str[i];
        i++;
      }
    }
    else
    {
      int temp = atoi(str);
      read_checksum += temp;
    }
    line++;
  }
  fclose(readFile);

  printf("Checksum attached to the copy : %d\n", read_checksum);
  printf("Checksum calculated from copied data : %d\n\n", calculate_checksum);

  if (read_checksum == calculate_checksum)
  {
    printf("The result of comparing %d(attached) and %d(calculated) is the same.\n", read_checksum, calculate_checksum);
  }
  else
  {
    printf("The result of comparing %d(attached) and %d(calculated), they are not equal.\n", read_checksum, calculate_checksum);
  }
  printf("==========\n");
}
