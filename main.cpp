#include <iostream>

using std::cout;
using std::endl;
using std::string;

// Lista duplamente encadeada

// Criando nova estrutura para um nó, para fazer lista duplamente encadeada
typedef struct Node
{
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

Node* createNode(int);
void insertFront(Node**, int);
void insertEnd(Node**, int);
void insertAfter(Node*, int);
void deleteNode(Node**, Node*);
void displayList(Node *);
void insertBefore(Node*, int);
void deleteNodeByValue(Node **, int);
Node* searchNodebyValue(Node**, int);

// Driver Code
int main()
{
    // Lista duplamente encadeada
    Node* head = nullptr;
    displayList(head);
    cout << "====================================" << endl;

    insertEnd(&head, 0);
    insertEnd(&head, 1);
    insertEnd(&head, 3);
    insertEnd(&head, 7);
    insertEnd(&head, 10);
    insertEnd(&head, 13);
    insertFront(&head, -1);
    displayList(head);
    cout << "====================================" << endl;

    insertAfter(head, 29);
    insertAfter(head->ptrNext->ptrNext, 30);
    displayList(head);
    cout << "====================================" << endl;

    insertBefore(head, -98);
    head = head->ptrPrev;
    insertBefore(head->ptrNext->ptrNext, 69);
    displayList(head);
    cout << "====================================" << endl;

    deleteNode(&head, head);
    displayList(head);
    cout << "====================================" << endl;

    Node* encontrado = searchNodebyValue(&head, 29);
    cout << encontrado << ": " << encontrado->iPayload << endl;
    Node* encontrado2 = searchNodebyValue(&encontrado, 10);
    deleteNode(&head, encontrado);
    displayList(head);
    cout << "====================================" << endl;

    deleteNodeByValue(&head, 30);
    displayList(head);
    cout << "====================================" << endl;
    return 0;
}

Node* createNode(int iPayload)
{
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->iPayload = iPayload;
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;

    return temp;
}

void displayList(Node* node)
{
    if (node == nullptr)
    {
        cout << "Lista vazia: Nao foi possivel realizar displayList" << endl;
        return;
    }

    if (node->ptrPrev != nullptr)
    {
        cout << "Meio da Lista: Nao foi possivel realizar displayList" << endl;
        return;
    }

    Node* temp = node;

    cout << "Payload: ";

    //Percorremos a lista até o fim (ptrNext do último é NULL)
    while (temp != nullptr)
    {
        cout << temp->iPayload << " ";
        temp = temp->ptrNext;
    }

    cout << endl;
}

void insertFront(Node** head, int iPayload)
{
    Node* newNode = createNode(iPayload);
	// newNode->ptrPrev = nullptr;

	if (*head != nullptr)
	{
		(*head)->ptrPrev = newNode;
		newNode->ptrNext = (*head);
		(*head) = newNode;
		return;
	}

	(*head) = newNode;

}

void insertEnd(Node** head, int iPayload)
{
    Node* newNode = createNode(iPayload);
    //newNode->ptrNext = nullptr;

    if (*head == nullptr)
    {
        //newNode->ptrPrev = nullptr;
        (*head) = newNode;
        return;
    }

    Node* temp = (*head);

    //Percorremos a lista até o fim (ptrNext do último é NULL)
    while (temp->ptrNext != nullptr) temp = temp->ptrNext;

    newNode->ptrPrev = temp; //newNode aponta para o fim da lista
    temp->ptrNext = newNode; //antigo último elemento aponta para o novo nó

}

void insertAfter(Node* ptrLocation, int iPayLoad)
{
	if (ptrLocation == nullptr)
	{
		cout << "Location é NULL" << endl;
	}

	Node* newNode = createNode(iPayLoad);

	// Corrigir nó a ser inserido
	newNode->ptrNext = ptrLocation->ptrNext;
	newNode->ptrPrev = ptrLocation;

	// Corrigir o ponto de inserção
	ptrLocation->ptrNext = newNode;

	if (newNode->ptrNext != nullptr) newNode->ptrNext->ptrPrev = newNode;
}

void deleteNode(Node** head, Node* ptrDelete)
{
	if (*head == nullptr || ptrDelete == nullptr)
	{
		cout << " Não foi possível remover." << endl;
		return;
	}

	// Caso o ptrDelete seja o primeiro elemento da lista
	if (*head == ptrDelete) (*head) = ptrDelete->ptrNext;

	// Se o ptrDelete não é o último nó
	if (ptrDelete->ptrNext != nullptr) ptrDelete->ptrNext->ptrPrev = ptrDelete->ptrPrev;

	// Se o ptrDelete não é o primeiro nó
	if (ptrDelete->ptrPrev != nullptr) ptrDelete->ptrPrev->ptrNext = ptrDelete->ptrNext;

	free(ptrDelete);
}

void insertBefore(Node* ptrLocation, int iPayload) {
    if (ptrLocation == nullptr)
	{
		cout << "Location é NULL" << endl;
	}

	Node* newNode = createNode(iPayload);

	// Corrigir nó a ser inserido
	newNode->ptrPrev = ptrLocation->ptrPrev;
	newNode->ptrNext = ptrLocation;

	// Corrigir o ponto de inserção
	ptrLocation->ptrPrev = newNode;

	if (newNode->ptrPrev != nullptr) newNode->ptrPrev->ptrNext = newNode;
}

void deleteNodeByValue(Node** head, int iPayload){
    if (*head == nullptr){
        cout << "Head é NULL" << endl;
        return;
    }
    if ((*head)->ptrPrev != nullptr){
        cout << "Meio da Lista: Nao foi possivel fazer a remoção" << endl;
        return;
    }
    Node* ptrResultado = searchNodebyValue(head, iPayload);
    if(ptrResultado == nullptr){
        cout << "Não tem esse valor na lista" << endl;
    } else {
        deleteNode(head, ptrResultado);
        cout << "Deletei" << endl;
    }
}

Node* searchNodebyValue(Node** head, int iPayload){
    if (*head == nullptr){
        cout << "Head é NULL" << endl;
        return nullptr;
    }
    if ((*head)->ptrPrev != nullptr){
        cout << "Meio da Lista: Nao foi possivel fazer a busca" << endl;
        return nullptr;
    }

    Node* temp = *head;
    while (temp != nullptr){
        if(temp->iPayload == iPayload){
            return temp;
        }
        temp = temp->ptrNext;
    }
    return nullptr;
}
