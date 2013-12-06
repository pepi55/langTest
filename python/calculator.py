#!/usr/bin/python

from math import *
from Fraction import *
from Ratio import *
from tkinter.ttk import *

import tkinter as tk

class Calculator(tk.Frame):
	def __init__(self, master = None):
		tk.Frame.__init__(self, master)
		self.pack()
		self.createWidgets()

	def createWidgets(self):
		self.EXIT = tk.Button(self, text = "QUIT", fg = "red", command = root.destroy)
		self.EXIT.pack(side = "bottom")

root = Tk()
calc = Calculator(master = root)

mainframe = ttk.Frame(root, padding = "3 3 12 12")

ratio1 = StringVar()
ratioAnsw = StringVar()

ratioEntry = ttk.Entry(mainframe, width = 7, textVar = ratio1)

root.title("Ratio convertion")

mainframe.grid(column = 0, row = 0, sticky = (N, W, E, S))
mainframe.columnconfigure(0, weight = 1)
mainframe.rowconfigure(0, weight = 1)

ratioEntry.grid(column = 2, row = 1, sticky = (W, E))

ttk.Label(mainframe, textvariable = ratioAnsw).grid(column = 2, row = 2, sticky = (W, E))
ttk.Button(mainframe, text = "Calculate", command = calculate).grid(column = 3, row = 3, sticky = W)

calc.mainloop()
