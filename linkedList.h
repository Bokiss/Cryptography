struct Node
{
  int data;
  struct Node *next;
};
struct Node* initializeList(struct Node** head)
{
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
	new_node->next = NULL;
	return new_node;
}
void insertlastNode(struct Node* new_node,struct Node* end)
{
	struct Node* parse;
	parse = end ;
	while( *parse->next != NULL)
	{
		printf("parse = %d",parse->data);
		parse = parse->next ;
		if(parse->next == NULL)
		{
			parse->next = new_node;
			new_node->next = NULL;
			printf("Added at end\n");
		}
	}
	
}
void popfirstNode(struct Node* start)
{

}