#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user
{
  char name[25];
  char email[20];
  char phoneNumber[13];
  int points;
};

typedef struct registeredResponse
{
  char phoneNumber[13];
  int status;
} registeredResponse;

struct user Users[100];
int usersCount = 0;

char Drinks[4][18] = {"Caramel Macchiato", "Cappucino", "Cafe Mocha", "Cafe Latte"};

int validateDrinkInput(char *drinkInput)
{
  for (int i = 0; i < 4; i++)
  {
    if (strcmp(drinkInput, Drinks[i]) == 0)
      return 1;
  }

  return 0;
}

int validatePhoneNumber(char *phoneNumber)
{
  if (strlen(phoneNumber) < 13 && strlen(phoneNumber) > 10)
    return 1;

  return 0;
}

int validateName(char *name)
{
  if (name < 5 && name > 25)
    return 0;

  char Mr[3];
  Mr[0] = name[0];
  Mr[1] = name[1];
  Mr[2] = name[2];
  Mr[3] = '\0';

  if (strcmp(Mr, "Mr.") == 0)
    return 1;

  char Mrs[4];
  Mrs[0] = name[0];
  Mrs[1] = name[1];
  Mrs[2] = name[2];
  Mrs[3] = name[3];
  Mrs[4] = '\0';
  if (strcmp(Mrs, "Mrs.") == 0)
    return 1;
}

int validateEmail(char *email)
{
  int emailLength = strlen(email);
  if (emailLength < 10 && emailLength > 20)
    return 0;

  for (int i = 0; i < emailLength; i++)
  {
    if (email[i] == '@')
    {
      break;
    }
    else
    {
      printf("Email Doesn't Include '@'");
      return 0;
    }
  }

  char dotCom[4];
  dotCom[0] = email[emailLength - 3];
  dotCom[1] = email[emailLength - 2];
  dotCom[2] = email[emailLength - 1];
  dotCom[3] = email[emailLength];
  dotCom[4] = '\0';

  if (strcmp(dotCom, ".com") == 0)
    return 1;

  char dotCoId[6];
  dotCoId[0] = email[emailLength - 5];
  dotCoId[1] = email[emailLength - 4];
  dotCoId[2] = email[emailLength - 3];
  dotCoId[3] = email[emailLength - 2];
  dotCoId[4] = email[emailLength - 1];
  dotCoId[5] = email[emailLength];
  if (strcmp(dotCoId, ".co.id") == 0)
    return 1;

  printf("Email Invalid");
  return 0;
}

registeredResponse CheckRegistered()
{
  registeredResponse res;
  char inputPhone[13];
  int inputPhoneStatus = 0;
  do
  {
    printf("Input Phone Number [10-13][numeric]: ");
    scanf("%s", &inputPhone);
    inputPhoneStatus = validatePhoneNumber(inputPhone);
  } while (inputPhoneStatus == 0);

  for (int i = 0; i < usersCount; i++)
  {
    if (strcmp(inputPhone, Users[i].phoneNumber) == 0)
    {
      strcpy(&res.phoneNumber, inputPhone);
      res.status = 1;

      return res;
    }
  }

  strcpy(&res.phoneNumber, inputPhone);
  res.status = 0;

  return res;
}

void OrderDrink(char *phoneNumber) {
  
}

void processUnregisteredOrder(char *phoneNumber)
{
  char inputName[25];
  int inputNameStatus = 0;

  do
  {
    printf("Input Name [5-25][Mr. |Mrs. ]: ");
    scanf("%s", &inputName);
    inputNameStatus = validateName(inputName);
  } while (inputNameStatus == 0);

  char inputEmail[20];
  int inputEmailStatus = 0;

  do
  {
    printf("Input Email [10-20][email format]: ");
    scanf("%s", &inputEmail);
    inputEmailStatus = validateEmail(inputEmail);
  } while (inputEmailStatus == 0);

  struct user temp;

  strcpy(&temp.email, inputEmail);
  strcpy(&temp.name, inputName);
  strcpy(&temp.phoneNumber, phoneNumber);

  Users[usersCount] = temp;
  usersCount++;


}

void processRegisteredOrder(char *phoneNumber)
{
}

void processOrder()
{
  registeredResponse registered = CheckRegistered();
  if (registered.status == 1)
  {
    processRegisteredOrder(registered.phoneNumber);
  }
  else
  {
    processUnregisteredOrder(registered.phoneNumber);
  }
}

int main()
{
  return 0;
}