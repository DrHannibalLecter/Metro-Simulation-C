#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10









typedef struct MetroStation{
    char name[20];
    double x;
    double y;
}MetroStation;


typedef struct MetroLine{
    char color[20];
    struct MetroStation MetroStations[SIZE];
}MetroLine;


typedef struct MetroSystem{
    char name[20];
    struct MetroLine MetroLines[SIZE];
}MetroSystem;


MetroSystem istanbul = {"istanbul", '\0'};



int equals(MetroStation s1, MetroStation s2){
    int i;
    for(i=0;s1.name[i];i++){
        if(s1.name[i]!=s2.name[i]){
            return 0;
        }
    }
    if(s2.name[i]){
        return 0;
    }
    return 1;
}

void addStation(MetroLine *ml, MetroStation mst){
    int i = 0;
    while(ml->MetroStations[i].name[0]){
        i++;
    }
    ml->MetroStations[i] = mst;
}

int hasStation(MetroLine ml, MetroStation mst){
    for(int i=0;ml.MetroStations[i].name[0];i++){
        if (equals(mst, ml.MetroStations[i])) {
            return 1;
        }
    }
    return 0;
}

MetroStation getFirstStop(MetroLine ml){
    return ml.MetroStations[0];
}

MetroStation getPreviousStop(MetroLine ml, MetroStation mst){
    for (int i = 0;ml.MetroStations[i].name[0];i++){
        if(equals(mst,ml.MetroStations[i]) && i!=0){
            return ml.MetroStations[i-1];
        }
    }
    MetroStation empty = {'\0'};
    return empty;
}

MetroStation getNextStop(MetroLine ml, MetroStation mst){
    for (int i = 0;ml.MetroStations[i+1].name[0];i++){
        if(equals(mst,ml.MetroStations[i])){
            return ml.MetroStations[i+1];
        }
    }
    MetroStation empty = {'\0'};
    return empty;
}

void addLine(MetroSystem *ms, MetroLine ml){
    int i = 0;
    while(ms->MetroLines[i].color[0]){
        i++;
    }
    ms->MetroLines[i] = ml;
}

void printLine(MetroLine ml){
    for (int i=0;ml.MetroStations[i].name[0];i++){
        printf("%s\n",ml.MetroStations[i].name);
    }
}

void printPath(MetroStation mstar[]){
    for (int i=0;mstar[i].name[0];i++){
        printf("%s\n",mstar[i].name);
    }
}

double getDistanceTravelled(MetroStation mstar[]){
    double a = 0;
    int i =1;
    while (mstar[i].name[0]){
        //2 points distance formula
        a += sqrt((pow(((mstar[i].x)-(mstar[i-1].x)),2)+pow((mstar[i].y-mstar[i-1].y),2)));
        i++;
    }
    return a;
}

MetroStation findNearestStation(MetroSystem ms, double x, double y){
    MetroStation tmp;
    MetroStation ret={'\0'};
    double a;
    double min = 0;
    for (int i = 0;ms.MetroLines[i].color[0];i++){
        tmp = getFirstStop(ms.MetroLines[i]);
        while(tmp.name[0]){
            a = sqrt((pow(((tmp.x)-x),2)+pow(((tmp.y)-y),2)));
            if (equals(tmp, getFirstStop(ms.MetroLines[0])) || min>a){
                ret=tmp;
                min = a;
            }
            tmp=getNextStop(ms.MetroLines[i],tmp);
        }
    }
    return ret;
}

void getNeighboringStations(MetroSystem ms, MetroStation mst, MetroStation neighboringStations[]){
    int a = 0;
    MetroStation tmp;
    for (int i = 0;ms.MetroLines[i].color[0];i++){
        tmp = getPreviousStop(ms.MetroLines[i],mst);
        if(tmp.name[0]!='\0'){
            neighboringStations[a]=tmp;
            a++;
        }
        tmp = getNextStop(ms.MetroLines[i],mst);
        if(tmp.name[0]!='\0'){
            neighboringStations[a]=tmp;
            a++;
        }
    }
}

