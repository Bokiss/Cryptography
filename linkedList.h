struct Node
{
  int data;
  struct Node *next;
};
void append(struct Node** head,int data)
{
	//allocate new node
	printf("\n----------\n");
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
	struct Node* parse = *head;

	//save data to new node
	new_node->data = data;
	//it will be last node so ->next = NULL
	new_node->next = NULL;

	//if its the FIRST node
	if(*head == NULL)
	{
		printf("Head NULL\n");
		*head = new_node;
		return;
	}
	//else go to last node
	while( parse->next != NULL)
	{
		printf("append-parsing\n");
		parse = parse->next ;
	}
	//make the last point to new node
	parse->next = new_node;
	return;
}
int popfirstNode(struct Node** head)
{
	struct Node* parse = *head;
	//if list is empty
	if(*head == NULL)
	{
		printf("List is empty\n");
		return -1;
	}
	//copy data
	int data = (*head)->data;
	*head = (*head)->next;
	free(parse);
	return data;
	//(*head)

}
void printList(struct Node* head)
{
	while(head != NULL)
	{
		printf("d = %d\n",head->data);
		head = head->next;
	}
}