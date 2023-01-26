#include<stdio.h>
#include<stdlib.h>


/* define struct */
struct RadixNode
{
  int number, bucketNumber, radix;
  struct RadixNode *nextNode, *radNode;
};

typedef struct RadixNode *List;


/* Function Prototypes */
void printList(List);
void printLast(int, List, List);
void createBuckets(List);
void insertNode(List ,int);
void radixSort(List ,int);
void stitchBuckets(List, List, int);
void deleteNode(List);
void reset(List);
List newList();
int getBiggest(List);
int main(int argc, char** argv);


/*
 * Function to get the head of the linkedList.
 *
 * @return head of the linkedList.
 */
List newList(void)
{
  List headNode = NULL;
  headNode = malloc(sizeof(struct RadixNode));
  if(headNode == NULL)
  {
    printf("Erorr Allocating Memory for < newList(void) >");
    exit(EXIT_FAILURE);
  }
  headNode->number = -1;
  headNode->bucketNumber = -1;
  headNode->radix = 0;
  return headNode;
}


/*
 * Function to create a node in the linked list.
 *
 * @param headNode - List representing the head of the linkedList.
 */
void createBuckets(List headNode)
{
  int i;
  List currentNode = headNode, newNode;

  /* create ten buckets */
  for(i = 0; i < 10; i++)
  {
    newNode = calloc(1, sizeof(struct RadixNode));
    if(newNode == NULL)
    {
      printf("Error Allcating Memory for < createNode(List headNode) >");
      exit(EXIT_SUCCESS);
    }
    newNode->nextNode = NULL;
    newNode->radNode = NULL;
    newNode->number = 0;
    newNode->radix = 0;
    newNode->bucketNumber = i;
    currentNode->nextNode = newNode;
    currentNode = newNode;

  }

}


/*
 * Function inserts a node into the list.
 *
 * @param number - largest integer position.
 * @param list - List to insert into.
 *
 */
void insertNode(List list, int number)
{
  int remainder = number % 10;
  List tmp = NULL;

  list = list->nextNode;
  while(list->bucketNumber != remainder)
    list = list->nextNode;

  while(list->radNode != NULL)
    list = list->radNode;

  tmp = calloc(number, sizeof(struct RadixNode));
  if (tmp == NULL)
  {
    printf("Error Allocating memory for < insertNode(List list, int number) >");
    exit(EXIT_FAILURE);
  }
  tmp->number = number;
  tmp->radix = 0;
  tmp->bucketNumber = list->bucketNumber;
  list->radNode = tmp;

}


/*
 * Function to get the largest integer in the list.
 *
 * @param list - List to get number from.
 *
 * @return the number of positons for the biggest integer.
 */
int getBiggest(List list)
{
  int biggest = 0, count = 0;
  List tmp = list, current = NULL;

  tmp = tmp ->nextNode;
  while (tmp != NULL)
  {

    current = tmp;
    while(current != NULL)
    {
      if(biggest < current->number)
        biggest = current->number;

      current = current->radNode;
    }

    tmp = tmp->nextNode;
  }

  count = 0;
  while(biggest > 0)
  {
    count++;
    biggest /= 10;
  }
  return count;
}


/*
 * Function to resest the list.
 *
 * @param list- list to reset.
 */
void reset(List list)
{
  List tmp;

  list = list->nextNode;
  while(list != NULL)
  {
    tmp = list->radNode;
    while(tmp != NULL)
    {
      tmp->radix = 0;
      tmp = tmp->radNode;
    }
    list = list->nextNode;
  }

}


/*
 * Function to sort the list.
 *
 * @param list - list to sort.
 * @param biggestNum - Largest integer in list.
 *
 */
