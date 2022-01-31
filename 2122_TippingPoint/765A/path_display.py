import PIL 
from PIL import Image, ImageDraw
import matplotlib
# import re 

# function = input("Enter function name: ")

functiontext = ""

with open("src/main.cpp", "r+") as texthandle:
    file = ""
    for line in texthandle:
        file += line
    # searchstring = "void " + function + "(.*)\}void"
    searchstring = "void leftskills"
    match = file.index("leftskills")
    match2 = file.index("void rightrings")
    function = file[match + 15:match2-4]
    function = function.replace(" ", "")
    # function = function.replace("\n", "")
    # print(function)
    commands = function.split("\n")
    movements = []
    for command in commands:
        command = command.strip()
        if command.startswith("distanceMove") or command.startswith("dragTurn") or command.startswith("moveTank"):
            movements.append(command)
    for movement in movements:
        print(movement)
    
    #635 width for 12 ft
    #52.9 px / ft and 4.4 px / inch
    #starting position = (85, 85)
    base_image = Image.open("skills_field.PNG")
    drawing = ImageDraw.Draw(base_image)
    drawing.ellipse([(70,70),(100,100)], "black", "black")
    currentheading = 
    for movement in movements:
        if movement.startswith("distanceMove"):

    base_image.show()