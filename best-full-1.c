/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {		//��� ����ü
	int key;				//Ű��
	struct node *left;		//���� �ڽ� ���
	struct node *right;		//������ �ڽ� ���
} Node;

int initializeBST(Node** h);		//�̿� Ž�� Ʈ�� ����

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */				//���� ��ȸ Ű�� ���
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */			//���� ��ȸ Ű�� ���
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */			//���� ��ȸ Ű�� ���
int insert(Node* head, int key);  /* insert a node to the tree */					//��� ����
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */	//������� ����
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */		//��ȯ�� Ž��
Node* searchIterative(Node* head, int key);  /* search the node for the key */		//�ݺ��� Ž��
int freeBST(Node* head); /* free all memories allocated to the tree */				//Ʈ���� ��ü�� �Ҵ�� �޸� ����
void freeNode(Node* ptr);	//���� �� �ڽ� ���鿡 �Ҵ�� �޸� ����(���α׷� ����ø� ���� �ϰ� ���ɶ� �ڽĳ����� NULL�̴�)
/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;	//head��� ����
	Node* ptr = NULL;	/* temp */
	printf("[----- [����ȭ] [2019038062] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");		//�޴����
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");	
		scanf(" %c", &command);		//�޴� ����

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);	//Ʈ�� ����
			break;
		case 'q': case 'Q':
			freeBST(head);			//Ʈ���� �Ҵ�� �޸� ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");	//��� ����
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");	//�Է��ϴ� key���� ������� ����
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':			//�ݺ��� Ž��
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':			//��ȯ�� Ž��
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':			//���� ��ȸ Ű�� ���
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':			//���� ��ȸ	Ű�� ���
			preorderTraversal(head->left);
			break;
		case 't': case 'T':			//���� ��ȸ Ű�� ���
			postorderTraversal(head->left);
			break;
		default:					//�޴� �̿��� �ٸ� �� �Է� �� �������� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');		//q�� Q�� �Է¹����� �ݺ��� ����

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)      //tree�� �����Ǿ� �ִٸ�
		freeBST(*h);    //�Ҵ�� �޸� ����

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));   //Ʈ���� head �����޸� �Ҵ�
	(*h)->left = NULL;	/* root */      //Ʈ���� head�� left�� root
	(*h)->right = *h;       //Ʈ���� head�� right�� �ڱ� �ڽ��� ����Ŵ
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)		//���� ��ȸ
{
	if(ptr) {		//ptr�� NULL�� �ƴ϶�� �ݺ�
		inorderTraversal(ptr->left);	//ptr�� ���� �ڽĳ�� ���� ��ȸ
		printf(" [%d] ", ptr->key);		//ptr�� Ű�� ���
		inorderTraversal(ptr->right);	//ptr�� ������ �ڽĳ�� ���� ��ȸ
	}
}

void preorderTraversal(Node* ptr)		//���� ��ȸ
{
	if(ptr) {		//ptr�� NULL�� �ƴ϶�� �ݺ�
		printf(" [%d] ", ptr->key);		//ptr�� Ű�� ���
		preorderTraversal(ptr->left);	//ptr�� ���� �ڽĳ�� ���� ��ȸ
		preorderTraversal(ptr->right);	//ptr�� ������ �ڽĳ�� ���� ��ȸ
	}
}