void radixSort(List list, int largestnum)
{
  List l1, l2, l3;
  int base = 10, number, i, position;

  for(i = 0; i < largestnum - 1; i++, base *= 10)
  {
    l2 = list;
    l2 = l2->nextNode;
    while(l2 != NULL)
    {
      l3 = l2;
      l1 = l2;

      l3 = l3->radNode;
      while(l3 != NULL)
      {
        number = l3->number;
        position = (number/base);
        position %= 10;

        if(l3->radix == 0)
        {
          deleteNode(l1);
          stitchBuckets(list, l3, position);
          l3 = l1;
        }
        else
          l1 = l1->radNode;


        l3 = l3->radNode;
      } /* end inner while loop */

      l2 = l2->nextNode;

    } /* end outer while loop */

    printf("\n\n S[%d]:\n\n", i + 1);
    printList(list);
    reset(list);

  } /* end for loop */

}


/*
 * Function to repostion a given node in the list.
 *
 * @param list - linkedList to reposition node from.
 * @param listPosition - List with positioning.
 * @param position - Integer of the correct position.
 *
 */
void stitchBuckets(List list, List listPosition, int position)
{
  List current = list, tmp = listPosition;

  current = current->nextNode;

  while(current->bucketNumber != position)
  {
    current = current->nextNode;
  }

  while(current->radNode != NULL)
  {
    current = current->radNode;
  }
  tmp->bucketNumber = position;
  tmp->radix = 1;
  tmp->radNode = 0;
  tmp->radNode = NULL;
  tmp->nextNode = NULL;
  current->radNode = tmp;
}


/*
 * Function to delete a node from the list.
 *
 * @param list - list to delete from.
 *
 */
void deleteNode(List list)
{

  List current = list;
  current->radNode = current->radNode->radNode;
}


/*
 * Function to print the list to stdout.
 *
 * @param list - list to print.
 *
 */
void printList(List list)
{
  List currentList = NULL, tmpList = list;
  int counter = 0;

  tmpList = tmpList->nextNode;
  while(tmpList != NULL)
  {
    printf("Bucket %d: ", counter);
    currentList = tmpList->radNode;
    while(currentList != NULL)
    {
      printf("%d,", currentList->number);
      currentList = currentList -> radNode;
    }
    printf("\n");
    counter++;
    tmpList=tmpList->nextNode;
  }

  printf("\n");
}


/*
 * Function to print the final "stitch" to show the sorted list.
 *
 * @param num - Largest number of integer positions
 */
void printLast(int num, List main, List tmp)
{

  printf("\n\n S[%d] = ", num);
  printf("{");
  main = main->nextNode;
  while(main != NULL)
  {
    tmp = main;
    while(tmp != NULL)
    {
      if(tmp->number != 0)
        printf("%d,", tmp->number);
      tmp = tmp->radNode;
    }
    main = main->nextNode;
  }
  printf("}\n\n");

}


/*
 * Function controls the flow of the program. Command-line arguments supplied as an array of character objects.
 *
 * @param argc - Number of arguments passed into the program at execution.
 * @param argv - Double pointer to array of arguments passed into program at execution.
 *
 * @return program execution status.
 */
int main(int argc, char** argv)
{

  int seed, numVal, low, high, biggestNum, i, num;
  List list = NULL, tmp = NULL;
  int *numbers = NULL;

  if (argc != 5)
  {
    printf("Invalid Number of arguments!\n");
    printf("Usage: ./MyProgram <seed> <numValues> <low> <high>\n");
    exit(EXIT_FAILURE);
  }

  seed = atoi(argv[1]);
  numVal = atoi(argv[2]);
  low = atoi(argv[3]);
  high = atoi(argv[4]);

  srand(seed);

  numbers = (int *) calloc(numVal, sizeof(int));

  printf("\n numbers to sort: {");
  for(i = 0; i < numVal; i++)
  {
    num = (rand() % (high - low)) + low;
    numbers[i] = num;
    printf("%d ", numbers[i]);
  }
  printf("}\n");

  list = newList();
  createBuckets(list);

  for(i = 0; i < numVal; i++)
    insertNode(list, numbers[i]);

  printf("\n [S0]:\n\n");
  printList(list);
  biggestNum = getBiggest(list);
  radixSort(list, biggestNum);
  printLast(biggestNum, list, tmp);

  free(list);
  free(numbers);

  return EXIT_SUCCESS;
}
