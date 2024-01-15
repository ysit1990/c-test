/*
 * @Author: ysit1990@gmail.com
 * @Date:   2014-01-13 14:07:29
 * @Desc:   使用二维数组实现存储字符串数据的环形队列
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义队列最大允许缓冲20个字符串 每个字符串允许最大大小500个字节
#define MAX_SIZE 4    // 测试，方案1判断队列的空和满 只能存3个字符串，方案2 可以存4个     
#define MAX_STRING_LENGTH 500

// 预先分配好内存空间，优点是不用每次重新分配，缺点是一直占用空间
typedef struct {
    char queue[MAX_SIZE][MAX_STRING_LENGTH];
    int front;  // 队列头
    int rear;   // 队列尾
    int count;  // 队列存储数据个数
} CircularQueue;

void initializeCircularQueue(CircularQueue* queue) {
    queue->front = 0;
    queue->rear = 0;
    queue->count = 0;
}

bool isFull(CircularQueue* queue) {
    //return (queue->rear + 1) % MAX_SIZE == queue->front;  // 浪费一个存储空间
    return queue->count == MAX_SIZE;
}

bool isEmpty(CircularQueue* queue) {
    // return queue->rear == queue->front;
    return queue->count == 0;
}

int queueLen(CircularQueue* queue) {
    // return (queue->rear - queue->front + MAX_SIZE) % MAX_SIZE;
    return queue->count;
}

// 字符串存入队列
void enqueue(CircularQueue* queue, const char* item) {
    if (isFull(queue)) {
        printf("Queue is full!\n");
        return;
    }
    
    if(strlen(item) >= MAX_STRING_LENGTH) {
        printf("item large then max string length, failed!!\n");
        return;    
    }
    
    // 拷贝数据到队列
    //strncpy(queue->queue[queue->rear], item, strlen(item));//MAX_STRING_LENGTH);
    strcpy(queue->queue[queue->rear], item);
    
    // 将rear 指针循环移动到下一个位置（超过尾巴的时候,将rear 指针循环移动到队列的开头位置）
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->count++;
}

void dequeue(CircularQueue* queue, char* item) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
   
    // 取出数据（或只返回指针，但除非马上使用否则有覆盖风险 还是建议拷贝数据的方式）
    //strncpy(item, queue->queue[queue->front], strlen(item));//MAX_STRING_LENGTH);
    strcpy(item, queue->queue[queue->front]);
    
    // 将front循环移动到下一个位置
    queue->front = (queue->front + 1) % MAX_SIZE;
    queue->count--;
}

int main() {
    // 初始化队列结构体
    CircularQueue queue;
    initializeCircularQueue(&queue);
   
    // 队列中插入字符串
    enqueue(&queue, "Hello");
    enqueue(&queue, "World");
    enqueue(&queue, "OpenAI");
    enqueue(&queue, "Chatbot");
    enqueue(&queue, "Example");   // full
    enqueue(&queue, "Overflow");  // full
    
    printf("queueLen: %d", queueLen(&queue));
    printf("-----------------\n");
    
    // 队列中取出字符串
    char item[MAX_STRING_LENGTH];
    dequeue(&queue, item);
    printf("%s\n", item); // Output: Hello
    memset(item, 0, sizeof(item));
    
    dequeue(&queue, item);
    printf("%s\n", item); // Output: World
    memset(item, 0, sizeof(item));
    
    dequeue(&queue, item);
    printf("%s\n", item); // Output: OpenAI
    memset(item, 0, sizeof(item));
    
    dequeue(&queue, item);
    printf("%s\n", item); // Output: Chatbot
    memset(item, 0, sizeof(item)); 
    
    // 后面队列已经空了 没数据了
    dequeue(&queue, item);  // empty
    printf("%s\n", item); 
    memset(item, 0, sizeof(item));
    
    dequeue(&queue, item); // empty
    memset(item, 0, sizeof(item));
    
    return 0;
}