void postorderTraversal(Node* ptr)		//������ȸ
{
	if(ptr) {
		postorderTraversal(ptr->left);	//ptr�� ���� �ڽĳ�� ���� ��ȸ
		postorderTraversal(ptr->right);	//ptr�� ������ �ڽĳ�� ���� ��ȸ
		printf(" [%d] ", ptr->key);		//ptr�� Ű�� ���
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));        //���ο� ��� ���� �޸��Ҵ�
	newNode->key = key;             //���ο� ��忡 �Է¹��� Ű�� ����
	newNode->left = NULL;           //���ο� ����� �ڽ� ���� ���� ����
	newNode->right = NULL;

	if (head->left == NULL) {       //Ʈ���� ��尡 ���ٸ�
		head->left = newNode;       //root�� ���ο� ���
		return 1;       //�Լ� ����
	}

	/* head->left is the root */
	Node* ptr = head->left;     //ptr�� root

	Node* parentNode = NULL;    //�θ��带 ������ ����ü����
	while(ptr != NULL) {    //�θ��尡 ���ٸ� �ݺ� ����

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;   //Ű���� ���ٸ� �Լ� ����

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;   //ptr�� �θ��尡 ��

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)      //ptr�� Ű���� ���ο� ����� Ű������ �۴ٸ�
			ptr = ptr->right;   //ptr�� ������ ��尡 ��
		else                    //ptr�� Ű���� ���ο� ����� Ű������ ũ�ٸ�
			ptr = ptr->left;    //ptr�� ���� ��尡 ��
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)           //�θ����� Ű���� ���ο� ����� Ű������ Ŭ ��
		parentNode->left = newNode;     //�θ����� left�� ���ο� ��带 ����Ŵ
	else                                //�θ����� Ű���� ���ο� ����� Ű������ �۰ų� ������
		parentNode->right = newNode;    //�θ����� right�� ���ο� ��带 ����Ŵ
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {                 //����Ʈ�� ������ ���� �ʾ�����
		printf("\n Nothing to delete!!\n");         //�������� ���
		return -1;      //�Լ� ����
	}

	if (head->left == NULL) {           //root�� ������
		printf("\n Nothing to delete!!\n");         //�������� ���
		return -1;      //�Լ� ����
	}

	/* head->left is the root */
	Node* ptr = head->left;     //ptr�� root�� ����Ŵ


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;    //�θ��带 ������ ����ü ����

	while(ptr != NULL) {        //ptr�� NULL�϶� �ݺ� ����

		if(ptr->key == key) {   //ptr�� Ű���� �Է¹��� Ű���� ����
			if(ptr->left == NULL && ptr->right == NULL) {   //ptr�� �ڽĳ�尡 ���ٸ�

				/* root node case */
				if(parentNode == head)      //�θ��尡 head����϶�
					head->left = NULL;      //root�� NULL

				/* left node case or right case*/
				if(parentNode->left == ptr)     //�θ����� left�� ptr�϶�
					parentNode->left = NULL;    //�θ����� left�� NULL�� �ٲ���
				else                            //�θ����� right�� ptr�϶�
					parentNode->right = NULL;   //�θ����� right�� NULL�� �ٲ���

				free(ptr);      //ptr�� �Ҵ�� �޸� ����
			}
			else {      //ptr�� �ڽĳ�尡 �ִٸ�
				printf("the node [%d] is not a leaf \n", ptr->key);     //�������� ���
			}
			return 1;   //�Լ�����
		}

		/* keep the parent node */
		parentNode = ptr;       //�θ���� ptr�� ��

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)      //ptr�� Ű���� �Է¹��� Ű������ �۴ٸ�
			ptr = ptr->right;   //ptr�� ptr�� ������ �ڽ� ��尡 ��
		else                    //ptr�� Ű���� �Է¹��� Ű������ ũ�ų� ���ٸ�
			ptr = ptr->left;    //ptr�� ptr�� ���� �ڽ� ��尡 ��


	}

	printf("Cannot find the node for key [%d]\n ", key);        //������ ��带 ã�� ��������� ���

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)     //ptr�� NULL�̸�
		return NULL;    //NULL����

	if(ptr->key < key)  //ptr�� Ű���� �Է¹��� Ű������ �۴ٸ�
		ptr = searchRecursive(ptr->right, key); //searchRecursive()�Լ� ���ȣ�� (ptr�� ������ �ڽĳ�带 ���ڷ� ȣ��)
	else if(ptr->key > key) //ptr�� Ű���� �Է¹��� Ű������ ũ�ٸ�
		ptr = searchRecursive(ptr->left, key);  //searchRecursive()�Լ� ���ȣ��(ptr�� ���� �ڽĳ�带 ���ڷ� ȣ��)

	/* if ptr->key == key */
	return ptr;         //ptr�� Ű���� �Է¹��� Ű���� ���ٸ� ptr�� ����

}
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;     //ptr�� root

	while(ptr != NULL)          //ptr�� NULL�̸� �ݺ� ����
	{
		if(ptr->key == key)     //ptr�� Ű���� �Է¹��� Ű���� ���ٸ�
			return ptr;         //ptr�� ����

		if(ptr->key < key) ptr = ptr->right;    //ptr�� Ű���� �Է¹��� Ű������ �۴ٸ� ptr�� ptr�� ������ �ڽĳ�尡 ��
		else                    //ptr�� Ű���� �Է¹��� Ű������ ũ�ٸ�
			ptr = ptr->left;    //ptr�� ptr�� ���� �ڽĳ�尡 ��
	}

	return NULL;        //ptr�� NULL�̸� NULL����
}

void freeNode(Node* ptr)
{
	if(ptr) {       //ptr�� NULL�� �ƴϸ�
		freeNode(ptr->left);        //ptr�� ���� �ڽĳ�忡 �Ҵ�� �޸� ����(��� ȣ��)
		freeNode(ptr->right);       //ptr�� ������ �ڽĳ�忡 �Ҵ�� �޸� ����(��� ȣ��)
		free(ptr);      //ptr�� �Ҵ�� �޸� ����
	}
}

int freeBST(Node* head)
{

	if(head->left == NULL)  //root�� NULL�̸�(root�� ��尡 ���ٸ�)
	{
		free(head);         //head��忡 �Ҵ�� �޸� ����
		return 1;           //�Լ� ����
	}

	Node* p = head->left;   //p�� root

	freeNode(p);    //root�� ��� �ڽ� ��忡 �Ҵ�� �޸� ����

	free(head);     //head��忡 �Ҵ�� �޸� ����
	return 1;
}