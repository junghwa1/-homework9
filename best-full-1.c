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

typedef struct node {		//노드 구조체
	int key;				//키값
	struct node *left;		//왼쪽 자식 노드
	struct node *right;		//오른쪽 자식 노드
} Node;

int initializeBST(Node** h);		//이원 탐색 트리 생성

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */				//중위 순회 키값 출력
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */			//전위 순회 키값 출력
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */			//후위 순회 키값 출력
int insert(Node* head, int key);  /* insert a node to the tree */					//노드 삽입
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */	//리프노드 삭제
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */		//순환적 탐색
Node* searchIterative(Node* head, int key);  /* search the node for the key */		//반복적 탐색
int freeBST(Node* head); /* free all memories allocated to the tree */				//트리에 전체에 할당된 메모리 해제
void freeNode(Node* ptr);	//노드와 그 자식 노드들에 할당된 메모리 해제(프로그램 종료시를 제외 하고 사용될때 자식노드들은 NULL이다)
/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;	//head노드 생성
	Node* ptr = NULL;	/* temp */
	printf("[----- [염중화] [2019038062] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");		//메뉴출력
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");	
		scanf(" %c", &command);		//메뉴 선택

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);	//트리 생성
			break;
		case 'q': case 'Q':
			freeBST(head);			//트리에 할당된 메모리 해제
			break;
		case 'n': case 'N':
			printf("Your Key = ");	//노드 삽입
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");	//입력하는 key값과 같은노드 삭제
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':			//반복적 탐색
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':			//순환적 탐색
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':			//중위 순회 키값 출력
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':			//전위 순회	키값 출력
			preorderTraversal(head->left);
			break;
		case 't': case 'T':			//후위 선회 키값 출력
			postorderTraversal(head->left);
			break;
		default:					//메뉴 이외의 다른 값 입력 시 에러문구 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');		//q나 Q를 입력받으면 반복문 종료

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)      //tree가 생성되어 있다면
		freeBST(*h);    //할당된 메모리 해제

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));   //트리의 head 동적메모리 할당
	(*h)->left = NULL;	/* root */      //트리의 head의 left는 root
	(*h)->right = *h;       //트리의 head의 right는 자기 자신을 가리킴
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)		//중위 순회
{
	if(ptr) {		//ptr이 NULL이 아니라면 반복
		inorderTraversal(ptr->left);	//ptr의 왼쪽 자식노드 중위 순회
		printf(" [%d] ", ptr->key);		//ptr의 키값 출력
		inorderTraversal(ptr->right);	//ptr의 오른쪽 자식노드 중위 순회
	}
}

void preorderTraversal(Node* ptr)		//전위 순회
{
	if(ptr) {		//ptr이 NULL이 아니라면 반복
		printf(" [%d] ", ptr->key);		//ptr의 키값 출력
		preorderTraversal(ptr->left);	//ptr의 왼쪽 자식노드 전위 순회
		preorderTraversal(ptr->right);	//ptr의 오른쪽 자식노드 전위 순회
	}
}

