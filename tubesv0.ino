#include <Arduino_FreeRTOS.h>

const int MAX_INT_QUEUE_SIZE = 10; // Sesuaikan ukuran berdasarkan kebutuhan Anda
const int MAX_CHAR_QUEUE_SIZE = 10;

String readString;

// Define a structure for the integer queue
struct IntQueue {
  int items[MAX_INT_QUEUE_SIZE];
  int front;
  int rear;
  int itemCount;
};

IntQueue intQueue; // Declare an integer queue structure

// Define a structure for the char queue
struct CharQueue {
  char items[MAX_CHAR_QUEUE_SIZE];
  int front;
  int rear;
  int itemCount;
};

CharQueue charQueue; // Declare a char queue structure

void setup() {
  Serial.begin(9600);
  Serial.println("Begin...");

  // Initialize the integer queue
  intQueue.front = 0;
  intQueue.rear = -1;
  intQueue.itemCount = 0;

  // Initialize the char queue
  charQueue.front = 0;
  charQueue.rear = -1;
  charQueue.itemCount = 0;
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    readString += c;
    delay(2);
  }

  if (readString.length() > 0) {
    Serial.println(readString);

    // Check if the input is an integer
    int n = readString.toInt();
    if (n != 0 || readString.charAt(0) == '0') {
      Serial.println(n);
      enqueueInt(n); // Store the integer in the integer queue
    } else {
      char charInput = readString.charAt(0);
      Serial.println(charInput);
      enqueueChar(charInput); // Store the char in the char queue
    }

    readString = "";

    // Additional actions with the queues can be performed here
    // For example, check the size of the queues or process the elements in the queues.

    // Print the contents of the queues
    Serial.print("Integer Queue Contents: ");
    printIntQueue();
    Serial.print("Char Queue Contents: ");
    printCharQueue();
  }
}

// Function to enqueue an integer item
void enqueueInt(int item) {
  if (intQueue.itemCount < MAX_INT_QUEUE_SIZE) {
    intQueue.rear = (intQueue.rear + 1) % MAX_INT_QUEUE_SIZE;
    intQueue.items[intQueue.rear] = item;
    intQueue.itemCount++;
  } else {
    // Handle the integer queue full condition
    Serial.println("Integer Queue is full. Removing the oldest item.");
    dequeueInt(); // Remove the oldest item before adding the new one
    enqueueInt(item);
  }
}

// Function to dequeue an integer item
void dequeueInt() {
  if (intQueue.itemCount > 0) {
    intQueue.front = (intQueue.front + 1) % MAX_INT_QUEUE_SIZE;
    intQueue.itemCount--;
  }
}

// Function to print the contents of the integer queue
void printIntQueue() {
  int index = intQueue.front;
  for (int i = 0; i < intQueue.itemCount; ++i) {
    Serial.print(intQueue.items[index]);
    Serial.print(" ");
    index = (index + 1) % MAX_INT_QUEUE_SIZE;
  }
  Serial.println();
}

// Function to enqueue a char item
void enqueueChar(char item) {
  if (charQueue.itemCount < MAX_CHAR_QUEUE_SIZE) {
    charQueue.rear = (charQueue.rear + 1) % MAX_CHAR_QUEUE_SIZE;
    charQueue.items[charQueue.rear] = item;
    charQueue.itemCount++;
  } else {
    // Handle the char queue full condition
    Serial.println("Char Queue is full. Removing the oldest item.");
    dequeueChar(); // Remove the oldest item before adding the new one
    enqueueChar(item);
  }
}

// Function to dequeue a char item
void dequeueChar() {
  if (charQueue.itemCount > 0) {
    charQueue.front = (charQueue.front + 1) % MAX_CHAR_QUEUE_SIZE;
    charQueue.itemCount--;
  }
}

// Function to print the contents of the char queue
void printCharQueue() {
  int index = charQueue.front;
  for (int i = 0; i < charQueue.itemCount; ++i) {
    Serial.print(charQueue.items[index]);
    Serial.print(" ");
    index = (index + 1) % MAX_CHAR_QUEUE_SIZE;
  }
  Serial.println();
}
