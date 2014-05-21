//////////////////////////////////////////////////////////////////////////////////
// Stack.h
// - This is a templated Stack data structure. Stacks are just like linked lists
//   only with the restriction that you can only access the top (tail) of the list.
//   The most recent element added to the stack is the first to come off and is also
//   the only element you can access. This behaviour is know as "Last in, First out". 
//   Adding an element to the stack is called "pushing", removing an element is called 
//   "popping" and accessing the top element is called "peeking"
// - Be sure to read the test harness for this tutorial if you want to see the stack
//   in use
// - You'll need to understand pointers, templates, and linked lists for this tutorial. 
//   See my site for tutorials on all of these 
// - Note that we need to put all of our code into the header file, otherwise  
//   templating won't work
//////////////////////////////////////////////////////////////////////////////////

// IMPORTANT: This file is just a modified version of "LinkedList.h". I've removed all of the    //
// comments relating to the linked list so you only have to look at those relating to the stack. //
#pragma once

// We can just leave the node data structure as is. //
template <class DataType>
class Node
{
public:
	DataType m_Data;        
	
	Node<DataType>* m_Next; 
};

// This is the main Stack class. I have placed comments where things have been removed or changed. //
template <class DataType>
class Stack
{
private:
	// We still need our head and tail pointers. m_Head is needed for the destructor   //
	// and for the Pop() method. m_Tail is the top of our stack, so we really need it! //
	Node<DataType>* m_Head;   
	Node<DataType>* m_Tail;   

	int m_Size;   // number of nodes in our stack

public:
	// Our constructor stays the same, it just sets the Head and Tail pointers to NULL. //
	Stack()
	{
		m_Head = m_Tail = NULL;
		m_Size = 0;
	}

	// Our destructor stays the same too. //
	~Stack()
	{
		while(m_Head != NULL)
		{
			RemoveHead();	
		}
	}

	// AddHead() has been removed. You can't add an element to the bottom of a stack. //
	
	// AddTail() has been renamed to Push(). If you already understood the linked list tutorial, //
	// you understand how this function works. I left the comments in, just in case.             // 
	void Push(DataType data)
	{
		// Let's start by creating the new node to add to the list. //
		Node<DataType>* NewNode = new Node<DataType>;
		NewNode->m_Data = data;
		NewNode->m_Next = NULL;  // we're adding this node to the end, so there's nothing after it

		// Now we just point the current tail's pointer to the new node. We first have to check that m_Tail //
		// isn't NULL (if it is there won't be a pointer there to point to anything and we'll get a crash). //
		if (m_Size == 0)
		{
			// Nothing in the list yet, set m_Head and m_Tail to the new node. //
			m_Head = m_Tail = NewNode;
		}
		else
		{
			// There's something there, so we make it point to our new tail. We first set our current //
			// tail to point to our new tail. We then set m_Tail to point to the new tail node. //            
			m_Tail->m_Next = NewNode;
			m_Tail = NewNode;
		}

		// Now we just have to increment our size variable. //
		m_Size++;
	}

	// Insert() has been removed. We can't access the middle of a stack. //
	
	// RemoveHead() is now a private function. It's only used in the destructor and in Pop().  //
	// To maintain the behaviour of the stack, we don't want to let other people remove the    //
	// bottom of the stack. //
	
	// RemoveTail() has been renamed to Pop(). It does the same thing     //
	// however. I left the comments in for anyone who wants to read them. //
	void Pop()
	{
		// If the list is empty, just return. //
		if (m_Size == 0)
			return;

		// If there is only one node, we might as well just call RemoveHead() //
		if (m_Size == 1)
		{
			RemoveHead();  // good thing we didn't delete RemoveHead()
			return;
		}

		// To remove the tail, we'll create an iterator and move it to the node before the end. //
		Node<DataType>* itr = m_Head;

		while (itr->m_Next != m_Tail)
			itr = itr->m_Next;

		// Now we delete itr->m_Next because itr->m_Next points to the tail. We should then set itr->m_Next //
		// to NULL because itr is the new tail. Finally, we set m_Tail to point to the new tail. //
		delete itr->m_Next;
		itr->m_Next = NULL;
		m_Tail = itr;

		// If there was only one node in the list, we should make sure m_Tail and m_Head point to NULL. //
		if (m_Size == 1)
			m_Head = m_Tail = NULL;

		m_Size--;
	}

	// RemoveNode() has been removed. You can't remove the middle of a stack, only the top. //
	
	// GetFrontData() and GetNodeData() have been removed. You can only access the top of a stack. //
	
	// GetBackData() has been renamed to Peek() //
	DataType Peek()
	{
		if (m_Tail)
			return m_Tail->m_Data;
		else
			return 0;
	}	

	// GetSize() remains the most complex function of our stucture. //
	int GetSize()
	{
		return m_Size;
	}

private:
	// RemoveHead() is a private function now. It can't be used to remove //
	// the bottom of the stack from outside of this class declaration.    //
	// This function is only used in Pop() and the destructor.			  //
	void RemoveHead()
	{
		// If there is nothing in the list, we'll just return //
		if (m_Size == 0)
			return;

		// Otherwise, we set m_Head to point to the next node in the list (it'll be null if there's   //
		// nothing there). Notice that we store the node at m_Head temporarily while we reset the     //
		// m_Head pointer. Otherwise, we'd have no reference to the node and it would sit in memory   //
		// until the computer crashes or gets rebooted. Needless to say, that would be poor practice. //
		Node<DataType>* temp = m_Head;
		m_Head = m_Head->m_Next;	
		delete temp;

		// If the size of the structure is 1 at this point, we know that m_Head and m_Tail pointed to //
		// the same node, so we better tell m_Tail that there's nothing there anymore. //
		if (m_Size == 1)
			m_Tail = NULL;

		m_Size--;
	}
};

// Aaron Cox - 2004 //






