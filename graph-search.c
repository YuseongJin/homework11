/* graph */

//필요한 헤더 파일 
#include <stdio.h>
#include <stdlib.h>

//구조체 선언, graph
typedef struct graph {
	int vertex;//int 형 변수 vertex 멤버 선언
	struct graph *link;//자기참조 구조체, Adjacent List
} Graph;//구조체 별칭, graph

//for stack(DFS)
#define MAX_STACK_SIZE	10	
//최대 Vertex의 수는 10개
Graph* stack[MAX_STACK_SIZE];
int top = -1;

Graph* pop();
void push(Graph* aNode);

//for queue(BFS)
#define MAX_QUEUE_SIZE	10 
//최대 Vertex의 수는 10개
Graph* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Graph* deQueue();
void enQueue(Graph* aNode);

//함수 원형 선언
int initializeGraph(Graph** h);
int freeGraph(Graph* h);
int InsertVertex(Graph* h,int);
int InsertEdge(Graph* h,int, int);
void DFS(Graph* h, int);
void BFS(Graph* h, int);
void PrintGraph(Graph* h);
void freeVertex(Graph *ptr);


int main()//메인함수
{
	char command;//char형 변수 선언, 명령어
	int v1,v2;//int형 변수 선언, v1, v2(edge)
    Graph* head=NULL;//graph head NULL로 초기화

	printf("[----- [Yuseong Jin] [2018038022] -----]");//이름, 학번 출력
	do{//do-while문을 통하여 반복 출력
		//메뉴출력
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                         Graph search                           \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph       = z                                     \n");
		printf(" Insert Vertex          = v      Insert Edge                = e \n");
		printf(" Depth First Search     = d      Breath First Search        = b \n");
		printf(" Print Graph            = p      Quit                       = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);
		//명령어 입력받기

		switch(command) {//스위치문
		//소문자와 대문자 모두 입력 받기
		case 'z': case 'Z'://z키를 입력 받았을 때
			initializeGraph(&head);
			//initializeGraph함수 실행
			break;//멈춤

        case 'q': case 'Q'://q키를 입력 받았을 때
			freeGraph(head);
			//freeGraph함수 실행
			break;//멈춤
        
        case 'v': case 'V'://v키를 입력 받았을 때
            printf("Your Key = ");
            scanf("%d",&v1);
			//키 값 입력받기
			InsertVertex(head,v1);
			//InsertVertex함수 실행
			break;//멈춤

        case 'e': case 'E'://e키를 입력 받았을 때
            printf("Your Key (v1) = ");
            scanf("%d",&v1);
            printf("Your Key (v2) = ");
            scanf("%d",&v2);
			//키 값 입력받기
			InsertEdge(head,v1,v2);
			//InsertEdge함수 실행
			break;//멈춤

        case 'd': case 'D'://d키를 입력 받았을 때
			printf("Your Key = ");
            scanf("%d",&v1);
			//키 값 입력받기
			DFS(head, v1);//DFS함수 실행
			break;//멈춤

        case 'b': case 'B'://b키를 입력 받았을 때
			printf("Your Key = ");
            scanf("%d",&v1);
			//키 값 입력받기
			BFS(head, v1);//BFS함수 실행
			break;//멈춤

        case 'p': case 'P'://p키를 입력 받았을 때
			PrintGraph(head);//PrintGraph함수 실행
			break;//멈춤
		
		default://이외의 입력 받았을 때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			//경고문 출력
			break;//멈춤
		}

	}while(command != 'q' && command != 'Q');
	//q키를 사용하기 전까지 계속 반복

	return 0;//종료
}

int initializeGraph(Graph** h){	//graph 초기화 함수
    //graph가 비어 있지 않다면 메모리 할당 해제
	if(*h!=NULL)//
        freeGraph(*h);

    *h=(Graph*)malloc(sizeof(Graph)*10);
	//10개의 헤더노드를 나타낼 배열 메모리 할당
    for(int i=0;i<10;i++){
	//for문을 활용하여 0~9까지 순차적으로 대입
        (*h+i)->link=NULL; 
        (*h+i)->vertex=-1;	//각 헤더노드의 vertex를 -1으로 초기화
    }

    top=-1;//top에 -1을 대입
    front = rear = -1;//-1을 앞과 뒤에 순차적으로 대입

    return 1;//종료
}

void freeVertex(Graph *ptr){//vertex 메모리 할당해제 함수
//link를 이동하면서 메모리 할당 해제
    if(ptr){
        freeVertex(ptr->link);
        free(ptr);
    }
}

int freeGraph(Graph* h){//graph 메모리 할당해제 함수
    for(int i=0;i<10;i++){//0-9
        if((h+i)->link){//헤더노드에 link가 존재한다면 
           freeVertex((h+i)->link);//연결된 모든 메모리 해제
        }
    }

    free(h);//헤더노드 동적할당 배열 메모리 해제
    return 0;//종료
}

int InsertVertex(Graph* h,int v1){//vertex 삽입 함수
   if((h+v1)->vertex==v1){	//해당 vertex가 이미 존재한다면
	   printf("\n key is already in graph\n");//이미 key값이 존재함을 출력
	   return 0;//종료
   }
   (h+v1)->vertex = v1;
   //헤더노드 vertex 값을 해당 vertex 값으로 초기화

   return 1;//종료
}

int InsertEdge(Graph* h,int v1, int v2){//edge 삽입 함수
	if((h+v1)->vertex==-1||(h+v2)->vertex==-1){	
	//해당 vertex가 존재하지 않는다면
		printf("\n key is not in graph \n");
		//key값이 graph에 없음을 출력
		return 0;//종료
	}


	Graph* temp1 =(Graph*)malloc(sizeof(Graph));//temp1 동적메모리할당
	Graph* temp2 =(Graph*)malloc(sizeof(Graph));//temp2 동적메모리할당
	Graph* p=(h+v1);//헤드노드의 해당되는 인덱스와 연결

	temp1->vertex=v1;
	temp1->link=NULL;
	temp2->vertex=v2;
	temp2->link=NULL;
	//메모리 연결

	while(1){//반복
		if(p->vertex==v2){// 이미 연결되어있다면
			printf("\n Edge already exist \n");
			//edge가 이미 존재함을 출력
			return 0;//종료
		}

		if(!p->link){	//가리키는 노드가 없다면 연결
			p->link=temp2;	//v1 이 v2 를 가리킴
			break;//멈춤
		}

		if(p->link->vertex > v2){
		//인접리스트를 vertex 크기 순으로 정렬
			temp2->link=p->link;
			p->link=temp2;
			break;//멈춤
		}

		else p=p->link;	// 다음 노드가 존재한다면 이동
	}

	p=(h+v2);
	while(1){
		if(!p->link){ 
		//가리키는 노드가 없다면 연결
			p->link=temp1;	//v2 가 v1을 가리킴
			break;//멈춤
		}
		if(p->link->vertex > v1){ 
		//인접리스트를 vertex 크기 순으로 정렬
			temp1->link=p->link;
			p->link=temp1;
			break;//멈춤
		}
		else p=p->link;
	}

	return 0;//종료
}

void DFS(Graph* h,int v){//Depth First Search
	if((h+v)->vertex==-1){
		printf("\n key is not in graph \n");
		//graph에 key값이 없음을 출력
		return ;//종료
	}
	Graph* p = h+v;	//그래프를 가리키는 포인터
	Graph* ptr = NULL;	//stack 의 pop을 받을 ptr

	int visited[10]; for(int i=0;i<10;i++){visited[i]=0;}	
	//visit flag  0으로 초기화(0-9)
	top = -1;	//stack top 초기화

	while(1){//반복
		
		v=p->vertex;//헤더노드의 vertex를 받는다.

		if(!visited[v]){//vertex에 방문하지 않았다면
			printf("  [%d]  ",v);//출력
			visited[v]=1;//방문flag
			push(h+v);//push
			p=h+v;//해당 값을 가진 헤더노드로 이동
		}
		else {//방문 했다면
			if(p->link==NULL){	//다음 노드가 존재하지 않는다면
				ptr=pop();		//pop
				p=h+(p->vertex);//헤더노드 이동
			}
			p=p->link;	//노드 이동
		}

		if(top==-1)	break;	//top이 -1이라면(stack이 비워지면) 반복문 끝
	}

}

void BFS(Graph* h, int v){//Breath First Search
	Graph* p=h+v;		//그래프를 가리킬 포인터
	
	if((h+v)->vertex==-1){//vertex가 -1이라면
		printf("\n key is not in graph \n");
		//graph에 key가 없음을 출력
		return ;//종료
	}

	int visited[10]; for(int i=0;i<10;i++){visited[i]=0;}
	//visit flag  0으로 초기화(0-9)
	rear=front=-1;//앞과 뒤에 순차적으로-1대입

	printf("  [%d]  ",v);//출력
	visited[v]=1;//방문 flag
	enQueue(p);//enQueue

	while(1){//반복
		p=deQueue();//deQueue
		for(p;p;p=p->link){
			v=p->vertex;//헤더노드의 vertex를 받음
			if(!visited[v]){//미방문 vertex
				printf("  [%d]  ",p->vertex);//출력
				enQueue(h+v);//enQueue
				visited[v]=1;//방문flag
			}
		}
		if(rear==front) break;
		//앞과 뒤가 같다면(비워졌을 때) 반복문 끝 
	}
}

void PrintGraph(Graph* h){//Graph 출력 함수, 인접리스트
	Graph* p=h;
	//graph 포인터형 변수 p 선언후 h의 값을 대입

	for(int i=0;i<10;i++){
	//for문을 사용하여, 10번 반복
		p=h+i;
		for(int j=0;j<10;j++){
			if(p->vertex!=-1){	
			//p->vertex가 -1 이 아니라면 vertex 출력
				printf(" [%d] ",(p->vertex));
			}
			//link를 통해 이동
			if(p->link){
				p=p->link;
			}
			else//이외
				break;//멈춤
		}
		printf("\n");//줄바꿈 문자 출력
	}
}

//stack: Last in First Out 방식

Graph* pop()//stack에서 값을 뺌
{
	if(top==-1)	return NULL;	
	//top값이 -1이라면 NULL을 반환
	else return stack[top--];
	//아니라면 top을 증감한 stack을 반환
}

void push(Graph* aNode)	//stack에 데이터를 넣음
{	if(top==MAX_STACK_SIZE-1) printf("stack is full\n");
	//top값이 9라면 스택이 가득 찼음을 출력
	else stack[++top]=aNode;	
	//아니라면 anode의 값을 top를 증감한 스택에 대입 후 반환
}

Graph* deQueue()//데이터 출력 함수
{
	if(front==rear)	return 0;//앞과 뒤가 같다면 종료
	else return queue[++front];	//아니라면 front를 증감한 큐를 반환
}

void enQueue(Graph* aNode)//데이터 입력함수
{
	if(rear==MAX_QUEUE_SIZE-1)	printf("queue is full\n");
	//뒤가 9와 같다면 큐가 다 찼음을 출력
	else queue[++rear]=aNode;
	//아니라면 anode의 값을 rear를 증감한 큐에 대입 후 반환
}