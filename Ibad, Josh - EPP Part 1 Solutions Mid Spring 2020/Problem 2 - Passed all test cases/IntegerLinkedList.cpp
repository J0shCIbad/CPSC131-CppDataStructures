/**
 * @author	Josh Ibad
 *	CWID:	888880036
 * 	Date:	EPP Mid-Spring 2020, 10 AM
 */
 // ADD ANSWER TO THIS FILE

#include "IntegerLinkedList.h"

bool IntegerLinkedList::checkList() {
	SNode *currNode = head;
	int testInt = head->elem;
	while(currNode != nullptr){
		if( currNode->elem != testInt){
			return false;
		}
		currNode = currNode->next;
	}
	return true;
}

bool IntegerLinkedList::checkRecurse (SNode *ptr) {
  // COMPLETE THIS FOR PROBLEM 3


}

void IntegerLinkedList::addFront(int x) {
  SNode *tmp = head;
	head = new SNode;
	head->next = tmp;
	head->elem = x;
}

// recursion helper function called from main for PROBLEM 3
bool IntegerLinkedList::checkRecurseHelper () {
  return checkRecurse(head);
}