void recursiveFindPath(MetroStation start, MetroStation finish, MetroStation partialPath[], MetroStation bestPath[]){
    for(int i=0;partialPath[i].name[0];i++){
        if (equals(start, partialPath[i])) {
            return;
        }
    }
    if(equals(start, finish)) {
        int b=0;
        while (partialPath[b].name[0]) {
            bestPath[b] = partialPath[b];
            b++;
        }
        bestPath[b]=finish;
        return;
        printf("lo");
    }
    MetroStation neighbors[SIZE]={'\0'};
    MetroStation currentPath[SIZE] = {'\0'};
    getNeighboringStations(istanbul, start, neighbors);
    for(int i=0; neighbors[i].name[0]; i++){
        MetroStation dp[SIZE]={'\0'};
        int a =0;
        while (partialPath[a].name[0]){
            dp[a]=partialPath[a];
            a++;
        }
        dp[a]=start;
        recursiveFindPath(neighbors[i], finish, dp, currentPath);
        if(currentPath[0].name[0]){
            if(getDistanceTravelled(bestPath)> getDistanceTravelled(currentPath) || !(bestPath[0].name[0])){
                for (int j = 0;currentPath[j].name[0];j++) {
                    bestPath[j] = currentPath[j];
                }
            }
        }
    }
}

void findPath(MetroStation mst1 , MetroStation mst2, MetroStation path[]){
    MetroStation partialPath[SIZE]={'\0'};
    recursiveFindPath(mst1, mst2, partialPath, path);
}














































//Declare a MetroSystem with the name of istanbul and an empty content.
//MetroSystem istanbul = {"istanbul", '\0'};

int main()
{
    double myX=1, myY=2;
    double goalX=62, goalY=45;

    // define 3 metro lines, 9 metro stations, and an empty myPath
    MetroLine red={'\0'}, blue={'\0'}, green={'\0'};
    MetroStation s1, s2, s3, s4, s5, s6, s7, s8, s9;
    MetroStation myPath[SIZE]={'\0'};

    strcpy(red.color, "red");
    strcpy(blue.color, "blue");
    strcpy(green.color, "green");


    strcpy(s1.name, "Haydarpasa"); 		s1.x=0; 	s1.y=0;
    strcpy(s2.name, "Sogutlucesme"); 	s2.x=10; 	s2.y=5;
    strcpy(s3.name, "Goztepe"); 		s3.x=20; 	s3.y=10;
    strcpy(s4.name, "Kozyatagi"); 		s4.x=30; 	s4.y=35;
    strcpy(s5.name, "Bostanci"); 		s5.x=45; 	s5.y=20;
    strcpy(s6.name, "Kartal"); 			s6.x=55; 	s6.y=20;
    strcpy(s7.name, "Samandira"); 		s7.x=60; 	s7.y=40;
    strcpy(s8.name, "Icmeler"); 		s8.x=70; 	s8.y=15;

    //Add several metro stations to the given metro lines.
    addStation(&red, s1); addStation(&red, s2); addStation(&red, s3); addStation(&red, s4); addStation(&red, s5); addStation(&red, s8);

    addStation(&blue, s2); addStation(&blue, s3); addStation(&blue, s4); addStation(&blue, s6); addStation(&blue, s7);

    addStation(&green, s2); addStation(&green, s3); addStation(&green, s5); addStation(&green, s6); addStation(&green, s8);

    // Add red, blue, green metro lines to the Istanbul metro system.
    addLine(&istanbul, red);
    addLine(&istanbul, blue);
    addLine(&istanbul, green);

    // print the content of the red, blue, green metro lines
    printLine(red);
    printLine(blue);
    printLine(green);


    // find the nearest stations to the current and target locations
    MetroStation nearMe = findNearestStation(istanbul, myX, myY);
    MetroStation nearGoal = findNearestStation(istanbul, goalX, goalY);

    printf("\n");
    //printf("%f", getDistanceTravelled(red.MetroStations));

    printf("The best path from %s to %s is:\n", nearMe.name, nearGoal.name);

    // if the nearest current and target stations are the same, then print a message and exit.
    if(equals(nearMe, nearGoal)){
        printf("It is better to walk!\n");
        return 0;
    }
    /*if(equals(red.MetroStations[4],green.MetroStations[2])){
        MetroStation ne[SIZE]={'\0'};
        getNeighboringStations(istanbul,green.MetroStations[1],ne);
        printPath(ne);
    }*/
    // Calculate and print the myPath with the minimum distance travelled from start to target stations.
    findPath(nearMe, nearGoal, myPath);
    if(strlen(myPath[0].name) == 0)
        printf("There is no path on the metro!\n");
    else{
        printPath(myPath);
    }

    return 0;

}
