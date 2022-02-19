#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int max,u,oldu,time,cronologia,r,counter;
typedef struct {
	char *contenuto;				//pointer to the content of the current row
	int s;					//s==1 means that the row has been written
} strriga;


typedef struct istruzione {
	strriga *old;			//type of operation that can do a modification, it can be c or d
	int max,ind1; //number of rows
	struct istruzione *next;
} stristruzione;


strriga *testariga=NULL;
stristruzione *testaistruzione=NULL;
stristruzione *inizioistruzione=NULL;
stristruzione **arrayistruzione;


void changeriga(int ind1, int ind2,int maxold){			//modifying the rows
	
	
	int i,size;
	char *temp;
	i=ind1-1;
	
	do{ 
		temp=calloc(1025,sizeof(char));			//i allocate a new memory space every time that i read
		if(fgets(temp,1025,stdin)!=NULL)
		if(*temp=='.')							//i stop when i find the dot
			{	
			free(temp);
				return;}
		else
		{	
			size=strlen(temp);
	

			temp[size-1]='\0';						//there were problems with the end of the sentence
			temp=realloc(temp,(size+1)*sizeof(char));	//it fixes some small errors

			(testariga+i)->contenuto=temp;
			
			(testariga+i)->s=1;
			

		}

		i++;
	}while(*temp!='.');
	free(temp);
	return;
}
void change( int ind1, int ind2){
	int maxold;
	maxold=max;
	if(ind2>max)
		{max=ind2;
			testariga=(strriga *)realloc(testariga,sizeof(strriga)*max);
		}
	changeriga(ind1,ind2,maxold);
	return;
}
int virgola(char *p){
	int v;
	for(v=0;p[v]!=',';v++)//i find where the comma is
		{}
		return v;
}




void aggiuntaistruzione(int ind1){			//it adds instructions to the list

	stristruzione *p;
	int i,len;
	

	p=calloc(1,sizeof(stristruzione));
	p->max=max;
	p->ind1=ind1;
	testaistruzione->next=p;
	testaistruzione=p;
	
	if(cronologia<1000)
		if((cronologia+1)%10==0)
		{
			testaistruzione->ind1=1;
			ind1=1;
		}
	else
		if((cronologia+1)%11==0)
		{
			testaistruzione->ind1=1;
			ind1=1;
		}
	if(cronologia<100)
		if((cronologia+1)%2==0)
		{
			testaistruzione->ind1=1;
			ind1=1;
		}
	testaistruzione->old=calloc(max-ind1+1,sizeof(strriga));


	for(i=0;i<max-ind1+1;i++){
		
				((testaistruzione->old)+i)->contenuto=(testariga+i+ind1-1)->contenuto;

	}
	
	cronologia++;
	if(cronologia%10==0)
	{	i=cronologia/10;
		i++;
		arrayistruzione=realloc(arrayistruzione,i*sizeof(stristruzione));
		arrayistruzione[i-1]=testaistruzione;	}
	return;
}

void cancellazione(int ind1,int ind2){

	int i,coda,j;
	strriga *p;
	char *temp;

	if(ind1==0)
		ind1++;
	if(ind2==0)
		return;
	if(ind2>max)						//a check that prevents to delete rows that don't exist
		ind2=max;
	coda=max-ind2;
	j=0;
	for(i=ind1-1;i<ind2&&i<max;i++)
		if((testariga+i)->s==1)
			{j++;					}
	for(i=ind2;i<max;i++)				//i don't do the double free because memory is not erased immediatly
		{(testariga+i)->s=0;		}

	memmove(testariga+ind1-1,testariga+ind2,coda*sizeof(strriga));

	if(max==1&&ind1==1&&ind2==1)
		{max=0;}						//corner case
	else
	{max=max-j;}
	if(max<0)
		max=0;
	testariga=(strriga *)realloc(testariga,sizeof(strriga)*max);
	for(i=0;i<max;i++)
		{(testariga+i)->s=1;
			}
	return;


}

