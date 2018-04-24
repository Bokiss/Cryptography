struct Node
{
  mpz_t data;
  struct Node *next;
};
void append(struct Node** head,mpz_t data)
{
	//allocate new node
	printf("\n----------\n");
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
	struct Node* parse = *head;

	//save data to new node
	mpz_init_set(new_node->data,data);
	//new_node->data = data;
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
void popfirstNode(struct Node** head,mpz_t data)
{
	struct Node* parse = *head;
	//if list is empty
	if(*head == NULL)
	{
		printf("List is empty\n");
		mpz_set_d(data,-1);
		return;
	}
	//copy data
	mpz_set(data,(*head)->data);
	//int data = (*head)->data;
	//move head to next node
	*head = (*head)->next;
	//free curent head
	free(parse);
	return ;
	//(*head)

}
void printList(struct Node* head)
{
	while(head != NULL)
	{
		gmp_printf("d = %Zd\n",head->data);
		head = head->next;
	}
}