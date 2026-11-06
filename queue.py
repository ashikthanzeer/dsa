class Queue:
    def __init__(self):
        self.queue=[]
    def isempty(self):
        return self.queue==[]
    def enqueue(self,v):
        self.queue.append(v)
    def dequeue(self):
        if self.isempty():
            return None
        else:
            return self.queue.pop(0)
    def display(self):
        if self.isempty():
            print("None")
        else:
            print(str(self.queue))

Q = Queue()
Q.enqueue(10)
Q.enqueue(20)
Q.enqueue(30)
Q.enqueue(40)
Q.dequeue()
Q.display()