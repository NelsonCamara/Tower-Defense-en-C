#include "Utils.h"



int pointInZone (Point checkPoint,Point centerPoint,int radiusZone){
    if((checkPoint.i >= centerPoint.i -radiusZone && checkPoint.i <= centerPoint.i +radiusZone )
        &&(checkPoint.j >= centerPoint.j -radiusZone && checkPoint.j <= centerPoint.j +radiusZone )){
            return 0;
        }
    else return 1;

}


int posFlInZone(float xPos,float yPos,float centerPointX,float centerPointY,float radiusZone){
    if((xPos >= centerPointX-radiusZone && xPos <= centerPointX+radiusZone) 
        && (yPos >=centerPointY-radiusZone && yPos <= centerPointY + radiusZone)
    )   return 0;

    else return 1;

}



int compareFlPoints(float p1X,float p1Y,float p2X,float p2Y){
    if((p1X == p2X) &&(p1Y == p2Y)) return 0;
    else return 1;
}


TimedEvent* newTimedEvent(double frametime,EventType type){
    TimedEvent* tEv;
    tEv = malloc(sizeof(TimedEvent));
    if(tEv == NULL) {
        fprintf(stderr,"MEM ERROR");
        exit(EXIT_FAILURE);
    }
    else{
        switch (type)
        {
            case EVENT_TYPE_DENDRO:
                tEv->duration = 10;
                tEv->frequency = 0.5;
                tEv->elapsed_since_last_event=0;
                tEv->elapsed_total = 0;
                tEv->active =true;
                break;
            case EVENT_TYPE_PYRO:

                break;
            case EVENT_TYPE_HYDRO:
                tEv->duration = 10;
                tEv->frequency = 0;
                tEv->elapsed_since_last_event=0;
                tEv->elapsed_total = 0; 
                tEv->active =true;
                break;
            case PYRO_AND_DENDRO:

                break;
            case PYRO_HYDRO:
                tEv->duration = 5;
                tEv->frequency = 0;
                tEv->elapsed_since_last_event=0;
                tEv->elapsed_total = 0;
                tEv->active = true;
                break;
            case DENDRO_HYDRO:
                tEv->duration = 3;
                tEv->frequency = 0;
                tEv->elapsed_since_last_event=0;
                tEv->elapsed_total = 0;
                tEv->active = true;
                break;
            default:
                break;
        }
    }
    return tEv;

}



void showTimedEvent(TimedEvent tEv){
    printf("---------TIMED EVENT----------\n");
    printf("Frequency : %0.3f\n",tEv.frequency);
    printf("Duration : %0.3f\n",tEv.duration);
    printf("Last event : %0.3f\n",tEv.elapsed_since_last_event);
    printf("Elapsed: %0.3f\n",tEv.elapsed_total);
}


void showEventType(EventType type){
    printf("------------EVENT TYPE-------------\n");
    switch (type)
    {
    case EVENT_TYPE_PYRO:
        printf("PYRO\n");
        break;
    case EVENT_TYPE_HYDRO:
        printf("HYDRO\n");
        break;
    case EVENT_TYPE_DENDRO:
        printf("DENDRO\n");
        break;
    case PYRO_AND_DENDRO:
        printf("PYRO AND DENDRO\n");
        break;
    case PYRO_HYDRO:
        printf("PYRO AND HYDRO\n");
        break;
    case DENDRO_HYDRO:
        printf("DENDRO HYDRO\n");
        break;
    default:
        break;
    }
}




void showElementalEvent(ElementalEvent event){
    printf("--------------ELEMENTAL EVENT----------------\n");
    printf("ShootTint :%d\n",event.shootTint);
    printf("ShootLevel :%d\n",event.shootLevel);
   

    showTimedEvent(*(event.timedEvent));
    showEventType(event.type);
     


}




int pointInWay(Point point,Point *way,int taille){
    for(int i =0;i<taille;i++){
        if(point.i == way[i].i && point.j== way[i].j) return 1;
    }
    return 0;
}



bool isAllDigits(const char *str){
    if (str == NULL || *str == '\0') {
        return false;
    }

    while (*str) {
        if (!isdigit((unsigned char)*str)) {
            return false;
        }
        str++;
    }

    return true;

}