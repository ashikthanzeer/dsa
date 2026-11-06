class Stack:
    def __init__(self):
        self.stack = []
    def isempty(self):
        return self.stack==[]
    def push(self,v):
        self.stack.append(v)
    def pop(self):
        if self.isempty():
            return None
        else:
            return self.stack.pop()
    def display(self):
        for elem in self.stack:
            print(elem,end=' ')

S=Stack()
S.push(10)
S.push(20)
S.push(30)
S.pop()
S.push(40)
S.display()