void undo(int maxold){

	if(time==1)
		oldu=oldu-u;
	else
		oldu=cronologia-u;
	if(oldu<0)
		oldu=0;

	int i,j,len,rapido,array;
	
	testaistruzione=inizioistruzione;
	max=testaistruzione->max;

		if(oldu<1000)
		{rapido=oldu/10;
				rapido=rapido*10;
				if(oldu%10==0)
					rapido=rapido-10;
				}
		else
		{
			rapido=oldu/11;
				rapido=rapido*11;
				if(oldu%11==0)
					rapido=rapido-11;
		}
		if(oldu<100)
	{	rapido=oldu/2;
			rapido=rapido*2;
			if(oldu%2==0)
				rapido=rapido-2;}
			array=rapido/10;
			testaistruzione=arrayistruzione[array];

	for(i=array*10;i<oldu;i++){
		if(testaistruzione->next!=NULL)
		{testaistruzione=testaistruzione->next;
			if(i>rapido-1)
	{	max=testaistruzione->max;
			testariga=realloc(testariga,max*sizeof(strriga));
				for(j=0;j<max-testaistruzione->ind1+1;j++)
			{
				(testariga+j+testaistruzione->ind1-1)->contenuto=((testaistruzione->old)+j)->contenuto;
							(testariga+j+testaistruzione->ind1-1)->s=1;
			}}}
		else
		break;
	}

	u=0;
	time=1;
	r=0;
	counter=0;
	return;
}
void redo(int maxold){
	if(time==0)
		return;

	int i,len,j,rapido,array;
	char *temp;
	if(r==1)
		counter=counter-u;
	else
		counter=oldu-u; //u is negative

	if(counter>cronologia)
		{counter=cronologia;
			time=0;//i don't lose my history

		}
	oldu=counter;
		testaistruzione=inizioistruzione;
		if(counter<1000)
		{rapido=counter/10;
				rapido=rapido*10;
				if(counter%10==0)
					rapido=rapido-10;}
		else
			{rapido=counter/11;
				rapido=rapido*11;
				if(counter%11==0)
					rapido=rapido-11;}
		if(counter<100)
		{rapido=counter/2;
				rapido=rapido*2;
				if(counter%2==0)
					rapido=rapido-2;}

					array=rapido/10;
			testaistruzione=arrayistruzione[array];
			array=array*10;
	for(i=array;i<counter;i++){
		if(testaistruzione->next!=NULL)
		{testaistruzione=testaistruzione->next;
			if(i>rapido-1)
		{max=testaistruzione->max;
				testariga=realloc(testariga,max*sizeof(strriga));
						for(j=0;j<max-testaistruzione->ind1+1;j++)
				{
					(testariga+j+testaistruzione->ind1-1)->contenuto=((testaistruzione->old)+j)->contenuto;
								(testariga+j+testaistruzione->ind1-1)->s=1;
				}}}
		else
		break;
	}
	u=0;
	r=1;

	return;
}
void cancellamemoria(){

	if(r==1)
		{cronologia=counter;
			time=0;
			counter=0;
		return;}
	if(r==0){
		cronologia=oldu;
		time=0;
		counter=0;
		return;
	}
	int i,len;
	char *temp;
	stristruzione *p;

	do{
		for(i=0;i<inizioistruzione->max-inizioistruzione->ind1+1;i++)
			{	

				if(i<max)
				{	
					if(*(((inizioistruzione->old)+i)->contenuto)!=*((testariga+i)->contenuto))
					{	
						if(0>*(((inizioistruzione->old)+i)->contenuto))	//corner case
						free(((inizioistruzione->old)+i)->contenuto);
										}
				}else
				{	
					if(0>*(((inizioistruzione->old)+i)->contenuto))	//corner case
					{free(((inizioistruzione->old)+i)->contenuto);
									}
				}

			}
			free(inizioistruzione->old);
		p=inizioistruzione;
		inizioistruzione=inizioistruzione->next;
		free(p);
	}while(inizioistruzione->next!=NULL);




	time=0;
	testaistruzione=calloc(1,sizeof(stristruzione));
	testaistruzione->next=NULL;
	inizioistruzione=testaistruzione;
	inizioistruzione->max=max;
	inizioistruzione->ind1=1;
	inizioistruzione->old=calloc(max,sizeof(strriga));
	for(i=0;i<max;i++){
		
		len=strlen((testariga+i)->contenuto);
		temp=calloc(len+1,sizeof(char));
		strncpy(temp,(testariga+i)->contenuto,len);			//there was a problem with the heap and this fixes that
		temp[len]='\0';
		((testaistruzione->old)+i)->contenuto=temp;

	}
	cronologia=0;
	r=0;
	counter=0;
	return;
}
int main(){
char *input=NULL, *input2;
int l,i,p;

char c;

int v, ind1, ind2;	
char *temp;

testariga=malloc(sizeof(strriga));	//initialization
max=1;
(testariga+0)->contenuto=".\n";
u=0;
testaistruzione=calloc(1,sizeof(stristruzione));
testaistruzione->next=NULL;
inizioistruzione=testaistruzione;
inizioistruzione->max=0;
inizioistruzione->ind1=1;
arrayistruzione=calloc(1,sizeof(stristruzione));
arrayistruzione[0]=inizioistruzione;
p=0;
oldu=0;
time=0;
cronologia=0;
r=0;
counter=0;
do{			//reading of the command
	if(scanf("%ms",&input)!=EOF)
	{while(getchar()!='\n');}		
	if(*input=='q')
		break;
	l=strlen(input);
	
	c=input[l-1];
	if(c!='u')
	if(c!='r')
	{	v=virgola(input);
		temp=calloc(v,sizeof(char));				
		strncpy(temp,input,v);		//i look for the first row
		ind1=atoi(temp);			
		input2=&input[v+1];
		free(temp);
		temp=calloc(l-v-2,sizeof(char));
		strncpy(temp,input2,l-v-1);	//i look for the second row
		ind2=atoi(temp);
		free(temp);}


	if(c=='c')
			{

			if(time==1)
			cancellamemoria();
		

						change(ind1,ind2);
					
					aggiuntaistruzione(ind1);
				}
	if(c=='p'){
				
					
										// i begin to print
						if(ind1==0){				// corner case
						printf(".\n");
						ind1++;
						}

						for(i=ind1-1;i<ind2;i++){
						if(i<max)
								 { 
								 	
								 	fputs((testariga+i)->contenuto,stdout);
							 	printf("\n");
								}
						else
							{	
								printf(".\n");}

						}
						}
	if(c=='d'){
		
				if(time==1)
				cancellamemoria();
		
		
		cancellazione(ind1,ind2);

		aggiuntaistruzione(ind1);
	}
	if(c=='u'){
		temp=calloc(l-2,sizeof(char));
		strncpy(temp,input,l-1);
		u=atoi(temp);
		free(temp);
		undo(max);
	}
	if(c=='r'){
				temp=calloc(l-2,sizeof(char));
				strncpy(temp,input,l-1);
				
				u=-1*atoi(temp);
				free(temp);
				redo(max);
		
	}

}while(*input!='q');



	return 0;
}