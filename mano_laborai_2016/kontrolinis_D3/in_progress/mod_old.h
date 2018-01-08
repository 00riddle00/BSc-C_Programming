
#define MAX_DATA 30

struct Stack {
  void* data[MAX_DATA];
  int size;
};  

// This function adds element to the end of the structure.
void push(struct Stack *s, void* value, int valueSize);

// This function removes element from the end of the structure.
void* pop(struct Stack *s);
//int pop(struct Stack *s);

