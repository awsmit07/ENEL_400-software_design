from tkinter import *

root = Tk()

myLabel = Label(root, text="hello world")
yourLabel = Label(root, text="your world")

myLabel.grid(row=0, column=0)
yourLabel.grid(row=0, column=1)

root.mainloop()