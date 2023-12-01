#include "FreeRTOS.h"
#include "list.h"

List_t MyList;

ListItem_t ListItem1;
ListItem_t ListItem2;
ListItem_t ListItem3;


int main(void)
{
	vListInitialise(&MyList);
	
	vListInitialiseItem(&ListItem1);
	ListItem1.xItemValue = 1;	
	
	vListInitialiseItem(&ListItem2);
	ListItem2.xItemValue = 2;
	
	vListInitialiseItem(&ListItem3);
	ListItem3.xItemValue = 3;
	
	vListInsert(&MyList, &ListItem1);
	vListInsert(&MyList, &ListItem2);
	vListInsert(&MyList, &ListItem3);
	
	for(;;);
}

