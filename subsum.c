#include <stdlib.h>  // just to define NULL ptr

typedef struct __subsum { //list element containing information about subarray sum
	int sum;
	int start; // summing from start
	int end;  // to end (not including end itself)
	struct __subsum *next;
} subsum;


subsum ss_EMPTY =  {0,0,0,NULL}; //just an 'empty' element

subsum * ss_init(int* arr, int len){ //initialize a lsit from an array

	subsum* ptr; //pointer to subsum strucc

	subsum* ssarr = calloc(sizeof(subsum),len);
	subsum curr;
	int i;
	
	for (i=0; i<len; i++){ //we loop through arr, assigning to curr and linking list elements
		curr.sum= arr[i]; //we consider each individual element as a "sum"
		curr.start = i;
		curr.end = i+1;
		if (i+1 <len){
			curr.next = &ssarr[i+1];
		}
		else {
			curr.next = NULL;
		}
		ssarr[i] =curr;
	}
	return ssarr;
}

void ss_merge(subsum* ptrfirst){

	subsum first = *ptrfirst;
	subsum sec = *(first.next);


	first.sum= first.sum + sec.sum; //add up 
	first.end = sec.end;   // extend bounds
	first.next = sec.next; //shortcircuit to the next one, sec is now unaccesible should i use free now?
	*ptrfirst = first;  // save changes
	return;  //done
}


int ss_single(subsum * ssptr){  // return nonzero if something is done,else return zero
	int flag=0;

	subsum this = *ssptr;
	subsum next;


	if (this.next == NULL) // the end, nothing to do here
		return flag;
	else{
		next= *(this.next);
		if (next.sum* this.sum >= 0 )  //merge sums of the same sign or merge with zeros
			{ss_merge(&this);
			flag++;
		}
	}	
	
	*ssptr = this; //SAVE chagnes! (if any)
	return flag;
	//note to self better not to include loops inside here for  modularity
}


int ss_triple(subsum * ssptr, int max){

	int flag = 0;

	subsum this = *ssptr; 
	subsum next;
	subsum third;

	

	if (this.next != NULL && (*(this.next)).next != NULL){  
		//check if theres room for this merge
		next=*this.next;
		third = *next.next;
		
	}
	else {return flag;} //if no room just go back

	int sum1 = this.sum, sum2 = next.sum , sum3 = third.sum;

	if (sum1 > 0 && sum2 < 0 && sum3 > 0 && sum1 + sum2 >= 0 && sum2 + sum3 >= 0 ) 
	{	// we merge a small trough between two ups 
		ss_merge(&this);
		ss_merge(&this);
		flag++;
		*ssptr = this;
		return flag;
	}

	if (sum1 < 0 && sum2 > 0 && sum3 < 0 && sum2 < max && sum1 + sum2 <= 0 && sum2 + sum3 <= 0 )
	{ //merge a small positive between two negs, if the small positive is actually small (<max)
		ss_merge(&this);
		ss_merge(&this);
		flag++;
		*ssptr = this;
		return flag;
	}

	return flag;
}


subsum ss_find(subsum * ss){
	subsum * curr; //cursor thing poitner
	subsum maxcopy={0,0,0,NULL};
	int max;
	int flag;
	subsum this;
	curr= ss; //initialzie to the beginning of the list
	max= (*curr).sum;  //initialzie max
	maxcopy= *curr;
	while(1){
		
		while(ss_single(curr)){
			if((*curr).sum >= max){
				max= (*curr).sum;
				maxcopy = *curr;
			} 
				}
		if((*curr).next==NULL)
			break; //if we reached the end, get out of loop
		else
			{curr=((*curr).next);
			if((*curr).sum >= max){
				max= (*curr).sum;
				maxcopy = *curr;
			} 
		} //take a step	and actualize max if needed

	}

	curr=ss; // we go back to the initial element of our list
	// at this point the list should be an alternating sequence of positives and negatives


	flag=0;
	while(1){
		
		while(ss_triple(curr,max)){
				if((*curr).sum >= max){
					max= (*curr).sum;
					maxcopy = *curr;
				} 
			flag++;}
		if((*curr).next==NULL){

			if (flag){
				//completed cylce and we have done some work, have to go back to te beginning
				curr=ss;
				flag=0; //reset counter
			}
			else{
				break; // completed a cycle without doing anything, we reached the end
			}
		}
		else
			{curr=((*curr).next);} //take a step	 

	}
	if (max != maxcopy.sum)
		printf("OOPS! i effed up somehow?\n");
	return maxcopy;
}

subsum maxsubarr(int* arr, int len){ // takes an array and its length, gives the maximum subarray sum
	subsum* ssarr;
	subsum res; //load result into here later
	ssarr = ss_init(arr,len); //load stuff into ssarr;
	res= ss_find(ssarr); // process list ssarr, copy result into res
	

	free(ssarr); //free space
	if(res.sum<=0){
		printf("Seems liek your array only contains negative or zero terms,"
				" So this algorirthms fails in those cases, luckily you "
				 "just need to find the greatest term in your array to find the real asnwer\n"
				 " or just take the empty sequence as an answer i guess!\n");
		res= ss_EMPTY;	 
	}
	return res;
}
