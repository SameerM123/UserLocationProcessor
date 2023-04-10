#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define false 0
#define true 1

  typedef struct position{
    double lat;
    double lon; 
    double alt;
 } tracking;

typedef struct person{ // what a person has
    char name[100];
    tracking position; //position in x (lat), y(long), z (alt)
    double time; //time in nano seconds
}profile;

typedef struct user_t{ //main GPS system
    profile our_user; 
    profile other_users[100]; //here is the array of profiles
}GPS; 

typedef struct distance_calc{ //determines closest person 
    char name[100];
    double distance; 
}distance_from_user; 

void scan_user_prepper(profile *empty_user,FILE *file, profile *our_user, int *flag); //make sure to pass the strcuture as an address in main function
void scan_user(tracking position, double time, profile *users);
distance_from_user math(profile *users, profile *other);
distance_from_user sort (distance_from_user *arrList, int size);

//main just calls these functions
int main(){
FILE *file;
char fnamer[1000]=""; //Storing File Path/Name
int flag = false;
printf("\n\nPlease Enter the list of other people: \n");
scanf("%s",&fnamer);

file=fopen(fnamer,"r");
        if(file==NULL)
	{
		printf("\n%s\" File NOT FOUND!",fnamer);
	}
    GPS system;
    char people[10]; //store the first character in the file 
    
    //get the first line which is # of others
    fgets(people, 10, file); 
    int numOfPeople = atof(people);

    distance_from_user newlist[numOfPeople];
    

    for(int i = 0; i <= numOfPeople; i++){
      //gets information of everyone including: name, time, and position.
      scan_user_prepper(&system.other_users[i], &(*file), &system.our_user, &flag); 

    newlist[i]  = math(&system.our_user, &system.other_users[i]);
    }
distance_from_user winner = newlist[0];
  for (int i = 0; i < numOfPeople - 1; i++){
    if(winner.distance > newlist[i+1].distance){ //if the second stance is smaller
      winner = newlist[i+1];
    }
  //   distance_from_user  cheat[] = {newlist}; //double pointer here I cant just I just cant

  // distance_from_user winningName = sort(&cheat, numOfPeople);
  // printf("%s is %1.2fm away from you", winningName.name, winningName.distance);
  }
  printf("%s is %1.2fm away from you", winner.name, winner.distance);
}
//gonna pass the first 4 lines of the file
void scan_user_prepper(profile *empty_user,FILE *file, profile *our_user, int *flag){ // (empty user, file, *our_user)
  tracking new_user_position;
    char line[100];
    double time;
    double lat; 
    double lon; 
    double alt; 
    tracking me;

  //for our user
  if(*flag == false){
    printf("What is your time?\n");
    scanf("%lf", &time);
    printf("What is your latitude?\n");
    scanf("%lf", &lat);
    printf("What is the longitude of the user?\n");
    scanf("%lf", &lon);
    printf("What is the altitude of the user?\n");
    scanf("%lf", &alt);
    our_user->time = time;
    me.lat = lat;
    me.lon = lon;
    me.alt = alt;
    scan_user(me, time, our_user);
    *flag = true;
  }

// name - > time -> lat -> lon -> alt
  for(int i = 0; i < 5; i++){
     fgets(line, 120, file);
     switch (i)
     {
        case 0:
          strcpy(empty_user->name, line); 
          break;

        case 1:
          time = atof(line); 
          break;

        case 2:
          new_user_position.lat = atof(line); 
          break;

        case 3:
          new_user_position.lon = atof(line); 
          break;

        case 4:
          new_user_position.alt = atof(line); 
          break;
     }
  }
  scan_user(new_user_position, time, &(*empty_user));
}

void scan_user(tracking position, double time, profile *users){
  users->position = position;
  users->time = time;
}

//POPULATES OTHER'S PROFILES, TO BE PUT INTO GPS IN MAIN
distance_from_user math(profile *users, profile *other){

  double totalLat = (users->position.lat) - (other->position.lat);
  double totalLon = (users->position.lon) - (other->position.lon);
  double totalAlt = (users->position.alt) - (other->position.alt);

  double resultant = sqrt(pow(totalLat, 2)+pow(totalLon, 2)+pow(totalAlt, 2));

  //section organizes the distances of other people with their names, popualte into list of distance_from_user
  distance_from_user temp;
  distance_from_user* pttemp = &temp; 
  strcpy(pttemp->name,  other->name); 
  pttemp->distance = resultant;  
  return(temp);
}

//finds the smallest distance with the name attached
// distance_from_user sort (distance_from_user arrList[], int size){
  
//   distance_from_user winner = *arrList;

//   for (int i = 0; i < size - 1; i ++){
//     if(arrList->distance > (arrList + 1)->distance){ //if the second stance is smaller
//       winner = *arrList;
//     }
//     else{
//       continue;
//     }
// return(winner);
//   }
// }