void postorderTraversal(Node* ptr)		//후위순회
{
	if(ptr) {
		postorderTraversal(ptr->left);	//ptr의 왼쪽 자식노드 후위 순회
		postorderTraversal(ptr->right);	//ptr의 오른쪽 자식노드 후위 순회
		printf(" [%d] ", ptr->key);		//ptr의 키값 출력
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));        //새로운 노드 동적 메모리할당
	newNode->key = key;             //새로운 노드에 입력받은 키값 저장
	newNode->left = NULL;           //새로운 노드의 자식 노드는 아직 없음
	newNode->right = NULL;

	if (head->left == NULL) {       //트리의 노드가 없다면
		head->left = newNode;       //root는 새로운 노드
		return 1;       //함수 종료
	}

	/* head->left is the root */
	Node* ptr = head->left;     //ptr은 root

	Node* parentNode = NULL;    //부모노드를 저장할 구조체생성
	while(ptr != NULL) {    //부모노드가 없다면 반복 종료

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;   //키값이 같다면 함수 종료

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;   //ptr은 부모노드가 됨

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)      //ptr의 키값이 새로운 노드의 키값보다 작다면
			ptr = ptr->right;   //ptr은 오른쪽 노드가 됨
		else                    //ptr의 키값이 새로운 노드의 키값보다 크다면
			ptr = ptr->left;    //ptr은 왼쪽 노드가 됨
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)           //부모노드의 키값이 새로운 노드의 키값보다 클 때
		parentNode->left = newNode;     //부모노드의 left는 새로운 노드를 가리킴
	else                                //부모노드의 키값이 새로운 노드의 키값보다 작거나 같을때
		parentNode->right = newNode;    //부모노드의 right는 새로운 노드를 가리킴
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {                 //리스트가 생성이 되지 않았으면
		printf("\n Nothing to delete!!\n");         //에러문구 출력
		return -1;      //함수 종료
	}

	if (head->left == NULL) {           //root가 없으면
		printf("\n Nothing to delete!!\n");         //에러문구 출력
		return -1;      //함수 종료
	}

	/* head->left is the root */
	Node* ptr = head->left;     //ptr은 root를 가리킴


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;    //부모노드를 저장할 구조체 생성

	while(ptr != NULL) {        //ptr이 NULL일때 반복 종료

		if(ptr->key == key) {   //ptr의 키값이 입력받은 키값과 같고
			if(ptr->left == NULL && ptr->right == NULL) {   //ptr의 자식노드가 없다면

				/* root node case */
				if(parentNode == head)      //부모노드가 head노드일때
					head->left = NULL;      //root는 NULL

				/* left node case or right case*/
				if(parentNode->left == ptr)     //부모노드의 left가 ptr일때
					parentNode->left = NULL;    //부모노드의 left를 NULL로 바꿔줌
				else                            //부모노드의 right가 ptr일때
					parentNode->right = NULL;   //부모노드의 right를 NULL로 바꿔줌

				free(ptr);      //ptr에 할당된 메모리 해제
			}
			else {      //ptr에 자식노드가 있다면
				printf("the node [%d] is not a leaf \n", ptr->key);     //에러문구 출력
			}
			return 1;   //함수종료
		}

		/* keep the parent node */
		parentNode = ptr;       //부모노드는 ptr이 됨

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)      //ptr의 키값이 입력받은 키값보다 작다면
			ptr = ptr->right;   //ptr은 ptr의 오른쪽 자식 노드가 됨
		else                    //ptr의 키값이 입력받은 키값보다 크거나 같다면
			ptr = ptr->left;    //ptr은 ptr의 왼쪽 자식 노드가 됨


	}

	printf("Cannot find the node for key [%d]\n ", key);        //삭제할 노드를 찾지 못했을경우 출력

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)     //ptr이 NULL이면
		return NULL;    //NULL리턴

	if(ptr->key < key)  //ptr의 키값이 입력받은 키값보다 작다면
		ptr = searchRecursive(ptr->right, key); //searchRecursive()함수 재귀호출 (ptr의 오른쪽 자식노드를 인자로 호출)
	else if(ptr->key > key) //ptr의 키값이 입력받은 키값보다 크다면
		ptr = searchRecursive(ptr->left, key);  //searchRecursive()함수 재귀호출(ptr의 왼쪽 자식노드를 인자로 호출)

	/* if ptr->key == key */
	return ptr;         //ptr의 키값과 입력받은 키값이 같다면 ptr을 리턴

}
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;     //ptr은 root

	while(ptr != NULL)          //ptr이 NULL이면 반복 종료
	{
		if(ptr->key == key)     //ptr의 키값과 입력받은 키값이 같다면
			return ptr;         //ptr을 리턴

		if(ptr->key < key) ptr = ptr->right;    //ptr의 키값이 입력받은 키값보다 작다면 ptr은 ptr의 오른쪽 자식노드가 됨
		else                    //ptr의 키값이 입력받은 키값보다 크다면
			ptr = ptr->left;    //ptr은 ptr의 왼쪽 자식노드가 됨
	}

	return NULL;        //ptr이 NULL이면 NULL리턴
}

void freeNode(Node* ptr)
{
	if(ptr) {       //ptr이 NULL이 아니면
		freeNode(ptr->left);        //ptr의 왼쪽 자식노드에 할당된 메모리 해제(재귀 호출)
		freeNode(ptr->right);       //ptr의 오른쪽 자식노드에 할당된 메모리 해제(재귀 호출)
		free(ptr);      //ptr에 할당된 메모리 해제
	}
}

int freeBST(Node* head)
{

	if(head->left == NULL)  //root가 NULL이면(root에 노드가 없다면)
	{
		free(head);         //head노드에 할당된 메모리 해제
		return 1;           //함수 종료
	}

	Node* p = head->left;   //p는 root

	freeNode(p);    //root와 모든 자식 노드에 할당된 메모리 해제

	free(head);     //head노드에 할당된 메모리 해제
	return 1;
}