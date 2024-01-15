/*
 * @Author: ysit1990@gmail.com
 * @Date:   2014-01-13 14:07:29
 * @Desc:   预先分配队列个数并动态分配内存用于存储队列数据实现的字符串环形队列
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 4             // 队列最大数据个数
#define MAX_STRING_LENGTH 1000 // 为了安全起见限制允许存入队列的最大字符串长度1000，根据项目实际来设置

// 下面队列存入的字符串每次都是动态内存分配的,无需提前占用过多内存空间，但用完后需要注意释放内存
typedef struct {
    char* queue[MAX_SIZE];   // 存储字符串对应指针的数组
    int front;      // 队列头
    int rear;       // 队列尾
    int count;      // 队列存储数据个数
} CircularQueue;

void initializeCircularQueue(CircularQueue* queue) {
    queue->front = 0;
    queue->rear = 0;
    queue->count = 0;
}

bool isFull(CircularQueue* queue) {
    return queue->count == MAX_SIZE;
}

bool isEmpty(CircularQueue* queue) {
    return queue->count == 0;
}

int queueLen(CircularQueue* queue) {
    return queue->count;
}

// 字符串存入队列
void enqueue(CircularQueue* queue, const char* item) {
    if (isFull(queue)) {
        printf("Queue is full!\n");
        return;
    }
    
    if(strlen(item) >= MAX_STRING_LENGTH) {
        printf("item larger then max string length, enqueue failed!!\n");
        return;    
    }
    
    // 申请内存空间并存储队列数据
    char* newItem = (char*)malloc((strlen(item) + 1) * sizeof(char));
    strcpy(newItem, item);
    // 保存对应数据的指针
    queue->queue[queue->rear] = newItem;
    
    // 将rear 指针循环移动到下一个位置（超过尾巴的时候,将rear 指针循环移动到队列的开头位置）
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->count++;
}

// 读取数据到item对应的地址空间中
void dequeue(CircularQueue* queue, char* item) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    
    // 数据拷贝出去(不要简单的只是返回指针,否则释放后就无法访问了)
    strcpy(item, queue->queue[queue->front]);
    // 马上释放(回收)申请的内存空间
    free(queue->queue[queue->front]);
    queue->queue[queue->front] = NULL;
    
    // 将front循环移动到下一个位置
    queue->front = (queue->front + 1) % MAX_SIZE;
    queue->count--;
}

// 释放(回收)队列申请的所有内存空间
void freeCircularQueue(CircularQueue* queue) {
    // 释放（回收）队列中未释放的内存      
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("i: %d, ptr: %p\n", i, queue->queue[i]);   
        if (queue->queue[i] != NULL) {
            free(queue->queue[i]);
            queue->queue[i] = NULL;
        }
    }
}

int main() {
    // 初始化队列结构体
    CircularQueue queue;
    // 队列最大数据个数MAX_SIZE
    initializeCircularQueue(&queue);
    
    // 队列中插入字符串
    enqueue(&queue, "Hello");
    enqueue(&queue, "World");
    enqueue(&queue, "OpenAI");
    enqueue(&queue, "Chatbot");
    enqueue(&queue, "Example");
    enqueue(&queue, "Overflow");
    
    printf("queueLen: %d\n", queueLen(&queue));
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
    
    // 队列中故意留一个数据不消费
//    dequeue(&queue, item);
//    printf("%s\n", item); // Output: Chatbot
//    memset(item, 0, sizeof(item)); 
    
//    dequeue(&queue, item);
//    printf("%s\n", item); // Output: Example
//    memset(item, 0, sizeof(item));
    
//     dequeue(&queue, item); // Output: Queue is empty!
//     memset(item, 0, sizeof(item));
    
    printf("-----------------\n");
    freeCircularQueue(&queue);
    
    return 0;
}